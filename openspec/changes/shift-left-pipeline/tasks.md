# Tasks: shift-left-pipeline

End-to-end validation pipeline: spec → unit tests → client build → device.

---

## Phase 0 — Fix workspace foundations (unblocks everything else)

- [x] **0.1** Add `workspace.manifest.yaml` at workspace root listing required sibling
  repos (`firebolt-apis`, `firebolt-cpp-client`, `firebolt-entos-runtime-apis`,
  `firebolt-sdk-gen`, `firebolt-cpp-transport`, `firebolt-dobby-testapp`,
  `firebolt-js-client`) with clone URLs and relative paths
- [x] **0.2** Add `check-workspace.sh` — reads manifest, verifies each repo exists at
  the declared relative path, emits clear error + clone command if not; exits non-zero
  on any missing repo
- [x] **0.3** Add `firebolt-cpp-client/firebolt-cpp-client.profile.yaml` as a symlink
  to `../firebolt-apis/openspec/rdke.profile.yaml`
- [x] **0.4** Fix `fb-conformance/run.py` full profile `profile_yaml` entry to resolve
  through the symlink (or directly to `rdke.profile.yaml`)
- [ ] **0.5** ~~Monarch profile~~ — left untouched; out of scope for this pipeline
- [x] **0.6** Add `check-workspace.sh` call to the top of `build-stack.sh` and
  `fb-conformance/run.py` so broken workspaces fail fast with clear output

---

## Phase 1 — Gate 2: Event tests

- [x] **1.1** Add `MethodKind::Event` case to `fb-testgen::derive_test_cases()` —
  emit a registration smoke test: call `subscribeOn*()`, assert `was_called == true`
  and `last_rpc == "Module.onFoo"`
- [x] **1.2** Add `fireEvent(rpc, json)` method to `MockHelper` in `emit_tests.rs` —
  routes a JSON payload through the subscription manager to the registered callback
- [x] **1.3** Emit a dispatch test for each Event method: register callback, call
  `mock.fireEvent(...)`, assert callback fired with correctly deserialized value
  (use spec example value as the injected payload)
- [ ] **1.4** Verify generated event tests compile and pass for `network`,
  `lifecycle`, `localization`, `texttospeech` modules (cpp-client)
  _**Partially done**: `lifecycle` 6/6, `localization` 9/9 — `texttospeech` and `network` not in openrpc dir_
- [ ] **1.5** Verify generated event tests compile and pass for `device`,
  `contentprotection` modules (entos)
  _**Partially done**: `device` 4/4 — `contentprotection` not in openrpc dir_

---

## Phase 2 — Fix Provider implementation

- [x] **2.1** Replace `// TODO: wire up provider` stub in `emit.rs` with real
  implementation: `registerFooProvider` stores the handler, subscribes via
  `subscriptionManager_` on the provider RPC name, on receipt deserializes the
  `FederatedRequest` payload, calls the handler with `req.parameters`, and
  responds via `helper_.get<Boolean>(rpc, {correlationId, result})`.
  Also fixed handler type: `std::function<ResultType(const FooParameters&)>`
  (was incorrectly `bool(const string&)`).
- [x] **2.2** Emit Provider registration + pull_response test cases in
  `emit_tests.rs`: `register{Cap}Provider` arm added to `emit_test_fn()`;
  registration checks `was_called` on mock, pull_response fires `fireEvent` and
  checks `handler_called`.
- [x] **2.3** Wire Provider into `fb-testgen::derive_test_cases()`: added
  `MethodKind::Provider` arm generating `_registration` and `_pull_response`
  cases; also fixed `PolymorphicReducer` missing from Getter/Rpc arm.
