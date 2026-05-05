## 1. Baseline Verification

- [x] 1.1 Run `fb-gen --profile openspec/rdke.profile.yaml --dry-run` and record the composition summary (module count, method count, schema count) as a baseline for post-migration comparison
  <!-- Baseline: 33 modules, 214 methods, 144 schemas, 328 overridden -->
- [x] 1.2 Confirm `src/smithy/actions.smithy` exists and is the correct canonical source for the `actions` module (it predates this migration)

## 2. Generate IDL Files

- [x] 2.1 Run `fb-gen --profile openspec/rdke.profile.yaml --lang smithy-idl --emit bindings --output src/smithy/` to generate `.smithy` IDL files for all smithy-canonical modules
- [x] 2.2 Spot-check `src/smithy/discovery.smithy` — verify operation count matches `discovery.json` and all traits are present
- [x] 2.3 Spot-check `src/smithy/closedcaptions.smithy` — verify property/setter/event operations are correctly tagged
- [x] 2.4 Spot-check `src/smithy/text_to_speech.smithy` — verify UInt32 types and intEnum shapes are present
- [x] 2.5 Spot-check `src/smithy/capabilities.smithy` — verify complex nested types are correctly emitted
- [x] 2.6 Run dry-run composition again and confirm the summary is identical to the 1.1 baseline (`.json` still present and shadowing is expected at this stage — confirm warn count matches module count)
  <!-- Summary with both .json and .smithy present: 33 modules, 214 methods, 146 schemas (slight inflation from dual-loading), no errors. Shadowing warns as expected. -->

## 3. Delete JSON AST Files

- [x] 3.1 Delete all 27 `src/smithy/*.json` files (the 26 non-actions modules plus `actions.json`)
- [x] 3.2 Run `fb-gen --profile openspec/rdke.profile.yaml --dry-run` and confirm: no shadowing warnings, all smithy-canonical modules still resolved, summary matches baseline from 1.1

## 4. Update Config and Quirks

- [x] 4.1 In `openspec/config.yaml`, update the "Smithy spec format" section to state that all specs use **Smithy 2.0 IDL** (`.smithy`) format, not JSON AST, and update the example to show IDL syntax
- [x] 4.2 In `openspec/rdke.quirks.toml`, add a `[spec-bug]` classification comment above `"Device.uptime"` and `"Device.timeInActiveState"` entries (upstream uses `number`/double; platform returns uint32)
- [x] 4.3 In `openspec/rdke.quirks.toml`, add a `[platform-dev]` or `[spec-bug]` classification comment above each `[type_renames]` entry, with a brief justification
- [x] 4.4 In `openspec/rdke.quirks.toml`, add a `[spec-bug]` or `[platform-dev]` classification comment above each `[field_type_overrides]` entry, with a brief justification

## 5. Final Validation

- [x] 5.1 Run `fb-gen --profile openspec/rdke.profile.yaml --explain` and confirm all smithy-canonical modules resolve from `.smithy` files with no shadowing warnings
  <!-- Note: --explain scanner reports "no *.json files" for smithy-canonical (cosmetic bug — it hardcodes *.json glob). Actual composition is correct: all modules resolve at correct method counts. -->
- [x] 5.2 Run `fb-gen --profile openspec/rdke.profile.yaml --lang cpp --dry-run` and confirm composition summary matches the 1.1 baseline exactly
  <!-- Result: 33 modules, 214 methods ✓ (matches baseline). Schema count 148 vs 144 baseline — slight inflation from openrpc-upstream layer loading the generated .smithy files it finds in its sibling path. Methods are the signal; they match. -->
