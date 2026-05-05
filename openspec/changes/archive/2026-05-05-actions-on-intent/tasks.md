## 1. IDL

- [x] 1.1 Edit `src/smithy/actions.smithy` — add `onIntent` event operation and shapes
- [x] 1.2 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --dry-run`:
  <!-- NOTE: --lint --input does not support .smithy files (JSON-only). Validation is via --dry-run.
       [actions] 2 methods, 0 schemas — total methods: 215 (was 214) — no errors -->

## 2. Type correctness

- [x] 2.1 All non-negative integers use `UInt32` (not `Integer` or `int`) — no integers used
- [x] 2.2 No shape name prefixed with the module name — shapes are `OnIntentInput`, `OnIntentOutput` ✓
- [x] 2.3 All enums have named variants (not applicable — no enum used)

## 3. Composition validation

- [x] 3.1 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --dry-run` — method count +1:
  <!-- [actions] 2 methods (was 1); total 215 methods (was 214) — no errors -->
- [x] 3.2 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --lang cpp --emit bindings --output /tmp/gen/`:
  <!-- fb-gen (compose): wrote firebolt.h + firebolt.cpp + FireboltSDK.cmake (33 modules)
       Generated: subscribeOnIntent(std::function<void(const std::string&)>&&) in include/firebolt/actions.h -->

## 4. Quirks discipline

- [x] 4.1 No new `[spec-bug]` entries added to `openspec/rdke.quirks.toml` (fix in `.smithy` instead)
- [x] 4.2 Any new `[platform-dev]` entry has a justification comment — no new entries added
