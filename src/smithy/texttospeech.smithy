$version: "2"
namespace com.firebolt.texttospeech

use com.firebolt#UInt32
use com.firebolt#event

service TexttospeechService {
    version: "1.0"
    operations: [speak, pause, resume, cancel, getspeechstate, onWillspeak, onSpeechstart, onSpeechpause, onSpeechresume, onSpeechcomplete, onSpeechinterrupted, onNetworkerror, onPlaybackerror, listvoices]
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
    speechid: Integer
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
    speechid: Integer
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
    speechid: Integer
}

structure CancelOutput {
    @required
    value: TTSStatusResponse
}

operation getspeechstate {
    input: GetspeechstateInput
    output: GetspeechstateOutput
}

structure GetspeechstateInput {
    @required
    speechid: Integer
}

structure GetspeechstateOutput {
    @required
    value: SpeechStateResponse
}

@event
operation onWillspeak {
    input: OnWillspeakInput
    output: OnWillspeakOutput
}

structure OnWillspeakInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnWillspeakOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechstart {
    input: OnSpeechstartInput
    output: OnSpeechstartOutput
}

structure OnSpeechstartInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechstartOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechpause {
    input: OnSpeechpauseInput
    output: OnSpeechpauseOutput
}

structure OnSpeechpauseInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechpauseOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechresume {
    input: OnSpeechresumeInput
    output: OnSpeechresumeOutput
}

structure OnSpeechresumeInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechresumeOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechcomplete {
    input: OnSpeechcompleteInput
    output: OnSpeechcompleteOutput
}

structure OnSpeechcompleteInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechcompleteOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onSpeechinterrupted {
    input: OnSpeechinterruptedInput
    output: OnSpeechinterruptedOutput
}

structure OnSpeechinterruptedInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnSpeechinterruptedOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onNetworkerror {
    input: OnNetworkerrorInput
    output: OnNetworkerrorOutput
}

structure OnNetworkerrorInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnNetworkerrorOutput {
    @required
    value: SpeechIdEvent
}

@event
operation onPlaybackerror {
    input: OnPlaybackerrorInput
    output: OnPlaybackerrorOutput
}

structure OnPlaybackerrorInput {
    @required
    SpeechId: SpeechIdEvent
}

structure OnPlaybackerrorOutput {
    @required
    value: SpeechIdEvent
}

operation listvoices {
    input: ListvoicesInput
    output: ListvoicesOutput
}

structure ListvoicesInput {
    @required
    language: String
}

structure ListvoicesOutput {
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
