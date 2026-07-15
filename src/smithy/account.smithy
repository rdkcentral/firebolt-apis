$version: "2"
namespace com.firebolt.account

use com.firebolt#propertyReadonly

service AccountService {
    version: "1.0"
    operations: [id, uid, session]
}

@propertyReadonly
operation id {
    input: IdInput
    output: IdOutput
}

structure IdInput {
}

structure IdOutput {
    @required
    value: String
}

@propertyReadonly
operation uid {
    input: UidInput
    output: UidOutput
}

structure UidInput {
}

structure UidOutput {
    @required
    value: String
}

operation session {
    input: SessionInput
    output: SessionOutput
}

structure SessionInput {
    @required
    expiresIn: Expiry
    @required
    token: Token
}

structure SessionOutput {}

structure Expiry {
    @required
    value: Integer
}

structure Token {
    @required
    value: String
}
