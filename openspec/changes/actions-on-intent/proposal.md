## Module

actions

## Operation

onIntent

## What it does

The platform fires an `onIntent` event to registered listeners whenever a new intent is
received. Apps subscribe to this event to react to intent changes without polling.

## Resolved trait

`@event`

Reason: The platform initiates the push — apps register a handler and the platform calls
it when an intent arrives. The app does not request the value; it is delivered at runtime.
This is the Firebolt event pattern (`@event`), not a property.

## Return type

`String`

Reason: The user confirmed the payload is "just the intent string". No structure needed;
a single required `String` field carries the intent value.

## Firebolt capability

`xrn:firebolt:capability:actions:intent`

Derived from the module name following the standard pattern. No existing capability string
is assigned to this event.

## Scope

Adding to existing module (`src/smithy/actions.smithy` already exists with one operation: `start`)

## What Changes

- `onIntent` event operation added to `ActionsService` in `src/smithy/actions.smithy`
- `OnIntentInput` and `OnIntentOutput` shapes added (output carries `intent: String`)
- `@event` trait applied to the operation
- New capability `xrn:firebolt:capability:actions:intent` declared

## Capabilities

### New Capabilities

actions: `onIntent` event — platform notifies registered listeners when an intent changes

### Modified Capabilities

(none — `start` operation is unchanged)

## Impact

- `src/smithy/actions.smithy` — add `onIntent` operation and shapes
- `openspec/rdke.profile.yaml` — no change (actions module already included)
- Generated bindings: C++, Rust, JS will gain an `onIntent` subscriber entry point
