## ADDED Requirements

### Requirement: Smithy IDL is the canonical spec format
All Firebolt module specs in `src/smithy/` SHALL be authored and maintained as
Smithy 2.0 IDL (`.smithy`) text files. Smithy JSON AST (`.json`) files SHALL NOT
exist in `src/smithy/` as a primary source.

#### Scenario: All modules present as IDL files
- **WHEN** `src/smithy/` is listed
- **THEN** every module has a `.smithy` file and no `.json` file

#### Scenario: Profile composition resolves all modules from IDL
- **WHEN** `fb-gen --profile openspec/rdke.profile.yaml --explain` is run
- **THEN** all smithy-canonical layer modules show as resolved with no shadowing warnings

#### Scenario: Codegen output is identical before and after migration
- **WHEN** `fb-gen --profile openspec/rdke.profile.yaml --lang cpp --dry-run` is run after migration
- **THEN** the composition summary (module count, method count, schema count) is identical to the pre-migration baseline

### Requirement: New module authoring uses IDL
When adding a new Firebolt module to `src/smithy/`, the author SHALL create a `.smithy`
IDL file. A `.json` JSON AST file SHALL NOT be created as a new module source.

#### Scenario: New module added as IDL
- **WHEN** a new module is added to the smithy-canonical profile layer
- **THEN** the corresponding file in `src/smithy/` has a `.smithy` extension

### Requirement: Quirks entries are classified
Every entry in `rdke.quirks.toml` SHALL have a comment classifying it as one of:
`[spec-bug]`, `[bad-ident]`, or `[platform-dev]`, per the design decision recorded 2026-05-05.

#### Scenario: All quirk entries have a classification comment
- **WHEN** `rdke.quirks.toml` is read
- **THEN** every value entry has an immediately preceding comment containing one of `[spec-bug]`, `[bad-ident]`, or `[platform-dev]`
