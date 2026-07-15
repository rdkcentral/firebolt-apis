$version: "2"
namespace com.firebolt.lifecycle

use com.firebolt#capability
use com.firebolt#event

service LifecycleService {
    version: "1.0"
    operations: [close, onInactive, onForeground, onBackground, onSuspended, onUnloading]
}

@capability(uses: ["xrn:firebolt:capability:lifecycle:state"])
operation close {
    input: CloseInput
    output: CloseOutput
}

structure CloseInput {
    @required
    reason: CloseReason
}

structure CloseOutput {}

@capability(uses: ["xrn:firebolt:capability:lifecycle:state"])
@event
operation onInactive {
    input: OnInactiveInput
    output: OnInactiveOutput
}

structure OnInactiveInput {
}

structure OnInactiveOutput {
    @required
    value: LifecycleEvent
}

@capability(uses: ["xrn:firebolt:capability:lifecycle:state"])
@event
operation onForeground {
    input: OnForegroundInput
    output: OnForegroundOutput
}

structure OnForegroundInput {
}

structure OnForegroundOutput {
    @required
    value: LifecycleEvent
}

@capability(uses: ["xrn:firebolt:capability:lifecycle:state"])
@event
operation onBackground {
    input: OnBackgroundInput
    output: OnBackgroundOutput
}

structure OnBackgroundInput {
}

structure OnBackgroundOutput {
    @required
    value: LifecycleEvent
}

@capability(uses: ["xrn:firebolt:capability:lifecycle:state"])
@event
operation onSuspended {
    input: OnSuspendedInput
    output: OnSuspendedOutput
}

structure OnSuspendedInput {
}

structure OnSuspendedOutput {
    @required
    value: LifecycleEvent
}

@capability(uses: ["xrn:firebolt:capability:lifecycle:state"])
@event
operation onUnloading {
    input: OnUnloadingInput
    output: OnUnloadingOutput
}

structure OnUnloadingInput {
}

structure OnUnloadingOutput {
    @required
    value: LifecycleEvent
}

enum CloseReason {
    D_O_N_E = "DONE"
    E_R_R_O_R = "ERROR"
    M_E_D_I_A__E_N_D_E_D = "MEDIA_ENDED"
    R_E_M_O_T_E__B_U_T_T_O_N = "REMOTE_BUTTON"
    U_S_E_R__E_X_I_T = "USER_EXIT"
}

structure LifecycleEvent {
    @required
    previous: LifecycleState
    source: String
    @required
    state: LifecycleState
}

enum LifecycleState {
    B_A_C_K_G_R_O_U_N_D = "BACKGROUND"
    F_O_R_E_G_R_O_U_N_D = "FOREGROUND"
    I_N_A_C_T_I_V_E = "INACTIVE"
    I_N_I_T_I_A_L_I_Z_I_N_G = "INITIALIZING"
    S_U_S_P_E_N_D_E_D = "SUSPENDED"
    U_N_L_O_A_D_I_N_G = "UNLOADING"
}
