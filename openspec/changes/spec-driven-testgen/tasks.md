# Tasks: spec-driven-testgen

Implementation of spec-driven constraint enforcement and test suite generation.

## Overview and orientation

### Repos involved

| Repo | Purpose | Local path (assumed) |
|------|---------|----------------------|
| `firebolt-sdk-gen` | Rust toolchain — all code changes go here | `../firebolt-sdk-gen/` |
| `firebolt-apis` | Smithy specs and this change tracker | this repo |

**Sections 1–7** (IR, C++/Rust backends, fb-testgen crate, CLI): work in `firebolt-sdk-gen`.  
**Section 8** (Smithy trait parsing + spec annotation): split — parser in `firebolt-sdk-gen`, spec files in `firebolt-apis/src/smithy/`.  
**Section 9** (CI): touches both repos.

### Toolchain prerequisites

Two paths — pick one:

#### Path A: Docker (recommended for QA, zero local install)

```bash
# Requirements: Docker Desktop (or Docker Engine + docker compose)
# That's it. No Rust, no C++, no fb-gen needed locally.

# One-time image build (takes ~5 min, cached after that):
cd /path/to/firebolt-cpp   # the parent workspace containing both repos
docker compose -f docker-compose.testgen.yml build testgen

# Run the full definition-of-done smoke test:
docker compose -f docker-compose.testgen.yml run smoke

# Generate test files locally into ./out/:
docker compose -f docker-compose.testgen.yml run generate
ls out/tests/   # generated C++ test files appear here

# Compile-check all generated C++ tests:
docker compose -f docker-compose.testgen.yml run compile-check
```

#### Path B: Native (for SDK contributors making code changes)

```bash
# Rust toolchain (stable + nightly for fuzz)
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
rustup toolchain install stable nightly
cargo install cargo-fuzz   # optional, Phase 1 only needs stable

# fb-gen — build and install from source
cd ../firebolt-sdk-gen && cargo install --path crates/fb-gen

# C++ compile-check tooling
# Ubuntu/Debian:   sudo apt install cmake g++ libgtest-dev
# macOS:           brew install cmake googletest
cmake --version   # ≥3.18
g++ --version     # ≥9, C++17

# Node.js (only if generating JS test output)
node --version    # ≥18 required
```

### Definition of done (end-to-end smoke test)

#### Docker path (QA — one command)

```bash
cd /path/to/firebolt-cpp
docker compose -f docker-compose.testgen.yml run smoke
```

All 6 checks print `✓`. Any `✗` means the change is not complete.

#### Native path (SDK contributors)

When all tasks are complete, the following commands should all pass:

```bash
# 1. Baseline: dry-run composition still works
fb-gen --profile openspec/rdke.profile.yaml --dry-run

# 2. C++ bindings contain constraint guards
fb-gen --profile openspec/rdke.profile.yaml --lang cpp --emit bindings --output /tmp/gen-cpp/
grep "Error::InvalidParams" /tmp/gen-cpp/src/voiceguidance_impl.cpp    # must match

# 3. Rust bindings contain constrained newtypes
fb-gen --profile openspec/rdke.profile.yaml --lang rust --emit bindings --output /tmp/gen-rust/
grep "TryFrom" /tmp/gen-rust/voiceguidance.rs                          # must match

# 4. Test suite generates successfully
fb-gen --profile openspec/rdke.profile.yaml --lang test --output /tmp/gen-tests/
ls /tmp/gen-tests/voiceguidance_test.cpp                               # must exist

# 5. Generated tests compile (syntax check)
g++ -std=c++17 -fsyntax-only /tmp/gen-tests/voiceguidance_test.cpp \
    -I/tmp/gen-cpp/include                                             # must succeed

# 6. All existing sdk-gen tests still pass
cd ../firebolt-sdk-gen && cargo test
```

If all six pass, the change is shippable for Phase 1.

---

## 0. Prerequisites

- [ ] 0.1 Confirm `fb-gen --profile openspec/rdke.profile.yaml --dry-run` passes clean
  before starting (record baseline method count as reference)
  <!-- paste output here -->

---

## 1. Constraint propagation through the IR (D1)

- [ ] 1.1 Add `Constraints` struct to `crates/fb-ir/src/lib.rs`:
  `minimum`, `maximum`, `min_length`, `max_length`, `pattern`, `min_items`, `max_items`
  (all `Option<_>`, derive Debug/Clone/Default)
- [ ] 1.2 Add `pub constraints: Constraints` field to `TypeDef::Scalar` variants and to
  `Param` (default = `Constraints::default()` — all None — keeps existing callers compiling)
