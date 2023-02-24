Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [authentication.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/authentication.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [token](#token)
    - [device](#device)
    - [session](#session)
    - [root](#root)



 - [Schemas](#schemas)
    - [TokenType](#tokentype)

<span></span>

## Usage
To use the Authentication module, you can import it into your project from the Firebolt SDK:

```javascript
import { Authentication } from '@firebolt-js/sdk'
```


## Methods
### token

This API is **deprecated** since version 0.9.0. Authentication module has individual methods for each token type.

Get a specific `type` of authentication token

```typescript
function token(type: TokenType, options?: object): Promise<object>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `type` | [`TokenType`](#tokentype) | true | What type of token to get  |
| `options` | `object` | false | Additional options for acquiring the token.  |


Promise resolution:

the token value, type, and expiration

| Field | Type | Description |
| ----- | ---- | ----------- |
| `value` | `string` |  |
| `expires` | `string` |  |
| `type` | `string` |  |


**Examples**

Acquire a Firebolt platform token

JavaScript:

```javascript
import { Authentication } from '@firebolt-js/sdk'

Authentication.token("platform", null)
    .then(token => {
        console.log(token)
    })
```
Value of `token`:

```javascript
{
  "value": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c",
  "expires": "2022-04-23T18:25:43.511Z",
  "type": "platform"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "authentication.token",
  "params": {
    "type": "platform"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "value": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c",
    "expires": "2022-04-23T18:25:43.511Z",
    "type": "platform"
  }
}
```

</details>

<details>
    <summary>More examples...</summary>
Acquire a Firebolt device identity token

JavaScript:

```javascript
import { Authentication } from '@firebolt-js/sdk'

Authentication.token("device", null)
    .then(token => {
        console.log(token)
    })
```
Value of `token`:

```javascript
{
  "value": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c",
  "expires": "2022-04-23T18:25:43.511Z",
  "type": "device"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "authentication.token",
  "params": {
    "type": "device"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "value": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c",
    "expires": "2022-04-23T18:25:43.511Z",
    "type": "device"
  }
}
```

</details>

Acquire a Firebolt distributor token

JavaScript:

```javascript
import { Authentication } from '@firebolt-js/sdk'

Authentication.token("distributor", {"clientId":"xyz"})
    .then(token => {
        console.log(token)
    })
```
Value of `token`:

```javascript
{
  "value": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c",
  "expires": "2022-04-23T18:25:43.511Z",
  "type": "distributor",
  "data": {
    "tid": "EB00E9230AB2A35F57DB4EFDDC4908F6446D38F08F4FF0BD57FE6A61E21EEFD9",
    "scope": "scope"
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
  "method": "authentication.token",
  "params": {
    "type": "distributor",
    "options": {
      "clientId": "xyz"
    }
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "value": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c",
    "expires": "2022-04-23T18:25:43.511Z",
    "type": "distributor",
    "data": {
      "tid": "EB00E9230AB2A35F57DB4EFDDC4908F6446D38F08F4FF0BD57FE6A61E21EEFD9",
      "scope": "scope"
    }
  }
}
```

</details>

</details>



---

### device

Get a device token scoped to the current app.

```typescript
function device(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the token value and expiration |


**Examples**

Acquire a Firebolt device identity token

JavaScript:

```javascript
import { Authentication } from '@firebolt-js/sdk'

Authentication.device()
    .then(token => {
        console.log(token)
    })
```
Value of `token`:

```javascript
"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "authentication.device",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"
}
```

</details>




---

### session

Get a destributor session token.

```typescript
function session(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the token value |


**Examples**

Acquire a distributor session token

JavaScript:

```javascript
import { Authentication } from '@firebolt-js/sdk'

Authentication.session()
    .then(token => {
        console.log(token)
    })
```
Value of `token`:

```javascript
"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "authentication.session",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"
}
```

</details>




---

### root

Get a root device token.

```typescript
function root(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the token value |


**Examples**

Acquire a Firebolt root device identity token

JavaScript:

```javascript
import { Authentication } from '@firebolt-js/sdk'

Authentication.root()
    .then(token => {
        console.log(token)
    })
```
Value of `token`:

```javascript
"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "authentication.root",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"
}
```

</details>




---










## Schemas

### TokenType


```typescript
type TokenType = 'platform' | 'device' | 'distributor'
```



---


