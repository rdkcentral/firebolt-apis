$version: "2"
namespace com.firebolt.authentication

service AuthenticationService {
    version: "1.0"
    operations: [token, device, session, root]
}

operation token {
    input: TokenInput
    output: TokenOutput
}

structure TokenInput {
    options: String
    @required
    type: TokenType
}

structure TokenOutput {
    @required
    value: AuthenticationTokenResult
}

operation device {
    input: DeviceInput
    output: DeviceOutput
}

structure DeviceInput {
}

structure DeviceOutput {
    @required
    value: String
}

operation session {
    input: SessionInput
    output: SessionOutput
}

structure SessionInput {
}

structure SessionOutput {
    @required
    value: String
}

operation root {
    input: RootInput
    output: RootOutput
}

structure RootInput {
}

structure RootOutput {
    @required
    value: String
}

structure AuthenticationTokenResult {
    expires: String
    type: String
    @required
    value: String
}

enum TokenType {
    DEVICE = "device"
    DISTRIBUTOR = "distributor"
    PLATFORM = "platform"
}
