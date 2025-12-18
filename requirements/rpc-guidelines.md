# Firebolt RPC Guidelines

| Contributor   | Organization |
| ------------- | ------------ |
| Joe Martin    | Comcast      |
| Kevin Pearson | Comcast      |

This document describes the guidelines and design principles for Firebolt APIs, with the primary objective of guiding Firebolt developers in following the design principles and conventions enforced by the Firebolt Advisory Board during API reviews.

While Firebolt predated these published guidelines, some existing APIs may not fully adhere to the rules and principles set forth in this document. In such cases, changes made in the same functional area should prioritize consistency with existing APIs over strict adherence to these rules.

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](http://www.ietf.org/rfc/rfc2119.txt).

- [1. Modules](#1-modules)
- [2. Methods](#2-methods)
  - [2.1 Parameters and Response Values](#21-parameters-and-response-values)
  - [2.2 Deprecated Methods](#22-deprecated-methods)
- [Enumerations](#enumerations)
- [Shared Schemas](#shared-schemas)
- [Updates to Existing Methods](#updates-to-existing-methods)

## 1. Modules

- Module names **SHOULD** follow the `PascalCase` naming convention (e.g. `SecondScreen`, `SecureStorage`)
- Module names **MAY** include uppercased words for well-known abbreviations or acronyms (e.g. `HDMI`, `IP`)
- Module names **MUST** be short, clear and succinct
- Module names **SHOULD** maintain a consistent naming convention with modules of a similar functional area (e.g. `HDMIInput`, `HDMIOutput`)
- Modules **MUST NOT** be overloaded with responsibilities. Each module must represent a distinct area of functionality or responsibility
- Modules **MUST** avoid overlapping functionality with other modules, except during deprecation or re-organization of functionality
- Modules **MUST** have their own dedicated error code space in accordance to JSON-RPC 2.0 specifications (e.g. `-48xxx` for all errors in the `Device` module)

## 2. Methods

- Method names **MUST** follow the `camelCase` naming convention
- Method names **MUST** be short, clear and succinct
- Method names **MAY** include uppercased words for well-known abbreviations or acronyms (e.g. `HDMI`, `UI`, etc.)
- Method names **MUST NOT** use abbreviations or acronyms unless they are common or otherwise widely understood (e.g. `id`, `uid`)
- Method names **MUST** follow the noun pluralization of the return value (e.g. an API named `channels` should return a collection of channels)
- Method names **MUST NOT** include verbs in getter methods (e.g. `value` instead of `getValue`)
- Method names **SHOULD** maintain a consistent naming convention with methods of a similar functional area (e.g. `videoMode`, `setVideoMode`)
- Method names for *event notifiers* **SHOULD** follow the format `<propertyName>Changed` (e.g. `languageChanged`, `deviceNameChanged`)
- Method names for *event listeners* for modified properties **SHOULD** follow the format `on<PropertyName>Changed` (e.g. `onLanguageChanged`, `onDeviceNameChanged`)
- Method descriptions **SHOULD** clearly and accurately describe the method's purpose, usage, and response value
- Methods **SHOULD** include at least two example requests and responses
- Methods **SHOULD** include examples that cover common use cases as well as edge cases
- Methods **SHOULD NOT** have multiple responsibilities; each method performs a single, well-defined task within a particular functional area
- Methods **SHOULD NOT** emit error codes in error code spaces assigned to other modules
- Methods **MUST** use standard JSON-RPC error codes (e.g. `-32602: Invalid Params`) when appropriate
- Methods **MUST** define JSON-RPC-compliant error codes and messages for all non-standard errors

### 2.1 Parameters and Response Values

- Parameter and response keys **MUST** follow the `camelCase` naming convention
- Parameter and response keys **MUST** be short, clear and succinct
- Parameter and response keys **MUST** follow the pluralization of the associated value (e.g. `program` for a single program, `programs` for a collection of programs)
- Parameter and response keys **SHOULD** use positive terms (e.g. `enabled` instead of `disabled`, `ready` instead of `notReady`, etc.)
- Parameter and response values **SHOULD** use data constraints (e.g. number ranges, character limits) where appropriate
- Parameter and response values **SHOULD** define default values for optional fields where applicable
- Parameter and response values **SHOULD** adhere to well-known formats or standards (e.g. ISO 8601 for datetime values, ISO 639 for language codes)
- Parameters **SHOULD** use a single object of values instead of multiple individual values for optional fields
- Parameters **MUST** use the name `options` to describe an object containing optional values
- Parameters **SHOULD NOT** accept `null` values
- Parameters **MUST** have required parameters listed first, followed by optional values
- Parameters **MUST NOT** include more than one object for optional values
- Responses **SHOULD** avoid ambiguous values (such as `null` or unstructured objects)
- Responses **SHOULD NOT** contain a flag to denote success (success should generally be implied by lack of an error response)

### 2.2 Deprecated Methods

- Deprecated methods **MUST** include a message that provides details on how a developer should handle the deprecation (e.g. suggest the new method to use instead), when applicable
- Deprecated methods **SHOULD** specify when support will be removed
- Deprecated methods **MUST** provide the Firebolt version where the method was first deprecated
- Deprecated methods **SHOULD** remain supported for at least one minor release (e.g. methods deprecated in v1.5.0 should be supported until at least v1.6.0)

## Enumerations

- Enums **SHOULD** include values reserved for certain failure scenarios, edge cases, or future uses (e.g. `other`, `unknown`)

## Shared Schemas

- Shared schemas **SHOULD** be used whenever two or more methods can reuse the same schema

## Updates to Existing Methods

- Existing method parameters, responses, or shared schemas SHOULD NOT be renamed or removed
