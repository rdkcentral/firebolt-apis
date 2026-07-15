$version: "2"
namespace com.firebolt.pinchallenge

use com.firebolt#event

service PinchallengeService {
    version: "1.0"
    operations: [onRequestChallenge]
}

@event
operation onRequestChallenge {
    input: OnRequestChallengeInput
    output: OnRequestChallengeOutput
}

structure OnRequestChallengeInput {
}

structure OnRequestChallengeOutput {
    @required
    value: PinChallengeProviderRequest
}

structure ChallengeRequestor {
    @required
    id: String
    @required
    name: String
}

structure PinChallenge {
    capability: String
    @required
    pinSpace: String
    @required
    requestor: ChallengeRequestor
}

structure PinChallengeProviderRequest {
    @required
    parameters: PinChallenge
}

structure PinChallengeResult {
    granted: Boolean
    @required
    reason: ResultReason
}

enum ResultReason {
    CANCELLED = "cancelled"
    CORRECT_PIN = "correctPin"
    EXCEEDED_PIN_FAILURES = "exceededPinFailures"
    NO_PIN_REQUIRED = "noPinRequired"
    NO_PIN_REQUIRED_WINDOW = "noPinRequiredWindow"
}
