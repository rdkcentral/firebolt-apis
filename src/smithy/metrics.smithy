$version: "2"
namespace com.firebolt.metrics

use com.firebolt#UInt32

service MetricsService {
    version: "1.0"
    operations: [ready, signIn, signOut, startContent, stopContent, page, error, mediaLoadStart, mediaPlay, mediaPlaying, mediaPause, mediaWaiting, mediaSeeking, mediaSeeked, mediaRateChanged, mediaRenditionChanged, mediaEnded, event, appInfo]
}

operation ready {
    input: ReadyInput
    output: ReadyOutput
}

structure ReadyInput {
}

structure ReadyOutput {
}

operation signIn {
    input: SignInInput
    output: SignInOutput
}

structure SignInInput {
}

structure SignInOutput {
}

operation signOut {
    input: SignOutInput
    output: SignOutOutput
}

structure SignOutInput {
}

structure SignOutOutput {
}

operation startContent {
    input: StartContentInput
    output: StartContentOutput
}

structure StartContentInput {
    entityId: String
    agePolicy: AgePolicy
}

structure StartContentOutput {
}

operation stopContent {
    input: StopContentInput
    output: StopContentOutput
}

structure StopContentInput {
    entityId: String
    agePolicy: AgePolicy
}

structure StopContentOutput {
}

operation page {
    input: PageInput
    output: PageOutput
}

structure PageInput {
    @required
    pageId: String
    agePolicy: AgePolicy
}

structure PageOutput {
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
    @required
    type: ErrorType
    @required
    code: String
    @required
    description: String
    @required
    visible: Boolean
    parameters: StringMap
    agePolicy: AgePolicy
}

structure ErrorOutput {
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
    @required
    entityId: String
    @required
    target: Double
    agePolicy: AgePolicy
}

structure MediaSeekingOutput {
}

operation mediaSeeked {
    input: MediaSeekedInput
    output: MediaSeekedOutput
}

structure MediaSeekedInput {
    @required
    entityId: String
    @required
    position: Double
    agePolicy: AgePolicy
}

structure MediaSeekedOutput {
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

structure MediaRateChangeOutput {}

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

structure MediaRenditionChangeOutput {}

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
}

operation event {
    input: EventInput
    output: EventOutput
}

structure EventInput {
    @required
    schema: String
    @required
    data: String
    agePolicy: AgePolicy
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
}

operation mediaRenditionChanged {
    input: MediaRenditionChangedInput
    output: MediaRenditionChangedOutput
}

structure MediaRenditionChangedInput {
    @required
    entityId: String
    @required
    bitrate: UInt32
    @required
    width: UInt32
    @required
    height: UInt32
    profile: String
    agePolicy: AgePolicy
}

structure MediaRenditionChangedOutput {
}

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

structure MediaPosition {
    @required
    value: Double
}

structure AgePolicy {
    @required
    value: String
}

union EventObjectPrimitives {
    stringValue: String
    doubleValue: Double
    intValue: Integer
    boolValue: Boolean
}

map StringMap {
    key: String
    value: String
}

map EventObjectPrimitivesMap {
    key: String
    value: EventObjectPrimitives
}
