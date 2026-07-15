$version: "2"
namespace com.firebolt.presentation

use com.firebolt#propertyReadonly

service PresentationService {
    version: "1.0"
    operations: [focused]
}

@propertyReadonly
operation focused {
    input: FocusedInput
    output: FocusedOutput
}

structure FocusedInput {
}

structure FocusedOutput {
    @required
    value: Boolean
}
