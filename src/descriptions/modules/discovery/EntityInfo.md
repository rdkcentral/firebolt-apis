An EntityInfo object represents an "entity" on the platform. Currently, only entities of type `program` are supported. `programType` must be supplied to identify the program type.

Additionally, EntityInfo objects must specify a properly formed
ContentIdentifiers object, `entityType`, and `title`.  The app should provide
the `synopsis` property for a good user experience if the contentmetadata is not available another way

The ContentIdentifiers must be sufficient for navigating the user to the
appropriate entity or detail screen via a `detail` intent or deep link.
EntityInfo objects must provide at least one WayToWatch object when returned as
part of an `entityInfo` method and a streamable asset is available to the user.
It is optional for the `purchasedContent` method, but recommended because the UI
may use those data.