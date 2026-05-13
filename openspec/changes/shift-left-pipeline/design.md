## Full Design

### Context

The Firebolt C++ SDK lives across 5+ sibling repos in a `firebolt-cpp/` workspace.
Today, the first real validation signal when adding a new API is manual inspection
on a physical SoC device (Gate 4). The intermediate gates — lint, generated unit
tests, client build — either don't exist in the workflow or are not wired together.
Additionally, several structural workspace bugs silently break tooling for new
contributors.

This design describes how to build and connect the full gate chain, fixing
foundations first, then adding gates from cheapest to most expensive.

---

### Architecture

```
OpenSpec session (firebolt-apis/)
        │
        │  Gate 0: Interview (/opsx:new-fb-api)
        │  Gate 1: Lint      (fb-gen --lint)            ← already wired
        ▼
   fb-gen (firebolt-sdk-gen/)
        │
        │  Gate 2: Generated unit tests
        │          emit tests → compile → run
        ▼
   build-stack.sh (firebolt-cpp/ workspace root)
        │
        │  Gate 3: Client build
        │          --change <name> → fb-gen regen → cmake rebuild
        ▼
   firebolt-dobby-testapp/
        │
        │  Gate 4: Device
        │          --emit gateway-probe → build-native/cross → iterate.sh
        ▼
   SoC / VM  (PLATFORM=soc|vm)
```

Gates 1–2 run automatically inside the AI session. Gates 3–4 are offered
explicitly after the prior gate passes.

---

### Phase 0: Workspace foundations

**Problem:** Five tools independently hardcode sibling repo paths. One expected
file is missing. No tool validates the workspace before running.

**Design:**

`workspace.manifest.yaml` is a new file at the workspace root. It is the
single source of truth for required sibling repos:

```yaml
workspace: firebolt-cpp
repos:
  - name: firebolt-apis
    path: firebolt-apis
    remote: git@github.com:rdkcentral/firebolt-apis.git
  - name: firebolt-sdk-gen
    path: firebolt-sdk-gen
    remote: <url>
  - name: firebolt-cpp-client
    path: firebolt-cpp-client
    remote: <url>
  - name: firebolt-entos-runtime-apis
    path: firebolt-entos-runtime-apis
    remote: <url>
  - name: firebolt-cpp-transport
    path: firebolt-cpp-transport
    remote: <url>
  - name: firebolt-dobby-testapp
    path: firebolt-dobby-testapp
    remote: <url>
  - name: firebolt-js-client
    path: firebolt-js-client
    remote: git@github.com:rdkcentral/firebolt-js-client.git
    note: "Required by rdke.profile.yaml openrpc-upstream layer (non-graduated modules)"
```

`check-workspace.sh` reads this manifest and emits:
```
✓ firebolt-apis         (present)
✓ firebolt-sdk-gen      (present)
✗ firebolt-js-client    MISSING
  → git clone git@github.com:rdkcentral/firebolt-js-client.git
```
Exits non-zero if any required repo is missing. Called at the top of
`build-stack.sh` and `fb-conformance/run.py`.

`firebolt-cpp-client/firebolt-cpp-client.profile.yaml` is added as a symlink
to `../firebolt-apis/openspec/rdke.profile.yaml`. This fixes the broken
`fb-conformance/run.py` full profile path without changing the profile itself.

---

### Phase 1: Gate 2 — Event tests

**Problem:** `fb-testgen::derive_test_cases()` returns empty for `MethodKind::Event`
and `MethodKind::Provider`. Event methods are the most common source of silent
on-device failure.

**Design — Part A (registration smoke):**

Extend `derive_test_cases()` with an `Event` arm:

```rust
MethodKind::Event => vec![TestCase {
    label: format!("{}_registration", method.name),
    args: vec![],  // no args — lambda is injected by emit_tests.rs
    oracle: Oracle::ok_and_called(Some(json!({
        "listen": true
    }))),
}],
```

`emit_tests.rs` renders this as:
```cpp
void network_onConnectedChanged_registration() {
    MockHelper mock;
    NetworkImpl impl(mock);
    bool fired = false;
    auto id = impl.subscribeOnConnectedChanged([&](bool) { fired = true; });
    CHECK(id.has_value());
    CHECK(mock.was_called);
    CHECK(mock.last_call.rpc == "Network.onConnectedChanged");
}
```

**Design — Part B (dispatch):**

Add `fireEvent(rpc, json)` to `MockHelper`. It routes the payload through the
`SubscriptionManager` by looking up the registered callback for that RPC name
and invoking it with the deserialized value:

```cpp
void fireEvent(const std::string& rpc, const nlohmann::json& payload) {
    subscriptionManager_.dispatch(rpc, payload);
}
```

`SubscriptionManager::dispatch` must be added (or exposed) as a test-only method.
The generated dispatch test:

```cpp
void network_onConnectedChanged_dispatch() {
    MockHelper mock;
    NetworkImpl impl(mock);
    bool fired = false; bool val = true;
    impl.subscribeOnConnectedChanged([&](bool v) { fired = true; val = v; });
    mock.fireEvent("Network.onConnectedChanged", {{"value", false}});
    CHECK(fired);
    CHECK(val == false);
}
```

The `value` key in the injected JSON matches the spec example value for the
event's result schema. This value comes from the IR's `examples` field.

---

### Phase 2: Provider implementation

**Problem:** `emit.rs` emits `// TODO: wire up provider` for every `MethodKind::Provider`.
Providers are non-functional in the generated client.

