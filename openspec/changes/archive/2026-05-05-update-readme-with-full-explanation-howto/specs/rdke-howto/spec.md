## ADDED Requirements

### Requirement: README documents the RDKe API authoring prerequisites
`README.md` SHALL include a section listing the software prerequisites for authoring
Firebolt APIs using the RDKe toolchain: `fb-gen` (from `firebolt-sdk-gen`) and the
`openspec` CLI.

#### Scenario: Prerequisites section present
- **WHEN** `README.md` is read
- **THEN** it lists `fb-gen` and `openspec` as required tools with installation instructions

#### Scenario: Sibling repo dependency is explicit
- **WHEN** `README.md` is read
- **THEN** it states that `firebolt-sdk-gen` must be cloned as a sibling directory

### Requirement: README documents the end-to-end workflow for adding an API
`README.md` SHALL include a step-by-step workflow section describing how to add a new
Firebolt API operation, from proposing the change through verifying generated bindings.

#### Scenario: Workflow steps are sequential and complete
- **WHEN** `README.md` is read
- **THEN** the workflow section covers: (1) creating a change proposal, (2) editing the `.smithy` file, (3) linting, (4) validating composition, (5) generating C++ bindings

#### Scenario: Each step includes a runnable command
- **WHEN** a developer follows the workflow section
- **THEN** every step that involves running a tool includes an exact shell command they can copy-paste

### Requirement: README documents quirks.toml policy
`README.md` SHALL state that `rdke.quirks.toml` is a transitional debt register and
that new quirk entries SHALL NOT be added to compensate for spec bugs — those SHALL be
fixed directly in the `.smithy` file.

#### Scenario: Quirks policy is visible in README
- **WHEN** `README.md` is read
- **THEN** it explains the `[spec-bug]` / `[platform-dev]` classification and the policy that spec bugs are fixed in the IDL, not papered over with quirk entries

### Requirement: README describes the openspec change management commands
`README.md` SHALL include a reference table or list of the `openspec` commands
(`propose`, `apply`, `archive`) and what each does.

#### Scenario: openspec commands are documented
- **WHEN** `README.md` is read
- **THEN** it lists `/opsx:propose`, `/opsx:apply`, and `/opsx:archive` with one-line descriptions of each
