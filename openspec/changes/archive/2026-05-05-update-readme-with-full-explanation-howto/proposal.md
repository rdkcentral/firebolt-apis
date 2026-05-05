## Why

The README describes the upstream OpenRPC-based authoring workflow but says nothing about the RDKe-specific toolchain (`fb-gen`, `openspec`) or how to add a new API to the Smithy IDL specs. Developers landing in this repo have no documented path from "I want a new API" to "I have generated bindings" — they must reverse-engineer the tooling by reading the source. This creates unnecessary onboarding friction and risks incorrect usage of quirks.toml.

## What Changes

- Add an **"Adding a new API"** section to `README.md` that covers:
  - Prerequisites (dependencies: `fb-gen`, `openspec` CLI, `firebolt-sdk-gen` sibling repo)
  - The end-to-end workflow: propose → edit `.smithy` → lint → generate → verify
  - When and how to use `openspec` change management
  - When to use `rdke.quirks.toml` (and when NOT to — fix in the spec instead)
  - Verification commands (`fb-gen --lint`, `fb-gen --dry-run`, `fb-gen --emit bindings`)
- Update the **"Repository layout"** section to include `src/smithy/` and `openspec/`.
- Update the **"Authoring APIs"** section to reflect the Smithy IDL workflow (replacing/supplementing the OpenRPC-only description).

## Capabilities

### New Capabilities

- `rdke-howto`: Describes the RDKe-specific developer workflow for adding Firebolt APIs using the Smithy IDL toolchain and OpenSpec change management.

### Modified Capabilities

- `smithy-idl-canonical`: The existing requirement that IDL is canonical format is now surfaced in the README as normative guidance.

## Impact

- `README.md` — primary file modified (documentation only, no code change)
- No generated code affected
- No `.smithy` files changed
- No profile or quirks changes
