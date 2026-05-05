## ADDED Requirements

### Requirement: IDL authoring workflow is discoverable from the README
The `smithy-idl-canonical` format requirement SHALL be surfaced in `README.md` so that
developers do not need to read `openspec/config.yaml` to discover that `.smithy` IDL is
the canonical source format.

#### Scenario: README references the smithy canonical format rule
- **WHEN** `README.md` is read
- **THEN** it states that all specs in `src/smithy/` are `.smithy` IDL files and that `.json` JSON AST files SHALL NOT be created
