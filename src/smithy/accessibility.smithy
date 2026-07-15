$version: "2"
namespace com.firebolt.accessibility

use com.firebolt#capability
use com.firebolt#propertyReadonly

service AccessibilityService {
    version: "1.0"
    operations: [closedCaptions, closedCaptionsSettings, highContrastUI, voiceGuidance, voiceGuidanceSettings, audioDescriptionSettings, audioDescription]
}

@capability(uses: ["xrn:firebolt:capability:accessibility:closedcaptions"])
@documentation("Get the user's preferred closed-captions settings")
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

@capability(uses: ["xrn:firebolt:capability:accessibility:closedcaptions"])
@propertyReadonly
@documentation("Get the user's preferred closed-captions settings")
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

@capability(uses: ["xrn:firebolt:capability:accessibility:highcontrastui"])
@propertyReadonly
@documentation("The user's preference for a high-contrast UI")
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

@capability(uses: ["xrn:firebolt:capability:accessibility:voiceguidance"])
@documentation("Get the user's preferred voice guidance settings")
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

@capability(uses: ["xrn:firebolt:capability:accessibility:voiceguidance"])
@propertyReadonly
@documentation("Get the user's preferred voice guidance settings")
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

@capability(uses: ["xrn:firebolt:capability:accessibility:audiodescriptions"])
@propertyReadonly
@documentation("Get the user's preferred audio description settings")
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

@capability(uses: ["xrn:firebolt:capability:accessibility:audiodescriptions"])
@propertyReadonly
@documentation("Get the user's audio description setting")
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
