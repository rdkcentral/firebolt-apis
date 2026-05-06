## Full Design

### Context

The Firebolt SDK is a 5-year-old JSON-RPC over WebSocket API originally designed for
JavaScript. The move to C++/Rust/TS native bindings (via `fb-gen`) exposed a structural
gap: the spec carries constraint metadata (ranges, patterns, enum sets, array bounds)
but the IR discards it. Generated bindings are therefore unguarded — invalid values
flow straight to the transport and on to the server, which may accept, reject, or
silently misbehave (the "pray" pattern). Client and server are developed independently
and have no shared enforcement point.

Current state:
- `using SpeechRate = float` — spec says [0.1, 10.0], binding enforces nothing
- `using Opacity = float` — spec says [0, 100], binding enforces nothing
- `using Timeout = int32_t` — spec says [0, 9999], binding enforces nothing
- 22 constrained named types + 5 constrained method params exist today; more to come

### Goals / Non-Goals

**Goals:**
- Propagate constraint metadata through the IR without loss
- Generate constraint guards in C++ setters (reject before wire, `Error::InvalidParams`)
- Generate Rust newtypes with `TryFrom` for constrained scalars
- Generate a deterministic, schema-derived test suite per module per language binding
- Test suite covers: boundary corpus, contract/guard verification, fuzz seeds
- All assertions derived from spec — zero bespoke test code needed
- Drop-in backward compatibility: callers already checking `!result.has_value()` are unaffected
- Binary footprint: <1 KB per module for constraint guards (no strings, no format strings)

**Non-Goals (Phase 1):**
- Response validation (validating server responses against constraints) — Layer 2 future work
- `Error::ConstraintViolation` distinct error code — planned Phase 2 migration
- JS/TS runtime enforcement — deferred (JS SDK has separate pipeline)
- Exhaustive regex-based invalid input generation — fuzz seeds only for Phase 1

### Decisions

#### D1: Where constraints live in the IR

Add `Constraints` as an optional field on `TypeDef` and on `Param`, not as a wrapper type:

```rust
pub struct Constraints {
    pub minimum: Option<f64>,
    pub maximum: Option<f64>,
    pub min_length: Option<usize>,
    pub max_length: Option<usize>,
    pub pattern: Option<String>,
    pub min_items: Option<usize>,
    pub max_items: Option<usize>,
}
```

Stored on `TypeDef` (named constrained type) and copied onto `Param` during lowering
when the param's type resolves to a constrained typedef. Backends read from the param
directly — no need to chase type references at codegen time.

**Alternative considered**: wrap constrained types in a `Validated<T, Constraints>`
newtype in the IR. Rejected — changes the shape of every TypeRef, breaks all existing
backend match arms, and the extra indirection adds complexity with no benefit.

#### D2: C++ enforcement idiom

Inline guard in the generated setter body, before `helper_.set()`:

```cpp
Result<void> VoiceguidanceImpl::setRate(const SpeechRate& value) {
    if (value < 0.1f || value > 10.0f) {             // generated from constraints
        return Result<void>{Error::InvalidParams};
    }
    nlohmann::json params;
    params["value"] = value;
    return helper_.set("voiceguidance.rate", params);
}
```

No strings. No format messages. The enum int32 `Error::InvalidParams = -32602` already
exists in the transport layer. The guard is ~16 bytes of instructions per constraint.
Total across all 27 current constraints: ~432 bytes. Negligible on embedded.

**Drop-in**: callers checking `!result.has_value()` or `result.error() != Error::None`
continue to work. No API surface change.

**Future (Phase 2)**: add `Error::ConstraintViolation = -32603` to the error enum.
Client-side rejection → `ConstraintViolation`. Server-returned rejection → `InvalidParams`.
Callers can distinguish "I sent bad data" from "server rejected valid data". One new enum
value, fully additive, opt-in to use.

#### D3: Rust enforcement idiom

Constrained scalar types become newtypes with `TryFrom`:

```rust
// generated
pub struct SpeechRate(f32);

impl TryFrom<f32> for SpeechRate {
    type Error = FireboltError;
    fn try_from(v: f32) -> Result<Self, Self::Error> {
        if v < 0.1 || v > 10.0 {
            return Err(FireboltError::InvalidParams);
        }
        Ok(SpeechRate(v))
    }
}
```

Idiomatic Rust. Zero runtime cost (inlined by optimizer). Callsite changes: callers must
use `SpeechRate::try_from(x)?` instead of passing bare `f32`. This is a breaking change
for Rust — document clearly and version accordingly.

#### D4: Test oracle — three-part assertion fully derived from IR

For each constrained param/type, the test generator derives:

1. **Result status** (`Error::InvalidParams` or `has_value()`) — from whether the input
   violates constraints
2. **Transport called?** (`mock.call_count == 0` or `== 1`) — invalid inputs must not
   reach the wire
3. **JSON body** (for valid inputs: `{"value": <input_value>}`, method name from
   `rpc_name` field) — from type serialization rules already in the IR

Test case inputs are derived mechanically from constraints:
- Numeric range `[min, max]`: inputs = `{min-ε, min, mid, max, max+ε, 0, -1, NaN, Inf}`
  where ε = smallest representable step (1 for integers, `f32::EPSILON * max` for floats)
- String pattern: valid = first `examples` entry from spec; invalid = lowercase of valid,
  extra char appended, empty string, `"\x00"` (null byte)
- Enum: valid = all known variants; invalid = `"unknown"`, `""`, uppercase variant
- Array bounds: valid = `[min_items..max_items]` length; invalid = empty (if min>0),
  oversized (if max set)

Test names are stable: `Set<Method>_AtMin`, `Set<Method>_BelowMin`, etc. Derived from
constraint semantics, not from input values. A constraint change changes the *call value*
but keeps the *test name* — the diff is readable and auditable.

#### D5: Fuzz harness seeds

For each constrained method, `fb-testgen` emits a `corpus/` directory alongside the test
file containing binary-encoded boundary values as libFuzzer seeds. The fuzz target itself
(a separate generated file) calls the method with the deserialized input and asserts:
- no undefined behaviour (sanitizers: ASan, UBSan)
- no crash
- constraint-violating inputs produce `Error::InvalidParams`
- valid inputs produce `has_value()` OR `Error::General` (transport error is OK in fuzz)

Property-based (proptest) tests are also generated for Rust as the primary CI fuzz mode
(deterministic, fixed seed, fast). libFuzzer targets are generated for nightly/extended
runs.

#### D6: Source of constraint truth — two-layer approach

**Layer A (immediate)**: read constraints from JSON Schema keywords in OpenRPC files
(`minimum`, `maximum`, `pattern`, `minLength`, etc.) via the existing `fb-frontend`.
Gives enforcement for all 27 existing constraints without touching any `.smithy` file.

**Layer B (progressive)**: parse `@range(min: X, max: Y)`, `@length(min: X, max: Y)`,
and `@pattern("regex")` traits in the Smithy IDL. As `.smithy` files are updated,
Smithy-sourced constraints override OpenRPC-sourced ones. A new lint rule warns when
Smithy and OpenRPC disagree on constraint bounds.

### Risks / Trade-offs

- **[Risk] Rust callsite breaking change** → Mitigate by versioning the Rust crate and
  providing a migration guide. Newtypes are strictly safer — callers that migrate are
  better off.
- **[Risk] Constraint coverage is sparse today (27 constraints)** → The system is fully
  additive. Test suites for unconstrained methods have zero generated cases — no noise.
  As constraints are added to Smithy, tests appear automatically.
- **[Risk] `fb-testgen` mock transport interface drift** → The mock transport must match
  the real `IHelper` interface. Tie the mock to the same interface definition to prevent
  drift. Add a compile-check in CI.
- **[Risk] Fuzz seeds hit legitimate server code paths** → Layer 1 tests use mock
  transport (no network). Layer 2 server pressure tests are opt-in and clearly labelled.
  No accidental server hammering in CI.