**Design:**

Provider pattern: the platform sends `Module.onRequestFoo` with a `correlationId`.
The client must respond with `Module.onRequestFoo.response`.

Generated implementation:

```cpp
void KeyboardImpl::registerStandardProvider(
    std::function<Standard(const std::string& correlationId)> handler)
{
    subscriptionManager_.subscribe<JsonData::KeyboardStandardRequest>(
        "Keyboard.onRequestStandard",
        [this, handler](const KeyboardStandardRequest& req) {
            auto result = handler(req.correlationId);
            // serialize result and send response
            helper_.set("Keyboard.onRequestStandard.response",
                        JsonData::Standard::toJson(result, req.correlationId));
        }
    );
}
```

The response RPC name convention is `<Module.onRequestFoo>.response` (confirmed
from Firebolt protocol spec). The `correlationId` is threaded through from the
request struct.

Gate 2 smoke test (compile-only for now):
```cpp
void keyboard_registerStandardProvider_smoke() {
    MockHelper mock;
    KeyboardImpl impl(mock);
    impl.registerStandardProvider([](const std::string&) {
        return Firebolt::Keyboard::Standard{};
    });
    // no assert needed — compile proves signature correctness
    ++g_tests_run;
}
```

Full dispatch testing (bidirectional mock) is deferred to a follow-on change.

---

### Phase 3: Gate 3 — build-stack orchestration

**Problem:** `build-stack.sh` rebuilds everything unconditionally. No awareness of
which modules changed.

**Design:**

`build-stack.sh --change <name>` reads `openspec/changes/<name>/proposal.md`
(or a new `openspec/changes/<name>/.modules` file listing affected modules) and
runs:

```bash
fb-gen --profile openspec/rdke.profile.yaml \
       --lang cpp \
       --modules <module1>,<module2> \
       --output ../firebolt-cpp-client/gen/
```

before the cmake incremental rebuild. cmake's dependency tracking handles
the rest — only translation units touching the regenerated headers recompile.

The `.modules` file is written by the AI during the apply step:
```
# openspec/changes/display-refresh-rate/.modules
display
```

If `--change` is not given, `build-stack.sh` behaves as today (full regen).

---

### Phase 4: Gate 4 — gateway probe

**Problem:** No generated test app exists. The `firebolt-dobby-testapp` `main.cpp`
is hand-written and only covers a fixed subset of APIs.

**Design:**

`fb-gen --emit gateway-probe --profile <profile> --output <dir>` generates
`main.cpp` that:

1. Connects to the gateway (`FIREBOLT_URL` or `--url`)
2. For every getter in the profile: calls it, prints `[PASS] Module.method: <value>`
   or `[FAIL] Module.method: error <N>`
3. For every event: registers a callback, prints `[REG] Module.onFoo: ok` or
   `[FAIL] Module.onFoo: error <N>`
4. Prints a summary: `N/M passed`
5. Exits 0 if all pass, 1 if any fail

Output goes to `firebolt-dobby-testapp/generated/main.cpp`. `build-native.sh`
and `build-cross.sh` check for `generated/main.cpp` and use it if present,
falling back to `app/main.cpp` otherwise. The `generated/` directory is
git-ignored.

---

### Phase 5: Skill wiring

The `openspec-apply-change` skill gains a post-lint section:

```
After lint passes:
1. Run: fb-gen --emit tests --profile rdke --modules <changed> --output /tmp/gate2/
2. Compile: g++ -std=c++17 ... /tmp/gate2/src/<module>_test.cpp -o /tmp/gate2/test
3. Run: /tmp/gate2/test
   → If fail: AI reads stderr, diagnoses spec issue, proposes fix, re-lints
   → If pass: surface to user "Gate 2 passed (N tests)"

4. Offer Gate 3: "Build the C++ client? (~2 min)"
   → On confirm: build-stack.sh --change <name>
   → Stream output; report pass/fail

5. Offer Gate 4: "Deploy to device?"
   → Prompt for PLATFORM, FIREBOLT_URL, SOC_HOST if not set
   → fb-gen --emit gateway-probe → build-native/cross → iterate.sh
   → Stream output
```

The AI never proceeds to Gate 3 or 4 without explicit user confirmation.

---

### Key Decisions

| Decision | Choice | Rationale |
|---|---|---|
| Profile yaml location | Symlink in firebolt-cpp-client | Zero drift; single source of truth stays in firebolt-apis |
| Manifest format | YAML at workspace root | Human-readable, parseable by check-workspace.sh and CI |
| Event dispatch injector | `SubscriptionManager::dispatch()` test-only method | Avoids coupling MockHelper to internal transport details |
| Provider response RPC | `Module.onRequestFoo.response` | Firebolt protocol convention |
| gateway-probe output | `generated/` subdir, git-ignored | Keeps testapp repo clean; no generated code committed |
| Gate 3 module list | `.modules` file written by AI | Machine-readable, avoids parsing proposal.md |

---

### Risks

| Risk | Likelihood | Mitigation |
|---|---|---|
| `SubscriptionManager::dispatch()` not safe to expose | Low | Add `#ifdef FIREBOLT_TESTING` guard |
| Provider response RPC name convention wrong | Medium | Verify against Firebolt protocol docs before implementing 2.1 |
| `fireEvent()` deserialization differs per type | Low | Use same `JsonType::fromJson()` path as production code |
| entos Gate 4 path undefined | Known | Tracked as 4.6; blocked on entos testapp creation |
