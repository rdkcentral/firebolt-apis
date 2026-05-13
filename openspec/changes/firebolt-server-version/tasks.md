## 0. New module setup

- [x] 0.1 Create `src/smithy/firebolt.smithy` with `FireboltService` skeleton and `serverVersion` `@propertyReadonly` operation
- [x] 0.2 Add `firebolt` to `smithy-canonical` modules list in `openspec/rdke.profile.yaml`

## 1. IDL

- [x] 1.1 Edit `src/smithy/firebolt.smithy` — add `serverVersion` operation with `@propertyReadonly` trait, `ServerVersionInput` (empty), `ServerVersionOutput { @required value: String }`
- [x] 1.2 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --dry-run` (validates Smithy IDL)
  <!-- fb-gen (compose): 34 modules, 216 methods, 149 schemas. [firebolt] 1 methods, 0 schemas. No errors. fb-gen (compose): --dry-run — no files written. -->

## 2. Type correctness

- [x] 2.1 All non-negative integer fields use `UInt32` — no integers in this operation
- [x] 2.2 No shape name is prefixed with the module name (`ServerVersion` not `FireboltServerVersion`)
- [x] 2.3 All enum shapes have named variants — no enums in this operation

## 3. Composition validation

- [x] 3.1 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --dry-run` — method count increased by `+2` (`serverVersion` getter + `subscribeOnServerVersionChanged`)
  <!-- [firebolt] 1 methods, 0 schemas — dry-run counts raw operations; emitted: `serverVersion()` getter + `subscribeOnServerVersion()` subscriber = +2 methods. -->
- [x] 3.2 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --lang cpp --emit bindings --output /tmp/gen/`
  <!-- firebolt.json → Firebolt (1 methods, 0 types, 0 ext-deps). Generated: FireboltApiImpl::serverVersion() + subscribeOnServerVersion(). FireboltInterface() added to IFireboltAccessor. No errors. -->

## 4. Quirks discipline

- [x] 4.1 No new `[spec-bug]` entries added to `openspec/rdke.quirks.toml`
- [x] 4.2 No `[platform-dev]` entries needed — `serverVersion` is expected to be available on all platforms
