$version: "2"
namespace com.firebolt.capabilities

use com.firebolt#event

service CapabilitiesService {
    version: "1.0"
    operations: [supported, available, permitted, granted, info, request, onAvailable, onUnavailable, onGranted, onRevoked]
}

operation supported {
    input: SupportedInput
    output: SupportedOutput
}

structure SupportedInput {
    @required
    capability: Capability
}

structure SupportedOutput {
    @required
    value: Boolean
}

operation available {
    input: AvailableInput
    output: AvailableOutput
}

structure AvailableInput {
    @required
    capability: Capability
}

structure AvailableOutput {
    @required
    value: Boolean
}

operation permitted {
    input: PermittedInput
    output: PermittedOutput
}

structure PermittedInput {
    @required
    capability: Capability
    options: CapabilityOption
}

structure PermittedOutput {
    @required
    value: Boolean
}

operation granted {
    input: GrantedInput
    output: GrantedOutput
}

structure GrantedInput {
    @required
    capability: Capability
    options: CapabilityOption
}

structure GrantedOutput {
    value: Boolean
}

operation info {
    input: InfoInput
    output: InfoOutput
}

structure InfoInput {
    @required
    capabilities: CapabilityList
}

structure InfoOutput {
    @required
    value: CapabilityInfoList
}

operation request {
    input: RequestInput
    output: RequestOutput
}

structure RequestInput {
    @required
    grants: PermissionList
}

structure RequestOutput {
    @required
    value: CapabilityInfoList
}

@event
operation onAvailable {
    input: OnAvailableInput
    output: OnAvailableOutput
}

structure OnAvailableInput {
    @required
    capability: Capability
}

structure OnAvailableOutput {
    @required
    value: CapabilityInfo
}

@event
operation onUnavailable {
    input: OnUnavailableInput
    output: OnUnavailableOutput
}

structure OnUnavailableInput {
    @required
    capability: Capability
}

structure OnUnavailableOutput {
    @required
    value: CapabilityInfo
}

@event
operation onGranted {
    input: OnGrantedInput
    output: OnGrantedOutput
}

structure OnGrantedInput {
    @required
    capability: Capability
    @required
    role: Role
}

structure OnGrantedOutput {
    @required
    value: CapabilityInfo
}

@event
operation onRevoked {
    input: OnRevokedInput
    output: OnRevokedOutput
}

structure OnRevokedInput {
    @required
    capability: Capability
    @required
    role: Role
}

structure OnRevokedOutput {
    @required
    value: CapabilityInfo
}

// TODO: alias Capability = String (Smithy has no direct alias — use a newtype structure or inline the target)

structure CapabilityInfo {
    @required
    available: Boolean
    capability: Capability
    @required
    manage: String
    @required
    provide: String
    @required
    supported: Boolean
    @required
    use: String
}

structure CapabilityOption {
    role: Role
}

structure Permission {
    @required
    capability: Capability
    role: Role
}

enum Role {
    M_A_N_A_G_E = "MANAGE"
    P_R_O_V_I_D_E = "PROVIDE"
    U_S_E = "USE"
}

list CapabilityList {
    member: Capability
}

list CapabilityInfoList {
    member: CapabilityInfo
}

list PermissionList {
    member: Permission
}
