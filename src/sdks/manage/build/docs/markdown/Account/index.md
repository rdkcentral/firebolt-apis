Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [account.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/account.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [listen](#listen)
    - [once](#once)
    - [provide](#provide)
    - [session](#session)
    - [Additional Methods](#additional-methods)    
 - [Events](#events)

    - [Additional Events](#additional-events)
 - [Provider Interfaces](#provider-interfaces)
    - [SessionProvider](#sessionprovider)
 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [Token](#token)
    - [Expiry](#expiry)
    - [Session](#session)
    - [ProviderResponse](#providerresponse)

<span></span>

## Usage
To use the Account module, you can import it into your project from the Firebolt SDK:

```javascript
import { Account } from '@firebolt-js/manage-sdk'
```


## Methods
### listen

Listen for events from this module.

```typescript
function listen(event?: string): Promise<boolean>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |




---

### once

Listen for only one occurance of an event from this module. The callback will be cleared after one event.

```typescript
function once(event?: string): Promise<boolean>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |




---

### provide

Register to provide a capability from this module.

See [Provider Interfaces](#provider-interfaces), for more info.

```typescript
function provide(provider: object | class): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `provider` | `object | class` | true | An Object or Class that implements all of the provider interface methods.  |


Promise resolution:

```javascript
void
```



---

### session

Used by a distributor to push Session token to firebolt.

```typescript
function session(token?: string, expiresIn?: number): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `token` | `string` | false |   |
| `expiresIn` | `number` | false |  <br/>minumum: 1 |


Promise resolution:

```javascript
void
```

**Examples**

Default Example

JavaScript:

```javascript
import { Account } from '@firebolt-js/manage-sdk'

Account.session("RmlyZWJvbHQgTWFuYWdlIFNESyBSb2NrcyEhIQ==", 84000)
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
  "method": "account.session",
  "params": {
    "token": "RmlyZWJvbHQgTWFuYWdlIFNESyBSb2NrcyEhIQ==",
    "expiresIn": 84000
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



### Additional methods
The following methods are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Parameters | Documentation |
|------------|-----|------------|---------------|
### sessionFocus

Internal API for Session Provider to request focus for UX purposes.




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "account.sessionFocus",
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

### sessionResponse

Internal API for Session Provider to send back response.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `response` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "account.sessionResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": {
        "token": "RmlyZWJvbHQgTWFuYWdlIFNESyBSb2NrcyEhIQ==",
        "expiresIn": 84000
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
  "result": null
}
```

</details>




---

### sessionError

Internal API for Session Provider to send back error.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `error` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example 1



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "account.sessionError",
  "params": {
    "error": {
      "correlationId": "123",
      "result": {
        "code": 1,
        "message": "Error"
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
  "result": null
}
```

</details>




---





## Events



### Additional events
The following events are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Payload | Documentation |
|------------|-----|---------|---------------|
### onRequestSession

Registers as a provider for when device needs a session



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

The request to get a new session

| Field | Type | Description |
| ----- | ---- | ----------- |
| `parameters` | `void` |  |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "account.onRequestSession",
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
    "correlationId": "abc",
    "parameters": null
  }
}
```

</details>




---






## Provider Interfaces
Providers are interfaces that your app can implement in order to provide certain capabilties back to the platform.

To register a provider, use the [`provide()`](#provide) method.

Every provider interface method has the following signature:

```typescript
(parameters: object | void, session: ProviderSession) => {}
```

`ProviderSession` has the following interface:

```typescript

interface ProviderSession {
    correlationId(): string        // Returns the correlation id of the current provider session
}


interface FocusableProviderSession extends ProviderSession {
    focus(): Promise<void>         // Requests that the provider app be moved into focus to prevent a user experience
}

```

### SessionProvider
The provider interface for the `xrn:firebolt:capability:token:session` capability.

```typescript
interface SessionProvider {
	session(parameters?: void, session?: FocusableProviderSession): Promise<object>
}

```

Usage:

```typescript
Account.provide('xrn:firebolt:capability:token:session', provider: SessionProvider | object)
```

### session

Registers as a provider for when device needs a session



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | `void` | false |   |
| `session` | `FocusableProviderSession` | false |   |


Promise resolution:

| Field | Type | Description |
| ----- | ---- | ----------- |
| `token` | `string` | Encoded token provided by the Distributor for Device Authentication. |
| `expiresIn` | `number` | Number of secs before the token expires |


**Examples**

undefined



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "account.session",
  "params": {
    "parameters": null,
    "session": {
      "correlationId": "abc"
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
    "token": "RmlyZWJvbHQgTWFuYWdlIFNESyBSb2NrcyEhIQ==",
    "expiresIn": 84000
  }
}
```

</details>




---



#### Examples

**Register your app to provide the `xrn:firebolt:capability:token:session` capability.**

```javascript
import { Account } from '@firebolt-js/manage-sdk'

class MySessionProvider {

    async session(parameters, session) {
        return await Promise.resolve({
            "token": "RmlyZWJvbHQgTWFuYWdlIFNESyBSb2NrcyEhIQ==",
            "expiresIn": 84000
        })
    }

}

Account.provide('xrn:firebolt:capability:token:session', new MySessionProvider())
```

<details>
    <summary>JSON-RPC</summary>

**Register to recieve each provider API**

Request:

```json

{
    "id": 1,
    "method": "account.onRequestSession",
    "params": {
        "listen": true
    }
}

```

Response:

```json

{
    "id": 1,
    "result": {
        "listening": true,
        "event": "Account.onRequestSession"
    }            
 
}

```



**Asynchronous event to initiate session()**

Event Response:

```json
{
    "id": 1,
    "result": {
        "correlationId": "abc",
        "parameters": null
    }
}
```

**App initiated response to event**

Request:

```json
{
    "id": 2,
    "method": "account.sessionResponse",
    "params": {
        "correlationId": "abc",
        "result": {
            "token": "RmlyZWJvbHQgTWFuYWdlIFNESyBSb2NrcyEhIQ==",
            "expiresIn": 84000
        }
    }
}
```

Response:

```json
{
    "id": 2,
    "result": true
}
```




</details>





## Schemas

### ListenResponse


```typescript
type ListenResponse = {
  event: string
  listening: boolean
}
```



---

### Token


Encoded token provided by the Distributor for Device Authentication.

```typescript
type Token = string
```



---

### Expiry


Number of secs before the token expires

```typescript
type Expiry = number
```



---

### Session


Session Token from the distributor.

```typescript
type Session = {
  token?: string      // Encoded token provided by the Distributor for Device Authentication.
  expiresIn?: number  // Number of secs before the token expires
}
```



---

### ProviderResponse


```typescript
type ProviderResponse = {
  correlationId: string    // The id that was passed in to the event that triggered a provider method to be called

}
```



---


