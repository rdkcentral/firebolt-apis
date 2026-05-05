## ADDED Requirements

### Requirement: AI-guided authoring does not require Smithy knowledge
The `smithy-idl-canonical` authoring workflow SHALL be accessible to developers
with no prior Smithy IDL knowledge. The `firebolt-api-change` schema SHALL encode
all IDL knowledge (traits, types, naming rules) so that the user only needs to
describe API behaviour in plain English.

#### Scenario: Developer adds API without writing IDL manually
- **WHEN** a developer follows the `/opsx:propose` → `/opsx:apply` workflow
- **THEN** the AI generates the correct `.smithy` IDL content from the developer's plain-English answers, including the correct trait, types, and naming

#### Scenario: IDL correctness verified by tooling, not by user
- **WHEN** the apply workflow reaches the validation tasks
- **THEN** `fb-gen --lint` is run and its output is recorded before the task is marked complete — the user does not manually verify IDL correctness
