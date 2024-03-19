# App Pass-through APIs

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
|-----------------|----------------|
| Jeremy LaCivita | Comcast        |
| Kevin Pearson   | Comcast        |
| Yuri Pasquali   | Sky            |

## 1. Overview
This document describes how one Firebolt App can provide a capability that may be used by another Firebolt App leveraging the platform as a permission broker that passes the requests and respones to each app with out feature-specific logic.

This document covers the App Pass-through Firebolt OpenRPC extension as well as how Firebolt implementations should detect and execute app provided pass-through APIs.

Some APIs require an app to fulfill the request on behalf of another app, e.g. to provide a UX or cross-app data sharing. Generally the calling app doesn't care or have a say in which other app provides the API, that is up to the Firebolt distributor.

To facilitate these APIs, Firebolt denotes an OpenRPC tag with OpenRPC extensions to connect the `provide` API to the `use` API.

This document is written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt) and should include the following summary in the Overview section:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Open RPC Extensions](#3-open-rpc-extensions)
  - [3.1. Provided By Extension](#31-provided-by-extension)
  - [3.2. Multiple Providers Extension](#32-multiple-providers-extension)
- [4. Routing App pass-through APIs](#4-routing-app-pass-through-apis)
- [5. Direct pass-through results](#5-direct-pass-through-results)
- [6. Aggregated pass-through results](#6-aggregated-pass-through-results)
- [7. Pass-through notifications](#7-pass-through-notifications)
- [8. Provider Candidates](#8-provider-candidates)
- [9. Best Candidate](#9-best-candidate)
- [10. Session Transformations](#10-session-transformations)
- [11. Provider Parameter Injection](#11-provider-parameter-injection)
- [12. API Gateway](#12-api-gateway)
- [13. Example: User Interest](#13-example-user-interest)
- [14. Example: Keyboard](#14-example-keyboard)

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

The method denoted by `x-provided-by` is referred to as the "provider" or "provider method" for the remainder of this document.

The method with the `x-provided-by` extension is referred to as the "platform method" for the remainder of this document.

To prevent unresolvable chaining of methods the `x-provided-by` extension **MUST NOT** be used on a method with any value in the `x-provides` extension.

To prevent compound methods an platform method **MUST** `use` a single capability or `manage` a single capability, but not both.

The provider method **MUST** provide the same capability that the platform method either uses or manages.

If an platform method has no provider method then it is not a valid Firebolt OpenRPC method schema, and a validation error **MUST** be generated.

### 3.2. Multiple Providers Extension
Firebolt OpenRPC **MUST** support a `string` `x-multiple-providers` extension property on the `capabilities` tag that denotes a single method request may be provided by multiple apps on the device registering for the specified provider API, e.g.:

```json
{
    "methods": [
        {
            "name": "Content.search",
            "tags": [
                {
                    "name": "capabilities",
                    "x-provided-by": "Discover.onRequestSearch",
                    "x-multiple-providers": true,
                    "x-uses": [
                        "xrn:firebolt:capability:discovery:search"
                    ]
                }
            ]
        }
    ]
}
```

Setting `x-multiple-providers` to `true` means that all available apps that can provide the capability **MUST** be called and their results aggregated into an array for the final result.

A platform method with `x-multiple-providers` set to `true` **MUST** have an `array` result type.

## 4. Routing App pass-through APIs
When an app calls a platform method the platform **MUST** return an unavailable error if there is no candidate app to execute the provider method.

## 5. Direct pass-through results
A direct pass-through is where a single app provides a single response to a single request by another app.

This section only applies to app provider methods that do not have an `event` tag and do not have the `x-multiple-providers` extension set to `true`.

The platform method result schema **MUST** either:

> Match the `x-response` schema on the provider method so that the result can be passed through.
>
> or
> 
> Have a property that matches the `x-response` schema on the provider method so that the result can
> be composed and passed through.

When an app calls a platform method the platform **MUST** return an unavailable error if there is no [candidate app](#7-provider-candidates) to execute the provider method.

The platform **MUST** call the provider method from the [best candidate](#8-best-candidate) app and acquire the result.

If the platform method result schema matches the `x-response` schema on the provider method then the value **MUST** be used as-is.

Otherwise if the platform method result schema has a property that matches the `x-response` schema on the provider method then the value **MUST** be composed into an object under the corresponding property name and the platform **MUST** apply any [session transformations](#9-session-transformations) to the composed result.

## 6. Aggregated pass-through results
An aggregated pass-through is where many apps provides responses to a single request by another app. The results are aggregated inside of an array.

This section only applies to app provider methods that do not have an `event` tag and do have the `x-multiple-providers` extension set to `true`.

The platform method result schema **MUST** have a type of `array`.

The platform method result schema **MUST** have an `items` sub-schema that either:

> Matches the `x-response` schema on the provider method so that the result can be added to the final array.
>
> or
>
> Has a property that matches the `x-response` schema on the provider method so that the result can be composed
> and added to the final array.

When an app calls a platform method the platform **MUST** return an unavailable error if there is no [candidate app](#7-provider-candidates) to execute the provider method.

The platform **MUST** call the provider method from each [candidate app](#7-provider-candidates) and aggregated all of the results into an array.

If the platform method result `items` schema matches the `x-response` schema on the provider method then each provier value **MUST** be used as-is.

Otherwise if the platform method result `items` schema has a property that matches the `x-response` schema on the provider method then each provider value **MUST** be composed into an object under the corresponding property name and the platform **MUST** apply any [session transformations](#9-session-transformations) to the composed result.

## 7. Pass-through notifications
Firebolt events have a synchronous subscriber registration method, e.g. `Lifecycle.onInactive(true)`, in addition to asynchronous notifications when the event actually happens. For events powered by an app pass-through, only the asynchronous notifications are passed in by the providing app. The initial event registration is handled by the platform, and the success response is not handled by the providing app.

This section only applies to platform methods that have an `event` tag.

App provided event registration **MUST** not return an availability error due to a lack of providers, since one may be launched at a future point.

To ensure that event provider methods all behave the same the provider method **MUST** have a result schema with `"type"` set to the string `"null"`, since it will not expect any result from the platform after pushing the notification.

The platform method result schema **MUST** either:

> Match the *last* parameter schema on the provider method so that the result can be passed through.
>
> Have a property that matches the *last* parameter schema on the provider method so that the result can
> be passed through.

The platform method event context parameters **MUST** each match the corresponding parameter schema on the provider method so that the result can be passed through.

When a provider app calls a provider method mapped to an event the platform **MUST** ignore the notification if the app is not a [candidate app](#7-provider-candidates) for this capability.

If the platform method result schema matches the *last* parameter schema on the provider method then the value **MUST** be used as-is.

Otherwise if the platform method result schema has a property that matches the *last* parameter schema on the provider method then the value **MUST** be composed into an object under the corresponding property name and the platform **MUST** apply any [session transformations](#9-session-transformations) to the composed result.

Finally the platform **MUST** dispatch the notification to the app that registered for the event via the original platform method, using all but the last parameter as context.

## 8. Provider Candidates
The Firebolt Device Manfist **MUST** have a list of `ProviderPolicy` configurations that map capabilities to policies for determining candidate providers:

```json
{
    "providerPolicies": [
        {
            "lifecycle": [
                "foreground"
            ],
            "allowLaunch": true,
            "capabilities": [
                "xrn:firebolt:capability:foo:bar"
            ]
        }
    ]
}
```

The policy **MUST** have a list of valid lifecycle states for an app to provide the capability.

The policy **MUST** have a boolean property `allowLaunch` to denote whether launching provider apps in order to fulfill a platform method is allowed.

## 9. Best Candidate
If there is only one candidate then it **MUST** be the best candidate.

If there is more than one candidate, then the app that was most recently in the foreground state **MUST** be the best candidate.

If none of the candidates have been in the foreground state then the app that was most recently launched **MUST** be the best candidate.

If none of the candidates have been launched and the `ProviderPolicy` has `allowLaunch` set to true then the platform **SHOULD** select a candidate app, launch it, and use it as the best candidate; how this selection occurs is out of scope for this document.

## 10. Session Transformations
An platform method may be configured to insert the providing app id into composite values. This is not allowed in non-composite results to avoid collisions with the provder method sending an appId and Firebolt overriding it.

If a "composite result" was used to wrap the provider method value and the platform method's schema has an `appId` `string` property at the top level then the property's value **MUST** be set to the the appId of the providing app for that calculated result.

## 11. Provider Parameter Injection
If the provider method has a parameter named `appId` and the platform method *does not*, then the appId of the app calling the platform method **MUST** be sent to the provider in the `appId` parameter.

## 12. API Gateway
The Firebolt API Gateway **MUST** detect app-passthrough APIs and map the `use`/`manage` APIs to the corresponding `provide` APIs by parsing the Firebolt OpenRPC Specification and following the logic outline in this document.

## 13. Example: User Interest

User Interest does not use the `x-app-method` property because there is only one method and one event in the API, so they can be detected automatically via the capability string.

Schemas

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

Content.requestUserInterest (pull, use)

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
                }
            ],
            "result": {
                "name": "interestedIn",
                "schema": {
                    "$ref": "#/components/schemas/EntityFromApp",
                }
            }
        }
    ]
}
```

Discovery.onRequestUserInterest (1.0, pull, provide)

```json
{
    "methods": [
        {
            "name": "onRequestUserInterest",
            "tags": [
                {
                    "name": "capabilities",
                    "x-provides": "xrn:firebolt:capability:discovery:interest",
                    "x-lifecycle": ["foreground", "background"],
                },
                {
                    "name": "event",
                    "x-response": {
                        "$ref": "https://meta.comcast.com/firebolt/entity#/definitions/Entity"
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
                        }
                    }
                }
            }
        }
    ]
}
```

Discovery.userInterest (2.0, pull, provide)

```json
{
    "methods": [
        {
            "name": "userInterest",
            "tags": [
                {
                    "name": "capabilities",
                    "x-lifecycle": ["foreground", "background"],
                    "x-provides": "xrn:firebolt:capability:discovery:interest"
                }
            ],
            "params": [
                {
                  "name": "type",
                  "schema": {
                      "$ref": "#/components/schemas/InterestType",
                  }
                }
            ],
            "result": {
                "name": "entity",
                "schema": {
                    "$ref": "https://meta.comcast.com/firebolt/entity#/definitions/Entity"
                }
            }
        }
    ]
}
```


Discovery.userInterest (push)

```json
{
    "methods": [
        {
            "name": "userInterest",
            "tags": [
                {
                    "name": "capabilities",
                    "x-provides": "xrn:firebolt:capability:discovery:interest",
                    "x-lifecycle": ["foreground", "background"],
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
                  "name": "entity",
                  "schema": {
                      "$ref": "https://meta.comcast.com/firebolt/entity#/definitions/Entity"
                  }                    
                }
            ]
        }
    ]
}
```

Content.onUserInterest (push) 

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
            "result": {
                "name": "info",
                "schema": {
                    "$ref": "#/components/schemas/InterestedInfo",
                }
            }
        }
    ]
}
```

## 14. Example: Keyboard

Keyboard *requires* the* `x-app-method` property because there are three methods in the same capability, so the mapping cannot be detected automatically via the capability string.

Schemas

```json
{
    "components": {
        "schemas": {

        }
    }
}
```

Keyboard.standard (use)

```json
{
    "methods": [
		{
			"name": "Keyboard.standard",
			"tags": [
				{
					"name": "capabilities",
                    "x-app-provided": true,
                    "x-app-method": "Keyboard.onRequestStandard",
					"x-uses": [
						"xrn:firebolt:capability:input:keyboard"
					]
				}
			],
			"summary": "Show the standard platform keyboard, and return the submitted value",
			"params": [
				{
					"name": "message",
					"summary": "The message to display while prompting",
					"required": true,
					"schema": {
						"type": "string"
					}
				}
			],
			"result": {
				"name": "value",
				"summary": "the selected or entered text",
				"schema": {
					"type": "string"
				}
			}
        }
    ]
}
```

Keyboard.onRequestStandard (1.0, provide)

```json
{
    "methods": [
		{
			"name": "Keyboard.onRequestStandard",
			"params": [
			],
			"tags": [
				{
					"name": "event",
					"x-response": {
						"$ref": "#/components/schemas/KeyboardResult",
						"examples": [
							{
								"text": "username"
							}
						]
					}
				},
				{
					"name": "capabilities",
					"x-provides": "xrn:firebolt:capability:input:keyboard",
					"x-allow-focus": true
				}
			],
			"result": {
				"name": "sessionRequest",
				"summary": "The request to start a keyboard session",
				"schema": {
					{
						"$ref": "#/components/schemas/KeyboardProviderRequest"
					}
				}
			}
        }
    ]
}
```

Keyboard.standard (2.0, provide in the app RPC doc):

```json
{
    "methods": [
		{
			"name": "Keyboard.standard",
			"params": [
                {
                    "name": "message",
                    "schema": {
                        "type": "string"
                    }
                }
			],
			"tags": [
				{
					"name": "capabilities",
					"x-provides": "xrn:firebolt:capability:input:keyboard",
					"x-allow-focus": true
				}
			],
			"result": {
				"name": "value",
				"summary": "The user entered string",
				"schema": {
					{
                        "type": "string"
					}
				}
			}
        }
    ]
}
```
