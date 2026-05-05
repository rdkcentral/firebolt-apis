$version: "2"
namespace com.firebolt.advertising

use com.firebolt#property
use com.firebolt#propertyReadonly

service AdvertisingService {
    version: "1.0"
    operations: [config, policy, skipRestriction, advertisingId, deviceAttributes, appBundleId, resetIdentifier]
}

operation config {
    input: ConfigInput
    output: ConfigOutput
}

structure ConfigInput {
    @required
    options: AdConfigurationOptions
}

structure ConfigOutput {
    @required
    value: String
}

@propertyReadonly
operation policy {
    input: PolicyInput
    output: PolicyOutput
}

structure PolicyInput {
}

structure PolicyOutput {
    @required
    value: AdPolicy
}

@property
operation skipRestriction {
    input: SkipRestrictionInput
    output: SkipRestrictionOutput
}

structure SkipRestrictionInput {
}

structure SkipRestrictionOutput {
    @required
    value: SkipRestriction
}

operation advertisingId {
    input: AdvertisingIdInput
    output: AdvertisingIdOutput
}

structure AdvertisingIdInput {
    options: AdvertisingIdOptions
}

structure AdvertisingIdOutput {
    @required
    value: Ifa
}

operation deviceAttributes {
    input: DeviceAttributesInput
    output: DeviceAttributesOutput
}

structure DeviceAttributesInput {
}

structure DeviceAttributesOutput {
    @required
    value: String
}

operation appBundleId {
    input: AppBundleIdInput
    output: AppBundleIdOutput
}

structure AppBundleIdInput {
}

structure AppBundleIdOutput {
    @required
    value: String
}

operation resetIdentifier {
    input: ResetIdentifierInput
    output: ResetIdentifierOutput
}

structure ResetIdentifierInput {
}

structure ResetIdentifierOutput {}

structure AdConfigurationOptions {
    authenticationEntity: String
    coppa: Boolean
    environment: String
}

structure AdPolicy {
    limitAdTracking: Boolean
    skipRestriction: SkipRestriction
}

structure AdvertisingIdOptions {
    scope: String
}

structure Ifa {
    @required
    ifa: String
    @required
    ifa_type: String
    @required
    lmt: String
}

enum SkipRestriction {
    A_D_S__A_L_L = "ADS_ALL"
    A_D_S__U_N_W_A_T_C_H_E_D = "ADS_UNWATCHED"
    A_L_L = "ALL"
    N_O_N_E = "NONE"
}
