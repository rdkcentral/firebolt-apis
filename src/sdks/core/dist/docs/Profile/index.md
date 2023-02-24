Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [profile.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/profile.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [approveContentRating](#approvecontentrating)
    - [approvePurchase](#approvepurchase)
    - [flags](#flags)



 - [Schemas](#schemas)
    - [FlatMap](#flatmap)

<span></span>

## Usage
To use the Profile module, you can import it into your project from the Firebolt SDK:

```javascript
import { Profile } from '@firebolt-js/sdk'
```


## Methods
### approveContentRating

Verifies that the current profile should have access to mature/adult content.

```typescript
function approveContentRating(): Promise<boolean>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` | Whether or not to allow access |


**Examples**

Default Example

JavaScript:

```javascript
import { Profile } from '@firebolt-js/sdk'

Profile.approveContentRating()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
false
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "profile.approveContentRating",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": false
}
```

</details>




---

### approvePurchase

Verifies that the current profile should have access to making purchases.

```typescript
function approvePurchase(): Promise<boolean>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` | Whether or not to allow access |


**Examples**

Default Example

JavaScript:

```javascript
import { Profile } from '@firebolt-js/sdk'

Profile.approvePurchase()
    .then(allow => {
        console.log(allow)
    })
```
Value of `allow`:

```javascript
false
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "profile.approvePurchase",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": false
}
```

</details>




---

### flags

Get a map of profile flags for the current session.

```typescript
function flags(): Promise<object>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | The profile flags. |


**Examples**

Default Example

JavaScript:

```javascript
import { Profile } from '@firebolt-js/sdk'

Profile.flags()
    .then(flags => {
        console.log(flags)
    })
```
Value of `flags`:

```javascript
{
  "userExperience": "1000"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "profile.flags",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "userExperience": "1000"
  }
}
```

</details>




---










## Schemas

### FlatMap


```typescript
type FlatMap = {
  [property: string]: string | number | boolean
}
```



---