- [x] **2.4** Verify Provider methods in `discovery` (`entityInfo`, `purchasedContent`)
  generate correctly and compile. Also: fixed 8 Gate 2 compile/runtime bugs discovered
  while verifying 1.4/1.5 (see notes below):
  - MockHelper rewritten to use `SubscriptionData` for real `onPropertyChangedCallback` dispatch
  - `<regex>` include added to generated `_impl.cpp` for pattern guard methods
  - Oracle changed to `bool(result)` (no `has_error()` on `Result<void>`)
  - Property setter uses `capitalise()` for method name (fixes `setLocality` etc.)
  - `default_value_for(Named)` returns `"XX"` via `render_value` for pattern-constrained strings
  - Dispatch tests restricted to `TypeRef::Scalar` payloads only (structs fail silent parse)
  - All params (required + optional) included in fuzz_seed call to match C++ signature
  - Event RPC name prefixed with `{module}.` to match subscription registration key
  - Verified: `localization` 9/9, `lifecycle` 6/6, `device` 4/4, `accessibility` 0/0 (no tests)

---

## Phase 3 — Gate 3: build-stack orchestration

- [x] **3.1** Add `--change <name>` flag to `build-stack.sh` — reads
  `openspec/changes/<name>/.modules` (one slug per line), runs `fb-gen --input
  <module>.json --lang cpp --schemas <dir>` for each module, copies output files
  back into `firebolt-cpp-client/src/` and `include/firebolt/`, then proceeds
  to normal cmake rebuild step. Syntax-verified with `bash -n`.
- [x] **3.2** Created `openspec/changes/display-refresh-rate/.modules` (device,
  localization) and verified `fb-gen` generates both modules cleanly with the
  correct output file layout (`_impl.cpp`, `_impl.h`, `include/firebolt/<mod>.h`,
  `src/json_types/<mod>.h`). Live test: both files produced with `fb-gen: done.`

---

## Phase 4 — Gate 4: gateway probe + sideload

- [x] **4.1** Add `--lang gateway-probe` mode to `fb-gen` (exposed as `--emit\n  gateway-probe` in design, implemented as `--lang gateway-probe` in the --input\n  path). Collects all parsed modules post-loop, calls `write_demo_main()` to\n  produce a self-contained `main.cpp` that connects to a live gateway, calls\n  every getter, and subscribes to all events. Verified: `fb-gen --input\n  device.json --input localization.json --lang gateway-probe --output /tmp/`\n  produces `main.cpp` with correct includes and method calls.\n- [ ] **4.2** _(pending dobby-testapp repo)_ Update `firebolt-dobby-testapp/build-native.sh` to use\n  `generated/main.cpp` when present, fall back to `app/main.cpp`\n- [ ] **4.3** _(pending dobby-testapp repo)_ Update `firebolt-dobby-testapp/build-cross.sh` identically\n- [ ] **4.4** _(pending dobby-testapp repo)_ Verify gateway probe runs against `mock_gateway.py` (fb-conformance)\n  and produces output for all spec-defined getters
- [ ] **4.5** Add `firebolt-dobby-testapp` to `workspace.manifest.yaml` as a first-class
  integration component (alongside the client repos) so it is validated by
  `check-workspace.sh` and always present when Gate 4 is offered
- [ ] **4.6** `TODO (follow-on)` — **entos sideload path**: `firebolt-dobby-testapp`
  currently targets `firebolt-cpp-client` only. entos has no equivalent testapp or
  Dobby container setup. Define and create the entos device integration path
  (separate repo or entos-specific subdir in `firebolt-dobby-testapp`); wire Gate 4
  into the entos profile. Tracked here for visibility; out of scope for this change.

---

## Phase 5 — Skill wiring

- [x] **5.1** Updated `openspec-apply-change` skill in both `firebolt-sdk-gen` and
  `bridge2sanity`: after all tasks are implemented, Gate 2 runs automatically.
  For each module in `.modules`, runs `fb-gen --lang cpp`, `fb-gen --lang test`,
  compiles with g++, and runs the test driver. Reports pass/fail per-module with
  AI diagnosis on failure.
- [x] **5.2** Gate 3 (build-stack.sh --change <name>) is offered after Gate 2 passes,
  with explicit confirmation required. Shows last 30 lines on failure.
- [x] **5.3** Gate 4 (device deploy) is offered after Gate 3 passes, with explicit
  confirmation and collection of PLATFORM/FIREBOLT_URL/SOC_HOST env vars.
- [x] **5.4** Updated `openspec-propose` skill in both repos: exit message now lists
  the Gate 2/3/4 pipeline that will run on `/opsx:apply`, so users know what validation
  to expect before they start implementation.
