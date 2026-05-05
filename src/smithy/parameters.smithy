$version: "2"
namespace com.firebolt.parameters

service ParametersService {
    version: "1.0"
    operations: [initialization]
}

operation initialization {
    input: InitializationInput
    output: InitializationOutput
}

structure InitializationInput {
}

structure InitializationOutput {
    @required
    value: AppInitialization
}

structure AppInitialization {
    discovery: String
    lmt: Integer
    secondScreen: String
    us_privacy: String
}
