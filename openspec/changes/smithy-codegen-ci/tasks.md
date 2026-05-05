# Tasks: smithy-codegen-ci

Track CI integration of `fb-gen` Smithy→OpenRPC and Smithy→C++ codegen steps.

## Context

`fb-gen --profile openspec/rdke.profile.yaml --lang openrpc` now works end-to-end.
Validation fails only on missing `examples` fields (structural output is correct).
Next step: wire both codegen outputs into CI so regressions are caught automatically.

---

## 1. Smithy → OpenRPC CI step

**Objective**: Ensure the Smithy source can always generate valid OpenRPC output, so the
Smithy spec remains the canonical source of truth and drift is caught in CI.

- [ ] **1.1** Add `@examples` trait support to `fb-frontend-smithy` IDL parser
  (parse `@examples([{...}])` blocks on operations)
- [ ] **1.2** Emit `examples` array on each method in `fb-backend-openrpc`
  (use first example as "Default Example" in the OpenRPC format)
- [ ] **1.3** Add CI job step (or separate job) that runs:
  ```
  fb-gen --profile openspec/rdke.profile.yaml --lang openrpc --output /tmp/gen-openrpc/
  node_modules/.bin/firebolt-openrpc validate --input /tmp/gen-openrpc/<module>.openrpc.json --schemas src/schemas
  ```
  for each generated module, failing the build if any module fails validation
- [ ] **1.4** Consider replacing `src/openrpc/*.json` hand-authored files with the
  generated ones as the source fed to `npm run compile` (makes Smithy the true single
  source of truth for the JS pipeline too)

## 2. Smithy → C++ client CI step

**Objective**: Ensure the Smithy source can always generate compilable C++ client bindings,
catching API regressions before they reach the C++ SDK consumers.

- [ ] **2.1** Identify target output directory for generated C++ headers/sources
  (likely `src/sdks/cpp/` or a sibling repo — confirm with team)
- [ ] **2.2** Add CI job step that runs:
  ```
  fb-gen --profile openspec/rdke.profile.yaml --lang cpp --output /tmp/gen-cpp/
  ```
  and verifies the command exits 0 (i.e., generation succeeds with no errors/warnings)
- [ ] **2.3** Add a compile-check step: build the generated C++ headers against a minimal
  stub to confirm they are syntactically valid (e.g., `g++ -fsyntax-only`)
- [ ] **2.4** Wire into the existing CI workflow alongside the OpenRPC validation step

## 3. `@examples` trait in Smithy files

**Objective**: Populate example values in all Smithy module files so that
generated OpenRPC passes `firebolt-openrpc validate` without hand-authored
`src/openrpc/*.json` files.

- [ ] **3.1** Define `@examples` trait in `openspec/rdke.profile.yaml` or a shared
  Smithy prelude so it is available across all modules
- [ ] **3.2** Add at least one `@examples` entry per operation in each `.smithy` file
  under `src/smithy/` (can be done module-by-module, prioritise high-traffic modules:
  `device`, `lifecycle`, `capabilities`, `account`)
- [ ] **3.3** Verify `npm run validate:each` passes on the generated output for all
  modules that have examples populated
