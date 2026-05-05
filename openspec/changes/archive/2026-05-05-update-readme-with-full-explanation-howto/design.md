## Context

`README.md` currently documents the upstream OpenRPC/npm pipeline. The repo has since adopted a second, parallel toolchain for the RDKe platform: Smithy 2.0 IDL specs in `src/smithy/`, composed by `fb-gen` via `openspec/rdke.profile.yaml`, with change management tracked by the `openspec` CLI. None of this workflow is documented for developers who read the README.

The target audience is a Firebolt platform developer who wants to add or modify an API exposed to C++ callers. They need to know: what tools to install, where the spec files live, how to make a change, and how to verify it.

## Goals / Non-Goals

**Goals:**
- Document installation of `fb-gen` and `openspec` (prerequisites)
- Explain `src/smithy/` as the canonical spec directory
- Walk through the full add-API workflow: propose → draft IDL → lint → verify codegen → commit
- Explain `rdke.quirks.toml` purpose and the rule "fix in spec, don't add quirk entries"
- Describe the `openspec` change management commands and when to use them

**Non-Goals:**
- Documenting the upstream OpenRPC/npm pipeline (already covered)
- Smithy IDL language tutorial (link to upstream docs instead)
- Documenting the `fb-mcp` MCP server (internal AI tooling, not required for manual workflows)
- API design guidelines beyond tool-enforced conventions

## Decisions

### Decision 1: Single new section, not a full README rewrite

**Choice:** Add a self-contained "Adding a new API (RDKe toolchain)" section rather than restructuring the whole README.

**Rationale:** The existing npm/OpenRPC content is still valid for the upstream/JS SDK path. Restructuring risks breaking inbound links and diverging from the upstream repo's README. A clearly-scoped additive section is lower risk and easier to review.

**Alternative considered:** Replace the "Authoring APIs" section entirely. Rejected — that section applies to the upstream JS SDK workflow, not the RDKe C++ workflow.

### Decision 2: Include concrete command examples, not just prose

**Choice:** Every step in the workflow section has a runnable shell command.

**Rationale:** Developers trust working commands more than prose descriptions. Commands also serve as implicit regression tests — if a command in the README stops working, it surfaces a tooling regression.

### Decision 3: Quirks.toml policy belongs in the README, not just config.yaml

**Choice:** The "do not add quirk entries to compensate for spec bugs — fix them in the spec" rule is documented in the README.

**Rationale:** Developers reading the README are more likely to encounter it before config.yaml. The quirks file is a debt register, and the policy needs to be visible at the "where do I start?" level.

## Risks / Trade-offs

- **Risk:** The README drifts from the actual tooling as `fb-gen` evolves.  
  → Mitigation: Commands in the README should be the same commands used in CI. If CI changes, the README must change too (enforced by review process, not automation).

- **Risk:** Two parallel authoring workflows (OpenRPC/npm and Smithy/fb-gen) in one README may confuse new contributors.  
  → Mitigation: Each section has a clear header that scopes it to its toolchain. A short intro note at the top of the new section distinguishes it from the existing npm workflow.

- **Trade-off:** The new section is longer than the existing "Authoring APIs" section. Accepted — the RDKe workflow has more moving parts (profile, quirks, openspec) and cannot be described adequately in fewer words.
