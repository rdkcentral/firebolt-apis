## Why

TV and STB apps need to know the display's current refresh rate (e.g. 24 Hz, 50 Hz, 60 Hz, 120 Hz) to make frame-pacing and motion-smoothness decisions. The existing `Device` module exposes screen/video resolution but has no refresh rate API, forcing apps to use platform-specific workarounds.

## What Changes

- Add `Device.displayRefreshRate` as a new readonly property returning the active display refresh rate in Hz (e.g. `60.0`).
- Add `Device.onDisplayRefreshRateChanged` event so apps can react when the user or system changes the refresh rate (e.g. switching from 60 Hz to 24 Hz for film playback).

## Capabilities

### New Capabilities

- `display-refresh-rate`: Exposes the active display refresh rate and change notifications via the `Device` module.

### Modified Capabilities

<!-- No existing spec-level requirements are changing -->

## Impact

- `src/openrpc/device.json` — add `displayRefreshRate` getter method, `onDisplayRefreshRateChanged` event, and `DisplayRefreshRate` schema.
- `firebolt-cpp-client` — regenerated Device headers/impl via `build-stack.sh --change display-refresh-rate`.
- No breaking changes; purely additive.
