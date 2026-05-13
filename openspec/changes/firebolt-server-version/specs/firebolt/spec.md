## ADDED Requirements

### Requirement: Firebolt module exposes serverVersion as a read-only property

The `firebolt` module SHALL expose `serverVersion` as a `@propertyReadonly` operation returning `String`. The returned value represents the version of the running Firebolt server (e.g. `"2.3.1"`). Apps MAY subscribe to receive push notifications when the value changes.

#### Scenario: App reads the server version at startup

GIVEN an app has initialised the Firebolt transport  
WHEN the app calls `Firebolt.serverVersion()`  
THEN the platform SHALL return the current server version as a non-empty `String`

#### Scenario: Platform notifies the app when the server version changes

GIVEN an app has subscribed to `serverVersion` change notifications  
WHEN the Firebolt server version changes (e.g. due to a live platform update)  
THEN the platform SHALL push the new version string to all subscribed apps
