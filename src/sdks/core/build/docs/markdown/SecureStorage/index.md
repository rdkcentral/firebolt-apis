Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [securestorage.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/securestorage.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [get](#get)
    - [set](#set)
    - [remove](#remove)



 - [Schemas](#schemas)
    - [StorageScope](#storagescope)
    - [StorageOptions](#storageoptions)

<span></span>

## Usage
To use the SecureStorage module, you can import it into your project from the Firebolt SDK:

```javascript
import { SecureStorage } from '@firebolt-js/sdk'
```


## Methods
### get

Get stored value by key

```typescript
function get(scope: StorageScope, key: string): Promise<string | null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `scope` | [`StorageScope`](#storagescope) | true | The scope of the key/value  |
| `key` | `string` | true | Key to get  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string \| null` | The retrieved value, if found. |


**Examples**

Successfully retrieve a refresh token with key authRefreshToken

JavaScript:

```javascript
import { SecureStorage } from '@firebolt-js/sdk'

SecureStorage.get("device", "authRefreshToken")
    .then(value => {
        console.log(value)
    })
```
Value of `value`:

```javascript
"VGhpcyBub3QgYSByZWFsIHRva2VuLgo="
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "securestorage.get",
  "params": {
    "scope": "device",
    "key": "authRefreshToken"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "VGhpcyBub3QgYSByZWFsIHRva2VuLgo="
}
```

</details>

<details>
    <summary>More examples...</summary>
Attempt to retrieve a key with no value set

JavaScript:

```javascript
import { SecureStorage } from '@firebolt-js/sdk'

SecureStorage.get("account", "authRefreshToken")
    .then(value => {
        console.log(value)
    })
```
Value of `value`:

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
  "method": "securestorage.get",
  "params": {
    "scope": "account",
    "key": "authRefreshToken"
  }
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

</details>



---

### set

Set or update a secure data value

```typescript
function set(scope: StorageScope, key: string, value: string, options?: StorageOptions): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `scope` | [`StorageScope`](#storagescope) | true | The scope of the data key  |
| `key` | `string` | true | Key to set  |
| `value` | `string` | true | Value to set  |
| `options` | [`StorageOptions`](#storageoptions) | false | Optional parameters to set  |


Promise resolution:

```javascript
void
```

**Examples**

Set a refresh token with name authRefreshToken with optional paramter

JavaScript:

```javascript
import { SecureStorage } from '@firebolt-js/sdk'

SecureStorage.set("device", "authRefreshToken", "VGhpcyBub3QgYSByZWFsIHRva2VuLgo=", {"ttl":600})
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

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
  "method": "securestorage.set",
  "params": {
    "scope": "device",
    "key": "authRefreshToken",
    "value": "VGhpcyBub3QgYSByZWFsIHRva2VuLgo=",
    "options": {
      "ttl": 600
    }
  }
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

<details>
    <summary>More examples...</summary>
Set a refresh token with name authRefreshToken without optional parameter

JavaScript:

```javascript
import { SecureStorage } from '@firebolt-js/sdk'

SecureStorage.set("account", "authRefreshToken", "VGhpcyBub3QgYSByZWFsIHRva2VuLgo=", null)
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

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
  "method": "securestorage.set",
  "params": {
    "scope": "account",
    "key": "authRefreshToken",
    "value": "VGhpcyBub3QgYSByZWFsIHRva2VuLgo="
  }
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

</details>



---

### remove

Remove a secure data value

```typescript
function remove(scope: StorageScope, key: string): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `scope` | [`StorageScope`](#storagescope) | true | The scope of the data key  |
| `key` | `string` | true | Key to remove  |


Promise resolution:

```javascript
void
```

**Examples**

Remove the value with key authRefreshToken for device

JavaScript:

```javascript
import { SecureStorage } from '@firebolt-js/sdk'

SecureStorage.remove("device", "authRefreshToken")
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

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
  "method": "securestorage.remove",
  "params": {
    "scope": "device",
    "key": "authRefreshToken"
  }
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

<details>
    <summary>More examples...</summary>
Remove the value with key authRefreshToken for account

JavaScript:

```javascript
import { SecureStorage } from '@firebolt-js/sdk'

SecureStorage.remove("account", "authRefreshToken")
    .then(success => {
        console.log(success)
    })
```
Value of `success`:

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
  "method": "securestorage.remove",
  "params": {
    "scope": "account",
    "key": "authRefreshToken"
  }
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

</details>



---










## Schemas

### StorageScope


The scope of the data

```typescript
type StorageScope = 'device' | 'account'
```



---

### StorageOptions


```typescript
type StorageOptions = {
  ttl: number            // Seconds from set time before the data expires and is removed
}
```



---


