---
title: Account
---

# Account Module
---
Version 0.8.0

## Overview
 A module for querying about the device account.

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [account.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/account.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [id](#id)
    - [uid](#uid)



 - [Schemas](#schemas)

<span></span>

## Usage
To use the Account module, you can import it into your project from the Firebolt SDK:

```javascript
import { Account } from '@firebolt-js/sdk'
```


## Methods
### id
Get the platform back-office account identifier



To get the value, call the method with no parameters:


```typescript
function id(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the id |


**Examples**

Default Example

JavaScript:

```javascript
import { Account } from '@firebolt-js/sdk'

Account.id()
    .then(id => {
        console.log(id)
    })
```
Value of `id`:

```javascript
"123"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "account.id",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "123"
}
```

</details>








### uid
Gets a unique id for the current app & account



To get the value, call the method with no parameters:


```typescript
function uid(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | a unique ID |


**Examples**

Getting the unique ID

JavaScript:

```javascript
import { Account } from '@firebolt-js/sdk'

Account.uid()
    .then(uniqueId => {
        console.log(uniqueId)
    })
```
Value of `uniqueId`:

```javascript
"ee6723b8-7ab3-462c-8d93-dbf61227998e"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "account.uid",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "ee6723b8-7ab3-462c-8d93-dbf61227998e"
}
```

</details>
















