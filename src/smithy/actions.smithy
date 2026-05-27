$version: "2"
namespace com.firebolt.actions

use com.firebolt#event

service ActionsService {
    version: "1.0"
    operations: [intent, onIntent]
}

operation intent {
    input: IntentInput
    output: IntentOutput
}

structure IntentInput {
    @required
    intent: String
}

structure IntentOutput {}

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
