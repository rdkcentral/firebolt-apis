## 1. Rewrite schema instructions

- [x] 1.1 Rewrite `proposal.instruction` in `schema.yaml` as an AI interview script with the full trait decision tree (plain-English answer → `@propertyReadonly` / `@property` / `@propertyImmutable` / `@event` / plain RPC) and type decision table (count/duration/non-negative → `UInt32`, yes/no → `Boolean`, fixed set → `enum`, free text → `String`, signed → `Integer`, complex object → `structure`)
- [x] 1.2 Rewrite `design.instruction` in `schema.yaml`: 1–3 sentences for simple ops on existing modules (always recording trait/type rationale); full doc for new modules or complex type hierarchies; always answers "why this trait, why this type"
- [x] 1.3 Rewrite `specs.instruction` in `schema.yaml`: one spec per module changed, reference existing `.smithy` shape names, include resolved trait in the capability description
- [x] 1.4 Rewrite `tasks.instruction` in `schema.yaml`: instruct AI to pre-populate the four task groups from the template, filling in the actual module name and expected method count delta
- [x] 1.5 Rewrite `apply.instruction` in `schema.yaml`: VERIFY tasks require pasted output; do not mark complete on assumption; if output shows errors, pause and report before continuing

## 2. Rewrite schema templates

- [x] 2.1 Rewrite `templates/proposal.md`: structured output format for the interview — Module, Operation name, Plain-English description, Resolved trait, Return type, Firebolt capability string (if applicable)
- [x] 2.2 Rewrite `templates/tasks.md`: pre-populated four-group checklist with placeholders for module name and expected method count
- [x] 2.3 Rewrite `templates/design.md`: short rationale format (Trait choice, Type decisions, Notes) for simple ops; full design format (Context / Goals / Decisions / Risks) for complex changes
- [x] 2.4 Rewrite `templates/spec.md`: Firebolt-specific scaffold with `## ADDED Requirements`, Smithy trait in the requirement description, and WHEN/THEN scenarios that reference the operation by name

## 3. Wire up config

- [x] 3.1 In `openspec/config.yaml`, change `schema: spec-driven` to `schema: firebolt-api-change`

## 4. Validate

- [x] 4.1 Run `openspec schema validate firebolt-api-change` — confirm no schema errors
  <!-- ✓ Schema 'firebolt-api-change' is valid -->
- [x] 4.2 Create a throwaway test change (`openspec new change "schema-smoke-test"`) and confirm it uses `firebolt-api-change` schema and that `openspec instructions proposal` returns the new interview-style instruction
  <!-- schema: firebolt-api-change / has interview: True -->
- [x] 4.3 Delete the smoke-test change (`rm -rf openspec/changes/schema-smoke-test`)
