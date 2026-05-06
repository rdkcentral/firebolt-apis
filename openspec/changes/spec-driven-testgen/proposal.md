## Module

`fb-testgen` — new crate in `firebolt-sdk-gen`, plus cross-cutting changes to `fb-ir`
and `fb-backend-cpp`.

## Operation

`fb-gen --lang test` — generate a spec-driven test suite from the Firebolt Smithy specs.

## What it does

The Firebolt spec contains constraint metadata (numeric ranges, string patterns, array
bounds, enum variants) that is currently stripped during IR lowering and never enforced
at the SDK binding layer. This change wires constraints end-to-end: from Smithy source
through the IR into generated SDK bindings (so invalid values are rejected before hitting
the wire) and into generated test suites (so boundary and contract conformance is
verified automatically for every language binding, with no hand-written test code).

## Resolved trait

Plain call — this is a code-generation tooling change, not a Firebolt API operation.

## Return type

The generator emits per-language test source files (GTest for C++, `#[test]` for Rust,
Jest for JS/TS).

## Firebolt capability

No capability association — this is a tooling/SDK infrastructure change.

## Scope

New crate (`fb-testgen`) in `firebolt-sdk-gen`, plus changes to `fb-ir`, `fb-frontend`,
`fb-backend-cpp`, and `fb-backend-rust`.

## What Changes

- **`fb-ir`**: `TypeDef` and `Param` gain a `Constraints` struct carrying `minimum`,
  `maximum`, `min_length`, `max_length`, `pattern`, `min_items`, `max_items`.
- **`fb-frontend/lower.rs`**: stops discarding constraint keywords from JSON Schema
  during lowering. Named constrained types (e.g. `SpeechRate`, `Opacity`, `CountryCode`)
  propagate constraints to all method params and return types that use them.
- **`fb-backend-cpp`**: setter and plain-call impls emit a constraint guard before
  `helper_.set()` / `helper_.call()`, returning `Error::InvalidParams` immediately on
  violation. Zero network traffic. Zero server load. Drop-in compatible (same error code
  callers already handle).
- **`fb-backend-rust`**: constrained scalar typedefs become newtypes with `TryFrom`
  returning `Err(Error::InvalidParams)`.
- **`fb-testgen`** (new crate): reads the IR and emits a test suite per module per
  language. For each constrained type, generates: boundary corpus tests (at-min,
  below-min, at-max, above-max, nominal, special values NaN/Inf/null), contract tests
  (verify transport NOT called on reject, IS called on accept), and a fuzz seed corpus
  derived from boundary values.
- **Test oracle derivation**: test assertions are fully derived from the IR — no
  bespoke test logic. The three-part oracle (result status × transport called? × JSON
  body shape) is produced from constraint bounds + type serialization rules already
  encoded in the IR.

## Capabilities

### New Capabilities
- `spec-driven-testgen`: spec-derived constraint enforcement and test suite generation
  for all Firebolt SDK language bindings.

### Modified Capabilities
- `fb-ir`: constraint metadata propagation (non-breaking IR addition)
- `fb-backend-cpp`: constraint guards in setters (additive, backward-compatible)
- `fb-backend-rust`: constrained newtypes (may require downstream callsite updates)

## Impact

- `firebolt-sdk-gen/crates/fb-ir/src/lib.rs` — add `Constraints` struct
- `firebolt-sdk-gen/crates/fb-frontend/src/lower.rs` — stop dropping constraints
- `firebolt-sdk-gen/crates/fb-backend-cpp/src/` — emit guards in setters
- `firebolt-sdk-gen/crates/fb-backend-rust/src/` — emit newtypes with TryFrom
- `firebolt-sdk-gen/crates/fb-testgen/` — new crate
- `firebolt-apis/openspec/changes/smithy-codegen-ci/tasks.md` — CI integration tasks
  are a sibling change; test output should be wired into CI as part of that change.
