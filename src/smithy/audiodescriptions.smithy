$version: "2"
namespace com.firebolt.audiodescriptions

use com.firebolt#property

service AudiodescriptionsService {
    version: "1.0"
    operations: [enabled]
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
