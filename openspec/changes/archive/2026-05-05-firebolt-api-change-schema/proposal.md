## Why

The current `spec-driven` schema is generic — it gives no Firebolt-specific guidance during proposal, no decision-tree for Smithy traits, and no enforcement of validation steps. A low-skill developer adding their first Firebolt API has to know Smithy IDL, trait semantics, type conventions, and the `fb-gen` validation workflow before they can produce a correct change. The result is spec bugs, wrong types, and skipped validation.

## What Changes

- **New schema** `firebolt-api-change` in `openspec/schemas/firebolt-api-change/` (already forked — needs its instruction fields and templates rewritten)
- **`proposal.instruction`**: rewritten as an AI interview script — the AI asks plain-English questions and maps answers to the correct Smithy trait, type, and module decisions without the user ever seeing Smithy syntax
- **`design.instruction`**: scaled depth — 1–3 sentences for simple operations on existing modules; full design doc only for new modules or complex type hierarchies; rationale for trait/type choices always required (audit trail)
- **`specs.instruction`**: Firebolt-specific — references existing `.smithy` shapes by name, enforces one spec per module changed, includes the resolved trait in the capability description
- **`tasks.instruction` + `templates/tasks.md`**: pre-populated four-group checklist (IDL / Type correctness / Composition validation / Quirks discipline) with **VERIFY** tasks that require pasting actual command output before marking complete
- **`apply.instruction`**: strict — VERIFY tasks must have output pasted, never marked complete on assumption
- **`config.yaml`**: switch default schema from `spec-driven` to `firebolt-api-change`

## Capabilities

### New Capabilities

- `firebolt-schema-ux`: The `firebolt-api-change` schema as a governed artifact — covers the interview flow, decision tree, task enforcement policy, and design depth rules

### Modified Capabilities

- `smithy-idl-canonical`: The authoring workflow is now guided by the schema; the "how the AI assists" aspect is a new requirement on top of "IDL files are canonical"

## Impact

- `openspec/schemas/firebolt-api-change/schema.yaml` — rewritten instruction fields (all 5)
- `openspec/schemas/firebolt-api-change/templates/*.md` — all 4 templates rewritten
- `openspec/config.yaml` — one line: `schema: firebolt-api-change`
- No `.smithy` files changed, no code generated
- All future changes created via `openspec new change` will use the new schema automatically
