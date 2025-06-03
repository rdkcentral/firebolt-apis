# Firebolt RPC Guidelines

This document describes the guidelines and design principles for Firebolt APIs.

The primary objective guide Firebolt developers in adhering to the design principles and conventions that the Firebolt Advisory Board expects and enforces during API reviews.

While Firebolt predated these published guidelines, some existing APIs may not adhere to the rules and principles set forth in this document.  In certain cases, it may be more appropriate to design new APIs so that they remain consistent with existing Firebolt APIs that support similar functional-areas (such as those in the same module) instead of following the rules set in this document.

## Modules

- Module names should use the `PascalCase` naming convention
- Module names MAY include uppercased words for well-known abbreviations or acronyms (e.g. `HDMI`, `IP`, etc.)
- Module names MUST be short, clear and succinct
- Module names should maintain a consistent naming convention with modules of a similar functional area (e.g. `HDMIInput`, `HDMIOutput`)
- Modules MUST NOT be overloaded with responsibilities, and instead represent a distinct area of functionality or responsibility
- Modules MUST avoid overlap in scope or functionality with other modules (except during periods of deprecation or re-organization of functionality)
- Modules MUST have their own dedicated error code space in accordance to JSON-RPC 2.0 specifications (e.g. `-48xxx` for all errors in the `Device` module)

## Methods

- Method names MUST use the `camelCase` naming convention
- Method names MUST be short, clear and succinct
- Method names MAY include uppercased words for well-known abbreviations or acronyms (e.g. `HDMI`, `UI`, etc.)
- Method names MUST NOT use abbreviations or acronyms unless they are common or otherwise widely understood (e.g. `id`, `uid`)
- Method names MUST follow the noun pluralization of the return value (e.g. an API named `channels` should return a collection of channels)
- Method names should not include verbs in getter and setter methods (e.g. `value` instead of `getValue` or `setValue`)
- Method names should maintain a consistent naming convention with methods of a similar functional area (e.g. `videoMode`, `setVideoMode`)
- Method examples MUST include at least one example of a request and response
- Method examples should cover common use cases as well as edge cases
- Method descriptions should clearly and accurately describe the method's purpose, usage, and response value
- Methods should not be overloaded with multiple responsibilities; each method should perform a single, well-defined task
- Methods should NOT emit error codes in spaces assigned to other modules

### Parameters

- Parameter keys MUST use the `camelCase` naming convention
- Parameter keys MUST be short, clear and succinct
- Parameter keys MUST be singular when the parameter is a single object or value
- Parameter keys MUST be pluralized when the parameter is a collection/array of values
- Parameter keys should use positive terms to maintain clarity (e.g. `enabled` instead of `disabled`, `ready` instead of `notReady`, etc.)
- Parameters should use data constraints (e.g. number ranges, character limits) as appropriate
- Parameters should not allow `null` values or empty string values
- Parameters should include default values for optional fields where applicable
- Parameter values should adhere to well-known or standardized formats (e.g. ISO 8601 for datetime values, ISO 639 for language codes)
- Objects should be used as parameters over multiple individual parameters
- TODO: Required vs optional

### Responses

- Response keys MUST use the `camelCase` naming convention
- Response keys should use positive terms to maintain clarity (e.g. `enabled` instead of `disabled`, `ready` instead of `notReady`, etc.)
- Responses MUST include all required fields
- Responses should avoid returning ambiguous values (e.g. unstructured objects, `null` values, or empty strings)
- TODO: Required vs optional

### Errors

- Methods MUST define error codes and messages for all non-standard/JSON-RPC failure scenarios
- Methods MUST use standard JSON-RPC error codes (e.g. `-32602: Invalid Params`, when applicable)

## Deprecated Methods

- Deprecated methods MUST include a message that provides details on the new method to be used instead, when applicable
- Deprecated methods should include a message that provides details on when support for the method will be removed, when applicable
- Deprecated methods MUST provide the Firebolt version when the method was first deprecated
- Deprecated methods should remain supported for at least one minor release after their deprecation (e.g., methods deprecated in v1.5.0 should be supported until at least v1.6.0)

## Events

- TODO

## JSON Schemas

- Shared schemas should be used whenever two or more methods can leverage the same schema

## Enumerations

- Enum values MUST use the `camelCase` naming convention
- Enum values MUST be prefixed with a string of text characters (e.g. `VIDEO_MODE_1080P60`)
- Enums should include values reserved for future or edge cases (e.g. `DynamicRangeFormat.UNKNOWN`)

## Updates to Existing Methods

- Existing fields in method parameters, responses, or shared schemas SHOULD NOT be renamed or removed
