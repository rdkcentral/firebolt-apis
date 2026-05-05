$version: "2"
namespace com.firebolt.network

use com.firebolt#propertyReadonly

service NetworkService {
    version: "1.0"
    operations: [connected]
}

@propertyReadonly
operation connected {
    input: ConnectedInput
    output: ConnectedOutput
}

structure ConnectedInput {
}

structure ConnectedOutput {
    @required
    value: Connected
}

// TODO: alias Connected = Boolean (Smithy has no direct alias — use a newtype structure or inline the target)
