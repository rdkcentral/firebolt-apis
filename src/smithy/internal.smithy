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
    version: Types::SemanticVersion
}

structure InitializeOutput {
    @required
    value: InitializeResult
}

structure InitializeResult {
    @required
    version: Types::SemanticVersion
}