- [ ] 1.3 In `crates/fb-frontend/src/lower.rs`: read `minimum`, `maximum`, `minLength`,
  `maxLength`, `pattern`, `minItems`, `maxItems` from `Schema` and populate `Constraints`
  instead of discarding them
- [ ] 1.4 In `crates/fb-frontend/src/lower.rs`: when resolving a param whose type is a
  named typedef with constraints, copy those constraints onto the `Param`
- [ ] 1.5 **VERIFY** `cargo test -p fb-frontend` passes
  <!-- paste output here -->
- [ ] 1.6 **VERIFY** `cargo test -p fb-ir` passes
  <!-- paste output here -->

---

## 2. Constraint guards in generated C++ (D2)

- [ ] 2.1 In `crates/fb-backend-cpp/src/`: identify the setter and plain-call emit paths
  (the `helper_.set()` call site)
- [ ] 2.2 For each setter/call with a param carrying non-empty `Constraints`: emit a
  guard block before the `nlohmann::json params` construction:
  ```cpp
  if (value < {min}f || value > {max}f) {
      return Result<void>{Error::InvalidParams};
  }
  ```
  For string maxLength: `if (value.size() > {max_length}) { ... }`
  For array minItems: `if (value.size() < {min_items}) { ... }`
- [ ] 2.3 Emit nothing (no guard, no change) when `Constraints` is all-None
- [ ] 2.4 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --lang cpp --emit bindings --output /tmp/gen-cpp/`
  Check that `voiceguidance_impl.cpp` contains guard for `SpeechRate [0.1, 10.0]`
  Check that `closedcaptions_impl.cpp` contains guard for `Opacity [0, 100]`
  Check that `wifi_impl.cpp` contains guard for `Timeout [0, 9999]`
  <!-- paste output here -->
- [ ] 2.5 **VERIFY** compile check: `cmake /tmp/gen-cpp/ && make -C /tmp/gen-cpp/` (or
  the equivalent compile-check script) succeeds with no new errors
  <!-- paste output here -->
- [ ] 2.6 **VERIFY** binary size check: compare size of `voiceguidance_impl.o` before
  and after — delta should be <100 bytes
  <!-- paste output here -->

---

## 3. Constrained newtypes in generated Rust (D3)

- [ ] 3.1 In `crates/fb-backend-rust/src/`: identify scalar typedef emit path
- [ ] 3.2 For each scalar typedef with non-empty numeric constraints: emit a newtype
  struct + `TryFrom` implementation (see design.md D3 for template)
- [ ] 3.3 Ensure typedef with no constraints continues to emit as bare type alias
  (`pub type SomeType = f32;`)
- [ ] 3.4 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --lang rust --emit bindings --output /tmp/gen-rust/`
  Check that `voiceguidance.rs` contains `struct SpeechRate(f32)` + `TryFrom<f32>`
  <!-- paste output here -->
- [ ] 3.5 **VERIFY** `cargo build` on generated Rust output succeeds

---

## 4. `fb-testgen` crate — new (D4, D5)

- [ ] 4.1 Create `crates/fb-testgen/` with `Cargo.toml`, deps: `fb-ir`, `fb-compose`
- [ ] 4.2 Implement `TestCase` enum:
  ```rust
  enum TestCase {
      BoundaryNumeric { input, expected_status, expect_transport_called, expected_json_body },
      BoundaryEnum { variant, valid },
      BoundaryString { input, expected_status },
      BoundaryArray { len, expected_status },
      FuzzSeed(Vec<u8>),
  }
  ```
- [ ] 4.3 Implement `fn derive_test_cases(method: &Method) -> Vec<TestCase>`:
  - For each constrained param: derive the boundary case set (see spec.md)
  - For enum params: one passing case per variant + 3–4 failing cases
  - If no constraints: return empty vec
- [ ] 4.4 Implement `fn json_body_for(method: &Method, input: &TestInput) -> serde_json::Value`:
  derive expected JSON payload from `rpc_name` and param serialization rules in IR
- [ ] 4.5 Implement mock transport struct `MockTransport` (implements `IHelper` interface):
  records call count and last received JSON body; returns configurable `Result`
- [ ] 4.6 **VERIFY** `cargo test -p fb-testgen` passes on mock transport unit tests
  <!-- paste output here -->

---

## 5. C++ test emitter (D4)

- [ ] 5.1 Implement `fn emit_cpp_tests(module: &Module, cases: &[TestCase]) -> String`
  emitting a GTest file with `TEST(ModuleName, MethodName_CaseLabel)` entries
