$version: "2"
namespace com.firebolt.lifecycle2

use com.firebolt#event

service Lifecycle2Service {
    version: "1.0"
    operations: [close, state, onStateChanged]
}

operation close {
    input: CloseInput
    output: CloseOutput
}

structure CloseInput {
    @required
    type: CloseType
}

structure CloseOutput {}

operation state {
    input: StateInput
    output: StateOutput
}

structure StateInput {
}

structure StateOutput {
    @required
    value: LifecycleState
}

@event
operation onStateChanged {
    input: OnStateChangedInput
    output: OnStateChangedOutput
}

structure OnStateChangedInput {
    history: StateChangeList
}

structure OnStateChangedOutput {
    @required
    value: StateChangeList
}

enum CloseType {
    DEACTIVATE = "deactivate"
    UNLOAD = "unload"
    KILL_RELOAD = "killReload"
    KILL_REACTIVATE = "killReactivate"
}

enum LifecycleState {
    INITIALIZING = "initializing"
    ACTIVE = "active"
    PAUSED = "paused"
    SUSPENDED = "suspended"
    HIBERNATED = "hibernated"
    TERMINATING = "terminating"
}

structure StateChange {
    newState: LifecycleState
    oldState: LifecycleState
}

list StateChangeList {
    member: StateChange
}
