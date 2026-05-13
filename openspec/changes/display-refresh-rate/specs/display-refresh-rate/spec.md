## ADDED Requirements

### Requirement: DisplayRefreshRate Property
The `Device` module SHALL expose a `displayRefreshRate` readonly property that returns the current active display refresh rate in Hz as a floating-point number.

#### Scenario: Get current refresh rate
- **WHEN** an app calls `Device.displayRefreshRate()`
- **THEN** the platform SHALL return the current display refresh rate in Hz (e.g. `60.0`, `23.976`, `120.0`)

#### Scenario: Value reflects active output rate
- **WHEN** the display is operating at a given refresh rate
- **THEN** `displayRefreshRate` SHALL return that rate regardless of what was requested

### Requirement: DisplayRefreshRateChanged Event
The `Device` module SHALL emit an `onDisplayRefreshRateChanged` event whenever the active display refresh rate changes.

#### Scenario: Rate change notification
- **WHEN** the platform changes the display refresh rate (e.g., switching from 60 Hz to 24 Hz for film playback)
- **THEN** all registered `onDisplayRefreshRateChanged` listeners SHALL be called with the new refresh rate value (Hz, float)

#### Scenario: Subscribe returns subscription ID
- **WHEN** an app subscribes to `onDisplayRefreshRateChanged`
- **THEN** the platform SHALL return a valid subscription ID that can be used to unsubscribe
