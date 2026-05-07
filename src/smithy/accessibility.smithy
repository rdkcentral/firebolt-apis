$version: "2"
namespace com.firebolt.accessibility

use com.firebolt#propertyReadonly

service AccessibilityService {
    version: "1.0"
    operations: [closedCaptions, closedCaptionsSettings, highContrastUI, voiceGuidance, voiceGuidanceSettings, audioDescriptionSettings, audioDescription]
}

operation closedCaptions {
    input: ClosedCaptionsInput
    output: ClosedCaptionsOutput
}

structure ClosedCaptionsInput {
}

structure ClosedCaptionsOutput {
    @required
    value: ClosedCaptionsSettings
}

@propertyReadonly
operation closedCaptionsSettings {
    input: ClosedCaptionsSettingsInput
    output: ClosedCaptionsSettingsOutput
}

structure ClosedCaptionsSettingsInput {
}

structure ClosedCaptionsSettingsOutput {
    @required
    value: ClosedCaptionsSettings
}

@propertyReadonly
operation highContrastUI {
    input: HighContrastUIInput
    output: HighContrastUIOutput
}

structure HighContrastUIInput {
}

structure HighContrastUIOutput {
    @required
    value: Boolean
}

operation voiceGuidance {
    input: VoiceGuidanceInput
    output: VoiceGuidanceOutput
}

structure VoiceGuidanceInput {
}

structure VoiceGuidanceOutput {
    @required
    value: VoiceGuidanceSettings
}

@propertyReadonly
operation voiceGuidanceSettings {
    input: VoiceGuidanceSettingsInput
    output: VoiceGuidanceSettingsOutput
}

structure VoiceGuidanceSettingsInput {
}

structure VoiceGuidanceSettingsOutput {
    @required
    value: VoiceGuidanceSettings
}

@propertyReadonly
operation audioDescriptionSettings {
    input: AudioDescriptionSettingsInput
    output: AudioDescriptionSettingsOutput
}

structure AudioDescriptionSettingsInput {
}

structure AudioDescriptionSettingsOutput {
    @required
    value: AudioDescriptionSettings
}

@propertyReadonly
operation audioDescription {
    input: AudioDescriptionInput
    output: AudioDescriptionOutput
}

structure AudioDescriptionInput {
}

structure AudioDescriptionOutput {
    @required
    value: Boolean
}

structure AudioDescriptionSettings {
    @required
    enabled: Boolean
}

structure ClosedCaptionsSettings {
    @required
    enabled: Boolean
    preferredLanguages: StringList
}

structure VoiceGuidanceSettings {
    @required
    enabled: Boolean
    @required
    navigationHints: Boolean
    @required
    rate: Double
}

list StringList {
    member: String
}

/// Speech rate multiplier — 0.1 (slowest) to 10.0 (fastest).
@range(min: 0.1, max: 10.0)
float SpeechRate
