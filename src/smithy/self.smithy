$version: "2"
namespace com.firebolt.self

use com.firebolt#propertyReadonly

service SelfService {
    version: "1.0"
    operations: [version]
}

/// Returns the current app instance version string.
@propertyReadonly
operation version {
    input: VersionInput
    output: VersionOutput
}

structure VersionInput {
}

structure VersionOutput {
    /// The app version identifier, e.g. "1.2.3".
    @required
    value: String
}