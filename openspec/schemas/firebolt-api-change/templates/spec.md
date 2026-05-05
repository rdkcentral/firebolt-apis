## ADDED Requirements

### Requirement: <module> exposes <operationName> <!-- as a @trait / as a plain call -->
The `<module>` module SHALL expose `<operationName>` <!-- as a `@propertyReadonly` / `@property` / `@propertyImmutable` / `@event` --> operation returning `<Type>`.
<!-- For @propertyReadonly/@property: Apps MAY subscribe to receive push notifications when the value changes. -->
<!-- For @property: Apps MAY set this value; the platform SHALL persist and broadcast the change. -->

#### Scenario: <!-- describe the primary app interaction -->
- **WHEN** <!-- app calls or subscribes -->
- **THEN** <!-- observable result -->

#### Scenario: <!-- describe the subscribe/push behaviour if applicable -->
- **WHEN** <!-- platform value changes -->
- **THEN** <!-- subscriber receives notification -->
