## 1. IDL

- [ ] 1.1 Edit `src/smithy/<module>.smithy` — add `<operation>` operation with resolved trait and types
- [ ] 1.2 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --dry-run` (validates Smithy IDL; `--lint --input` is JSON-only)
  <!-- paste output here -->

## 2. Type correctness

- [ ] 2.1 All non-negative integer fields use `UInt32` (not `Integer` or bare number)
- [ ] 2.2 No shape name is prefixed with the module name (e.g. `Volume` not `<Module>Volume`)
- [ ] 2.3 All enum shapes have named variants (no auto-generated `V0`, `V1`...)

## 3. Composition validation

- [ ] 3.1 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --dry-run` — method count increased by `+<N>`
  <!-- paste output here -->
- [ ] 3.2 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --lang cpp --emit bindings --output /tmp/gen/`
  <!-- paste output here -->

## 4. Test generation

- [ ] 4.1 **VERIFY** `fb-gen --input src/smithy/<module>.smithy --lang test --output /tmp/gen-test/ --schemas src/schemas/`
  <!-- paste output here -->
- [ ] 4.2 If any test functions were generated (setter fuzz seeds or event dispatch),
      compile to confirm syntax: `g++ -std=c++17 -fsyntax-only -I/tmp/gen-test/include -I<transport>/include /tmp/gen-test/src/<module>_test.cpp`
  <!-- paste output here, or N/A if no test functions were generated (expected for @propertyReadonly with no constraints) -->

## 5. Quirks discipline

- [ ] 5.1 No new `[spec-bug]` entries added to `openspec/rdke.quirks.toml` (fix type errors in `.smithy` instead)
- [ ] 5.2 Any new `[platform-dev]` entry has a justification comment explaining why the platform genuinely differs
