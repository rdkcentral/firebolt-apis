$version: "2"
namespace com.firebolt.actions

use com.firebolt#event
use com.firebolt#JsonDocument

service ActionsService {
    version: "1.0"
    operations: [intent, onIntent]
}

operation intent {
    output: IntentOutput
}

structure IntentOutput {
     @required
     value: JsonDocument
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
