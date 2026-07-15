$version: "2"
namespace com.firebolt.device

use com.firebolt#UInt32
use com.firebolt#capability
use com.firebolt#event
use com.firebolt#property
use com.firebolt#propertyReadonly

service DeviceService {
    version: "1.0"
    operations: [uid, hdr, deviceClass, uptime, timeInActiveState, chipsetId]
}

@capability(uses: ["xrn:firebolt:capability:device:id"])
@propertyReadonly
operation id {
    input: IdInput
    output: IdOutput
}

structure IdInput {
}

structure IdOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:device:distributor"])
@propertyReadonly
operation distributor {
    input: DistributorInput
    output: DistributorOutput
}

structure DistributorInput {
}

structure DistributorOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:device:info"])
@propertyReadonly
operation platform {
    input: PlatformInput
    output: PlatformOutput
}

structure PlatformInput {
}

structure PlatformOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:device:uid"])
operation uid {
    input: UidInput
    output: UidOutput
}

structure UidInput {
}

structure UidOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:device:info"])
@propertyReadonly
operation type {
    input: TypeInput
    output: TypeOutput
}

structure TypeInput {
}

structure TypeOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:device:model"])
@propertyReadonly
operation model {
    input: ModelInput
    output: ModelOutput
}

structure ModelInput {
}

structure ModelOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:device:sku"])
@propertyReadonly
operation sku {
    input: SkuInput
    output: SkuOutput
}

structure SkuInput {
}

structure SkuOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:device:make"])
@propertyReadonly
operation make {
    input: MakeInput
    output: MakeOutput
}

structure MakeInput {
}

structure MakeOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:device:info"])
@propertyReadonly
operation hdcp {
    input: HdcpInput
    output: HdcpOutput
}

structure HdcpInput {
}

structure HdcpOutput {
    @required
    value: HDCPVersionMap
}

@capability(uses: ["xrn:firebolt:capability:device:info"])
@propertyReadonly
operation hdr {
    input: HdrInput
    output: HdrOutput
}

structure HdrInput {
}

structure HdrOutput {
    @required
    value: HDRFormat
}

@capability(uses: ["xrn:firebolt:capability:device:info"])
@propertyReadonly
operation audio {
    input: AudioInput
    output: AudioOutput
}

structure AudioInput {
}

structure AudioOutput {
    @required
    value: AudioProfiles
}

@capability(uses: ["xrn:firebolt:capability:device:info"])
@propertyReadonly
operation screenResolution {
    input: ScreenResolutionInput
    output: ScreenResolutionOutput
}

structure ScreenResolutionInput {
}

structure ScreenResolutionOutput {
    @required
    value: IntegerList
}

@capability(uses: ["xrn:firebolt:capability:device:info"])
@propertyReadonly
operation videoResolution {
    input: VideoResolutionInput
    output: VideoResolutionOutput
}

structure VideoResolutionInput {
}

structure VideoResolutionOutput {
    @required
    value: IntegerList
}

@capability(uses: ["xrn:firebolt:capability:device:name"])
@property
operation name {
    input: NameInput
    output: NameOutput
}

structure NameInput {
}

structure NameOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:device:name"])
@event
operation onDeviceNameChanged {
    input: OnDeviceNameChangedInput
    output: OnDeviceNameChangedOutput
}

structure OnDeviceNameChangedInput {
}

structure OnDeviceNameChangedOutput {
    @required
    value: String
}

@capability(uses: ["xrn:firebolt:capability:network:status"])
@propertyReadonly
operation network {
    input: NetworkInput
    output: NetworkOutput
}

structure NetworkInput {
}

structure NetworkOutput {
    @required
    value: NetworkInfoResult
}

@capability(manages: ["xrn:firebolt:capability:account:id", "xrn:firebolt:capability:device:id", "xrn:firebolt:capability:device:distributor"])
operation provision {
    input: ProvisionInput
    output: ProvisionOutput
}

structure ProvisionInput {
    @required
    accountId: String
    @required
    deviceId: String
    distributorId: String
}

structure ProvisionOutput {}

operation deviceClass {
    input: DeviceClassInput
    output: DeviceClassOutput
}

structure DeviceClassInput {
}

structure DeviceClassOutput {
    @required
    value: DeviceClass
}

operation uptime {
    input: UptimeInput
    output: UptimeOutput
}

structure UptimeInput {
}

structure UptimeOutput {
    @required
    value: UInt32
}

operation timeInActiveState {
    input: TimeInActiveStateInput
    output: TimeInActiveStateOutput
}

structure TimeInActiveStateInput {
}

structure TimeInActiveStateOutput {
    @required
    value: UInt32
}

operation chipsetId {
    input: ChipsetIdInput
    output: ChipsetIdOutput
}

structure ChipsetIdInput {
}

structure ChipsetIdOutput {
    @required
    value: String
}

@propertyReadonly
operation room {
    input: RoomInput
    output: RoomOutput
}

structure RoomInput {
}

structure RoomOutput {
    /// The room name configured for this device, e.g. "Living Room"
    @required
    value: String
}

structure AudioProfiles {
    @required
    dolbyAtmos: Boolean
    @required
    dolbyDigital51: Boolean
    @required
    dolbyDigital51Plus: Boolean
    @required
    stereo: Boolean
}

enum DeviceClass {
    OTT = "ott"
    STB = "stb"
    TV = "tv"
}

structure HDCPVersionMap {
    @required
    hdcp14: Boolean
    @required
    hdcp22: Boolean
}

structure HDRFormat {
    @required
    dolbyVision: Boolean
    @required
    hdr10: Boolean
    @required
    hdr10Plus: Boolean
    @required
    hlg: Boolean
}

structure NetworkInfoResult {
    @required
    state: NetworkState
    @required
    type: NetworkType
}

enum NetworkState {
    CONNECTED = "connected"
    DISCONNECTED = "disconnected"
}

enum NetworkType {
    ETHERNET = "ethernet"
    HYBRID = "hybrid"
    WIFI = "wifi"
}

list IntegerList {
    member: Integer
}
