$version: "2"
namespace com.firebolt.texttospeech

use com.firebolt#UInt32
use com.firebolt#event

service TexttospeechService {
    version: "1.0"
    operations: [speak, pause, resume, cancel, getSpeechState, onWillSpeak, onSpeechStart, onSpeechPause, onSpeechResume, onSpeechComplete, onSpeechInterrupted, onNetworkError, onPlaybackError, listVoices]
}

operation speak {
    input: SpeakInput
    output: SpeakOutput
}

structure SpeakInput {
    @required
    text: String
}

structure SpeakOutput {
    @required
    value: SpeechResponse
}

operation pause {
    input: PauseInput
    output: PauseOutput
}

structure PauseInput {
    @required
    speechid: UInt32
}

structure PauseOutput {
    @required
    value: TTSStatusResponse
}

operation resume {
    input: ResumeInput
    output: ResumeOutput
}

structure ResumeInput {
    @required
    speechid: UInt32
}

structure ResumeOutput {
    @required
    value: TTSStatusResponse
}

operation cancel {
    input: CancelInput
    output: CancelOutput
}

structure CancelInput {
    @required
    speechid: UInt32
}

structure CancelOutput {
    @required
    value: TTSStatusResponse
}

operation getSpeechState {
    input: GetSpeechStateInput
    output: GetSpeechStateOutput
}

structure GetSpeechStateInput {
    @required
    speechid: UInt32
}

structure GetSpeechStateOutput {
    @required
    value: SpeechStateResponse
}

@event
operation onWillSpeak {
    input: OnWillSpeakInput
    output: OnWillSpeakOutput
}

structure OnWillSpeakInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnWillSpeakOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechStart {
    input: OnSpeechStartInput
    output: OnSpeechStartOutput
}

structure OnSpeechStartInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechStartOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechPause {
    input: OnSpeechPauseInput
    output: OnSpeechPauseOutput
}

structure OnSpeechPauseInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechPauseOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechResume {
    input: OnSpeechResumeInput
    output: OnSpeechResumeOutput
}

structure OnSpeechResumeInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechResumeOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechComplete {
    input: OnSpeechCompleteInput
    output: OnSpeechCompleteOutput
}

structure OnSpeechCompleteInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechCompleteOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechInterrupted {
    input: OnSpeechInterruptedInput
    output: OnSpeechInterruptedOutput
}

structure OnSpeechInterruptedInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechInterruptedOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onNetworkError {
    input: OnNetworkErrorInput
    output: OnNetworkErrorOutput
}

structure OnNetworkErrorInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnNetworkErrorOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onPlaybackError {
    input: OnPlaybackErrorInput
    output: OnPlaybackErrorOutput
}

structure OnPlaybackErrorInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnPlaybackErrorOutput {
    @required
    value: SpeechIdEvent
}

operation listVoices {
    input: ListVoicesInput
    output: ListVoicesOutput
}

structure ListVoicesInput {
    @required
    language: String
}

structure ListVoicesOutput {
    @required
    value: ListVoicesResponse
}

structure FallbackText {
    scenario: String
    value: String
}

structure ListVoicesResponse {
    @required
    TTS_Status: Integer
    @required
    voices: StringList
}

// TODO: alias SpeechId = Integer (Smithy has no direct alias — use a newtype structure or inline the target)

structure SpeechIdEvent {
    @required
    speechid: UInt32
}

enum SpeechRate {
    F_A_S_T = "FAST"
    F_A_S_T_E_R = "FASTER"
    F_A_S_T_E_S_T = "FASTEST"
    M_E_D_I_U_M = "MEDIUM"
    S_L_O_W = "SLOW"
}

structure SpeechResponse {
    @required
    TTS_Status: Integer
    @required
    speechid: UInt32
    @required
    success: Boolean
}

intEnum SpeechState {
    V1 = 1
    V3 = 3
    V2 = 2
    V0 = 0
}

structure SpeechStateResponse {
    @required
    TTS_Status: Integer
    @required
    speechstate: SpeechState
    @required
    success: Boolean
}

structure TTSConfiguration {
    fallbacktext: FallbackText
    language: String
    primvolduckpercent: Integer
    rate: Integer
    speechrate: SpeechRate
    @required
    success: Boolean
    ttsendpoint: String
    ttsendpointsecured: String
    voice: String
    volume: Integer
}

structure TTSEnabled {
    @required
    TTS_Status: Integer
    @required
    isenabled: Boolean
}

structure TTSState {
    @required
    state: Boolean
}

// TODO: alias TTSStatus = Integer (Smithy has no direct alias — use a newtype structure or inline the target)

structure TTSStatusResponse {
    @required
    TTS_Status: Integer
    @required
    success: Boolean
}

structure TTSVoice {
    @required
    voice: String
}

list StringList {
    member: String
}
