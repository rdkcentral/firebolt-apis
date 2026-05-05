## 1. Update Repository Layout Section

- [x] 1.1 In `README.md`, update the "Repository layout" code block to add `src/smithy/` (canonical Smithy 2.0 IDL specs) and `openspec/` (change management) entries
- [x] 1.2 Verify the updated layout block still accurately describes `src/openrpc/` as upstream reference (not primary source)

## 2. Add Prerequisites Section

- [x] 2.1 Add a "Prerequisites (RDKe toolchain)" subsection listing: `fb-gen` binary from `firebolt-sdk-gen` (sibling repo), `openspec` CLI, and the `firebolt-sdk-gen` repo must be cloned as a sibling directory
- [x] 2.2 Include the install command for `fb-gen`: `cargo install --path crates/fb-gen` from the `firebolt-sdk-gen` directory
- [x] 2.3 Include the install command for `openspec` (or note where it comes from if installed differently)

## 3. Add End-to-End API Authoring Workflow Section

- [x] 3.1 Add a new top-level section "Adding a new API (RDKe toolchain)" to `README.md`
- [x] 3.2 Step 1 — Propose the change: document `openspec new change "<name>"` and the three `/opsx:` commands (`propose`, `apply`, `archive`) with one-line descriptions
- [x] 3.3 Step 2 — Edit the `.smithy` file: document the `src/smithy/<module>.smithy` file as the edit target; include the minimal IDL skeleton (namespace, service, operation, structure)
- [x] 3.4 Step 3 — Lint: document `fb-gen --lint --input src/smithy/<module>.smithy` with expected output
- [x] 3.5 Step 4 — Validate composition: document `fb-gen --profile openspec/rdke.profile.yaml --dry-run` showing modules/methods count
- [x] 3.6 Step 5 — Generate bindings: document `fb-gen --profile openspec/rdke.profile.yaml --lang cpp --emit bindings --output /tmp/gen/` as verification step
- [x] 3.7 Add a note that `.json` Smithy JSON AST files SHALL NOT be created; IDL is the canonical format

## 4. Add Quirks Policy Subsection

- [x] 4.1 Add a "Quirks file policy" subsection explaining `openspec/rdke.quirks.toml` as a transitional debt register
- [x] 4.2 Document the three entry categories: `[spec-bug]`, `[bad-ident]`, `[platform-dev]`
- [x] 4.3 State the rule: spec bugs and bad identifiers MUST be fixed in the `.smithy` file, not papered over with quirk entries; new quirk entries require a `[platform-dev]` justification

## 5. Verify README is Self-Consistent

- [x] 5.1 Read the full updated `README.md` to confirm the new section does not contradict the existing OpenRPC/npm workflow section
- [x] 5.2 Confirm every shell command in the new sections is runnable (not referencing placeholder paths that don't exist)
- [x] 5.3 Confirm the "Authoring APIs" section for OpenRPC still makes sense alongside the new Smithy section (add a one-line forward-reference if needed)
