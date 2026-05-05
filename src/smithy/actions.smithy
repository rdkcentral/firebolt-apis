$version: "2"
namespace com.firebolt.actions

service ActionsService {
    version: "1.0"
    operations: [start]
}

operation start {
    input: StartInput
    output: StartOutput
}

structure StartInput {
    @required
    intent: String
}

structure StartOutput {}
