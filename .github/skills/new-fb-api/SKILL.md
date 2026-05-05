---
name: new-fb-api
description: Add a new Firebolt API — runs a plain-English interview to determine the module, operation, trait, and types, then creates an OpenSpec change with all artifacts and immediately begins implementation. Use when the user wants to add a new method, property, or event to a Firebolt module. Triggered by /opsx:new-fb-api.
license: MIT
compatibility: Requires openspec CLI and fb-gen.
metadata:
  author: firebolt-apis
  version: "1.0"
---

Add a new Firebolt API from scratch — no Smithy knowledge required.

This skill conducts a plain-English interview, resolves all Smithy decisions automatically, creates an OpenSpec change with the `firebolt-api-change` schema, generates all artifacts, and then immediately begins the apply loop to implement the change.

---

**Steps**

1. **Confirm the schema is active**

   ```bash
   openspec config get schema
   ```

   If the result is not `firebolt-api-change`, warn the user:
   > "The active schema is not `firebolt-api-change`. Run `openspec config set schema firebolt-api-change` first, or the interview step will not be available."

   Otherwise proceed.

2. **Derive a change name from the user's description**

   If the user provided a description (e.g. "add a brightness property to the Display module"), derive a kebab-case name:
   - Strip module prefix if duplicated: `Display.brightness` → `display-brightness`
   - Format: `<module>-<operation>` in lowercase kebab-case
   - Examples: `device-audio-profiles`, `lifecycle-suspend-event`, `metrics-session-start`

   If no description was given, use the **AskUserQuestion tool** (open-ended) to ask:
   > "What Firebolt API do you want to add? Describe it in plain English — e.g. 'a property on the Display module that returns the current brightness level as a percentage'."

3. **Create the change**

   ```bash
   openspec new change "<name>"
   ```

4. **Run the proposal interview**

   ```bash
   openspec instructions proposal --change "<name>" --json
   ```

   Read the `instruction` field — it contains the INTERVIEW SCRIPT. Follow it exactly:
   - Ask each question in turn using the **AskUserQuestion tool**
   - Apply the trait decision table (plain-English answer → resolved Smithy trait)
   - Apply the type decision table (description → concrete Smithy type)
   - Do NOT ask the user about Smithy syntax at any point
   - Record all decisions, then write `openspec/changes/<name>/proposal.md` using the template

5. **Create remaining artifacts in dependency order**

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

6. **Confirm ready for implementation**

   ```bash
   openspec status --change "<name>"
   ```

   Then ask:
   > "Proposal, design, specs, and tasks are ready. Shall I start implementing now?"

   If yes, immediately hand off to the `openspec-apply-change` skill workflow:
   - Read task list from `openspec instructions apply --change "<name>" --json`
   - Work through each task, pausing at VERIFY steps to paste real output
   - Mark tasks complete as they are done

7. **On completion**

   Summarize:
   - Change name and location (`openspec/changes/<name>/`)
   - Module and operation added
   - Trait applied and why
   - VERIFY outputs (lint, dry-run, bindings)
   - Suggest: `git add src/smithy/<module>.smithy openspec/changes/<name>/ && git commit -m "feat(<module>): <description>"`

---

**Guardrails**

- Never ask the user what Smithy trait or type to use — resolve it from their plain-English answers
- VERIFY tasks require real pasted output; never mark a VERIFY task complete on assumption
- Do not add `[spec-bug]` entries to `rdke.quirks.toml` — fix shape errors in the `.smithy` file instead
- If the `firebolt-api-change` schema is not active, stop and warn rather than proceeding with wrong instructions
