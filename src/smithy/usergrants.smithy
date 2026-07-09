$version: "2"
namespace com.firebolt.usergrants

service UsergrantsService {
    version: "1.0"
    operations: [app, device, capability, grant, deny, clear, request]
}

operation app {
    input: AppInput
    output: AppOutput
}

structure AppInput {
    @required
    appId: String
}

structure AppOutput {
    @required
    value: GrantInfoList
}

operation device {
    input: DeviceInput
    output: DeviceOutput
}

structure DeviceInput {
}

structure DeviceOutput {
    @required
    value: GrantInfoList
}

operation capability {
    input: CapabilityInput
    output: CapabilityOutput
}

structure CapabilityInput {
    @required
    capability: Capability
}

structure CapabilityOutput {
    @required
    value: GrantInfoList
}

operation grant {
    input: GrantInput
    output: GrantOutput
}

structure GrantInput {
    @required
    capability: Capability
    options: GrantModificationOptions
    @required
    role: Role
}

structure GrantOutput {}

operation deny {
    input: DenyInput
    output: DenyOutput
}

structure DenyInput {
    @required
    capability: Capability
    options: GrantModificationOptions
    @required
    role: Role
}

structure DenyOutput {}

operation clear {
    input: ClearInput
    output: ClearOutput
}

structure ClearInput {
    @required
    capability: Capability
    options: GrantModificationOptions
    @required
    role: Role
}

structure ClearOutput {}

operation request {
    input: RequestInput
    output: RequestOutput
}

structure RequestInput {
    @required
    appId: String
    options: RequestOptions
    @required
    permissions: PermissionList
}

structure RequestOutput {
    @required
    value: GrantInfoList
}

structure AppInfo {
    @required
    id: String
    title: String
}

structure Capability {
    @required
    value: String
}

structure GrantInfo {
    app: AppInfo
    @required
    capability: Capability
    expires: String
    @required
    lifespan: String
    @required
    role: Role
    @required
    state: GrantState
}

structure GrantModificationOptions {
    appId: String
}

enum GrantState {
    DENIED = "denied"
    GRANTED = "granted"
}

structure Permission {
    @required
    capability: Capability
    role: Role
}

structure RequestOptions {
    force: Boolean
}

enum Role {
    M_A_N_A_G_E = "MANAGE"
    P_R_O_V_I_D_E = "PROVIDE"
    U_S_E = "USE"
}

list GrantInfoList {
    member: GrantInfo
}

list PermissionList {
    member: Permission
}
