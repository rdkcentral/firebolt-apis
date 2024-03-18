# App Pass-through APIs

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
|-----------------|----------------|
| Jeremy LaCivita | Comcast        |
| Kevin Pearson   | Comcast        |

## 1. Overview
This document describes the the `x-lifecycle` Firebolt OpenRPC extension.

Some APIs require that they are only called when an app is in a certain Lifecycle state.

To facilitate these APIs, Firebolt denotes an OpenRPC extension to limit the states than ap app is allowed to be in when a method request is made.

This document is written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt) and should include the following summary in the Overview section:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Lifecycle Extension on the Capabilities tag](#3-lifecycle-extension-on-the-capabilities-tag)
  - [Events](#events)

## 3. Lifecycle Extension on the Capabilities tag
Firebolt OpenRPC **MUST** support an extension named `x-lifecycle` that denotes a method should not be requested when an app is in a particular state.

The `x-lifecycle` extension **MUST** only be used on a method's `capabilities` tag.

The `x-lifecycle` value **MUST** be an array with one or more of the following values:

 - initializing
 - foreground
 - background
 - inactive

If the `x-lifecycle` value is not provided, then it **MUST** default to:

```json
[
    "initializing"
    "foreground"
    "background"
    "inactive"
]
```
 
If a method has an `x-lifecycle` extension on the `capabilities` tag then that method **MUST NOT** return a success/result unless the app is in one of the listed lifecycle states during the time of the method request.

If the app is not in one of the listed lifecycle states during the time of the request then the method **MUST** return an unavailable error.

**TODO**: define the error?

### Events
If a method with an `event` tag has the `x-lifecycle` extension set to a valid value then event notifications **MUST NOT** be sent to the app when it is not in one of the listed states during the time of the notification.

The default behavior is that events not sent to an app due to `x-lifecycle` configuration **MUST NOT** be stored and sent to the app at a later point.

An overriding requirement **MUST** exist in a specific feature document in order for a specific event to deviate from the default behavior.

Registering for event notifications is possible in any lifecycle state and **MUST NOT** be prevented by a method's `x-lifecycle` value.
