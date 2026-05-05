## ADDED Requirements

### Requirement: API authoring uses an interview-driven proposal
When a developer begins a Firebolt API change, the AI SHALL conduct a conversational
interview to determine the API's behaviour, and SHALL NOT require the user to know
Smithy IDL, trait names, or type identifiers.

#### Scenario: Trait resolved from plain-English description
- **WHEN** a developer describes what an API does in plain English (e.g. "apps read it, platform pushes updates, apps can't change it")
- **THEN** the AI resolves the correct Smithy trait (`@propertyReadonly`, `@property`, `@propertyImmutable`, `@event`, or plain RPC) without the user naming it

#### Scenario: Type resolved from value description
- **WHEN** a developer describes the return value in plain English (e.g. "a count", "yes or no", "one of a fixed set of options")
- **THEN** the AI resolves the correct Smithy type (`UInt32`, `Boolean`, `String`, `enum`, `Integer`, or `structure`) without the user naming it

#### Scenario: Escape hatch for unusual patterns
- **WHEN** a developer's API does not fit any of the standard patterns
- **THEN** the AI asks for a full description and determines the trait from first principles, rather than failing or forcing an incorrect pattern

### Requirement: Design captures trait and type rationale
Every archived change SHALL include a `design.md` that records at minimum the
trait choice and any non-obvious type decisions, regardless of change complexity.

#### Scenario: Simple operation records rationale
- **WHEN** a change adds a single operation to an existing module
- **THEN** `design.md` contains at least 1–3 sentences explaining the trait choice and type decisions

#### Scenario: New module has full design doc
- **WHEN** a change introduces a new Firebolt module or a complex type hierarchy
- **THEN** `design.md` contains a full design document with Context, Goals/Non-Goals, Decisions, and Risks sections

### Requirement: Tasks enforce validation before completion
Every Firebolt API change SHALL include a pre-populated task checklist with VERIFY
tasks that require actual command output to be recorded before the task is marked complete.

#### Scenario: VERIFY tasks have output slots
- **WHEN** a tasks.md is generated for a Firebolt API change
- **THEN** it contains VERIFY tasks for: `fb-gen --lint`, `fb-gen --dry-run`, and `fb-gen --emit bindings`, each with a comment slot for pasted output

#### Scenario: VERIFY task not marked complete without output
- **WHEN** the AI is applying tasks
- **THEN** it SHALL NOT mark a VERIFY task complete without pasting the actual command output into the slot

### Requirement: Quirks discipline enforced at task level
The task checklist SHALL include an explicit step confirming no new `[spec-bug]`
entries were added to `rdke.quirks.toml`.

#### Scenario: Spec bugs fixed in IDL not quirks
- **WHEN** a developer discovers a type error in the upstream spec during a change
- **THEN** the task checklist prompts them to fix it directly in the `.smithy` file rather than adding a quirk entry

### Requirement: Schema is the project default
The `firebolt-api-change` schema SHALL be set as the default in `openspec/config.yaml`
so that all new changes automatically use it without requiring `--schema` flag.

#### Scenario: New change uses firebolt-api-change schema
- **WHEN** a developer runs `openspec new change "<name>"` without any flags
- **THEN** the resulting change uses the `firebolt-api-change` schema
