$version: "2"
namespace com.firebolt.internal

service InternalService {
    version: "1.0"
    operations: [initialize]
}

operation initialize {
    input: InitializeInput
    output: InitializeOutput
}

structure InitializeInput {
    @required
    version: SemanticVersion
}

structure InitializeOutput {
    @required
    value: InitializeResult
}

structure InitializeResult {
    @required
    version: SemanticVersion
}

structure SemanticVersion {
    @required
    major: Integer
    @required
    minor: Integer
    @required
    patch: Integer
    @required
    readable: String
}
