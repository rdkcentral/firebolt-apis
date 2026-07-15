$version: "2"
namespace com.firebolt.keyboard

use com.firebolt#event

service KeyboardService {
    version: "1.0"
    operations: [email, password, standard, onRequestStandard, onRequestPassword, onRequestEmail]
}

operation email {
    input: EmailInput
    output: EmailOutput
}

structure EmailInput {
    message: String
    @required
    type: EmailUsage
}

structure EmailOutput {
    @required
    value: String
}

operation password {
    input: PasswordInput
    output: PasswordOutput
}

structure PasswordInput {
    message: String
}

structure PasswordOutput {
    @required
    value: String
}

operation standard {
    input: StandardInput
    output: StandardOutput
}

structure StandardInput {
    @required
    message: String
}

structure StandardOutput {
    @required
    value: String
}

@event
operation onRequestStandard {
    input: OnRequestStandardInput
    output: OnRequestStandardOutput
}

structure OnRequestStandardInput {
}

structure OnRequestStandardOutput {
    @required
    value: KeyboardProviderRequest
}

@event
operation onRequestPassword {
    input: OnRequestPasswordInput
    output: OnRequestPasswordOutput
}

structure OnRequestPasswordInput {
}

structure OnRequestPasswordOutput {
    @required
    value: KeyboardProviderRequest
}

@event
operation onRequestEmail {
    input: OnRequestEmailInput
    output: OnRequestEmailOutput
}

structure OnRequestEmailInput {
}

structure OnRequestEmailOutput {
    @required
    value: KeyboardProviderRequest
}

enum EmailUsage {
    SIGN_IN = "signIn"
    SIGN_UP = "signUp"
}

structure KeyboardParameters {
    @required
    message: String
}

structure KeyboardProviderRequest {
    @required
    correlationId: String
    @required
    parameters: KeyboardParameters
}

enum KeyboardType {
    EMAIL = "email"
    PASSWORD = "password"
    STANDARD = "standard"
}
