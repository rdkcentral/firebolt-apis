$version: "2"
namespace com.firebolt.voiceguidance

use com.firebolt#property

service VoiceguidanceService {
    version: "1.0"
    operations: [enabled, navigationHints, rate, speed]
}

@property
operation enabled {
    input: EnabledInput
    output: EnabledOutput
}

structure EnabledInput {
}

structure EnabledOutput {
    @required
    value: Boolean
}

@property
operation navigationHints {
    input: NavigationHintsInput
    output: NavigationHintsOutput
}

structure NavigationHintsInput {
}

structure NavigationHintsOutput {
    @required
    value: Boolean
}

@property
operation rate {
    input: RateInput
    output: RateOutput
}

structure RateInput {
}

structure RateOutput {
    @required
    value: SpeechRate
}

@property
operation speed {
    input: SpeedInput
    output: SpeedOutput
}

structure SpeedInput {
}

structure SpeedOutput {
    @required
    value: SpeechRate
}

/// Speech rate multiplier — 0.1 (slowest) to 10.0 (fastest).
@range(min: 0.1, max: 10.0)
float SpeechRate
