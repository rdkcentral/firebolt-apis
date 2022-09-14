---
title: Discovery
---

# Discovery Module
---
Version 0.8.0

## Overview
 Your App likely wants to integrate with the Platform's discovery capabilities. For example to add a "Watch Next" tile that links to your app from the platform's home screen.

Getting access to this information requires to connect to lower level APIs made available by the platform. Since implementations differ between operators and platforms, the Firebolt SDK offers a Discovery module, that exposes a generic, agnostic interface to the developer.

Under the hood, an underlaying transport layer will then take care of calling the right APIs for the actual platform implementation that your App is running on.

The Discovery plugin is used to _send_ information to the Platform.

### Localization
Apps should provide all user-facing strings in the device's language, as specified by the Firebolt `Localization.language` property.

Apps should provide prices in the same currency presented in the app. If multiple currencies are supported in the app, the app should provide prices in the user's current default currency.

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [discovery.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/discovery.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [entitlements](#entitlements)
    - [entityInfo](#entityinfo)
    - [launch](#launch)
    - [listen](#listen)
    - [once](#once)
    - [policy](#policy)
    - [purchasedContent](#purchasedcontent)
    - [signIn](#signin)
    - [signOut](#signout)
    - [watched](#watched)
    - [watchNext](#watchnext)

 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [DiscoveryPolicy](#discoverypolicy)
    - [EntityInfo](#entityinfo)
    - [WayToWatch](#waytowatch)
    - [ContentRating](#contentrating)
    - [ContentIdentifiers](#contentidentifiers)
    - [FederatedRequest](#federatedrequest)
    - [FederatedResponse](#federatedresponse)
    - [EntityInfoFederatedRequest](#entityinfofederatedrequest)
    - [EntityInfoParameters](#entityinfoparameters)
    - [EntityInfoFederatedResponse](#entityinfofederatedresponse)
    - [EntityInfoResult](#entityinforesult)
    - [PurchasedContentFederatedRequest](#purchasedcontentfederatedrequest)
    - [PurchasedContentParameters](#purchasedcontentparameters)
    - [PurchasedContentFederatedResponse](#purchasedcontentfederatedresponse)
    - [PurchasedContentResult](#purchasedcontentresult)

<span></span>

## Usage
To use the Discovery module, you can import it into your project from the Firebolt SDK:

```javascript
import { Discovery } from '@firebolt-js/sdk'
```


## Methods
### entitlements

Inform the platform of the users latest entitlements w/in this app

```typescript
function entitlements(entitlements: Entitlement[]): Promise<boolean>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `entitlements` | [`Entitlement`[]](undefinedEntertainmentSchema#/definitions/Entitlement) | true | Array of entitlement objects  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` | whether the call was successful or not |


**Examples**

Update user's entitlements

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.entitlements([
                         {
                           "entitlementId": "partner.com/entitlement/123",
                           "startTime": "2021-04-23T18:25:43.511Z",
                           "endTime": "2021-04-23T18:25:43.511Z"
                         },
                         {
                           "entitlementId": "partner.com/entitlement/456",
                           "startTime": "2021-04-23T18:25:43.511Z",
                           "endTime": "2021-04-23T18:25:43.511Z"
                         }
                       ])
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.entitlements",
  "params": {
    "entitlements": [
      {
        "entitlementId": "partner.com/entitlement/123",
        "startTime": "2021-04-23T18:25:43.511Z",
        "endTime": "2021-04-23T18:25:43.511Z"
      },
      {
        "entitlementId": "partner.com/entitlement/456",
        "startTime": "2021-04-23T18:25:43.511Z",
        "endTime": "2021-04-23T18:25:43.511Z"
      }
    ]
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### entityInfo
Provide information about a program entity and its available watchable assets, such as entitlement status and price, via either a push or pull call flow. Includes information about the program entity and its relevant associated entities, such as extras, previews, and, in the case of TV series, seasons and episodes.

See the `EntityInfo` and `WayToWatch` data structures below for more information.

The app only needs to implement Pull support for `entityInfo` at this time.



To allow the platform to pull data, use `entityInfo(callback)`:


```typescript
function entityInfo(callback: (parameters: EntityInfoParameters) => Promise<EntityInfoResult>): Promise<boolean>
```



Parameters: 

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `callback` | `function` | Yes | A method the platform will call to pull `entityInfo` data. |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `boolean` | Whether or not the callback registration was successful |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`EntityInfoParameters`](#entityinfoparameters) | true | A EntityInfoFederatedRequest object.  |

Callback promise resolution:

| Type | Description |
| ---- | ----------- |
| [`EntityInfoResult`](#entityinforesult) | The result for an `entityInfo()` push or pull. |


**Examples**

Send entity info for a movie to the platform. (Pull)


JavaScript:

```javascript
Discovery.entityInfo(function(parameters) {
  return Promise.resolve({
  "correlationId": null,
  "result": {
    "expires": "2025-01-01T00:00:00.000Z",
    "entity": {
      "identifiers": {
        "entityId": "345"
      },
      "entityType": "program",
      "programType": "movie",
      "title": "Cool Runnings",
      "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
      "releaseDate": "1993-01-01T00:00:00.000Z",
      "contentRatings": [
        {
          "scheme": "US-Movie",
          "rating": "PG"
        },
        {
          "scheme": "CA-Movie",
          "rating": "G"
        }
      ],
      "waysToWatch": [
        {
          "identifiers": {
            "assetId": "123"
          },
          "expires": "2025-01-01T00:00:00.000Z",
          "entitled": true,
          "entitledExpires": "2025-01-01T00:00:00.000Z",
          "offeringType": "buy",
          "price": 2.99,
          "videoQuality": [
            "UHD"
          ],
          "audioProfile": [
            "dolbyAtmos"
          ],
          "audioLanguages": [
            "en"
          ],
          "closedCaptions": [
            "en"
          ],
          "subtitles": [
            "es"
          ],
          "audioDescriptions": [
            "en"
          ]
        }
      ]
    }
  }
})
}).then(success => {
  console.log(success)
})
```
Value of `success`

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request (from callback):

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.entityInfo",
  "params": {
    "correlationId": "xyz",
    "result": {}
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

<details>
    <summary>More examples...</summary>
Send entity info for a movie with a trailer to the platform. (Pull)


JavaScript:

```javascript
Discovery.entityInfo(function(parameters) {
  return Promise.resolve({
  "correlationId": null,
  "result": {
    "expires": "2025-01-01T00:00:00.000Z",
    "entity": {
      "identifiers": {
        "entityId": "345"
      },
      "entityType": "program",
      "programType": "movie",
      "title": "Cool Runnings",
      "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
      "releaseDate": "1993-01-01T00:00:00.000Z",
      "contentRatings": [
        {
          "scheme": "US-Movie",
          "rating": "PG"
        },
        {
          "scheme": "CA-Movie",
          "rating": "G"
        }
      ],
      "waysToWatch": [
        {
          "identifiers": {
            "assetId": "123"
          },
          "expires": "2025-01-01T00:00:00.000Z",
          "entitled": true,
          "entitledExpires": "2025-01-01T00:00:00.000Z",
          "offeringType": "buy",
          "price": 2.99,
          "videoQuality": [
            "UHD"
          ],
          "audioProfile": [
            "dolbyAtmos"
          ],
          "audioLanguages": [
            "en"
          ],
          "closedCaptions": [
            "en"
          ],
          "subtitles": [
            "es"
          ],
          "audioDescriptions": [
            "en"
          ]
        }
      ]
    },
    "related": [
      {
        "identifiers": {
          "entityId": "345"
        },
        "entityType": "program",
        "programType": "preview",
        "title": "Cool Runnings Trailer",
        "waysToWatch": [
          {
            "identifiers": {
              "assetId": "123111",
              "entityId": "345"
            },
            "entitled": true,
            "videoQuality": [
              "HD"
            ],
            "audioProfile": [
              "dolbyAtmos"
            ],
            "audioLanguages": [
              "en"
            ],
            "closedCaptions": [
              "en"
            ]
          }
        ]
      }
    ]
  }
})
}).then(success => {
  console.log(success)
})
```
Value of `success`

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request (from callback):

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.entityInfo",
  "params": {
    "correlationId": "xyz",
    "result": {}
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Send entity info for a TV Series with seasons and episodes to the platform. (Pull)


JavaScript:

```javascript
Discovery.entityInfo(function(parameters) {
  return Promise.resolve({
  "correlationId": null,
  "result": {
    "expires": "2025-01-01T00:00:00.000Z",
    "entity": {
      "identifiers": {
        "entityId": "98765"
      },
      "entityType": "program",
      "programType": "series",
      "title": "Perfect Strangers",
      "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
      "releaseDate": "1986-01-01T00:00:00.000Z",
      "contentRatings": [
        {
          "scheme": "US-TV",
          "rating": "TV-PG"
        }
      ]
    },
    "related": [
      {
        "identifiers": {
          "entityId": "111",
          "seriesId": "98765"
        },
        "entityType": "program",
        "programType": "season",
        "seasonNumber": 1,
        "title": "Perfect Strangers Season 3",
        "contentRatings": [
          {
            "scheme": "US-TV",
            "rating": "TV-PG"
          }
        ],
        "waysToWatch": [
          {
            "identifiers": {
              "assetId": "556",
              "entityId": "111",
              "seriesId": "98765"
            },
            "entitled": true,
            "offeringType": "free",
            "videoQuality": [
              "SD"
            ],
            "audioProfile": [
              "stereo"
            ],
            "audioLanguages": [
              "en"
            ],
            "closedCaptions": [
              "en"
            ]
          }
        ]
      },
      {
        "identifiers": {
          "entityId": "111",
          "seriesId": "98765"
        },
        "entityType": "program",
        "programType": "episode",
        "seasonNumber": 1,
        "episodeNumber": 1,
        "title": "Knock Knock, Who's There?",
        "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
        "releaseDate": "1986-03-25T00:00:00.000Z",
        "contentRatings": [
          {
            "scheme": "US-TV",
            "rating": "TV-PG"
          }
        ],
        "waysToWatch": [
          {
            "identifiers": {
              "assetId": "556",
              "entityId": "111",
              "seriesId": "98765"
            },
            "entitled": true,
            "offeringType": "free",
            "videoQuality": [
              "SD"
            ],
            "audioProfile": [
              "stereo"
            ],
            "audioLanguages": [
              "en"
            ],
            "closedCaptions": [
              "en"
            ]
          }
        ]
      },
      {
        "identifiers": {
          "entityId": "112",
          "seriesId": "98765"
        },
        "entityType": "program",
        "programType": "episode",
        "seasonNumber": 1,
        "episodeNumber": 2,
        "title": "Picture This",
        "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
        "releaseDate": "1986-04-01T00:00:00.000Z",
        "contentRatings": [
          {
            "scheme": "US-TV",
            "rating": "TV-PG"
          }
        ],
        "waysToWatch": [
          {
            "identifiers": {
              "assetId": "557",
              "entityId": "112",
              "seriesId": "98765"
            },
            "entitled": true,
            "offeringType": "free",
            "videoQuality": [
              "SD"
            ],
            "audioProfile": [
              "stereo"
            ],
            "audioLanguages": [
              "en"
            ],
            "closedCaptions": [
              "en"
            ]
          }
        ]
      }
    ]
  }
})
}).then(success => {
  console.log(success)
})
```
Value of `success`

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request (from callback):

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.entityInfo",
  "params": {
    "correlationId": "xyz",
    "result": {}
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

</details>




To push data to the platform, e.g. during app launch, use `entityInfo(correlationId: string, result: EntityInfoResult)`:

```typescript
function entityInfo(correlationId: string, result: EntityInfoResult): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `correlationId` | `string` | true |   |
| `result` | [`EntityInfoResult`](#entityinforesult) | true | The entityInfo data.  |


Promise resolution:

boolean

**Examples**

Send entity info for a movie to the platform.


JavaScript:

```javascript
import { Discovery } from ''

Discovery.entityInfo(null,
                     {
                       "expires": "2025-01-01T00:00:00.000Z",
                       "entity": {
                         "identifiers": {
                           "entityId": "345"
                         },
                         "entityType": "program",
                         "programType": "movie",
                         "title": "Cool Runnings",
                         "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
                         "releaseDate": "1993-01-01T00:00:00.000Z",
                         "contentRatings": [
                           {
                             "scheme": "US-Movie",
                             "rating": "PG"
                           },
                           {
                             "scheme": "CA-Movie",
                             "rating": "G"
                           }
                         ],
                         "waysToWatch": [
                           {
                             "identifiers": {
                               "assetId": "123"
                             },
                             "expires": "2025-01-01T00:00:00.000Z",
                             "entitled": true,
                             "entitledExpires": "2025-01-01T00:00:00.000Z",
                             "offeringType": "buy",
                             "price": 2.99,
                             "videoQuality": [
                               "UHD"
                             ],
                             "audioProfile": [
                               "dolbyAtmos"
                             ],
                             "audioLanguages": [
                               "en"
                             ],
                             "closedCaptions": [
                               "en"
                             ],
                             "subtitles": [
                               "es"
                             ],
                             "audioDescriptions": [
                               "en"
                             ]
                           }
                         ]
                       }
                     })
```
Value of `success`

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.entityInfo",
  "params": {
    "correlationId": null,
    "result": {
      "expires": "2025-01-01T00:00:00.000Z",
      "entity": {
        "identifiers": {
          "entityId": "345"
        },
        "entityType": "program",
        "programType": "movie",
        "title": "Cool Runnings",
        "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
        "releaseDate": "1993-01-01T00:00:00.000Z",
        "contentRatings": [
          {
            "scheme": "US-Movie",
            "rating": "PG"
          },
          {
            "scheme": "CA-Movie",
            "rating": "G"
          }
        ],
        "waysToWatch": [
          {
            "identifiers": {
              "assetId": "123"
            },
            "expires": "2025-01-01T00:00:00.000Z",
            "entitled": true,
            "entitledExpires": "2025-01-01T00:00:00.000Z",
            "offeringType": "buy",
            "price": 2.99,
            "videoQuality": [
              "UHD"
            ],
            "audioProfile": [
              "dolbyAtmos"
            ],
            "audioLanguages": [
              "en"
            ],
            "closedCaptions": [
              "en"
            ],
            "subtitles": [
              "es"
            ],
            "audioDescriptions": [
              "en"
            ]
          }
        ]
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

<details>
    <summary>More examples...</summary>
Send entity info for a movie with a trailer to the platform.


JavaScript:

```javascript
import { Discovery } from ''

Discovery.entityInfo(null,
                     {
                       "expires": "2025-01-01T00:00:00.000Z",
                       "entity": {
                         "identifiers": {
                           "entityId": "345"
                         },
                         "entityType": "program",
                         "programType": "movie",
                         "title": "Cool Runnings",
                         "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
                         "releaseDate": "1993-01-01T00:00:00.000Z",
                         "contentRatings": [
                           {
                             "scheme": "US-Movie",
                             "rating": "PG"
                           },
                           {
                             "scheme": "CA-Movie",
                             "rating": "G"
                           }
                         ],
                         "waysToWatch": [
                           {
                             "identifiers": {
                               "assetId": "123"
                             },
                             "expires": "2025-01-01T00:00:00.000Z",
                             "entitled": true,
                             "entitledExpires": "2025-01-01T00:00:00.000Z",
                             "offeringType": "buy",
                             "price": 2.99,
                             "videoQuality": [
                               "UHD"
                             ],
                             "audioProfile": [
                               "dolbyAtmos"
                             ],
                             "audioLanguages": [
                               "en"
                             ],
                             "closedCaptions": [
                               "en"
                             ],
                             "subtitles": [
                               "es"
                             ],
                             "audioDescriptions": [
                               "en"
                             ]
                           }
                         ]
                       },
                       "related": [
                         {
                           "identifiers": {
                             "entityId": "345"
                           },
                           "entityType": "program",
                           "programType": "preview",
                           "title": "Cool Runnings Trailer",
                           "waysToWatch": [
                             {
                               "identifiers": {
                                 "assetId": "123111",
                                 "entityId": "345"
                               },
                               "entitled": true,
                               "videoQuality": [
                                 "HD"
                               ],
                               "audioProfile": [
                                 "dolbyAtmos"
                               ],
                               "audioLanguages": [
                                 "en"
                               ],
                               "closedCaptions": [
                                 "en"
                               ]
                             }
                           ]
                         }
                       ]
                     })
```
Value of `success`

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.entityInfo",
  "params": {
    "correlationId": null,
    "result": {
      "expires": "2025-01-01T00:00:00.000Z",
      "entity": {
        "identifiers": {
          "entityId": "345"
        },
        "entityType": "program",
        "programType": "movie",
        "title": "Cool Runnings",
        "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
        "releaseDate": "1993-01-01T00:00:00.000Z",
        "contentRatings": [
          {
            "scheme": "US-Movie",
            "rating": "PG"
          },
          {
            "scheme": "CA-Movie",
            "rating": "G"
          }
        ],
        "waysToWatch": [
          {
            "identifiers": {
              "assetId": "123"
            },
            "expires": "2025-01-01T00:00:00.000Z",
            "entitled": true,
            "entitledExpires": "2025-01-01T00:00:00.000Z",
            "offeringType": "buy",
            "price": 2.99,
            "videoQuality": [
              "UHD"
            ],
            "audioProfile": [
              "dolbyAtmos"
            ],
            "audioLanguages": [
              "en"
            ],
            "closedCaptions": [
              "en"
            ],
            "subtitles": [
              "es"
            ],
            "audioDescriptions": [
              "en"
            ]
          }
        ]
      },
      "related": [
        {
          "identifiers": {
            "entityId": "345"
          },
          "entityType": "program",
          "programType": "preview",
          "title": "Cool Runnings Trailer",
          "waysToWatch": [
            {
              "identifiers": {
                "assetId": "123111",
                "entityId": "345"
              },
              "entitled": true,
              "videoQuality": [
                "HD"
              ],
              "audioProfile": [
                "dolbyAtmos"
              ],
              "audioLanguages": [
                "en"
              ],
              "closedCaptions": [
                "en"
              ]
            }
          ]
        }
      ]
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Send entity info for a TV Series with seasons and episodes to the platform.


JavaScript:

```javascript
import { Discovery } from ''

Discovery.entityInfo(null,
                     {
                       "expires": "2025-01-01T00:00:00.000Z",
                       "entity": {
                         "identifiers": {
                           "entityId": "98765"
                         },
                         "entityType": "program",
                         "programType": "series",
                         "title": "Perfect Strangers",
                         "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
                         "releaseDate": "1986-01-01T00:00:00.000Z",
                         "contentRatings": [
                           {
                             "scheme": "US-TV",
                             "rating": "TV-PG"
                           }
                         ]
                       },
                       "related": [
                         {
                           "identifiers": {
                             "entityId": "111",
                             "seriesId": "98765"
                           },
                           "entityType": "program",
                           "programType": "season",
                           "seasonNumber": 1,
                           "title": "Perfect Strangers Season 3",
                           "contentRatings": [
                             {
                               "scheme": "US-TV",
                               "rating": "TV-PG"
                             }
                           ],
                           "waysToWatch": [
                             {
                               "identifiers": {
                                 "assetId": "556",
                                 "entityId": "111",
                                 "seriesId": "98765"
                               },
                               "entitled": true,
                               "offeringType": "free",
                               "videoQuality": [
                                 "SD"
                               ],
                               "audioProfile": [
                                 "stereo"
                               ],
                               "audioLanguages": [
                                 "en"
                               ],
                               "closedCaptions": [
                                 "en"
                               ]
                             }
                           ]
                         },
                         {
                           "identifiers": {
                             "entityId": "111",
                             "seriesId": "98765"
                           },
                           "entityType": "program",
                           "programType": "episode",
                           "seasonNumber": 1,
                           "episodeNumber": 1,
                           "title": "Knock Knock, Who's There?",
                           "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
                           "releaseDate": "1986-03-25T00:00:00.000Z",
                           "contentRatings": [
                             {
                               "scheme": "US-TV",
                               "rating": "TV-PG"
                             }
                           ],
                           "waysToWatch": [
                             {
                               "identifiers": {
                                 "assetId": "556",
                                 "entityId": "111",
                                 "seriesId": "98765"
                               },
                               "entitled": true,
                               "offeringType": "free",
                               "videoQuality": [
                                 "SD"
                               ],
                               "audioProfile": [
                                 "stereo"
                               ],
                               "audioLanguages": [
                                 "en"
                               ],
                               "closedCaptions": [
                                 "en"
                               ]
                             }
                           ]
                         },
                         {
                           "identifiers": {
                             "entityId": "112",
                             "seriesId": "98765"
                           },
                           "entityType": "program",
                           "programType": "episode",
                           "seasonNumber": 1,
                           "episodeNumber": 2,
                           "title": "Picture This",
                           "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
                           "releaseDate": "1986-04-01T00:00:00.000Z",
                           "contentRatings": [
                             {
                               "scheme": "US-TV",
                               "rating": "TV-PG"
                             }
                           ],
                           "waysToWatch": [
                             {
                               "identifiers": {
                                 "assetId": "557",
                                 "entityId": "112",
                                 "seriesId": "98765"
                               },
                               "entitled": true,
                               "offeringType": "free",
                               "videoQuality": [
                                 "SD"
                               ],
                               "audioProfile": [
                                 "stereo"
                               ],
                               "audioLanguages": [
                                 "en"
                               ],
                               "closedCaptions": [
                                 "en"
                               ]
                             }
                           ]
                         }
                       ]
                     })
```
Value of `success`

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.entityInfo",
  "params": {
    "correlationId": null,
    "result": {
      "expires": "2025-01-01T00:00:00.000Z",
      "entity": {
        "identifiers": {
          "entityId": "98765"
        },
        "entityType": "program",
        "programType": "series",
        "title": "Perfect Strangers",
        "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
        "releaseDate": "1986-01-01T00:00:00.000Z",
        "contentRatings": [
          {
            "scheme": "US-TV",
            "rating": "TV-PG"
          }
        ]
      },
      "related": [
        {
          "identifiers": {
            "entityId": "111",
            "seriesId": "98765"
          },
          "entityType": "program",
          "programType": "season",
          "seasonNumber": 1,
          "title": "Perfect Strangers Season 3",
          "contentRatings": [
            {
              "scheme": "US-TV",
              "rating": "TV-PG"
            }
          ],
          "waysToWatch": [
            {
              "identifiers": {
                "assetId": "556",
                "entityId": "111",
                "seriesId": "98765"
              },
              "entitled": true,
              "offeringType": "free",
              "videoQuality": [
                "SD"
              ],
              "audioProfile": [
                "stereo"
              ],
              "audioLanguages": [
                "en"
              ],
              "closedCaptions": [
                "en"
              ]
            }
          ]
        },
        {
          "identifiers": {
            "entityId": "111",
            "seriesId": "98765"
          },
          "entityType": "program",
          "programType": "episode",
          "seasonNumber": 1,
          "episodeNumber": 1,
          "title": "Knock Knock, Who's There?",
          "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
          "releaseDate": "1986-03-25T00:00:00.000Z",
          "contentRatings": [
            {
              "scheme": "US-TV",
              "rating": "TV-PG"
            }
          ],
          "waysToWatch": [
            {
              "identifiers": {
                "assetId": "556",
                "entityId": "111",
                "seriesId": "98765"
              },
              "entitled": true,
              "offeringType": "free",
              "videoQuality": [
                "SD"
              ],
              "audioProfile": [
                "stereo"
              ],
              "audioLanguages": [
                "en"
              ],
              "closedCaptions": [
                "en"
              ]
            }
          ]
        },
        {
          "identifiers": {
            "entityId": "112",
            "seriesId": "98765"
          },
          "entityType": "program",
          "programType": "episode",
          "seasonNumber": 1,
          "episodeNumber": 2,
          "title": "Picture This",
          "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
          "releaseDate": "1986-04-01T00:00:00.000Z",
          "contentRatings": [
            {
              "scheme": "US-TV",
              "rating": "TV-PG"
            }
          ],
          "waysToWatch": [
            {
              "identifiers": {
                "assetId": "557",
                "entityId": "112",
                "seriesId": "98765"
              },
              "entitled": true,
              "offeringType": "free",
              "videoQuality": [
                "SD"
              ],
              "audioProfile": [
                "stereo"
              ],
              "audioLanguages": [
                "en"
              ],
              "closedCaptions": [
                "en"
              ]
            }
          ]
        }
      ]
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

</details>


---

### launch

Launch or foreground the specified app, and optionally instructs it to navigate to the specified user action

```typescript
function launch(appId: string, intent?: NavigationIntent): Promise<boolean>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `appId` | `string` | true | The durable app Id of the app to launch  |
| `intent` | [`NavigationIntent`](../schemas/intents#/definitions/navigationintent) | false | An optional `NavigationIntent` with details about what part of the app to show first, and context around how/why it was launched  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` | whether the call was successful or not |


**Examples**

Launch the 'Foo' app to it's home screen.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("foo", {"action":"home","context":{"source":"voice"}})
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "foo",
    "intent": {
      "action": "home",
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

<details>
    <summary>More examples...</summary>
Launch the 'Foo' app to it's own page for a specific entity.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("foo",
                 {
                   "action": "entity",
                   "data": {
                     "entityType": "program",
                     "programType": "movie",
                     "entityId": "example-movie-id"
                   },
                   "context": {
                     "source": "voice"
                   }
                 })
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "foo",
    "intent": {
      "action": "entity",
      "data": {
        "entityType": "program",
        "programType": "movie",
        "entityId": "example-movie-id"
      },
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Launch the 'Foo' app to a fullscreen playback experience for a specific entity.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("foo",
                 {
                   "action": "playback",
                   "data": {
                     "entityType": "program",
                     "programType": "movie",
                     "entityId": "example-movie-id"
                   },
                   "context": {
                     "source": "voice"
                   }
                 })
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "foo",
    "intent": {
      "action": "playback",
      "data": {
        "entityType": "program",
        "programType": "movie",
        "entityId": "example-movie-id"
      },
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Launch the Aggregated Experience to a global page for a specific entity.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("urn:firebolt:apps:main",
                 {
                   "action": "entity",
                   "data": {
                     "entityType": "program",
                     "programType": "movie",
                     "entityId": "example-movie-id"
                   },
                   "context": {
                     "source": "voice"
                   }
                 })
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "urn:firebolt:apps:main",
    "intent": {
      "action": "entity",
      "data": {
        "entityType": "program",
        "programType": "movie",
        "entityId": "example-movie-id"
      },
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Launch the Aggregated Experience to a global page for the company / partner with the ID 'foo'.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("urn:firebolt:apps:main",
                 {
                   "action": "section",
                   "data": {
                     "sectionName": "company:foo"
                   },
                   "context": {
                     "source": "voice"
                   }
                 })
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "urn:firebolt:apps:main",
    "intent": {
      "action": "section",
      "data": {
        "sectionName": "company:foo"
      },
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Launch the Aggregated Experience to it's home screen, as if the Home remote button was pressed.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("urn:firebolt:apps:main", {"action":"home","context":{"source":"voice"}})
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "urn:firebolt:apps:main",
    "intent": {
      "action": "home",
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Launch the Aggregated Experience to it's search screen.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("urn:firebolt:apps:main", {"action":"search","context":{"source":"voice"}})
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "urn:firebolt:apps:main",
    "intent": {
      "action": "search",
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Launch the Aggregated Experience to it's settings screen.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("urn:firebolt:apps:main",
                 {
                   "action": "section",
                   "data": {
                     "sectionName": "settings"
                   },
                   "context": {
                     "source": "voice"
                   }
                 })
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "urn:firebolt:apps:main",
    "intent": {
      "action": "section",
      "data": {
        "sectionName": "settings"
      },
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Launch the Aggregated Experience to it's linear/epg guide.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("urn:firebolt:apps:main",
                 {
                   "action": "section",
                   "data": {
                     "sectionName": "guide"
                   },
                   "context": {
                     "source": "voice"
                   }
                 })
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "urn:firebolt:apps:main",
    "intent": {
      "action": "section",
      "data": {
        "sectionName": "guide"
      },
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

Launch the Aggregated Experience to the App Store details page for a specfic app with the ID 'foo'.

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.launch("urn:firebolt:apps:main",
                 {
                   "action": "section",
                   "data": {
                     "sectionName": "app:foo"
                   },
                   "context": {
                     "source": "voice"
                   }
                 })
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.launch",
  "params": {
    "appId": "urn:firebolt:apps:main",
    "intent": {
      "action": "section",
      "data": {
        "sectionName": "app:foo"
      },
      "context": {
        "source": "voice"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

</details>



---

### listen
Listen for events from this module.

To listen to a specific event pass the event name as the first parameter:


```typescript
Discovery.listen(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Discovery.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Discovery.listen((event: string, data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. The event data depends on which event is firing, see [Events](#events). |


Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event that has occured listen for, see [Events](#events). |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |


Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Discovery.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

---

### once
Listen for only one occurance of an event from this module. The callback will be cleared after one event.

To listen to a specific event pass the event name as the first parameter:


```typescript
Discovery.once(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Discovery.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Discovery.once((event: string, data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. The event data depends on which event is firing, see [Events](#events). |


Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event that has occured listen for, see [Events](#events). |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |


Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Discovery.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

---

### policy
get the discovery policy



To get the value, call the method with no parameters:


```typescript
function policy(): Promise<DiscoveryPolicy>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`DiscoveryPolicy`](#discoverypolicy) | discovery policy opt-in/outs |


**Examples**

Getting the discovery policy

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.policy()
    .then(policy => {
        console.log(policy)
    })
```
Value of `policy`:

```javascript
{
  "enableRecommendations": true,
  "shareWatchHistory": true,
  "rememberWatchedPrograms": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.policy",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "enableRecommendations": true,
    "shareWatchHistory": true,
    "rememberWatchedPrograms": true
  }
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function policy(subscriber: (policy: DiscoveryPolicy) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for policy changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Discovery.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `policy` | [`DiscoveryPolicy`](#discoverypolicy) | Yes | discovery policy opt-in/outs  |

**Examples**

Getting the discovery policy


JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.policy(policy => {
  // property value was changed
  console.log(policy)
}).then(listenerId => {
  // you can clear this listener w/ Discovery.clear(listenerId)
})
```

value of `policy`:

```javascript
{
  "enableRecommendations": true,
  "shareWatchHistory": true,
  "rememberWatchedPrograms": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.onPolicyChanged",
  "params": {
    "listen": true
  }
}
```

Response:
```json
{
  "jsonrpc": "2.0",
  "id": "1",
  "result": {
    "listening": "true"
  }
}
```

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "enableRecommendations": true,
    "shareWatchHistory": true,
    "rememberWatchedPrograms": true
  }
}
```

</details>



---


### purchasedContent
Return content purchased by the user, such as rentals and electronic sell through purchases.

The app should return the user's 100 most recent purchases in `entries`. The total count of purchases must be provided in `count`. If `count` is greater than the total number of `entries`, the UI may provide a link into the app to see the complete purchase list.

The `EntityInfo` object returned is not required to have `waysToWatch` populated, but it is recommended that it do so in case the UI wants to surface additional information on the purchases screen.

The app should implement both Push and Pull methods for `purchasedContent`.

The app should actively push `purchasedContent` when:

*  The app becomes Active.
*  When the state of the purchasedContent set has changed.
*  The app goes into Inactive or Background state, if there is a chance a change event has been missed.



To allow the platform to pull data, use `purchasedContent(callback)`:


```typescript
function purchasedContent(callback: (parameters: PurchasedContentParameters) => Promise<PurchasedContentResult>): Promise<boolean>
```



Parameters: 

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `callback` | `function` | Yes | A method the platform will call to pull `purchasedContent` data. |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `boolean` | Whether or not the callback registration was successful |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`PurchasedContentParameters`](#purchasedcontentparameters) | true | A PurchasedContentFederatedRequest object.  |

Callback promise resolution:

| Type | Description |
| ---- | ----------- |
| [`PurchasedContentResult`](#purchasedcontentresult) |  |


**Examples**

Inform the platform of the user's purchased content (Pull)


JavaScript:

```javascript
Discovery.purchasedContent(function(parameters) {
  return Promise.resolve({
  "correlationId": null,
  "result": {
    "totalCount": 10,
    "expires": "2025-01-01T00:00:00.000Z",
    "entries": [
      {
        "identifiers": {
          "entityId": "345"
        },
        "entityType": "program",
        "programType": "movie",
        "title": "Cool Runnings",
        "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
        "releaseDate": "1993-01-01T00:00:00.000Z",
        "contentRatings": [
          {
            "scheme": "US-Movie",
            "rating": "PG"
          },
          {
            "scheme": "CA-Movie",
            "rating": "G"
          }
        ],
        "waysToWatch": [
          {
            "identifiers": {
              "assetId": "123"
            },
            "expires": "2025-01-01T00:00:00.000Z",
            "entitled": true,
            "entitledExpires": "2025-01-01T00:00:00.000Z",
            "offeringType": "buy",
            "price": 2.99,
            "videoQuality": [
              "UHD"
            ],
            "audioProfile": [
              "dolbyAtmos"
            ],
            "audioLanguages": [
              "en"
            ],
            "closedCaptions": [
              "en"
            ],
            "subtitles": [
              "es"
            ],
            "audioDescriptions": [
              "en"
            ]
          }
        ]
      }
    ]
  }
})
}).then(success => {
  console.log(success)
})
```
Value of `success`

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request (from callback):

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.purchasedContent",
  "params": {
    "correlationId": "xyz",
    "result": {}
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To push data to the platform, e.g. during app launch, use `purchasedContent(correlationId: string, result: PurchasedContentResult)`:

```typescript
function purchasedContent(correlationId: string, result: PurchasedContentResult): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `correlationId` | `string` | true |   |
| `result` | [`PurchasedContentResult`](#purchasedcontentresult) | true | The data for the purachasedContent  |


Promise resolution:

boolean

**Examples**

Inform the platform of the user's purchased content


JavaScript:

```javascript
import { Discovery } from ''

Discovery.purchasedContent(null,
                           {
                             "totalCount": 10,
                             "expires": "2025-01-01T00:00:00.000Z",
                             "entries": [
                               {
                                 "identifiers": {
                                   "entityId": "345"
                                 },
                                 "entityType": "program",
                                 "programType": "movie",
                                 "title": "Cool Runnings",
                                 "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
                                 "releaseDate": "1993-01-01T00:00:00.000Z",
                                 "contentRatings": [
                                   {
                                     "scheme": "US-Movie",
                                     "rating": "PG"
                                   },
                                   {
                                     "scheme": "CA-Movie",
                                     "rating": "G"
                                   }
                                 ],
                                 "waysToWatch": [
                                   {
                                     "identifiers": {
                                       "assetId": "123"
                                     },
                                     "expires": "2025-01-01T00:00:00.000Z",
                                     "entitled": true,
                                     "entitledExpires": "2025-01-01T00:00:00.000Z",
                                     "offeringType": "buy",
                                     "price": 2.99,
                                     "videoQuality": [
                                       "UHD"
                                     ],
                                     "audioProfile": [
                                       "dolbyAtmos"
                                     ],
                                     "audioLanguages": [
                                       "en"
                                     ],
                                     "closedCaptions": [
                                       "en"
                                     ],
                                     "subtitles": [
                                       "es"
                                     ],
                                     "audioDescriptions": [
                                       "en"
                                     ]
                                   }
                                 ]
                               }
                             ]
                           })
```
Value of `success`

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.purchasedContent",
  "params": {
    "correlationId": null,
    "result": {
      "totalCount": 10,
      "expires": "2025-01-01T00:00:00.000Z",
      "entries": [
        {
          "identifiers": {
            "entityId": "345"
          },
          "entityType": "program",
          "programType": "movie",
          "title": "Cool Runnings",
          "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
          "releaseDate": "1993-01-01T00:00:00.000Z",
          "contentRatings": [
            {
              "scheme": "US-Movie",
              "rating": "PG"
            },
            {
              "scheme": "CA-Movie",
              "rating": "G"
            }
          ],
          "waysToWatch": [
            {
              "identifiers": {
                "assetId": "123"
              },
              "expires": "2025-01-01T00:00:00.000Z",
              "entitled": true,
              "entitledExpires": "2025-01-01T00:00:00.000Z",
              "offeringType": "buy",
              "price": 2.99,
              "videoQuality": [
                "UHD"
              ],
              "audioProfile": [
                "dolbyAtmos"
              ],
              "audioLanguages": [
                "en"
              ],
              "closedCaptions": [
                "en"
              ],
              "subtitles": [
                "es"
              ],
              "audioDescriptions": [
                "en"
              ]
            }
          ]
        }
      ]
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>



---

### signIn

Inform the platform that your user is signed in, for increased visiblity in search & discovery.

```typescript
function signIn(entitlements?: Entitlement[]): Promise<boolean>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `entitlements` | [`Entitlement`[]](undefinedEntertainmentSchema#/definitions/Entitlement) | false | Optional array of Entitlements, in case of a different user account, or a long time since last sign-in.  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Send signIn metric

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.signIn(null)
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.signIn",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

<details>
    <summary>More examples...</summary>
Send signIn notification with entitlements

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.signIn([
                   {
                     "entitlementId": "123",
                     "startTime": "2025-01-01T00:00:00.000Z",
                     "endTime": "2025-01-01T00:00:00.000Z"
                   }
                 ])
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.signIn",
  "params": {
    "entitlements": [
      {
        "entitlementId": "123",
        "startTime": "2025-01-01T00:00:00.000Z",
        "endTime": "2025-01-01T00:00:00.000Z"
      }
    ]
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>

</details>



---

### signOut

Inform the platform that your user has signed out and that entitlements may no longer be valid.

```typescript
function signOut(): Promise<boolean>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Send signOut notification

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.signOut()
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.signOut",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### watched

Notify the platform that content was partially or completely watched

```typescript
function watched(entityId: string, progress?: number, completed?: boolean, watchedOn?: string): Promise<boolean>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `entityId` | `string` | true | The entity Id of the watched content.  |
| `progress` | `number` | false | How much of the content has been watched (percentage as 0-1 for VOD, number of seconds for live) <br/>minumum: 0 |
| `completed` | `boolean` | false | Whether or not this viewing is considered "complete," per the app's definition thereof  |
| `watchedOn` | `string` | false | Date/Time the content was watched, ISO 8601 Date/Time <br/>format: date-time |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` | whether the call was successful or not |


**Examples**

Notifying the platform of watched content

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.watched("partner.com/entity/123", 0.95, true, "2021-04-23T18:25:43.511Z")
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.watched",
  "params": {
    "entityId": "partner.com/entity/123",
    "progress": 0.95,
    "completed": true,
    "watchedOn": "2021-04-23T18:25:43.511Z"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### watchNext

Suggest a call-to-action for this app on the platform home screen

```typescript
function watchNext(title?: LocalizedString, identifiers?: ContentIdentifiers, expires?: string, images?: object): Promise<boolean>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `title` | [`LocalizedString`](../schemas/types#/definitions/localizedstring) | false | The title of this call to action  |
| `identifiers` | [`ContentIdentifiers`](#contentidentifiers) | false | A set of content identifiers for this call to action  |
| `expires` | `string` | false | When this call to action should no longer be presented to users <br/>format: date-time |
| `images` | `object` | false | A set of images for this call to action  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` | whether the call was successful or not |


**Examples**

Suggest a watch-next tile for the home screen

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.watchNext("A Cool Show",
                    {
                      "entityId": "partner.com/entity/123"
                    },
                    "2021-04-23T18:25:43.511Z",
                    {
                      "3x4": {
                        "en-US": "https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg",
                        "es": "https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg"
                      },
                      "16x9": {
                        "en": "https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg"
                      }
                    })
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.watchNext",
  "params": {
    "title": "A Cool Show",
    "identifiers": {
      "entityId": "partner.com/entity/123"
    },
    "expires": "2021-04-23T18:25:43.511Z",
    "images": {
      "3x4": {
        "en-US": "https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg",
        "es": "https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg"
      },
      "16x9": {
        "en": "https://i.ytimg.com/vi/4r7wHMg5Yjg/maxresdefault.jpg"
      }
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---






## Events

### navigateTo
listen to `navigateTo` events


See also: [listen()](#listen), [once()](#listen), [clear()](#listen).

Event value:

| Type | Description |
| ---- | ----------- |
| [`NavigationIntent`](../schemas/intents#/definitions/navigationintent) | A Firebolt compliant representation of a user intention to navigate to a specific place in an app. |


**Examples**

Listening for `navigateTo` events:

JavaScript:

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.listen('navigateTo', value => {
  console.log(value)
})
```
Value of `value`

```javascript
{
  "action": "search",
  "data": {
    "query": "a cool show"
  },
  "context": {
    "campaign": "unknown",
    "source": "voice"
  }
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "discovery.onNavigateTo",
  "params": {
    "listen": true
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "action": "search",
    "data": {
      "query": "a cool show"
    },
    "context": {
      "campaign": "unknown",
      "source": "voice"
    }
  }
}
```

</details>



---




### Additional events
The following events are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Payload | Documentation |
|------------|-----|---------|---------------|
| policyChanged | onPolicyChanged | [DiscoveryPolicy](#discoverypolicy) | [policy](#policy) |
| _NA_ | onPullEntityInfo | [EntityInfoFederatedRequest](#entityinfofederatedrequest) | [entityInfo](#entityinfo) |
| _NA_ | onPullPurchasedContent | [PurchasedContentFederatedRequest](#purchasedcontentfederatedrequest) | [purchasedContent](#purchasedcontent) |







## Schemas

### DiscoveryPolicy


```typescript
type DiscoveryPolicy = {
  enableRecommendations: boolean    // Whether or not to the user has enabled history-based recommendations
  shareWatchHistory: boolean        // Whether or not the user has enabled app watch history data to be shared with the platform
  rememberWatchedPrograms: boolean  // Whether or not the user has enabled watch history
}
```



---

### EntityInfo


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

```typescript
type EntityInfo = {
  identifiers: ContentIdentifiers   // The ContentIdentifiers object is how the app identifies an entity or asset to
  title: string                     // Title of the entity.
  entityType: "program"
  programType: ProgramType          // In the case of a program `entityType`, specifies the program type.
  synopsis?: string                 // Short description of the entity.
  seasonNumber?: number             // For TV seasons, the season number. For TV episodes, the season that the episode belongs to.
  episodeNumber?: number            // For TV episodes, the episode number.
  releaseDate?: string              // The date that the program or entity was released or first aired.
  contentRatings?: ContentRating[]  // A list of ContentRating objects, describing the entity's ratings in various rating schemes.
  waysToWatch?: WayToWatch[]        // An array of ways a user is might watch this entity, regardless of entitlements.
}
```

See also: 

 - [ProgramType](../schemas/entertainment#programtype)

---

### WayToWatch


A WayToWatch describes a way to watch a video program. It may describe a single
streamable asset or a set of streamable assets. For example, an app provider may
describe HD, SD, and UHD assets as individual WayToWatch objects or rolled into
a single WayToWatch.

If the WayToWatch represents a single streamable asset, the provided
ContentIdentifiers must be sufficient to play back the specific asset when sent
via a playback intent or deep link. If the WayToWatch represents multiple
streamable assets, the provided ContentIdentifiers must be sufficient to
playback one of the assets represented with no user action. In this scenario,
the app SHOULD choose the best asset for the user based on their device and
settings. The ContentIdentifiers MUST also be sufficient for navigating the user
to the appropriate entity or detail screen via an entity intent.

The app should set the `entitled` property to indicate if the user can watch, or
not watch, the asset without making a purchase. If the entitlement is known to
expire at a certain time (e.g., a rental), the app should also provide the
`entitledExpires` property. If the entitlement is not expired, the UI will use
the `entitled` property to display watchable assets to the user, adjust how
assets are presented to the user, and how intents into the app are generated.
For example, the Aggregated Experience could render a "Watch" button for an
entitled asset versus a "Subscribe" button for an non-entitled asset.

The app should set the `offeringType` to define how the content may be
authorized. The UI will use this to adjust how content is presented to the user.

A single WayToWatch cannot represent streamable assets available via multiple
purchase paths. If, for example, an asset has both Buy, Rent and Subscription
availability, the three different entitlement paths MUST be represented as
multiple WayToWatch objects.

`price` should be populated for WayToWatch objects with `buy` or `rent`
`offeringType`. If the WayToWatch represents a set of assets with various price
points, the `price` provided must be the lowest available price.

```typescript
type WayToWatch = {
  identifiers: ContentIdentifiers       // The ContentIdentifiers object is how the app identifies an entity or asset to
  expires?: string                      // Time when the WayToWatch is no longer available.
  entitled?: boolean                    // Specify if the user is entitled to watch the entity.
  entitledExpires?: string              // Time when the entity is no longer entitled.
  offeringType?: OfferingType           // The offering type of the WayToWatch.
  hasAds?: boolean                      // True if the streamable asset contains ads.
  price?: number                        // For "buy" and "rent" WayToWatch, the price to buy or rent in the user's preferred currency.
  videoQuality?: 'SD' | 'HD' | 'UHD'[]  // List of the video qualities available via the WayToWatch.
  audioProfile?: AudioProfile[]         // List of the audio types available via the WayToWatch.
  audioLanguages?: string[]             // List of audio track languages available on the WayToWatch. The first is considered the primary language. Languages are expressed as ISO 639 1/2 codes.
  closedCaptions?: string[]             // List of languages for which closed captions are available on the WayToWatch. Languages are expressed as ISO 639 1/2 codes.
  subtitles?: string[]                  // List of languages for which subtitles are available on the WayToWatch. Languages are expressed as ISO 639 1/2 codes.
  audioDescriptions?: string[]          // List of languages for which audio descriptions (DVS) are available on the WayToWatch. Languages are expressed as ISO 639 1/2 codes.
}
```

See also: 

 - [OfferingType](../schemas/entertainment#offeringtype)
 - [AudioProfile](../schemas/types#audioprofile)

---

### ContentRating


A ContentRating represents an age or content based of an entity. Supported rating schemes and associated types are below.

## United States

`US-Movie` (MPAA):

Ratings: `NR`, `G`, `PG`, `PG13`, `R`, `NC17`

Advisories: `AT`, `BN`, `SL`, `SS`, `N`, `V`

`US-TV` (Vchip):

Ratings: `TVY`, `TVY7`, `TVG`, `TVPG`, `TV14`, `TVMA`

Advisories: `FV`, `D`, `L`, `S`, `V`

## Canada

`CA-Movie` (OFRB):

Ratings: `G`, `PG`, `14A`, `18A`, `R`, `E`

`CA-TV` (AGVOT)

Ratings: `E`, `C`, `C8`, `G`, `PG`, `14+`, `18+`

Advisories: `C`, `C8`, `G`, `PG`, `14+`, `18+`

`CA-Movie-Fr` (Canadian French language movies):

Ratings: `G`, `8+`, `13+`, `16+`, `18+`

`CA-TV-Fr` (Canadian French language TV):

Ratings: `G`, `8+`, `13+`, `16+`, `18+`


```typescript
type ContentRating = {
  scheme: 'CA-Movie' | 'CA-TV' | 'CA-Movie-Fr' | 'CA-TV-Fr' | 'US-Movie' | 'US-TV'  // The rating scheme.
  rating: string                                                                    // The content rating.
  advisories?: string[]                                                             // Optional list of subratings or content advisories.
}
```



---

### ContentIdentifiers


The ContentIdentifiers object is how the app identifies an entity or asset to
the Firebolt platform. These ids are used to look up metadata and deep link into
the app.

Apps do not need to provide all ids. They only need to provide the minimum
required to target a playable stream or an entity detail screen via a deep link.
If an id isn't needed to get to those pages, it doesn't need to be included.

```typescript
type ContentIdentifiers = {
  assetId?: string           // Identifies a particular playable asset. For example, the HD version of a particular movie separate from the UHD version.
  entityId?: string          // Identifies an entity, such as a Movie, TV Series or TV Episode.
  seasonId?: string          // The TV Season for a TV Episode.
  seriesId?: string          // The TV Series for a TV Episode or TV Season.
  appContentData?: string    // App-specific content identifiers.
}
```



---

### FederatedRequest


```typescript
type FederatedRequest = {
  correlationId: string
}
```



---

### FederatedResponse


```typescript
type FederatedResponse = {
  correlationId: string
}
```



---

### EntityInfoFederatedRequest


```typescript
type EntityInfoFederatedRequest = {
  correlationId: string
  parameters: EntityInfoParameters
}
```



---

### EntityInfoParameters


```typescript
type EntityInfoParameters = {
  entityId: string
  assetId?: string
}
```



---

### EntityInfoFederatedResponse


```typescript
type EntityInfoFederatedResponse = {
  correlationId: string
  result: EntityInfoResult            // The result for an `entityInfo()` push or pull.
}
```



---

### EntityInfoResult


The result for an `entityInfo()` push or pull.

```typescript
type EntityInfoResult = {
  expires: string
  entity: EntityInfo       // An EntityInfo object represents an "entity" on the platform. Currently, only entities of type `program` are supported. `programType` must be supplied to identify the program type.
  related?: EntityInfo[]
}
```



---

### PurchasedContentFederatedRequest


```typescript
type PurchasedContentFederatedRequest = {
  correlationId: string
  parameters: PurchasedContentParameters
}
```



---

### PurchasedContentParameters


```typescript
type PurchasedContentParameters = {
  limit: number
  offeringType?: OfferingType        // The offering type of the WayToWatch.
  programType?: ProgramType          // In the case of a program `entityType`, specifies the program type.
}
```

See also: 

 - [OfferingType](../schemas/entertainment#offeringtype)
 - [ProgramType](../schemas/entertainment#programtype)

---

### PurchasedContentFederatedResponse


```typescript
type PurchasedContentFederatedResponse = {
  correlationId: string
  result: PurchasedContentResult
}
```



---

### PurchasedContentResult


```typescript
type PurchasedContentResult = {
  expires: string
  totalCount: number
  entries: EntityInfo[]
}
```



---


