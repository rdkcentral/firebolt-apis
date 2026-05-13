## ADDED Requirements

### Requirement: Device module exposes room as a read-only property

The `device` module SHALL expose `room` as a `@propertyReadonly` operation returning `String`. The returned value represents the room name configured for the device (e.g. `"Living Room"`). Apps MAY subscribe to receive push notifications when the value changes.

#### Scenario: App reads the device room at startup

GIVEN an app has initialised the Firebolt transport  
WHEN the app calls `Device.room()`  
THEN the platform SHALL return the configured room name as a non-empty `String`

#### Scenario: Platform notifies the app when the room name changes

GIVEN an app has subscribed to `room` change notifications  
WHEN the user changes the device's room assignment (e.g. via a companion app or platform settings)  
THEN the platform SHALL push the new room name string to all subscribed apps
