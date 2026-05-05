$version: "2"
namespace com.firebolt.securestorage

service SecurestorageService {
    version: "1.0"
    operations: [get, set, remove, setForApp, removeForApp, clearForApp, clear]
}

operation get {
    input: GetInput
    output: GetOutput
}

structure GetInput {
    @required
    key: String
    @required
    scope: StorageScope
}

structure GetOutput {
    value: String
}

operation set {
    input: SetInput
    output: SetOutput
}

structure SetInput {
    @required
    key: String
    options: StorageOptions
    @required
    scope: StorageScope
    @required
    value: String
}

structure SetOutput {}

operation remove {
    input: RemoveInput
    output: RemoveOutput
}

structure RemoveInput {
    @required
    key: String
    @required
    scope: StorageScope
}

structure RemoveOutput {}

operation setForApp {
    input: SetForAppInput
    output: SetForAppOutput
}

structure SetForAppInput {
    @required
    appId: String
    @required
    key: String
    options: StorageOptions
    @required
    scope: StorageScope
    @required
    value: String
}

structure SetForAppOutput {}

operation removeForApp {
    input: RemoveForAppInput
    output: RemoveForAppOutput
}

structure RemoveForAppInput {
    @required
    appId: String
    @required
    key: String
    @required
    scope: StorageScope
}

structure RemoveForAppOutput {}

operation clearForApp {
    input: ClearForAppInput
    output: ClearForAppOutput
}

structure ClearForAppInput {
    @required
    appId: String
    @required
    scope: StorageScope
}

structure ClearForAppOutput {}

operation clear {
    input: ClearInput
    output: ClearOutput
}

structure ClearInput {
    @required
    scope: StorageScope
}

structure ClearOutput {}

structure StorageOptions {
    @required
    ttl: Double
}

enum StorageScope {
    ACCOUNT = "account"
    DEVICE = "device"
}
