## Context

The `firebolt-api-change` schema lives at `openspec/schemas/firebolt-api-change/` (already forked from `spec-driven`). It has a `schema.yaml` with five `instruction` fields and four template files. None of the instruction fields currently contain Firebolt-specific guidance. The task is to rewrite them.

The target user is a developer who knows what their API should *do* but has little or no Smithy IDL knowledge. The schema must encode all IDL knowledge so the user never has to look it up.

## Goals / Non-Goals

**Goals:**
- Encode the full Firebolt trait decision tree in `proposal.instruction` as a conversational interview script
- Encode the type decision table (UInt32 vs Integer vs String vs enum vs structure) in `proposal.instruction`
- Make `tasks.md` template a strict pre-populated checklist with VERIFY steps requiring pasted output
- Make `design.md` scale from 1–3 sentences (simple op) to full doc (new module / complex types) — always capturing trait/type rationale for the audit trail
- Switch `config.yaml` default to `firebolt-api-change` so all future changes inherit this automatically

**Non-Goals:**
- Teaching Smithy IDL to users (they should never need to look it up)
- Changing any `.smithy` source files
- Modifying the `spec-driven` global schema

## Decisions

### Decision 1: Interview-style proposal, not a form

**Choice:** `proposal.instruction` is an AI briefing: "Ask these questions in this order, map answers using this decision tree, then write the proposal."

**Rationale:** A form requires domain knowledge to fill in correctly. An interview surfaces domain knowledge through questions the user can answer in plain English. The AI holds the mapping; the user holds the intent.

**Alternative considered:** Annotated form with examples per field. Rejected — still requires the user to know what "capability" means, what "breaking" means, and how to name things.

### Decision 2: Decision tree embedded in the instruction (not config.yaml)

**Choice:** The full trait and type decision trees live inside `proposal.instruction` in `schema.yaml`, not in `config.yaml`.

**Rationale:** `config.yaml` context is injected into every artifact. The decision tree is only relevant during proposal creation — putting it there reduces noise in other artifact instructions. `schema.yaml` is the right owner because it is schema-specific, not project-specific.

### Decision 3: VERIFY tasks require pasted output

**Choice:** Tasks marked `**VERIFY**` in `tasks.md` include a `<!-- paste output here -->` slot. `apply.instruction` states: do not mark a VERIFY task complete without pasting actual command output.

**Rationale:** The only alternative is CI enforcement, which requires infrastructure. For an AI-assisted workflow, the instruction-level constraint is the best available gate. It creates an audit trail inside the tasks.md file itself, which becomes part of the archived change.

### Decision 4: design.md scales with complexity, always captures rationale

**Choice:** `design.instruction` says: "For a simple operation on an existing module, write 1–3 sentences explaining the trait choice and any non-obvious type decisions. For a new module or complex type hierarchy, write a full design doc."

**Rationale:** The file always exists (schema doesn't support conditional artifacts), so the instruction controls depth. Requiring at least the trait/type rationale ensures every archived change answers "why this shape?" — the core audit trail requirement.

## Risks / Trade-offs

- **Risk:** `apply.instruction` can say "paste output" but cannot enforce it if a user or AI skips it.
  → Mitigation: VERIFY tasks have explicit `<!-- paste output here -->` slots; the instruction says not to mark complete without filling them. Over time, a CI lint on tasks.md could enforce this.

- **Risk:** The interview script in `proposal.instruction` may not cover every edge case (e.g., bidirectional APIs, provider/consumer patterns).
  → Mitigation: Include an escape hatch: "If none of the above patterns fit, describe what the API does and I will determine the correct trait."

- **Trade-off:** The schema YAML is 246 lines and will grow. It is not human-authored in practice — the AI manages it — but it is checked into the repo and versioned. If `openspec` changes its schema format, this file will need updating.
