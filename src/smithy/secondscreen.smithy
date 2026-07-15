$version: "2"
namespace com.firebolt.secondscreen

use com.firebolt#event
use com.firebolt#propertyReadonly

service SecondscreenService {
    version: "1.0"
    operations: [protocols, device, friendlyName, onLaunchRequest, onCloseRequest]
}

operation protocols {
    input: ProtocolsInput
    output: ProtocolsOutput
}

structure ProtocolsInput {
}

structure ProtocolsOutput {
    @required
    value: BooleanMap
}

operation device {
    input: DeviceInput
    output: DeviceOutput
}

structure DeviceInput {
    type: String
}

structure DeviceOutput {
    @required
    value: String
}

@propertyReadonly
operation friendlyName {
    input: FriendlyNameInput
    output: FriendlyNameOutput
}

structure FriendlyNameInput {
}

structure FriendlyNameOutput {
    @required
    value: String
}

@event
operation onLaunchRequest {
    input: OnLaunchRequestInput
    output: OnLaunchRequestOutput
}

structure OnLaunchRequestInput {
}

structure OnLaunchRequestOutput {
    @required
    value: SecondScreenEvent
}

@event
operation onCloseRequest {
    input: OnCloseRequestInput
    output: OnCloseRequestOutput
}

structure OnCloseRequestInput {
}

structure OnCloseRequestOutput {
    @required
    value: SecondScreenEvent
}

structure SecondScreenEvent {
    data: String
    @required
    type: String
    version: String
}

map BooleanMap {
    key: String
    value: Boolean
}
