$version: "2"
namespace com.firebolt.discovery

use com.firebolt#event
use com.firebolt#propertyReadonly

service DiscoveryService {
    version: "1.0"
    operations: [policy, entityInfo, purchasedContent, watched, watchNext, entitlements, contentAccess, clearContentAccess, launch, onNavigateTo, signIn, signOut, onSignIn, onSignOut, userInterest, onRequestUserInterest]
}

@propertyReadonly
operation policy {
    input: PolicyInput
    output: PolicyOutput
}

structure PolicyInput {
}

structure PolicyOutput {
    @required
    value: DiscoveryPolicy
}

operation entityInfo {
    input: EntityInfoInput
    output: EntityInfoOutput
}

structure EntityInfoInput {
    @required
    correlationId: String
    @required
    result: EntityInfoResult
}

structure EntityInfoOutput {
    @required
    value: Boolean
}

operation purchasedContent {
    input: PurchasedContentInput
    output: PurchasedContentOutput
}

structure PurchasedContentInput {
    @required
    correlationId: String
    @required
    result: PurchasedContentResult
}

structure PurchasedContentOutput {
    @required
    value: Boolean
}

operation watched {
    input: WatchedInput
    output: WatchedOutput
}

structure WatchedInput {
    agePolicy: String
    completed: Boolean
    @required
    entityId: String
    progress: Double
    watchedOn: String
}

structure WatchedOutput {
    @required
    value: Boolean
}

operation watchNext {
    input: WatchNextInput
    output: WatchNextOutput
}

structure WatchNextInput {
    expires: String
    @required
    identifiers: ContentIdentifiers
    images: String
    @required
    title: String
}

structure WatchNextOutput {
    @required
    value: Boolean
}

operation entitlements {
    input: EntitlementsInput
    output: EntitlementsOutput
}

structure EntitlementsInput {
    @required
    entitlements: EntitlementList
}

structure EntitlementsOutput {
    @required
    value: Boolean
}

operation contentAccess {
    input: ContentAccessInput
    output: ContentAccessOutput
}

structure ContentAccessInput {
    @required
    ids: ContentAccessIdentifiers
}

structure ContentAccessOutput {}

operation clearContentAccess {
    input: ClearContentAccessInput
    output: ClearContentAccessOutput
}

structure ClearContentAccessInput {
}

structure ClearContentAccessOutput {}

operation launch {
    input: LaunchInput
    output: LaunchOutput
}

structure LaunchInput {
    @required
    appId: String
    intent: String
}

structure LaunchOutput {
    @required
    value: Boolean
}

@event
operation onNavigateTo {
    input: OnNavigateToInput
    output: OnNavigateToOutput
}

structure OnNavigateToInput {
}

structure OnNavigateToOutput {
    @required
    value: String
}

operation signIn {
    input: SignInInput
    output: SignInOutput
}

structure SignInInput {
    entitlements: EntitlementList
}

structure SignInOutput {
    @required
    value: Boolean
}

operation signOut {
    input: SignOutInput
    output: SignOutOutput
}

structure SignOutInput {
}

structure SignOutOutput {
    @required
    value: Boolean
}

@event
operation onSignIn {
    input: OnSignInInput
    output: OnSignInOutput
}

structure OnSignInInput {
}

structure OnSignInOutput {
    @required
    value: OnSignIn
}

@event
operation onSignOut {
    input: OnSignOutInput
    output: OnSignOutOutput
}

structure OnSignOutInput {
}

structure OnSignOutOutput {
    @required
    value: OnSignOut
}

operation userInterest {
    input: UserInterestInput
    output: UserInterestOutput
}

structure UserInterestInput {
    @required
    entity: EntityDetails
    @required
    reason: InterestReason
    @required
    type: InterestType
}

structure UserInterestOutput {}

@event
operation onRequestUserInterest {
    input: OnRequestUserInterestInput
    output: OnRequestUserInterestOutput
}

structure OnRequestUserInterestInput {
}

