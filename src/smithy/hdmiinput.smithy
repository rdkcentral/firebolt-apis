$version: "2"
namespace com.firebolt.hdmiinput

use com.firebolt#event
use com.firebolt#property

service HdmiinputService {
    version: "1.0"
    operations: [ports, port, open, close, onConnectionChanged, onSignalChanged, lowLatencyMode, onAutoLowLatencyModeSignalChanged, autoLowLatencyModeCapable, edidVersion]
}

operation ports {
    input: PortsInput
    output: PortsOutput
}

structure PortsInput {
}

structure PortsOutput {
    @required
    value: HDMIInputPortList
}

operation port {
    input: PortInput
    output: PortOutput
}

structure PortInput {
    @required
    portId: HDMIPortId
}

structure PortOutput {
    @required
    value: HDMIInputPort
}

operation open {
    input: OpenInput
    output: OpenOutput
}

structure OpenInput {
    @required
    portId: HDMIPortId
}

structure OpenOutput {}

operation close {
    input: CloseInput
    output: CloseOutput
}

structure CloseInput {
}

structure CloseOutput {}

@event
operation onConnectionChanged {
    input: OnConnectionChangedInput
    output: OnConnectionChangedOutput
}

structure OnConnectionChangedInput {
}

structure OnConnectionChangedOutput {
    @required
    value: ConnectionChangedInfo
}

@event
operation onSignalChanged {
    input: OnSignalChangedInput
    output: OnSignalChangedOutput
}

structure OnSignalChangedInput {
}

structure OnSignalChangedOutput {
    @required
    value: SignalChangedInfo
}

@property
operation lowLatencyMode {
    input: LowLatencyModeInput
    output: LowLatencyModeOutput
}

structure LowLatencyModeInput {
}

structure LowLatencyModeOutput {
    @required
    value: Boolean
}

@event
operation onAutoLowLatencyModeSignalChanged {
    input: OnAutoLowLatencyModeSignalChangedInput
    output: OnAutoLowLatencyModeSignalChangedOutput
}

structure OnAutoLowLatencyModeSignalChangedInput {
}

structure OnAutoLowLatencyModeSignalChangedOutput {
    @required
    value: AutoLowLatencyModeSignalChangedInfo
}

@property
operation autoLowLatencyModeCapable {
    input: AutoLowLatencyModeCapableInput
    output: AutoLowLatencyModeCapableOutput
}

structure AutoLowLatencyModeCapableInput {
    @required
    port: HDMIPortId
}

structure AutoLowLatencyModeCapableOutput {
    @required
    value: Boolean
}

@property
operation edidVersion {
    input: EdidVersionInput
    output: EdidVersionOutput
}

structure EdidVersionInput {
    @required
    port: HDMIPortId
}

structure EdidVersionOutput {
    @required
    value: EDIDVersion
}

structure AutoLowLatencyModeSignalChangedInfo {
    autoLowLatencyModeSignalled: Boolean
    port: HDMIPortId
}

structure ConnectionChangedInfo {
    connected: Boolean
    port: HDMIPortId
}

enum EDIDVersion {
    UNKNOWN = "unknown"
    V1_4 = "v1_4"
    V2_0 = "v2_0"
}

structure HDMIInputPort {
    @required
    arcCapable: Boolean
    @required
    arcConnected: Boolean
    @required
    autoLowLatencyModeCapable: Boolean
    @required
    autoLowLatencyModeSignalled: Boolean
    @required
    connected: Boolean
    @required
    edidVersion: EDIDVersion
    @required
    port: HDMIPortId
    @required
    signal: HDMISignalStatus
}

// TODO: alias HDMIPortId = String (Smithy has no direct alias — use a newtype structure or inline the target)

enum HDMISignalStatus {
    NONE = "none"
    STABLE = "stable"
    UNKNOWN = "unknown"
    UNSTABLE = "unstable"
    UNSUPPORTED = "unsupported"
}

structure SignalChangedInfo {
    @required
    port: HDMIPortId
    @required
    signal: HDMISignalStatus
}

list HDMIInputPortList {
    member: HDMIInputPort
}
