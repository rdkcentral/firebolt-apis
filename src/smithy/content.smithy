$version: "2"
namespace com.firebolt.content

use com.firebolt#event

service ContentService {
    version: "1.0"
    operations: [requestUserInterest, onUserInterest]
}

operation requestUserInterest {
    input: RequestUserInterestInput
    output: RequestUserInterestOutput
}

structure RequestUserInterestInput {
    @required
    reason: InterestReason
    @required
    type: InterestType
}

structure RequestUserInterestOutput {
    @required
    value: InterestResult
}

@event
operation onUserInterest {
    input: OnUserInterestInput
    output: OnUserInterestOutput
}

structure OnUserInterestInput {
}

structure OnUserInterestOutput {
    @required
    value: InterestEvent
}

structure ContentIdentifiers {
    assetId: String
    entityId: String
    seasonId: String
    seriesId: String
}

structure EntityDetails {
    @required
    identifiers: ContentIdentifiers
    info: String
}

structure InterestEvent {
    @required
    appId: String
    @required
    entity: EntityDetails
    @required
    reason: InterestReason
    @required
    type: InterestType
}

enum InterestReason {
    P_L_A_Y_L_I_S_T = "PLAYLIST"
    R_E_A_C_T_I_O_N = "REACTION"
    R_E_C_O_R_D_I_N_G = "RECORDING"
}

structure InterestResult {
    @required
    appId: String
    @required
    entity: EntityDetails
}

enum InterestType {
    D_I_S_I_N_T_E_R_E_S_T = "DISINTEREST"
    I_N_T_E_R_E_S_T = "INTEREST"
}
