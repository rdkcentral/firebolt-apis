$version: "2"
namespace com.firebolt.firebolt

use com.firebolt#propertyReadonly

service FireboltService {
    version: "1.0"
    operations: [serverVersion]
}

/// Returns the version string of the Firebolt server (gateway) currently in use.
@propertyReadonly
operation serverVersion {
    input: ServerVersionInput
    output: ServerVersionOutput
}

structure ServerVersionInput {
}

structure ServerVersionOutput {
    /// The Firebolt server version string, e.g. "2.3.1"
    @required
    value: String
}
