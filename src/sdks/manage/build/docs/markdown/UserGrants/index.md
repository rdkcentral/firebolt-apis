Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [usergrants.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/usergrants.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [app](#app)
    - [device](#device)
    - [capability](#capability)
    - [grant](#grant)
    - [deny](#deny)
    - [clear](#clear)
    - [request](#request)



 - [Schemas](#schemas)
    - [Capability](#capability)
    - [Permission](#permission)
    - [Role](#role)
    - [GrantInfo](#grantinfo)
    - [AppInfo](#appinfo)
    - [GrantState](#grantstate)
    - [GrantModificationOptions](#grantmodificationoptions)

<span></span>

## Usage
To use the UserGrants module, you can import it into your project from the Firebolt SDK:

```javascript
import { UserGrants } from '@firebolt-js/manage-sdk'
```


## Methods
### app

Get all granted and denied user grants for the given app

```typescript
function app(appId: string): Promise<object[]>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `appId` | `string` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | The list of grants for this app |


**Examples**

Default Example

JavaScript:

```javascript
import { UserGrants } from '@firebolt-js/manage-sdk'

UserGrants.app("certapp")
    .then(info => {
        console.log(info)
    })
```
Value of `info`:

```javascript
[
  {
    "app": {
      "id": "certapp",
      "title": "Firebolt Certification"
    },
    "state": "granted",
    "capability": "xrn:firebolt:capability:data:app-usage",
    "role": "use",
    "lifespan": "seconds",
    "expires": "2022-12-14T20:20:39+00:00"
  },
  {
    "app": {
      "id": "certapp",
      "title": "Firebolt Certification"
    },
    "state": "denied",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "role": "use",
    "lifespan": "appActive"
  }
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "usergrants.app",
  "params": {
    "appId": "certapp"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    {
      "app": {
        "id": "certapp",
        "title": "Firebolt Certification"
      },
      "state": "granted",
      "capability": "xrn:firebolt:capability:data:app-usage",
      "role": "use",
      "lifespan": "seconds",
      "expires": "2022-12-14T20:20:39+00:00"
    },
    {
      "app": {
        "id": "certapp",
        "title": "Firebolt Certification"
      },
      "state": "denied",
      "capability": "xrn:firebolt:capability:localization:postal-code",
      "role": "use",
      "lifespan": "appActive"
    }
  ]
}
```

</details>




---

### device

Get all granted and denied user grants for the device

```typescript
function device(): Promise<object[]>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | The list of grants for the device |


**Examples**

Default Example

JavaScript:

```javascript
import { UserGrants } from '@firebolt-js/manage-sdk'

UserGrants.device()
    .then(info => {
        console.log(info)
    })
```
Value of `info`:

```javascript
[
  {
    "state": "granted",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "role": "use",
    "lifespan": "powerActive"
  }
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "usergrants.device",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    {
      "state": "granted",
      "capability": "xrn:firebolt:capability:localization:postal-code",
      "role": "use",
      "lifespan": "powerActive"
    }
  ]
}
```

</details>




---

### capability

Get all granted and denied user grants for the given capability

```typescript
function capability(capability: string): Promise<object[]>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `capability` | `string` | true |  <br/>pattern: xrn:firebolt:capability:([a-z0-9]+)((:[a-z0-9]+)?) |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | The list of grants associated with the given capability |


**Examples**

Default Example

JavaScript:

```javascript
import { UserGrants } from '@firebolt-js/manage-sdk'

UserGrants.capability("xrn:firebolt:capability:localization:postal-code")
    .then(info => {
        console.log(info)
    })
```
Value of `info`:

```javascript
[
  {
    "state": "granted",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "role": "use",
    "lifespan": "powerActive"
  }
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "usergrants.capability",
  "params": {
    "capability": "xrn:firebolt:capability:localization:postal-code"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    {
      "state": "granted",
      "capability": "xrn:firebolt:capability:localization:postal-code",
      "role": "use",
      "lifespan": "powerActive"
    }
  ]
}
```

</details>




---

### grant

Grants a given capability to a specific app, if appropriate. Calling this results in a persisted active grant that lasts for the duration of the grant policy lifespan. 

```typescript
function grant(role: Role, capability: string, options?: object): Promise<'null'>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `role` | [`Role`](#role) | true |   |
| `capability` | `string` | true |  <br/>pattern: xrn:firebolt:capability:([a-z0-9]+)((:[a-z0-9]+)?) |
| `options` | `object` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| 'null' |  |


**Examples**

Default Example

JavaScript:

```javascript
import { UserGrants } from '@firebolt-js/manage-sdk'

UserGrants.grant("use", "xrn:firebolt:capability:localization:postal-code", {"appId":"certapp"})
    .then(voice => {
        console.log(voice)
    })
```
Value of `voice`:

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
  "method": "usergrants.grant",
  "params": {
    "role": "use",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "options": {
      "appId": "certapp"
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




---

### deny

Denies a given capability, to a specific app if appropriate. Calling this results in a persisted Denied Grant that lasts for the duration of the Grant Policy lifespan. 

```typescript
function deny(role: Role, capability: string, options?: object): Promise<'null'>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `role` | [`Role`](#role) | true |   |
| `capability` | `string` | true |  <br/>pattern: xrn:firebolt:capability:([a-z0-9]+)((:[a-z0-9]+)?) |
| `options` | `object` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| 'null' |  |


**Examples**

Default Example

JavaScript:

```javascript
import { UserGrants } from '@firebolt-js/manage-sdk'

UserGrants.deny("use", "xrn:firebolt:capability:localization:postal-code", {"appId":"certapp"})
    .then(voice => {
        console.log(voice)
    })
```
Value of `voice`:

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
  "method": "usergrants.deny",
  "params": {
    "role": "use",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "options": {
      "appId": "certapp"
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




---

### clear

Clears the grant for a given capability, to a specific app if appropriate. Calling this results in a persisted Denied Grant that lasts for the duration of the Grant Policy lifespan. 

```typescript
function clear(role: Role, capability: string, options?: object): Promise<'null'>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `role` | [`Role`](#role) | true |   |
| `capability` | `string` | true |  <br/>pattern: xrn:firebolt:capability:([a-z0-9]+)((:[a-z0-9]+)?) |
| `options` | `object` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| 'null' |  |


**Examples**

Default Example

JavaScript:

```javascript
import { UserGrants } from '@firebolt-js/manage-sdk'

UserGrants.clear("use", "xrn:firebolt:capability:localization:postal-code", {"appId":"certapp"})
    .then(voice => {
        console.log(voice)
    })
```
Value of `voice`:

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
  "method": "usergrants.clear",
  "params": {
    "role": "use",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "options": {
      "appId": "certapp"
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




---

### request

Requests Firebolt to carry out a set of user grants for a given application such that the user grant provider is notified or an existing user grant is reused.

```typescript
function request(appId: string, permissions: Permission[]): Promise<object[]>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `appId` | `string` | true |   |
| `permissions` | [`Permission`[]](#permission) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | The result of all grants requested by this |


**Examples**

Default result

JavaScript:

```javascript
import { UserGrants } from '@firebolt-js/manage-sdk'

UserGrants.request("certapp",
                   [
                     {
                       "role": "use",
                       "capability": "xrn:firebolt:capability:localization:postal-code"
                     }
                   ])
    .then(info => {
        console.log(info)
    })
```
Value of `info`:

```javascript
[
  {
    "app": {
      "id": "certapp",
      "title": "Certification App"
    },
    "state": "granted",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "role": "use",
    "lifespan": "powerActive"
  }
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "usergrants.request",
  "params": {
    "appId": "certapp",
    "permissions": [
      {
        "role": "use",
        "capability": "xrn:firebolt:capability:localization:postal-code"
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
  "result": [
    {
      "app": {
        "id": "certapp",
        "title": "Certification App"
      },
      "state": "granted",
      "capability": "xrn:firebolt:capability:localization:postal-code",
      "role": "use",
      "lifespan": "powerActive"
    }
  ]
}
```

</details>




---










## Schemas

### Capability


A Capability is a discrete unit of functionality that a Firebolt device might be able to perform.

```typescript
type Capability = string
```



---

### Permission


A Capability combined with a Role, which an app may be permitted (by a distributor) or granted (by an end user).

```typescript
type Permission = {
  role?: Role          // Role provides access level for the app for a given capability.
  capability?: string  // A Capability is a discrete unit of functionality that a Firebolt device might be able to perform.
}
```



---

### Role


Role provides access level for the app for a given capability.

```typescript
type Role = 'use' | 'manage' | 'provide'
```



---

### GrantInfo


Information about a grant given by a user

```typescript
type GrantInfo = {
  app?: {
    id: string
    title?: string
  }
  state: 'granted' | 'denied'                                             // The state the grant is in
  capability: string                                                      // A Capability is a discrete unit of functionality that a Firebolt device might be able to perform.
  role: Role                                                              // Role provides access level for the app for a given capability.
  lifespan: 'once' | 'forever' | 'appActive' | 'powerActive' | 'seconds'
  expires?: string
}
```



---

### AppInfo


Information about an app that a grant was for

```typescript
type AppInfo = {
  id: string
  title?: string
}
```



---

### GrantState


The state the grant is in

```typescript
type GrantState = 'granted' | 'denied'
```



---

### GrantModificationOptions


Options when modifying any grant

```typescript
type GrantModificationOptions = {
  appId?: string
}
```



---


