---
name: modify-fb-api
description: Modify an existing Firebolt API — interviews you in plain English to identify the operation and what is changing, resolves all Smithy decisions, creates an OpenSpec change, and implements it end-to-end. Use when the user wants to change a type, add a field to a struct, change a trait, deprecate, or rename an existing method, property, or event. Triggered by /opsx:modify-fb-api.
license: MIT
compatibility: Requires openspec CLI and fb-gen.
metadata:
  author: firebolt-apis
  version: "1.0"
---

Modify an existing Firebolt API from scratch — no Smithy knowledge required.

This skill conducts a plain-English interview to identify the existing operation and the nature of the change, resolves all Smithy decisions automatically, creates an OpenSpec change with the `firebolt-api-change` schema, generates all artifacts, and then immediately begins the apply loop to implement the change.

---

**Steps**

1. **Confirm the schema is active**

   ```bash
   openspec config get schema
   ```

   If the result is not `firebolt-api-change`, warn the user:
   > "The active schema is not `firebolt-api-change`. Run `openspec config set schema firebolt-api-change` first, or the interview step will not be available."

   Otherwise proceed.

2. **Conduct the modification interview**

   Use the **AskUserQuestion tool** for each question in sequence. Do NOT ask about Smithy syntax at any point.

   **Q1 — Which operation?**
   > "Which module and operation are you changing? (e.g. 'Device.model', 'Lifecycle.ready event', 'Metrics.startContent')"

   From the answer, locate the operation in `src/smithy/<module>.smithy` and read it to understand the current definition before proceeding.

   **Q2 — What is changing?**
   > "What do you want to change about it? For example: change a return type, add a field to a struct, add or remove an enum variant, change whether it's read-only or read-write, deprecate it, rename it, or something else."

   Classify the change into one of these categories (you resolve this — do not ask the user):

   | What they describe | Change category |
   |--------------------|----------------|
   | Different return value type | **Type change** |
   | Add/remove field on a struct | **Schema extension** |
   | Add/remove enum variant | **Enum extension** |
   | Make writable / make read-only | **Trait change** |
   | Mark as deprecated | **Deprecation** |
   | Rename the operation | **Rename** |
   | Change which capability it requires | **Capability change** |
   | Other / multiple | **Compound** |

   **Q3 — Breaking change assessment**

   Evaluate automatically based on the change category:
   - **Breaking**: removing a field, removing an enum variant, narrowing a type, renaming
   - **Non-breaking**: adding an optional field, adding an enum variant, widening a type, deprecation

   If breaking, tell the user:
   > "This is a **breaking change** — it removes or narrows something callers may depend on. Breaking changes require a major version bump and a deprecation notice in the spec. Do you want to proceed, or would you prefer a non-breaking approach (e.g. adding a new operation alongside the old one)?"

   Wait for confirmation before continuing.

   **Q4 — Why?**
   > "What's the reason for this change? (One sentence is fine — this goes into the design rationale and is permanent.)"

3. **Derive a change name**

   Format: `<module>-<operation>-<verb>` in lowercase kebab-case.
   Examples: `device-model-add-variant`, `lifecycle-ready-deprecate`, `metrics-startcontent-rename`, `display-brightness-widen-type`

4. **Create the change**

   ```bash
   openspec new change "<name>"
   ```

5. **Create proposal artifact**

   ```bash
   openspec instructions proposal --change "<name>" --json
   ```

   Write `openspec/changes/<name>/proposal.md` using the template. Include:
   - **Module**: the affected module
   - **Operation**: the existing operation name (exact `.smithy` identifier)
   - **Current definition**: brief summary of what it is today
   - **Change type**: the resolved category from Q2
   - **What changes**: plain-English description of the delta
   - **Breaking**: Yes / No, with rationale
   - **Reason**: the answer from Q4

6. **Create remaining artifacts in dependency order**

   ```bash
   openspec status --change "<name>" --json
   ```

   For each artifact not yet `done` (in dependency order):

   ```bash
   openspec instructions <artifact-id> --change "<name>" --json
   ```

   Create the artifact file at `outputPath` following the `instruction` and `template`.
   Read any dependency artifacts for context first.
   Show brief progress: "Created <artifact-id>"

   **For tasks.md specifically**, pre-populate with the modification-specific task groups:

   ```
   ## 1. IDL
   - [ ] 1.1 Edit src/smithy/<module>.smithy — modify <operation>
   - [ ] 1.2 **VERIFY** fb-gen --lint: <!-- paste output here -->

   ## 2. Type correctness
   - [ ] 2.1 All non-negative integers use UInt32 (not Integer or int)
   - [ ] 2.2 No shape name prefixed with the module name
   - [ ] 2.3 All enums have named variants (no auto-generated V0, V1...)
   [If breaking change:]
   - [ ] 2.4 Old operation marked @deprecated with a migration note

   ## 3. Composition validation
   - [ ] 3.1 **VERIFY** fb-gen --dry-run — method count unchanged (modification, not addition): <!-- paste output here -->
   - [ ] 3.2 **VERIFY** fb-gen --emit bindings: <!-- paste output here -->

   ## 4. Quirks discipline
   - [ ] 4.1 No new [spec-bug] entries in rdke.quirks.toml (fix in .smithy instead)
   - [ ] 4.2 Any new [platform-dev] entry has a justification comment
   ```

7. **Confirm ready for implementation**

   ```bash
   openspec status --change "<name>"
   ```

   Then ask:
   > "Proposal, design, specs, and tasks are ready. Shall I start implementing now?"

   If yes, immediately begin the apply loop:
   - Read task list from `openspec instructions apply --change "<name>" --json`
   - Work through each task, pausing at VERIFY steps to paste real output
   - Mark tasks complete as they are done

8. **On completion**

   Summarize:
   - Change name and location (`openspec/changes/<name>/`)
   - Module and operation modified
   - Change category and whether it was breaking
   - VERIFY outputs (lint, dry-run, bindings)
   - If breaking: remind to bump version and add deprecation in spec
   - Suggest: `git add src/smithy/<module>.smithy openspec/changes/<name>/ && git commit -m "fix(<module>): <description>"`

---

**Guardrails**

- Always read the current `.smithy` definition before proposing any change
- Never ask the user what Smithy syntax to use — resolve it from their plain-English answers
- VERIFY tasks require real pasted output; never mark a VERIFY task complete on assumption
- For breaking changes: do not proceed past Q3 without explicit user confirmation
- Do not add `[spec-bug]` entries to `rdke.quirks.toml` — fix shape errors in the `.smithy` file instead
- If the `firebolt-api-change` schema is not active, stop and warn rather than proceeding with wrong instructions