structure OnRequestUserInterestOutput {
    @required
    value: OnRequestUserInterest
}

structure Availability {
    catalogId: String
    endTime: String
    @required
    id: String
    startTime: String
    @required
    type: String
}

structure ContentAccessIdentifiers {
    availabilities: AvailabilityList
    entitlements: EntitlementList
}

structure ContentIdentifiers {
    appContentData: String
    assetId: String
    entityId: String
    seasonId: String
    seriesId: String
}

structure DiscoveryPolicy {
    @required
    enableRecommendations: Boolean
    @required
    rememberWatchedPrograms: Boolean
    @required
    shareWatchHistory: Boolean
}

structure EntityDetails {
    @required
    identifiers: ContentIdentifiers
    info: String
}

structure EntityInfo {
    contentRatings: StringList
    @required
    entityId: String
    @required
    entityType: String
    programType: ProgramType
    releaseDate: String
    synopsis: String
    @required
    title: String
}

structure EntityInfoFederatedRequest {
    @required
    parameters: EntityInfoParameters
}

structure EntityInfoFederatedResponse {
    result: EntityInfoResult
}

structure EntityInfoParameters {
    assetId: String
    @required
    entityId: String
}

structure EntityInfoResult {
    @required
    entity: EntityInfo
    @required
    expires: String
}

structure FederatedRequest {
    @required
    correlationId: String
}

structure FederatedResponse {
    @required
    correlationId: String
}

enum InterestReason {
    P_L_A_Y_L_I_S_T = "PLAYLIST"
    R_E_A_C_T_I_O_N = "REACTION"
    R_E_C_O_R_D_I_N_G = "RECORDING"
}

enum InterestType {
    D_I_S_I_N_T_E_R_E_S_T = "DISINTEREST"
    I_N_T_E_R_E_S_T = "INTEREST"
}

enum OfferingType {
    B_U_Y = "BUY"
    F_R_E_E = "FREE"
    R_E_N_T = "RENT"
    S_U_B_S_C_R_I_B_E = "SUBSCRIBE"
}

structure OnRequestUserInterest {
    @required
    correlationId: String
    @required
    parameters: UserInterestProviderParameters
}

structure OnSignIn {
    @required
    appId: String
}

structure OnSignOut {
    @required
    appId: String
}

enum ProgramType {
    A_D_V_E_R_T_I_S_E_M_E_N_T = "ADVERTISEMENT"
    C_O_N_C_E_R_T = "CONCERT"
    E_P_I_S_O_D_E = "EPISODE"
    E_X_T_R_A = "EXTRA"
    M_I_N_I_S_O_D_E = "MINISODE"
    M_O_V_I_E = "MOVIE"
    M_U_S_I_C__V_I_D_E_O = "MUSIC_VIDEO"
    O_T_H_E_R = "OTHER"
    P_R_E_V_I_E_W = "PREVIEW"
    S_E_A_S_O_N = "SEASON"
    S_E_R_I_E_S = "SERIES"
    S_P_O_R_T_I_N_G__E_V_E_N_T = "SPORTING_EVENT"
}

structure PurchasedContentFederatedRequest {
    @required
    parameters: PurchasedContentParameters
}

structure PurchasedContentFederatedResponse {
    result: PurchasedContentResult
}

structure PurchasedContentParameters {
    @required
    limit: Integer
    offeringType: OfferingType
    programType: ProgramType
}

structure PurchasedContentResult {
    @required
    entries: EntityInfoList
    @required
    expires: String
    @required
    totalCount: Integer
}

enum TuneChannels {
    XRN_FIREBOLT_CHANNEL_ANY = "xrnFireboltChannelAny"
}

structure UserInterestProviderParameters {
    @required
    reason: InterestReason
    @required
    type: InterestType
}

list EntitlementList {
    member: String
}

list AvailabilityList {
    member: Availability
}

list StringList {
    member: String
}

list EntityInfoList {
    member: EntityInfo
}
