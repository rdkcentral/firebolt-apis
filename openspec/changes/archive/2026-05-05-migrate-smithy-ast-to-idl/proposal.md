## Why

The 27 Firebolt module specs in `src/smithy/` are authored as Smithy 2.0 JSON AST — a machine-friendly but human-hostile format. Switching to Smithy IDL (`.smithy` text format) makes specs readable, reviewable, and editable without tooling, which is the right authoring experience for a source-of-truth spec repo.

## What Changes

- **Migrated**: all 27 `src/smithy/*.json` Smithy JSON AST files replaced by equivalent `src/smithy/*.smithy` IDL files
- **Deleted**: the 27 `.json` files (except `actions.smithy` already exists — its `.json` shadow is removed)
- **Updated**: `openspec/rdke.profile.yaml` — `smithy-canonical` layer already uses `format: smithy`; no layer change needed since `fb-gen` already prefers `.smithy` when `.json` is absent
- **Updated**: `openspec/config.yaml` — update the canonical format description from "Smithy 2.0 JSON AST" to "Smithy 2.0 IDL"
- **Updated**: `openspec/rdke.quirks.toml` — annotate existing entries with their debt category (`spec-bug`, `bad-ident`, `platform-dev`) per the design decision recorded 2026-05-05

## Capabilities

### New Capabilities

- `smithy-idl-canonical`: Smithy IDL (`.smithy`) is the canonical spec format for all Firebolt modules in this repo. Authors read, write, and review `.smithy` files. The JSON AST is a generated/transient format, not a source of truth.

### Modified Capabilities

*(none — this is a format migration with no API surface changes)*

## Impact

- `src/smithy/` — 27 `.json` files replaced by 27 `.smithy` files; semantics identical
- `openspec/config.yaml` — authoring guidance updated to reflect IDL as canonical
- `openspec/rdke.quirks.toml` — entries annotated with debt category
- No generated output changes — `fb-gen` profile composition produces identical IR before and after
- No SDK changes — downstream codegen is unaffected
