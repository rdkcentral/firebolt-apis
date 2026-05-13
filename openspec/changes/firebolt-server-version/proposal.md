## Why

Apps communicating with the Firebolt platform sometimes need to know the exact version of the Firebolt server (gateway) they are connected to — for feature detection, diagnostic logging, and version-gated behaviour. There is currently no standard API for this; apps either parse banner strings or rely on out-of-band configuration.

## What Changes

- Create a new `firebolt` module exposing `serverVersion` as a read-only property that returns the running Firebolt server version as a string (e.g. `"2.3.1"`).
- Apps can call `Firebolt.serverVersion()` to read the current value. The platform owns this value; apps cannot set it.

## Capabilities

### New Capabilities

- `firebolt-server-version`: Exposes the Firebolt gateway server version via the `firebolt` module.

### Modified Capabilities

<!-- No existing spec-level requirements are changing -->

## Impact

- `src/smithy/firebolt.smithy` — new module file with `FireboltService` service and `serverVersion` `@propertyReadonly` operation returning `String`.
- `openspec/rdke.profile.yaml` — add `firebolt` to the `smithy-canonical` modules list.
- No breaking changes; purely additive (new module).
