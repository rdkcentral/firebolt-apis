$version: "2"
namespace com.firebolt.metrics

service MetricsService {
    version: "1.0"
    operations: [ready, signIn, signOut, startContent, stopContent, page, action, error, mediaLoadStart, mediaPlay, mediaPlaying, mediaPause, mediaWaiting, mediaProgress, mediaSeeking, mediaSeeked, mediaRateChange, mediaRenditionChange, mediaEnded, event, appInfo, mediaRateChanged, mediaRenditionChanged]
}

operation ready {
    input: ReadyInput
    output: ReadyOutput
}

structure ReadyInput {
}

structure ReadyOutput {
    @required
    value: Boolean
}

operation signIn {
    input: SignInInput
    output: SignInOutput
}

structure SignInInput {
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

operation startContent {
    input: StartContentInput
    output: StartContentOutput
}

structure StartContentInput {
    agePolicy: AgePolicy
    entityId: String
}

structure StartContentOutput {
    @required
    value: Boolean
}

operation stopContent {
    input: StopContentInput
    output: StopContentOutput
}

structure StopContentInput {
    agePolicy: AgePolicy
    entityId: String
}

structure StopContentOutput {
    @required
    value: Boolean
}

operation page {
    input: PageInput
    output: PageOutput
}

structure PageInput {
    agePolicy: AgePolicy
    @required
    pageId: String
}

structure PageOutput {
    @required
    value: Boolean
}

operation action {
    input: ActionInput
    output: ActionOutput
}

structure ActionInput {
    agePolicy: AgePolicy
    @required
    category: String
    parameters: StringMap
    @required
    type: String
}

structure ActionOutput {
    @required
    value: Boolean
}

operation error {
    input: ErrorInput
    output: ErrorOutput
}

structure ErrorInput {
    agePolicy: AgePolicy
    @required
    code: String
    @required
    description: String
    parameters: StringMap
    @required
    type: ErrorType
    @required
    visible: Boolean
}

structure ErrorOutput {
    @required
    value: Boolean
}

operation mediaLoadStart {
    input: MediaLoadStartInput
    output: MediaLoadStartOutput
}

structure MediaLoadStartInput {
    agePolicy: AgePolicy
    @required
    entityId: String
}

structure MediaLoadStartOutput {
    @required
    value: Boolean
}

operation mediaPlay {
    input: MediaPlayInput
    output: MediaPlayOutput
}

structure MediaPlayInput {
    agePolicy: AgePolicy
    @required
    entityId: String
}

structure MediaPlayOutput {
    @required
    value: Boolean
}

operation mediaPlaying {
    input: MediaPlayingInput
    output: MediaPlayingOutput
}

structure MediaPlayingInput {
    agePolicy: AgePolicy
    @required
    entityId: String
}

structure MediaPlayingOutput {
    @required
    value: Boolean
}

operation mediaPause {
    input: MediaPauseInput
    output: MediaPauseOutput
}

structure MediaPauseInput {
    agePolicy: AgePolicy
    @required
    entityId: String
}

structure MediaPauseOutput {
    @required
    value: Boolean
}

operation mediaWaiting {
    input: MediaWaitingInput
    output: MediaWaitingOutput
}

structure MediaWaitingInput {
    agePolicy: AgePolicy
    @required
    entityId: String
}

structure MediaWaitingOutput {
    @required
    value: Boolean
}

operation mediaProgress {
    input: MediaProgressInput
    output: MediaProgressOutput
}

structure MediaProgressInput {
    agePolicy: AgePolicy
    @required
    entityId: String
    @required
    progress: MediaPosition
}

structure MediaProgressOutput {
    @required
    value: Boolean
}

operation mediaSeeking {
    input: MediaSeekingInput
    output: MediaSeekingOutput
}

structure MediaSeekingInput {
    agePolicy: AgePolicy
    @required
    entityId: String
    @required
    target: MediaPosition
}

structure MediaSeekingOutput {
    @required
    value: Boolean
}

operation mediaSeeked {
    input: MediaSeekedInput
    output: MediaSeekedOutput
}

structure MediaSeekedInput {
    agePolicy: AgePolicy
    @required
    entityId: String
    @required
    position: MediaPosition
}

structure MediaSeekedOutput {
    @required
    value: Boolean
}

operation mediaRateChange {
    input: MediaRateChangeInput
    output: MediaRateChangeOutput
}

structure MediaRateChangeInput {
    agePolicy: AgePolicy
    @required
    entityId: String
    @required
    rate: Double
}

structure MediaRateChangeOutput {
    @required
    value: Boolean
}

operation mediaRenditionChange {
    input: MediaRenditionChangeInput
    output: MediaRenditionChangeOutput
}

structure MediaRenditionChangeInput {
    agePolicy: AgePolicy
    @required
    bitrate: Double
    @required
    entityId: String
    @required
    height: Double
    profile: String
    @required
    width: Double
}

structure MediaRenditionChangeOutput {
    @required
    value: Boolean
}

operation mediaEnded {
    input: MediaEndedInput
    output: MediaEndedOutput
}

structure MediaEndedInput {
    agePolicy: AgePolicy
    @required
    entityId: String
}

structure MediaEndedOutput {
    @required
    value: Boolean
}

operation event {
    input: EventInput
    output: EventOutput
}

structure EventInput {
    agePolicy: AgePolicy
    @required
    data: EventObject
    @required
    schema: String
}

structure EventOutput {}

operation appInfo {
    input: AppInfoInput
    output: AppInfoOutput
}

structure AppInfoInput {
    @required
    build: String
}

structure AppInfoOutput {}

operation mediaRateChanged {
    input: MediaRateChangedInput
    output: MediaRateChangedOutput
}

structure MediaRateChangedInput {
    @required
    entityId: String
    @required
    rate: Double
    agePolicy: AgePolicy
}

structure MediaRateChangedOutput {
    @required
    value: Boolean
}

operation mediaRenditionChanged {
    input: MediaRenditionChangedInput
    output: MediaRenditionChangedOutput
}

structure MediaRenditionChangedInput {
    @required
    entityId: String
    @required
    bitrate: Double
    @required
    width: Double
    @required
    height: Double
    profile: String
    agePolicy: AgePolicy
}

structure MediaRenditionChangedOutput {
    @required
    value: Boolean
}

// TODO: alias AgePolicy = String (Smithy has no direct alias — use a newtype structure or inline the target)

enum ErrorType {
    ENTITLEMENT = "entitlement"
    MEDIA = "media"
    NETWORK = "network"
    OTHER = "other"
    RESTRICTION = "restriction"
}

structure EventObject {
    @required
    value: EventObjectPrimitivesMap
}

union EventObjectPrimitives {
    stringValue: String
    doubleValue: Double
    intValue: Integer
    boolValue: Boolean
}

// TODO: alias MediaPosition = Double (Smithy has no direct alias — use a newtype structure or inline the target)

map StringMap {
    key: String
    value: String
}

map EventObjectPrimitivesMap {
    key: String
    value: EventObjectPrimitives
}
