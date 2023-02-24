Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [advertising.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/advertising.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [resetIdentifier](#resetidentifier)



 - [Schemas](#schemas)

<span></span>

## Usage
To use the Advertising module, you can import it into your project from the Firebolt SDK:

```javascript
import { Advertising } from '@firebolt-js/manage-sdk'
```


## Methods
### resetIdentifier

Resets a user's identifier in the ad platform so that the advertising id that apps get will be a new value

```typescript
function resetIdentifier(): Promise<void>
```


Promise resolution:

```javascript
void
```

**Examples**

Default Example

JavaScript:

```javascript
import { Advertising } from '@firebolt-js/manage-sdk'

Advertising.resetIdentifier()
    .then(result => {
        console.log(result)
    })
```
Value of `result`:

```javascript
null
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "advertising.resetIdentifier",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": null
}
```

</details>




---









