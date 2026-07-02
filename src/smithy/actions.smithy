$version: "2"
namespace com.firebolt.actions

use com.firebolt#event

service ActionsService {
    version: "1.0"
    operations: [intent, onIntent]
}

operation intent {
    output: IntentOutput
}

structure IntentOutput {
     @required
     value: String
}

@event
operation onIntent {
    input: OnIntentInput
    output: OnIntentOutput
}

structure OnIntentInput {}

structure OnIntentOutput {
    @required
     intent: String
}
