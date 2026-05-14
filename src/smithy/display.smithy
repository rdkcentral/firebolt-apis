$version: "2"
namespace com.firebolt.display

use com.firebolt#UInt32

service DisplayService {
    version: "1.0"
    operations: [edid, size, maxResolution, videoResolutions, colorimetry]
}

operation edid {
    input: EdidInput
    output: EdidOutput
}

structure EdidInput {
}

structure EdidOutput {
    @required
    value: String
}

operation size {
    input: SizeInput
    output: SizeOutput
}

structure SizeInput {
}

structure SizeOutput {
    @required
    value: DisplaySize
}

operation maxResolution {
    input: MaxResolutionInput
    output: MaxResolutionOutput
}

structure MaxResolutionInput {
}

structure MaxResolutionOutput {
    @required
    value: DisplaySize
}

structure DisplaySize {
    @required
    height: UInt32
    @required
    width: UInt32
}

/// HD video resolution formats supported by the connected display.
enum VideoResolution {
    R720P50 = "720p50"
    R720P60 = "720p60"
    R1080P50 = "1080p50"
    R1080P60 = "1080p60"
    R2160P50 = "2160p50"
    R2160P60 = "2160p60"
}

list VideoResolutionList {
    member: VideoResolution
}

/// SDR/HDR colorimetry standards supported by the connected display.
enum ColorimetryStandard {
    BT709 = "bt709"
    BT2020 = "bt2020"
}

list ColorimetryStandardList {
    member: ColorimetryStandard
}

/// Returns an unordered list of HD video resolution formats supported by the
/// connected or integral display. Returns an empty list when no HDMI display
/// is connected.
operation videoResolutions {
    input: VideoResolutionsInput
    output: VideoResolutionsOutput
}

structure VideoResolutionsInput {}

structure VideoResolutionsOutput {
    @required
    value: VideoResolutionList
}

/// Returns the SDR and HDR colorimetry standards supported by the connected
/// or integral display. Returns an empty list when no HDMI display is connected.
operation colorimetry {
    input: ColorimetryInput
    output: ColorimetryOutput
}

structure ColorimetryInput {}

structure ColorimetryOutput {
    @required
    value: ColorimetryStandardList
}
