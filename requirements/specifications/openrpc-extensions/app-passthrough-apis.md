# App Pass-through APIs

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
|-----------------|----------------|
| Jeremy LaCivita | Comcast        |
| Kevin Pearson   | Comcast        |
| Yuri Pasquali   | Sky            |

## 1. Overview
This document describes how one Firebolt App can provide a capability that may be used by another Firebolt App, with the platform as a permission broker that passes the requests and responses to each app without feature-specific logic.

This document covers the App Pass-through Firebolt OpenRPC extension as well as how Firebolt implementations should detect and execute app provided pass-through APIs.

Some APIs require an app to fulfill the request on behalf of another app, e.g. to provide a UX or cross-app data sharing. Generally the calling app doesn't care, or have a say in, which other app provides the API, that is up to the Firebolt distributor.

To facilitate these APIs, Firebolt denotes an OpenRPC tag with OpenRPC extensions to connect the `provide` API to the `use` API.

This document is written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt) and should include the following summary in the Overview section:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Open RPC Extensions](#3-open-rpc-extensions)
  - [3.1. Provided By Extension](#31-provided-by-extension)
  - [3.2. Provider Selection Extension](#32-provider-selection-extension)
- [4. Routing App pass-through APIs](#4-routing-app-pass-through-apis)
  - [4.1. No available providers](#41-no-available-providers)
  - [4.2. Direct pass-through](#42-direct-pass-through)
  - [4.3. Pass-through notifications](#43-pass-through-notifications)
- [5. Provider Candidates](#5-provider-candidates)
- [6. Best Candidate](#6-best-candidate)
- [7. Application Context](#7-application-context)
  - [7.1. Application Context Surfacing](#71-application-context-surfacing)
  - [7.2. Application Context Selection](#72-application-context-selection)
- [8. API Gateway](#8-api-gateway)
- [9. Example: User Interest](#9-example-user-interest)
  - [9.1. User Interest Pull](#91-user-interest-pull)
  - [9.2. User Interest Push](#92-user-interest-push)

## 3. Open RPC Extensions

### 3.1. Provided By Extension
Firebolt OpenRPC **MUST** support a `string` `x-provided-by` extension property on the `capabilities` tag that denotes a method is provided by some app on the device registering for the specified provider API, e.g.:

```json
{
    "methods": [
        {
            "name": "Keyboard.standard",
            "tags": [
                {
                    "name": "capabilities",
                    "x-provided-by": "Keyboard.onRequestStandard",
                    "x-uses": [
                        "xrn:firebolt:capability:input:keyboard"
                    ]
                }
            ]
        }
    ]
}
```

The method denoted by `x-provided-by` is referred to as the "*provider*" or "*provider method*" for the remainder of this document.

The method with the `x-provided-by` extension is referred to as the "*platform method*" for the remainder of this document.

To prevent unresolvable chaining of methods the `x-provided-by` extension **MUST NOT** be used on a method with any value in the `x-provides` extension.

To prevent compound methods a platform method **MUST** `use` a single capability or `manage` a single capability, but not both.

The provider method **MUST** provide the same capability that the platform method either uses or manages.

If a platform method has no provider method then it is not a valid Firebolt OpenRPC method schema, and a validation error **MUST** be generated.

### 3.2. Provider Selection Extension
Firebolt OpenRPC **MUST** support a `string` `x-provider-selection` extension property on the `capabilities` tag that denotes how to pick the best provider candidate, e.g.:

```json
{
    "methods": [
        {
            "name": "Keyboard.standard",
            "tags": [
                {
                    "name": "capabilities",
                    "x-provided-by": "Keyboard.onRequestStandard",
                    "x-provider-selection": "appId"
                    "x-uses": [
                        "xrn:firebolt:capability:input:keyboard"
                    ]
                }
            ],
            "parameters": [
                {
                    "name": "appId",
                    "type": "string"
                }
            ]
        }
    ]
}
```

The value of `x-provider-selection`, if defined, **MUST** be either `"appId"` or `"focus"`.

Given the `x-provider-selection` extension has the value `"appId"`, then the method **MUST** have an `appId` `string` parameter.

## 4. Routing App pass-through APIs
App pass-through APIs may be routed in one of several ways.

When an app calls a platform method, i.e. one with an `x-provided-by` extension, the platform **MUST** use one of the routing methods defined in this section based on various properties of the method.

### 4.1. No available providers
When an app calls a platform method with an `x-provided-by` extension, the platform **MUST** return an unavailable error if there is no [candidate app](#5-provider-candidates) to execute the provider method.

```json
{
    "id": 1,
    "error": {
        "code": -50300,
        "message": "Capability <XRN> is unavailable."
    }
}
```

Where `<XRN>` is the capability XRN string, e.g. `xrn:firebolt:capabilities:example:foo`.

### 4.2. Direct pass-through
A direct pass-through is where a single app provides a single response to a single request by another app.

This section only applies to app provider methods that do not have an `event` tag.

The platform method result schema **MUST** either:

> Match the `x-response` schema on the provider method so that the result can be passed through.
>
> or
>
> Have a property that matches the `x-response-name` string and `x-response` schema on the
> provider method so that the result can be composed and passed through.

The platform **MUST** call the provider method from the [best candidate](#6-best-candidate) app and acquire the result.

If the platform method result schema matches the `x-response` schema on the provider method then the value **MUST** be used as-is.

Otherwise if the platform method result schema has a property that matches the `x-response` schema on the provider method then the value **MUST** be composed into an object under the corresponding property name.

### 4.3. Pass-through notifications
Firebolt events have a synchronous subscriber registration method, e.g. `Lifecycle.onInactive(true)`, in addition to asynchronous notifications when the event actually happens. For events powered by an app pass-through, only the asynchronous notifications are passed in by the providing app. The initial event registration is handled by the platform, and the success response is not handled by the providing app.

This section only applies to platform methods that have an `event` tag.

App provided event registration **MUST** not return an availability error due to a lack of providers, since one may be launched at a future point.

To ensure that event provider methods all behave the same the provider method **MUST** have a `result` schema with `"type"` set to `"null"`, since it will not expect any data in the response from the platform after pushing the notification.

The platform method result schema **MUST** either:

> Match the *last* parameter schema on the provider method so that the result can be passed through.
>
> Have a property that matches the *last* parameter name and schema on the provider method so that the result can be passed through.

Example platform method with context:
```json
{
    "name": "onFoo",
    "tags": [
        {
            "name": "capabilities",
            "x-uses": [
                "xrn:firebolt:capabilities:example:foo"
            ],
            "x-provided-by": "foo"
        },
        {
            "name": "event"
        }
    ],
    "params": [
        {
            "name": "context1",
            "schema":{
                "type": "string"
            }
        },
        {
            "name": "context2",
            "schema": {
                "type": "number"
            }
        }
    ],
    "result": {
        "name": "value",
        "schema": {
            "type": "boolean"
        }
    }
}
```

Matching provider method:

```json
{
    "name": "foo",
    "tags": [
        {
            "name": "capabilities",
            "x-provides": "xrn:firebolt:capabilities:example:foo"
        }
    ],
    "params": [
        {
            "name": "context1",
            "schema":{
                "type": "string"
            }
        },
        {
            "name": "context2",
            "schema": {
                "type": "number"
            }
        },
        {
            "name": "value",
            "schema": {
                "type": "boolean"
            }
        }
    ]
}
```

When a provider app calls a provider method mapped to an event the platform **MUST** ignore the notification if the app is not a [candidate app](#5-provider-candidates) for this capability.

If the platform method result schema matches the *last* parameter schema on the provider method then the value **MUST** be used as-is.

Otherwise if the platform method result schema has a property that matches the *last* parameter schema on the provider method then the value **MUST** be composed into an object under the corresponding property name.

If the value was composed into the platform method result under a matching property, then any context parameter values from the provider method that correspond to a property name and schema in the platform method result **MUST** also be composed into the platform method result under those properties.

Finally the platform **MUST** dispatch the notification to the app that registered for the event via the original platform method, using all but the last parameter as context.

## 5. Provider Candidates
When a platform method with an `x-provided-by` extension is called, then
all loaded apps that have permission to provide the capability **MUST** be
considered as candidates to fulfill the method.

## 6. Best Candidate
A provider candidate app **MUST** include the capability in the `provide` section of the app manifest.

If a provider candidate is currently running, it **MUST** have already registered to provide the capability in
question.

If there is exactly one provider candidate then it **MUST** be the best candidate.

If there is more than one provider candidate then the following requirements **MUST** be used to select the best candidate, in order.

> Given there is an `x-provider-selection` extension on the platform method capabilities tag, when that extension is set to the value `"appId"` then the provider candidate with an appId that matches the value of the platform method `appId` parameter **MUST** be the best candidate.
> 
> Given there is an `x-provider-selection` extension on the platform method capabilities tag, when that extension is set to the value `"focus"` then the provider candidate that currently has RCU focus **MUST** be the best candidate.
>
> Given there is no `x-provider-selection` extension, or it has a value not defined in this specification, when there is a provider candidate that was launched more recently then the other candidates then that provider candidate **MUST** be the best candidate.

## 7. Application Context

Application Context provides a mechanism for applications to know the identity of the applications they are communicating with. Application Context can be given in both directions. An application that uses a capability can know which app is providing that capability. An application that provides a capability can know which app is using that capability.

### 7.1. Application Context Surfacing

A method may be configured to surface application context by inserting the "other" appId into the request or response and is triggered by the presense of an `appId` in either the platform method or the provider method, but not both.

If a "composite result" was used to wrap the provider method value and the platform method's schema has an `appId` `string` property at the top level then the property's value **MUST** be set to the the appId of the providing app for that result.

If a platform method is an `event` and the event result is a "composite result" with an `appId` `string` property at the top level, then the property **MUST** be set to the appId that initiated the provider (push) call.

If a platform method is an `event` and the event has an `appId` `string` context parameter and the provider method *does not* have an `appId` parameter, then the `appId` context parameter **MUST** be set to the appId that initiated the provider (push) call.

If the provider method has an `appId` `string` parameter and the platform method does not have an `appId` parameter, then the id of app that initiated the platform method call **MUST** be used to set the `appId` in the provider method request.

### 7.2. Application Context Selection

A method may be configured to enabled application context selection by exposing an appId parameter to allow the calling app to influence which app will provide it.

When a platform method is invoked, the gateway will find the provider using the `Provider Candidate` rules as described above. However, some Firebolt APIs allow selecting the provider that should be used. If a platform method request schema is a "composite request" with `appId` `string` parameter but the provider method request schema is not a composite request, then the given appId shall be used to select the provider. 
If "appId" is a required parameter in the platform method request schema, then it must be supplied. If it is not, then the request should fail with invalid parameters. If it is an optional parameter and it is not supplied, then the gateway should use rules in "Provider Candidate" section for selecting the candidate.

## 8. API Gateway
The Firebolt API Gateway **MUST** detect app-passthrough APIs and map the `use`/`manage` APIs to the corresponding `provide` APIs by parsing the Firebolt OpenRPC Specification and following the logic outline in this document.

## 9. Example: User Interest

The following schemas are referenced by these examples:

```json
{
    "components": {
        "schemas": {
            "InterestType": {
                "type": "string",
                "enum": [
                    "interest",
                    "disinterest"
                ]
            },
            "InterestReason": {
                "type": "string",
                "enum": [
                    "playlist"
                ]
            },
            "EntityDetailsFromApp": {
                "type": "object",
                "properties": {
                    "appId": {
                        "type": "string"
                    },
                    "entity": {
                        "$ref": "https://meta.comcast.com/firebolt/entity#/definitions/EntityDetails"
                    }
                },
                "required": [
                    "appId",
                    "entity"
                ]
            }
        }
    }
}
```

### 9.1. User Interest Pull

Platform method:

```json
{
    "methods": [
        {
            "name": "requestUserInterest",
            "tags": [
                {
                    "name": "capabilities",
                    "x-provided-by": "Discovery.onRequestUserInterest",
                    "x-uses": [
                        "xrn:firebolt:capability:discovery:interest"
                    ]
                }
            ],
            "params": [
                {
                    "name": "type",
                    "required": true,
                    "schema": {
                        "$ref": "#/components/schemas/InterestType"
                    }
                },
                {
                    "name": "reason",
                    "required": true,
                    "schema": {
                        "$ref": "#/components/schemas/InterestReason"
                    }
                }
            ],
            "result": {
                "name": "interest",
                "schema": {
                    "$ref": "#/components/schemas/EntityDetailsFromApp",
                }
            }
        }
    ]
}
```

Provider method:

```json
{
    "methods": [
        {
            "name": "onRequestUserInterest",
            "tags": [
                {
                    "name": "capabilities",
                    "x-provides": "xrn:firebolt:capability:discovery:interest"
                },
                {
                    "name": "event",
                    "x-response": {
                        "$ref": "https://meta.comcast.com/firebolt/entity#/definitions/EntityDetails"
                    }
                }
            ],
            "result": {
                "name": "request",
                "schema": {
                    "type": "object",
                    "properties": {
                        "type": {
                            "$ref": "#/components/schemas/InterestType",
                        },
                        "reason": {
                            "$ref": "#/components/schemas/InterestReason",
                        }
                    }
                }
            }
        }
    ]
}
```

### 9.2. User Interest Push

Provider method:

```json
{
    "methods": [
        {
            "name": "userInterest",
            "tags": [
                {
                    "name": "capabilities",
                    "x-provides": "xrn:firebolt:capability:discovery:interest"
                }
            ],
            "params": [
                {
                  "name": "type",
                  "schema": {
                      "$ref": "#/components/schemas/InterestType",
                  }
                },
                {
                  "name": "reason",
                  "schema": {
                      "$ref": "#/components/schemas/InterestReason",
                  }
                },
                {
                  "name": "entity",
                  "schema": {
                      "$ref": "https://meta.comcast.com/firebolt/entity#/definitions/EntityDetails"
                  }                    
                }
            ],
            "result": {
                "name": "result",
                "schema": {
                    "type": "null"
                }
            }
        }
    ]
}
```

Platform Method:

```json
{
    "methods": [
        {
            "name": "onUserInterest",
            "tags": [
                {
                    "name": "capabilities",
                    "x-provided-by": "Discovery.userInterest",
                    "x-uses": [
                        "xrn:firebolt:capability:discovery:interest"
                    ]
                },
                {
                    "name": "event"
                }
            ],
            "params": [],
            "result": {
                "name": "interest",
                "schema": {
                    "type": "object",
                    "properties": {
                        "appId": {
                            "type": "string"
                        },
                        "type": {
                            "$ref": "#/components/schemas/InterestType"
                        },
                        "reason": {
                            "$ref": "#/components/schemas/InterestReason"
                        },
                        "entity": {
                            "$ref": "https://meta.comcast.com/firebolt/entity#/definitions/EntityDetails"
                        }
                    }

                }
            }
        }
    ]
}
```
