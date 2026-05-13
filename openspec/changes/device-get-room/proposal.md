## Why

Apps running on Firebolt devices sometimes need to know which room of the home the device is physically located in (e.g. "Living Room", "Bedroom", "Kitchen") — for personalisation, content recommendations, and voice-assistant context. There is currently no standard Firebolt API for this; apps must rely on out-of-band configuration or proprietary extensions.

## What Changes

- Add `Device.room` as a new read-only property that returns the room name configured for the device as a `String` (e.g. `"Living Room"`).
- Apps can call `Device.room()` to read the current value and subscribe to `subscribeOnRoomChanged()` to be notified if the user changes the room setting.

> **Naming note:** Following Firebolt's property-naming convention, the operation is named `room` (not `getRoom`). The generated getter is `Device.room()` and the subscriber is `Device.subscribeOnRoomChanged()`.

## Capabilities

### New Capabilities

- `device-room`: Exposes the configured room name for the device via the `Device` module.

### Modified Capabilities

<!-- No existing spec-level requirements are changing -->

## Impact

- `src/smithy/device.smithy` — add `room` operation with `@propertyReadonly` trait; add `RoomInput` / `RoomOutput` shapes.
- No breaking changes; purely additive.
