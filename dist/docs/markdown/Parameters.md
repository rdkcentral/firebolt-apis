---
title: Parameters
---

# Parameters Module
---
Version 0.8.0

## Overview
 Methods for getting initialization parameters for an app cold launch.

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [parameters.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/parameters.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [initialization](#initialization)



 - [Schemas](#schemas)
    - [AppInitialization](#appinitialization)

<span></span>

## Usage
To use the Parameters module, you can import it into your project from the Firebolt SDK:

```javascript
import { Parameters } from '@firebolt-js/sdk'
```


## Methods
### initialization

Returns any initialization parameters for the app, e.g. initialial `NavigationIntent`.

```typescript
function initialization(): Promise<AppInitialization>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`AppInitialization`](#appinitialization) | The initialization parameters. |


**Examples**

Default Example

JavaScript:

```javascript
import { Parameters } from '@firebolt-js/sdk'

Parameters.initialization()
    .then(init => {
        console.log(init)
    })
```
Value of `init`:

```javascript
{
  "lmt": 0,
  "us_privacy": "1-Y-",
  "discovery": {
    "navigateTo": {
      "action": "entity",
      "data": {
        "entityId": "abc",
        "entityType": "program",
        "programType": "movie"
      },
      "context": {
        "source": "voice"
      }
    }
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
  "method": "parameters.initialization",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "lmt": 0,
    "us_privacy": "1-Y-",
    "discovery": {
      "navigateTo": {
        "action": "entity",
        "data": {
          "entityId": "abc",
          "entityType": "program",
          "programType": "movie"
        },
        "context": {
          "source": "voice"
        }
      }
    }
  }
}
```

</details>




---










## Schemas

### AppInitialization


```typescript
type AppInitialization = {
  us_privacy?: string                  // The IAB US Privacy string.
  lmt?: number                         // The IAB limit ad tracking opt out value.
  discovery?: {
    navigateTo?: NavigationIntent      // A Firebolt compliant representation of a user intention to navigate to a specific place in an app.
  }
  secondScreen?: {
    launchRequest?: SecondScreenEvent  // An a message notification from a second screen device
  }
}
```

See also: 

 - [NavigationIntent](../schemas/intents#navigationintent)
 - [SecondScreenEvent](../schemas/secondscreen#secondscreenevent)

---


