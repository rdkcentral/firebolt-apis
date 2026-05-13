## 1. IDL

- [x] 1.1 Edit `src/smithy/device.smithy` — add `room` to the `DeviceService` operations list; add `@propertyReadonly operation room` with `RoomInput` (empty) and `RoomOutput { @required value: String }`
- [x] 1.2 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --dry-run` (validates Smithy IDL)
  <!-- [device] 22 methods, 8 schemas (was 21). No errors. -->

## 2. Type correctness

- [x] 2.1 All non-negative integer fields use `UInt32` — no integers in this operation
- [x] 2.2 No shape name is prefixed with the module name (`Room` not `DeviceRoom`)
- [x] 2.3 All enum shapes have named variants — no enums in this operation

## 3. Composition validation

- [x] 3.1 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --dry-run` — method count for `[device]` increased by `+2` (`room` getter + `subscribeOnRoomChanged`)
  <!-- [device] 22 methods (was 21 raw ops → +2 emitted: room() + subscribeOnRoom() with subscribeOnRoomChanged() legacy alias). -->
- [x] 3.2 **VERIFY** `fb-gen --profile openspec/rdke.profile.yaml --lang cpp --emit bindings --output /tmp/gen/`
  <!-- device.json → Device (22 methods, 7 types, 0 ext-deps). Generated: DeviceImpl::room(), subscribeOnRoom(), subscribeOnRoomChanged() legacy alias in IDevice. No errors. -->

## 4. Test generation

- [x] 4.1 **VERIFY** `fb-gen --input src/smithy/device.smithy --lang test --output /tmp/gen-test/ --schemas src/schemas/`
  <!-- device.smithy → Device (22 methods, 7 types, 0 ext-deps). 4 test functions generated: name_fuzz_seed, onDeviceNameChanged_registration, onDeviceNameChanged_dispatch, provision_fuzz_seed. No room() test function (expected: @propertyReadonly with no constraints). -->
- [x] 4.2 If any test functions were generated, compile to confirm syntax
  <!-- g++ -std=c++17 -fsyntax-only device_test.cpp → OK. Note: compile requires --lang cpp bindings in same output dir to provide device_impl.h. -->

## 5. Quirks discipline

- [x] 5.1 No new `[spec-bug]` entries added to `openspec/rdke.quirks.toml`
- [x] 5.2 No `[platform-dev]` entries needed — `room` is expected to be available on all platforms
