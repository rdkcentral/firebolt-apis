$version: "2"

/// Shared Firebolt type dictionary.
///
/// Types defined here live in the `com.firebolt` root namespace and are
/// available to all modules via `use com.firebolt#<TypeName>`.
///
/// The generator (`fb-frontend-smithy`) recognises these as prelude types
/// so they resolve correctly even though each module is parsed independently.
namespace com.firebolt

/// An untyped JSON document value.
///
/// Wire representation: JSON-encoded `std::string` in C++.
/// Use `nlohmann::json::parse(value)` to work with the document structure.
///
/// Usage in a module:
///
///     use com.firebolt#JsonDocument
///
///     structure MyOutput {
///         @required
///         payload: JsonDocument
///     }
document JsonDocument
