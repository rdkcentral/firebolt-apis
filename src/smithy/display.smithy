$version: "2"
namespace com.firebolt.display

use com.firebolt#UInt32

service DisplayService {
    version: "1.0"
    operations: [edid, size, maxResolution]
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
