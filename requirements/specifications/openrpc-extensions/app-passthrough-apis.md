# App Pass-through APIs

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
|-----------------|----------------|
| Jeremy LaCivita | Comcast        |
| Kevin Pearson   | Comcast        |

## 1. Overview
This document describes the App Pass-through Firebolt OpenRPC extension.

Some APIs require an app to fulfill the request on behalf of another app, e.g. to provide a UX or cross-app data sharing. Generally the calling app doesn't care or have a say in which other app provides the API, that is up to the Firebolt distributor.

To facilitate these APIs, Firebolt denotes an OpenRPC tag with OpenRPC extensions to connect the `provide` API to the `use` API.

This document is written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt) and should include the following summary in the Overview section:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Provided By Extension](#3-provided-by-extension)
- [4. Selecting the best provider app](#4-selecting-the-best-provider-app)
- [5. Calculating the result](#5-calculating-the-result)
  - [5.1. Selecting multiple provider apps](#51-selecting-multiple-provider-apps)
  - [5.2. Composite Results](#52-composite-results)
  - [5.3. Inserting the appId](#53-inserting-the-appid)
- [6. API Gateway](#6-api-gateway)
- [7. Example: User Interest](#7-example-user-interest)
- [8. Example: Keyboard](#8-example-keyboard)

## 3. Provided By Extension
Firebolt OpenRPC **MUST** support a `string` `x-provided-by` extension property on the `capabilities` tag that denotes a method is provided by some app on the device registering for the specified provider API, e.g. `Module.onRequestMethod`.

The method denoted by `x-provided-by` is referred to as the "provider" or "provider method" for the remainder of this document.

The method with the `x-provided-by` extension is referred to as the "app provided method" for the remainder of this document.

The `x-provided-by` extension **MUST NOT** be used on a method with any value in the `x-provides` extension.

An app provided method **MUST** `use` a single capability or `manage` a single capability, but not both.

The provider method **MUST** provide the same capability that the app provided method either uses or manages.

If the app provided method has an `event` tag then the provider method **MUST** have a result schema with `"type"` set to the string `"null"`.

If an app provided method has no provider method then it is not a valid Firebolt OpenRPC method schema, and a validation error **MUST** be generated.

## 4. Selecting the best provider app
A provider method's `capabilites` tag **MAY** have the `x-lifecycle` property which denotes which lifecycle states the providing app is allowed to be in during an app provided transaction.

If the `x-lifecycle` property is not present then it **MUST** be assumed to be `["foreground", "background", "inactive"]` for the remainder of this section.

The app selected to provide a value **MUST** be in one of the lifecycle states listed in the `x-lifecycle` extension of the provider method. 

If the *app provided method's* `capabilities` tag has the `x-multiple-providers` property is set to `true` then all apps matching `x-lifecycle` at the time of the transaction **MUST** be used to provide the value, see [Selecting multiple provider apps](#32-selecting-multiple-provider-apps) for more info.

If the *app provided method's* `capabilities` tag has the `x-multiple-providers` is set to `false` or not set then:

> If more than one app is possible, then the candidate apps **MUST** be pruned by reevaluating the `x-lifecycle` array with the last value removed; This is repeated until there is only one app or only one lifecycle state remaining.
>
> If more than one app is still possible, then the app that was most recently in the `foreground` state **MUST** be selected; In the case of a tie, the platform **MUST** choose only one app using its own discretion.
>
> If there is no provider most recently in the `foreground` state then the app that was most recently in the inactive state **MUST** be selected.

If the app provided method does not have an `event` tag and no matching app provides the required capability then the calling app **MUST** receive an error that the capability is unavailable and not a result.

If the app provided method has an `event` tag then event registration **MUST** not return an availability error due to a lack of providers, since one may be launched at a future point.

**TODO**: ^^ do we want to scan the catalog and see if it's even possible to have an app that provides it? Seems heavy/overkill and dives into a spec we don't have yet.

## 5. Calculating the result
Each app provided method result **MUST** be calculated with the following potential transformations.

If an app provided method has `x-multiple-providers` set to `true` and the app provided method does not have an `event` tag, then the term "calculated result" refers to each item of the app provided method result array for the remainder of this section.

Otherwise, the term "calculated result" refers to the app provided method result for the remainder of this section.

### 5.1. Selecting multiple provider apps
An app provided method's `capabilites` tag **MAY** have the `x-multiple-providers` property set to `true` which denotes that more than one app may provider this capability at the same time.

If an app provided method has `x-multiple-providers` set to `true` and the app provided method does not have an `event` tag then:

> The method **MUST** have a result with the type set to `array`.
>
> At least one of the following **MUST** be true:
> 
> - The `items` schema of the array **MUST** match the `x-response` schema on the provider method.
> 
> - The `items` schema of the array **MUST** have a property whose name is not `"appId"` and schema matches the `x-response` schema.
>
> The final result returned by the app provided method **MUST** be a flattened array with all of the values from all selected providers.

If an app provided method has `x-multiple-providers` is set to `true` and the app provided method has an `event` tag then:

> - The method result schema **MUST** match the `x-response` schema on the provider method.
> 
> - The method result schema **MUST** have a property whose name is not `"appId"` and schema matches the `x-response` schema.
> 
> The app provided method **MUST** dispatch each "calculated result" as a separate event to all listeners.

### 5.2. Composite Results
An app provided method may be configured to use the provided value as the calculated result, or to compose it into an object along with other values.

If the app provided method does not have an `event` tag:

> If the calculated result schema matches the provider method result schema then the provider method result value **MUST** be passed through as-is, this is *not* considered a "composite result."
>
> Otherwise, if the calculated result schema is an object with a property whose name and schema matches the provider method result name and schema then the provider method result value **MUST** inserted into an object under the property name; this is refered to as a "composite result" for the rest of this document.

If the app provided method has an `event` tag:

> If the calculated result schema matches the provider method's *last* parameter schema then the value of that parameter **MUST** be passed through as the calculated result value as-is.
>
> Otherwise, if the calculated result schema is an object with a property whose name and schema matches the provider method's *last* parameter name and schema then the value of that parameter **MUST** inserted into an object under the property name; this is refered to as a "composite result" for the rest of this document.

### 5.3. Inserting the appId
An app provided method may be configured to insert the providing app id into composite results. This is not allowed in non-composite results to avoid collisions with the provder method sending an appId and Firebolt overriding it.

If a "composite result" was used to wrap the provider method value and the app provided method's schema has an `appId` `string` property at the top level then the property's value **MUST** be set to the the appId of the providing app for that calculated result.

## 6. API Gateway
The Firebolt API Gateway **MUST** detect app-passthrough APIs and map the `use`/`manage` APIs to the corresponding `provide` APIs by parsing the Firebolt OpenRPC Specification and following the logic outline in this document.

## 7. Example: User Interest

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

## 8. Example: Keyboard

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
