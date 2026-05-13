This is a simple new-module change (one operation). Short rationale applies.

**Trait choice: `@propertyReadonly`**
The server version is owned entirely by the platform — an app cannot set or influence it. The value could change if the platform performs a live update, so `@propertyReadonly` (getter + subscriber) is appropriate rather than `@propertyImmutable` (getter only). If the platform guarantees the version never changes during a session, this can be downgraded to `@propertyImmutable` in a follow-up.

**Type decision: `String`**
The caller asked for a free-form version string (e.g. `"2.3.1"`). A structured type would be over-engineering at this stage — apps typically need the version for logging or a simple equality check, not arithmetic on parts. A `String` is the lightest correct choice.

**Module placement: new `firebolt` module**
The value describes the Firebolt platform itself, not a specific device subsystem. Placing it in a thin `firebolt` module keeps the API clearly scoped and avoids polluting `device` (which is about hardware) or `lifecycle` (which is about app lifecycle).
