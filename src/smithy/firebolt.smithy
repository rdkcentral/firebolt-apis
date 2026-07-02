$version: "2"
namespace com.firebolt.firebolt

use com.firebolt#propertyReadonly

service FireboltService {
    version: "1.0"
    operations: [serverVersion, clientVersion]
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

/// Returns the version string of the Firebolt client library in use.
/// This is client-local metadata and does not require a gateway/server round-trip.
/// The value source can be wired to build metadata by platform implementations.
@propertyReadonly
operation clientVersion {
    input: ClientVersionInput
    output: ClientVersionOutput
}

structure ClientVersionInput {
}

structure ClientVersionOutput {
    /// The Firebolt client version string, e.g. "1.0.0"
    @required
    value: String
}
