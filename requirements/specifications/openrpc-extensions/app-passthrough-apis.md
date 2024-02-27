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
- [3. App Provided Extension](#3-app-provided-extension)
  - [3.1. Aggregated vs Single Providers](#31-aggregated-vs-single-providers)
  - [3.2. Selecting the best provider app](#32-selecting-the-best-provider-app)
  - [3.3. Calculating the final result](#33-calculating-the-final-result)
    - [3.3.1. Composite Results](#331-composite-results)
    - [3.3.2. Inserting the appId](#332-inserting-the-appid)
- [4. API Gateway](#4-api-gateway)
- [5. Example: User Interest](#5-example-user-interest)
- [6. Example: Keyboard](#6-example-keyboard)

## 3. App Provided Extension
Firebolt OpenRPC **MUST** support a `boolean` `x-app-provided` extension property on the `capabilities` tag that denotes a method is provided by some app on the device.

The `x-app-provided` extension **MUST NOT** be used on a method with any value in the `x-provides` extension.

If a method has a `capabilities` tag with `x-app-provided` set to `true` then it **MUST** `use` a single capability or `manage` a single capability, but not both. Any such method is referred to as an "app provided method" for the rest of this document.

If an app provided method's `capabilities` tag has an `x-app-method` string property, then:

> The method denoted by the `x-app-method` property **MUST** provide the same capability that is either used or managed by this method; This method is referred to as the "provider" for the rest of this document.

If an app provided method's `capabilities` tag has no `x-app-method` property and the method has an `event` tag, then:

> There **MUST** be another method that provides that capability via `x-provides`, and is a notification method (i.e. it has no `x-response` defined); This method is referred to as the "provider" for the rest of this document.

If an app provided method's `capabilities` tag has no `x-app-method` property and the method does not have an `event` tag, then:

> There **MUST** be another method that provides that capability via `x-provides`, and is not a notification method (i.e. it has an `x-response` defined); This method is referred to as the "provider" for the rest of this document.

If an app provided method has no provider method, or more than one provider method, then it is not a valid Firebolt OpenRPC method schema, and a validation error **MUST** be generated.

### 3.1. Aggregated vs Single Providers
An app provided method's `capabilites` tag **MAY** have a `boolean` `x-aggregate` property which denotes whether or not multiple apps may provide responses to a single request of the method.

If the `x-aggregate` property is not present then it defaults to `false`.

If an app provided method has an `event` tag then the `capabilities` tag **MUST NOT** have the `x-aggregate` property set to `true`.

If an app provided method has `x-aggregate` set to `true` then:

> The method **MUST** have a result with the type set to `array`.
>
> The `items` schema of the array **MUST** match the `x-response` schema on the provider method.
>
> The final result returned by the app provided method **MUST** be a flattened array with all of the calculated results from each provider.

Otherwise, if `x-aggregate` is `false` (explicityly or by default):

> The method **MUST** have a result, which can by any type.
>
> The result schema **MUST** match the `x-response` schema on the provider method.
>
> The final result returned by the app provided method **MUST** be the [calculated result](#33-calculating-the-final-result) from the selected provider.

### 3.2. Selecting the best provider app
If a method does not have `x-aggregate` set to `true` then it **MAY** have a `boolean` `x-app-selection` property which denotes how to pick a single app to provide the response.

If the `x-app-selection` property is not present then it defaults to `false`.

If `x-app-selection` is set to `"presentation"` then the app selected to provide the result **MUST** be the `foreground` or `background` app.

If `x-app-selection` is set to `"presentation"` and neither the `forground` or `background` app provides the required capability then the calling app **MUST** receive an error and not a result.

If `x-app-selection` is set to `"recent"` then the app selected to provide the result **MUST** be the most recently launched app that provides the required capability.

### 3.3. Calculating the final result
For each app provided method result, the result **MUST** be calculated with the following potential transformations.

If an app provided method has `x-aggregate` set to `true`, then the term "calculated result" refers to the items of the app provided method result array for the remainder of this section.

If an app provided method has `x-aggregate` set to `false` or the property does not exist, then the term "calculated result" refers to the app provided method result for the remainder of this section.

#### 3.3.1. Composite Results
An app provided method may be configured to use the provided value as the calculated result, or to compose it into an object along with  other values.

If the app provided method does not have an `event` tag then:

> If an app provided method's `capabilities` tag has an `x-composite-result` property set to `true`, then the app provided method result schema **MUST** have a property that matches name and schema of the provider method result, and property's value **MUST** be set to the value returned by the providing app for the final result.
>
> If an app provided method's `capabilities` tag does not have an `x-composite-result` property or it is `false`, then the calculated result schema **MUST** match the app provided method result schema and the value of the calculated result **MUST** be the value returned by the providing app.

If the app provided method has an `event` tag then:

> If an app provided method's `capabilities` tag has an `x-composite-result` property, then every property of the provided method result schema that has a matching name and schema *parameter* in the provider method **MUST** have that property set to the value of the matching parameter from the provider notification for the final result.
>
> If an app provided method's `capabilities` tag does not have an `x-composite-result` property, then the calculated result schema **MUST** match the *last parameter* of the provider method and the value of the calculated result **MUST** be the value of that parameter from the provider notification for the final result.


#### 3.3.2. Inserting the appId
An app provided method may be configured to insert the providing app id into composite results. This is not allowed in non-composite results to avoid collisions with the provder method sending an appId and Firebolt overriding it.

If an app provided method's `capabilities` tag has an `x-composite-result` property set to `true` then the method **MAY** have an `x-app-id-property`.

If an app provided method's `capabilities` tag has an `x-composite-result` property set to `false` or does not have the property then the method **MUST NOT** have an `x-app-id-property`.

If an app provided method's `capabilities` tag has an `x-app-id-property` property, then the calculated result schema **MUST** have a property with that name, and property's value **MUST** be set to the the appId of the providing app for that calculated result.

## 4. API Gateway
The Firebolt API Gateway **MUST** detect app-passthrough APIs and map the `use`/`manage` APIs to the corresponding `provide` APIs by parsing the Firebolt OpenRPC Specification and following the logic outline in this document.

## 5. Example: User Interest

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
            "InterestInfo": {
                "type": "object",
                "properties": {
                    "appId": {
                        "type": "string"
                    },
                    "entity": {
                        "$ref": "https://meta.comcast.com/firebolt/discovery#/definitions/EntityInfo"
                    },
                    "type": {
                        "$ref": "#/components/schemas/InterestType"
                    }
                },
                "required": [
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
                    "x-app-provided": true,
                    "x-app-selection": "presentation",
                    "x-composite-result": true,
                    "x-app-id-property": "appId",
                    "x-aggregate": false,
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
                    "$ref": "#/components/schemas/InterestInfo",
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
                },
                {
                    "name": "event",
                    "x-response": {
                        "$ref": "https://meta.comcast.com/firebolt/discovery#/definitions/EntityInfo"
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
                    "$ref": "https://meta.comcast.com/firebolt/discovery#/definitions/EntityInfo"
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
                  "name": "entity",
                  "schema": {
                      "$ref": "https://meta.comcast.com/firebolt/discovery#/definitions/EntityInfo"
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
                    "x-app-provided": true,
                    "x-composite-result": true,
                    "x-aggregate": false,
                    "x-app-id-property": "appId",
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

## 6. Example: Keyboard

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