- [ ] 5.2 Test structure per case:
  - Instantiate module impl with `MockTransport`
  - Call method with test input
  - Assert result status (`.error() == Error::InvalidParams` or `.has_value()`)
  - Assert `mock.call_count()` (0 for reject, 1 for accept)
  - For accept: assert `mock.last_params()` matches expected JSON body
- [ ] 5.3 Emit fuzz seed `corpus/<module>_<method>/seed_N` binary files alongside test file
- [ ] 5.4 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --lang test --emit bindings --output /tmp/gen-tests/`
  Manually inspect `voiceguidance_test.cpp` — confirm test names and assertion bodies
  for `SetRate_AtMin`, `SetRate_BelowMin`, `SetRate_AtMax`, `SetRate_AboveMax`
  <!-- paste output here -->
- [ ] 5.5 **VERIFY** generated tests compile: `g++ -std=c++17 -fsyntax-only
  /tmp/gen-tests/voiceguidance_test.cpp -I/tmp/gen-cpp/include` (syntax check only)
  <!-- paste output here -->

---

## 6. Rust test emitter

- [ ] 6.1 Implement `fn emit_rust_tests(module: &Module, cases: &[TestCase]) -> String`
  emitting `#[test]` and `proptest!` blocks
- [ ] 6.2 Property-based tests for numeric ranges use `proptest` strategy:
  `in_range` strategy for valid range, `outside_range` strategy for rejection
  Both use fixed seed for deterministic CI runs
- [ ] 6.3 **VERIFY** generated Rust tests compile: `cargo build` on generated output
  <!-- paste output here -->

---

## 7. Wire `--lang test` into `fb-gen` CLI

- [ ] 7.1 Add `"test"` to the language enum in `crates/fb-gen/src/main.rs`
- [ ] 7.2 Route `--lang test` to `fb-testgen` emit path (same pattern as `--lang cpp`)
- [ ] 7.3 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --lang test --output /tmp/gen-tests/`
  runs to completion with `fb-gen (compose): done.`
  <!-- paste output here -->

---

## 8. Smithy `@range`, `@length`, `@pattern` trait parsing (Layer B)

> **Repo split**: parser changes (8.1–8.5) are in `firebolt-sdk-gen`.
> Spec annotation (8.6) is in `firebolt-apis/src/smithy/`.

- [ ] 8.1 In `../firebolt-sdk-gen/crates/fb-frontend-smithy/src/parse_idl.rs`:
  parse `@range(min: X, max: Y)` trait and populate `Constraints.minimum` / `Constraints.maximum`
- [ ] 8.2 Parse `@length(min: X, max: Y)` → `min_length` / `max_length`
- [ ] 8.3 Parse `@pattern("regex")` → `pattern`
- [ ] 8.4 In lowering: Smithy-sourced constraints take precedence over OpenRPC-sourced ones
- [ ] 8.5 Add lint rule: if Smithy and OpenRPC disagree on constraint bounds, emit a
  `LintLevel::Warning` with rule id `constraint-mismatch`
- [ ] 8.6 **VERIFY** (in `firebolt-apis` repo): add `@range(min: 0, max: 9999)` to `Timeout`
  in `src/smithy/wifi.smithy`, then confirm it round-trips through the IR:
  ```bash
  cargo install --path ../firebolt-sdk-gen/crates/fb-gen   # rebuild after 8.1-8.5
  fb-gen --profile openspec/rdke.profile.yaml --lang test --output /tmp/gen-tests/
  grep "9999\|0.*Timeout" /tmp/gen-tests/wifi_test.cpp     # must match
  ```
  <!-- paste output here -->

---

## 9. CI integration (hooks into smithy-codegen-ci change)

> **Sibling change dependency**: task 9.1 adds a task to `smithy-codegen-ci`
> (`openspec/changes/smithy-codegen-ci/tasks.md` in `firebolt-apis`). Both changes
> should be merged together or `smithy-codegen-ci` merged first.

- [ ] 9.1 In `firebolt-apis/openspec/changes/smithy-codegen-ci/tasks.md`: add a new
  task under section 2 (C++ CI):
  ```
  - [ ] 2.5 Run fb-gen --lang test --output /tmp/gen-tests/ and compile-check
        voiceguidance_test.cpp, closedcaptions_test.cpp, wifi_test.cpp
  ```
- [ ] 9.2 **VERIFY** full existing e2e test suite still passes:
  ```bash
  cd ../firebolt-sdk-gen && cargo test -p fb-e2e
  ```
  <!-- paste output here -->
- [ ] 9.3 **VERIFY** end-to-end smoke test (the six commands in the "Definition of done"
  section at the top of this file) all pass with no errors
  <!-- paste output here -->
