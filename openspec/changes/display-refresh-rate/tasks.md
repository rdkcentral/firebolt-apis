## 1. Schema

- [x] 1.1 Add `DisplayRefreshRate` schema to `src/openrpc/device.json` components: `{ "type": "number", "description": "The display refresh rate in Hz" }`

## 2. OpenRPC spec — Device module

- [x] 2.1 Add `displayRefreshRate` method to `src/openrpc/device.json`: readonly property tagged `property:readonly`, no params, result `$ref: DisplayRefreshRate`
- [x] 2.2 Add `onDisplayRefreshRateChanged` event method: tagged `event`, no params, result `$ref: DisplayRefreshRate`

## 3. Shadow Comparison Setup (Gate 2c)

- [x] 3.1 Create `.legacy-impl` sidecar at `openspec/changes/display-refresh-rate/.legacy-impl`
      Contains: `device  device_impl.h  Firebolt::Device::DeviceImpl`
- [ ] 3.2 Remediate legacy `firebolt-cpp-client` DeviceImpl to compile against current `IDevice`
      Required changes (found by Gate 2c):
      - Remove `chipsetId()`, `timeInActiveState()`, `uptime()`, `deviceClass()` — removed from spec
      - Rename `HDRFormat` → `HDRFormatMap` in `hdr()` return type and `subscribeOnHdrChanged` → `subscribeOnHdr` signature
      Files: `firebolt-cpp-client/src/device_impl.h`, `firebolt-cpp-client/src/device_impl.cpp`
- [ ] 3.3 Re-run Gate 2c and confirm 0 mismatches
      Command: `fb-gen --lang compare --input device.json --legacy-impl "device_impl.h:Firebolt::Device::DeviceImpl"`
- [ ] 3.4 Update `compat.md` Verification section — replace ⚠ with ✓ result
