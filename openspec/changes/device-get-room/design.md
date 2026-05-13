Simple addition to an existing module (one new operation). Short rationale applies.

**Trait choice: `@propertyReadonly`**
The room assignment is configured by the user or platform administrator — apps cannot change it via the API. The value can change at runtime (user renames the room in a companion app), so `@propertyReadonly` (getter + subscriber) is correct rather than `@propertyImmutable` (getter only).

**Type decision: `String`**
Room names are free-form text set by the user (e.g. "Living Room", "Master Bedroom", "Bob's Office"). An enum would need to enumerate every possible room name and would break as users choose arbitrary names. `String` is the correct choice.

**Operation name: `room` not `getRoom`**
Firebolt property operations are named by their noun, not by a `get` prefix — consistent with `Device.id`, `Device.model`, `Device.name`, etc. The generated C++ getter is `DeviceImpl::room()`.

**Module placement: existing `device` module**
Room is a physical characteristic of the device placement — squarely within the `Device` module's responsibility alongside `name`, `uid`, and `model`.
