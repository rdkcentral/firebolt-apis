# Firebolt RPC Guidelines

This document describes the guidelines and design principles for Firebolt APIs.

The primary objective guide Firebolt developers in adhering to the design principles and conventions that the Firebolt Advisory Board expects and enforces during API reviews.

While Firebolt predated these published guidelines, some existing APIs may not adhere to the rules and principles set forth in this document.  In certain cases, it may be more appropriate to design new APIs so that they remain consistent with existing Firebolt APIs that support similar functional-areas (such as those in the same module) instead of following the rules set in this document.

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](http://www.ietf.org/rfc/rfc2119.txt).

- [Modules](#modules)
- [Methods](#methods)
  - [Parameters and Response Values](#parameters-and-response-values)
- [Deprecated Methods](#deprecated-methods)
- [Enumerations](#enumerations)
- [Shared Schemas](#shared-schemas)
- [Updates to Existing Methods](#updates-to-existing-methods)

## Modules

- Module names **SHOULD** use the `PascalCase` naming convention
- Module names **MAY** include uppercased words for well-known abbreviations or acronyms (e.g. `HDMI`, `IP`, etc.)
- Module names **MUST** be short, clear and succinct
- Module names **SHOULD** maintain a consistent naming convention with modules of a similar functional area (e.g. `HDMIInput`, `HDMIOutput`)
- Modules **MUST NOT** be overloaded with responsibilities, and instead represent a distinct area of functionality or responsibility
- Modules **MUST** avoid overlap in scope or functionality with other modules (except during periods of deprecation or re-organization of functionality)
- Modules **MUST** have their own dedicated error code space in accordance to JSON-RPC 2.0 specifications (e.g. `-48xxx` for all errors in the `Device` module)

## Methods

- Method names **MUST** use the `camelCase` naming convention
- Method names **MUST** be short, clear and succinct
- Method names **MAY** include uppercased words for well-known abbreviations or acronyms (e.g. `HDMI`, `UI`, etc.)
- Method names **MUST NOT** use abbreviations or acronyms unless they are common or otherwise widely understood (e.g. `id`, `uid`)
- Method names **MUST** follow the noun pluralization of the return value (e.g. an API named `channels` should return a collection of channels)
- Method names **SHOULD NOT** include verbs in getter methods (e.g. `value` instead of `getValue`)
- Method names **SHOULD** maintain a consistent naming convention with methods of a similar functional area (e.g. `videoMode`, `setVideoMode`)
- Method names that notify a listener on modified properties **MUST** follow the format `on<PropertyName>Changed` (e.g. `onLanguageChanged`, `onDeviceNameChanged`)
- Method descriptions **SHOULD** clearly and accurately describe the method's purpose, usage, and response value
- Method examples **MUST** include at least one example of a request and response
- Method examples **SHOULD** cover common use cases as well as edge cases
- Methods **SHOULD NOT** be overloaded with multiple responsibilities; each method performs a single, well-defined task for a particular functional area
- Methods **SHOULD NOT** emit error codes in error code spaces assigned to other modules
- Methods **MUST** use standard JSON-RPC error codes (e.g. `-32602: Invalid Params`) when appropriate
- Methods **MUST** define JSON-RPC-compliant error codes and messages for all non-standard errors

### Parameters and Response Values

- Parameter and response keys **MUST** use the `camelCase` naming convention
- Parameter and response keys **MUST** be short, clear and succinct
- Parameter and response keys **MUST** follow the pluralization of the associated value (e.g. `program` for a single program, `programs` for a collection of programs)
- Parameter and response keys **SHOULD** use positive terms (e.g. `enabled` instead of `disabled`, `ready` instead of `notReady`, etc.)
- Parameter and response values **SHOULD** use data constraints (e.g. number ranges, character limits) when appropriate
- Parameter and response values **SHOULD** define default values for optional fields where applicable
- Parameter and response values **SHOULD** adhere to well-known or standardized formats (e.g. ISO 8601 for datetime values, ISO 639 for language codes)
- Parameters and responses **SHOULD** use a single object to define multiple parameters instead of multiple, individual parameters
- Parameters **SHOULD NOT** allow `null` values
- Responses **SHOULD** avoid returning ambiguous values (e.g. `null` values or objects without a defined structure)

## Deprecated Methods

- Deprecated methods **MUST** include a message that provides details on how a developer should handle the deprecation (e.g. suggest the new method to use instead), when applicable
- Deprecated methods **SHOULD** include a message that provides details on when support for the method will be removed
- Deprecated methods **MUST** provide the Firebolt version where the method was first deprecated
- Deprecated methods **SHOULD** remain supported for at least one minor release after their deprecation (e.g., methods deprecated in v1.5.0 **SHOULD** be supported until at least v1.6.0)

## Enumerations

- Enum values **MUST** use the `camelCase` naming convention
- Enum values **MUST** be prefixed with text characters (e.g. `VIDEO_MODE_1080P60`)
- Enums **SHOULD** include values reserved for failure scenarios, edge cases, or future use (e.g. `other`, `unknown`)

## Shared Schemas

- Shared schemas **SHOULD** be used whenever two or more methods can leverage the same schema

## Updates to Existing Methods

- Existing method parameters, responses, or shared schemas SHOULD NOT be renamed or removed
