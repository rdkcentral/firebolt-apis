$version: "2"
namespace com.firebolt.profile

service ProfileService {
    version: "1.0"
    operations: [approveContentRating, approvePurchase, flags]
}

operation approveContentRating {
    input: ApproveContentRatingInput
    output: ApproveContentRatingOutput
}

structure ApproveContentRatingInput {
}

structure ApproveContentRatingOutput {
    @required
    value: Boolean
}

operation approvePurchase {
    input: ApprovePurchaseInput
    output: ApprovePurchaseOutput
}

structure ApprovePurchaseInput {
}

structure ApprovePurchaseOutput {
    @required
    value: Boolean
}

operation flags {
    input: FlagsInput
    output: FlagsOutput
}

structure FlagsInput {
}

structure FlagsOutput {
    @required
    value: StringMap
}

map StringMap {
    key: String
    value: String
}
