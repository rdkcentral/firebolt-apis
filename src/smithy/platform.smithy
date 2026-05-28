$version: "2"
namespace com.firebolt.platform

use com.firebolt#propertyReadonly

service PlatformService {
    version: "1.0"
    operations: [version]
}

/// Returns the current platform software version string.
@propertyReadonly
operation version {
    input: VersionInput
    output: VersionOutput
}

structure VersionInput {
}

structure VersionOutput {
    /// The platform software version identifier, e.g. "1.2.3".
    @required
    value: String
}