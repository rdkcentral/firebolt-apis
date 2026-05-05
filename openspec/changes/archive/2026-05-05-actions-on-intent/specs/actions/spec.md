## ADDED Requirements

### Requirement: Actions module exposes onIntent as an event
The `actions` module SHALL expose `onIntent` as an `@event` operation delivering a
`String` intent value to subscribed listeners.

#### Scenario: App subscribes and receives an intent
- **WHEN** an app registers a listener on `onIntent`
- **THEN** the platform delivers the intent string to that listener each time an intent is received

#### Scenario: Platform fires event on intent change
- **WHEN** the platform receives or generates a new intent
- **THEN** all registered `onIntent` listeners are called with the intent string as the payload
