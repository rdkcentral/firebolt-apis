## ADDED Requirements

### Requirement: Constraint metadata is preserved through the IR
The `fb-ir` crate SHALL carry a `Constraints` struct on `TypeDef` and `Param` shapes,
preserving `minimum`, `maximum`, `min_length`, `max_length`, `pattern`, `min_items`,
and `max_items` values sourced from the Firebolt spec.

The `fb-frontend` lowering pass SHALL NOT discard these constraint keywords when lowering
JSON Schema types to IR types.

#### Scenario: Constrained named type used as param
- **WHEN** a method param's type resolves to a named typedef that carries constraints
- **THEN** those constraints SHALL be copied onto the param in the lowered IR

#### Scenario: Constraint sourcing
- **WHEN** a constraint is present in both the Smithy IDL (`@range`, `@length`,
  `@pattern`) and the OpenRPC JSON Schema (`minimum`, `maximum`, `pattern`)
- **THEN** the Smithy IDL value SHALL take precedence

---

### Requirement: Generated C++ setters enforce constraints before the transport
For each C++ setter or plain-call method whose parameter carries a constraint, the
generated implementation SHALL evaluate the constraint inline and return
`Result<void>{Error::InvalidParams}` if violated, before any call to
`helper_.set()` or `helper_.call()`.

#### Scenario: Value below numeric minimum
- **WHEN** a caller passes a value strictly less than `minimum`
- **THEN** the method SHALL return `Error::InvalidParams` synchronously
- **AND** the transport layer SHALL NOT be invoked

#### Scenario: Value above numeric maximum
- **WHEN** a caller passes a value strictly greater than `maximum`
- **THEN** the method SHALL return `Error::InvalidParams` synchronously
- **AND** the transport layer SHALL NOT be invoked

#### Scenario: Value at boundary
- **WHEN** a caller passes a value exactly equal to `minimum` or `maximum`
- **THEN** the method SHALL proceed normally and invoke the transport

#### Scenario: String exceeds maxLength
- **WHEN** a caller passes a string whose length in characters exceeds `max_length`
- **THEN** the method SHALL return `Error::InvalidParams` synchronously
- **AND** the transport layer SHALL NOT be invoked

#### Scenario: Array below minItems
- **WHEN** a caller passes an array with fewer elements than `min_items`
- **THEN** the method SHALL return `Error::InvalidParams` synchronously
- **AND** the transport layer SHALL NOT be invoked

#### Scenario: No constraint present
- **WHEN** a method's parameter has no constraint metadata
- **THEN** the generated implementation SHALL be identical to the current baseline
  (no guard emitted, no binary size increase)

---

### Requirement: Generated Rust constrained types use newtypes with TryFrom
For each Rust typedef that carries a numeric or string constraint, the generated type
SHALL be a newtype struct (e.g. `pub struct SpeechRate(f32);`) with a `TryFrom`
implementation that returns `Err(FireboltError::InvalidParams)` when the value violates
the constraint.

#### Scenario: Out-of-range value
- **WHEN** a caller constructs `SpeechRate::try_from(99.0)`
- **THEN** the result SHALL be `Err(FireboltError::InvalidParams)`

#### Scenario: Valid value
- **WHEN** a caller constructs `SpeechRate::try_from(5.0)`
- **THEN** the result SHALL be `Ok(SpeechRate(5.0))`

---

### Requirement: fb-testgen generates a spec-derived test suite
The `fb-testgen` crate SHALL accept an IR module as input and emit a test suite
containing boundary corpus tests, contract/guard tests, and fuzz seed corpus files.

No bespoke test logic SHALL be required to achieve full constraint coverage — all test
cases and all assertions SHALL be derived from the IR.

#### Scenario: Boundary corpus — numeric range
- **GIVEN** a constrained method param with `minimum = M` and `maximum = N`
- **THEN** the generated test suite SHALL include test cases for at least:
  - value = M − ε (below minimum) → expects `Error::InvalidParams`, transport not called
  - value = M (at minimum) → expects success, transport called with `{"value": M}`
  - value = (M+N)/2 (nominal) → expects success, transport called
  - value = N (at maximum) → expects success, transport called with `{"value": N}`
  - value = N + ε (above maximum) → expects `Error::InvalidParams`, transport not called
  - value = NaN (if float) → expects `Error::InvalidParams`, transport not called
  - value = +Inf (if float) → expects `Error::InvalidParams`, transport not called
  - value = INT_MIN or INT_MAX (if integer) → expects `Error::InvalidParams` if out of range

#### Scenario: Boundary corpus — enum type
- **GIVEN** a method param whose type is an enum
- **THEN** the generated test suite SHALL include one passing test per known variant
- **AND** SHALL include failing tests for: empty string, unknown variant string,
  uppercase variant, and an integer literal

#### Scenario: Contract test — transport not called on rejection
- **GIVEN** any test case expected to produce `Error::InvalidParams`
- **THEN** the generated test SHALL assert that the mock transport received zero calls

#### Scenario: Contract test — JSON body on acceptance
- **GIVEN** any test case expected to succeed
- **THEN** the generated test SHALL assert that the mock transport was called exactly once
- **AND** SHALL assert the JSON body matches the expected serialized form of the input

#### Scenario: Fuzz seeds
- **GIVEN** a constrained method
- **THEN** the generator SHALL emit a `corpus/<module>_<method>/` directory
  containing binary-encoded boundary values suitable as libFuzzer seed inputs

#### Scenario: No constraint — no test generated
- **GIVEN** a method with no constrained params and no constrained return type
- **THEN** no boundary or contract test cases SHALL be generated for that method
  (constraint-free methods are out of scope for this system)

---

### Requirement: Generated test names are stable and spec-derived
Test names SHALL be derived from method name and constraint semantics, not from input
values or random seeds. A constraint range change SHALL change test call values but
SHALL NOT change test names.

#### Scenario: Constraint value change
- **WHEN** `SpeechRate.minimum` changes from `0.1` to `0.5` in the spec
- **THEN** the test name `SetRate_AtMin` SHALL remain unchanged
- **AND** the test's call value SHALL change from `0.1f` to `0.5f`
- **AND** the diff SHALL be auditable without reading test logic

---

### Requirement: Constraint guards are binary-size neutral for unconstrained methods
For any method whose params carry no constraint metadata, the generated C++ output
SHALL be byte-for-byte identical to the current generated output (no guard code emitted).

The total binary size increase across all constrained methods SHALL not exceed 1 KB
on an ARM Cortex-A target compiled with `-Os`.

---

### Requirement: All constraint guards use existing error codes (backward compat)
Constraint violations in generated C++ SHALL return `Error::InvalidParams` (value
`-32602`), which is already present in the `Firebolt::Error` enum in the transport layer.

No new error codes SHALL be required for Phase 1. The Phase 2 migration path to a
distinct `Error::ConstraintViolation` code is noted in the design but out of scope here.
