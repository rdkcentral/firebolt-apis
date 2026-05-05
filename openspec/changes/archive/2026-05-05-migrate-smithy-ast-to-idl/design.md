## Context

`src/smithy/` currently holds 27 Smithy 2.0 JSON AST files (`.json`) that are the
canonical source for all Firebolt module specs. These were generated from upstream
OpenRPC JSON during the `smithy-canonical-spec-transition` and then curated by hand
(identifier sanitization, type corrections, RDKe-specific methods added).

The `fb-gen` toolchain already supports `.smithy` IDL as a first-class input format
(implemented in `zero-friction-api-authoring`). The profile layer (`rdke.profile.yaml`)
already declares `format: smithy` and already prefers `.smithy` over `.json` when
both exist. The only thing keeping JSON AST as canonical is that the `.json` files
exist and shadow any `.smithy` files.

The conversion is mechanical: `fb-gen --profile rdke.profile.yaml --lang smithy-idl
--emit bindings` generates all `.smithy` files from the current JSON AST via the IR
roundtrip, preserving all semantic content.

## Goals / Non-Goals

**Goals:**
- Replace all 27 `src/smithy/*.json` files with equivalent `src/smithy/*.smithy` files
- Verify the IR roundtrip produces identical codegen output (C++ bindings dry-run)
- Annotate existing `rdke.quirks.toml` entries with their debt category
- Update `openspec/config.yaml` authoring guidance to reflect IDL as canonical

**Non-Goals:**
- No API surface changes — methods, types, and semantics are identical before and after
- No changes to `src/openrpc/` (upstream reference, never edited)
- No changes to `src/schemas/` (shared JSON Schema, not part of Smithy authoring)
- No graduation of new modules (out of scope for this change)
- No deletion of quirk entries (debt resolution is a follow-on concern)

## Decisions

### D1: Mechanical generation via `fb-gen --lang smithy-idl`, no hand-authoring

**Decision:** Generate all `.smithy` files from the existing JSON AST using
`fb-gen --profile openspec/rdke.profile.yaml --lang smithy-idl --emit bindings
--output src/smithy/`. Then delete the `.json` files.

**Rationale:** The JSON AST is already the curated, correct source. Running it
through the IDL emitter produces structurally identical output — all traits,
types, and operations are preserved. Hand-rewriting 27 files would introduce
transcription errors and provide no benefit over the mechanical approach.

**Alternative considered:** Convert using `smithy-cli ast-to-idl`. Rejected —
`smithy-cli` is not installed in this workspace, and `fb-gen`'s IDL emitter
is the supported path.

### D2: Verify via dry-run codegen diff, not line-by-line file comparison

**Decision:** Confirm correctness by running `fb-gen --profile rdke.profile.yaml
--lang cpp --dry-run` before and after, and diffing the composition summary
(module count, method count, schema count). A matching summary is sufficient
evidence of a lossless roundtrip.

**Rationale:** The IDL emitter normalizes formatting (ordering, whitespace) so
a file diff would show noise. The IR summary diff is signal-only.

### D3: Delete `.json` files atomically after `.smithy` files are verified

**Decision:** Generate all `.smithy` files first, verify, then delete all `.json`
files in a single commit. Do not leave a mixed state committed.

**Rationale:** The profile's first-wins merge prefers `.json` over `.smithy` when
both exist (with a warning). A mixed committed state would be confusing and
would prevent the `.smithy` files from being the effective canonical source.

### D4: `actions.smithy` already exists — delete `actions.json` only

**Decision:** `src/smithy/actions.smithy` already exists in the repo. The
corresponding `actions.json` shadows it (with a `warn` from `fb-gen`). This
file is simply deleted; the existing `actions.smithy` becomes the live spec.

**Rationale:** The `actions.smithy` was hand-authored and is already correct.
Regenerating it would overwrite intentional authoring decisions.

## Risks / Trade-offs

**[Risk] IR roundtrip drops information not expressible in IDL emitter output**
→ Mitigation: run `--dry-run` composition diff before and after. Method counts,
schema counts, and type names in the summary will reveal any loss.

**[Risk] `fb-gen` IDL emitter has a bug that alters semantics for edge-case shapes**
→ Mitigation: spot-check 3–4 complex modules (`discovery`, `closedcaptions`,
`text_to_speech`, `capabilities`) by reading the generated IDL before committing.

**[Risk] Config.yaml still refers to JSON AST as canonical — causes confusion for AI agents**
→ Mitigation: update `config.yaml` in the same commit. This change includes that update as a task.

## Migration Plan

1. Dry-run `fb-gen` profile composition — capture baseline summary (method/schema counts)
2. Generate all `.smithy` files into `src/smithy/` via `--lang smithy-idl --emit bindings`
3. Spot-check 4 complex module IDL files for correctness
4. Run dry-run composition again — confirm summary is identical
5. Delete all 27 `src/smithy/*.json` files (keep `actions.smithy`, delete `actions.json`)
6. Run final dry-run — confirm profile still resolves all modules cleanly
7. Annotate `rdke.quirks.toml` entries with debt category comments
8. Update `openspec/config.yaml` canonical format description
9. Commit

**Rollback:** `git revert` restores all `.json` files. The `.smithy` files can
be deleted. The profile composition falls back to `.json` transparently.
