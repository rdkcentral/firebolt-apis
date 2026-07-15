$version: "2"
namespace com.firebolt.acknowledgechallenge

use com.firebolt#event

service AcknowledgechallengeService {
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
    value: ChallengeProviderRequest
}

structure Challenge {
    @required
    capability: String
    @required
    requestor: ChallengeRequestor
}

structure ChallengeProviderRequest {
    @required
    parameters: Challenge
}

structure ChallengeRequestor {
    @required
    id: String
    @required
    name: String
}

structure GrantResult {
    granted: Boolean
}
