$version: "2"
namespace com.firebolt.actions

use com.firebolt#event

service ActionsService {
    version: "1.0"
    operations: [start, onIntent]
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

@event
operation onIntent {
    input: OnIntentInput
    output: OnIntentOutput
}

structure OnIntentInput {}

structure OnIntentOutput {
    @required
    value: String
}
