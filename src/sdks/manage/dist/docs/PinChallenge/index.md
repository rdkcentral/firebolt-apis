Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [pinchallenge.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/pinchallenge.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [listen](#listen)
    - [once](#once)
    - [provide](#provide)
    - [Additional Methods](#additional-methods)    
 - [Events](#events)

    - [Additional Events](#additional-events)
 - [Provider Interfaces](#provider-interfaces)
    - [ChallengeProvider](#challengeprovider)
 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [ProviderResponse](#providerresponse)
    - [ChallengeRequestor](#challengerequestor)
    - [ProviderRequest](#providerrequest)
    - [PinChallenge](#pinchallenge)
    - [PinChallengeProviderRequest](#pinchallengeproviderrequest)
    - [ResultReason](#resultreason)
    - [PinChallengeResult](#pinchallengeresult)

<span></span>

## Usage
To use the PinChallenge module, you can import it into your project from the Firebolt SDK:

```javascript
import { PinChallenge } from '@firebolt-js/manage-sdk'
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



### Additional methods
The following methods are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Parameters | Documentation |
|------------|-----|------------|---------------|
### challengeFocus

Internal API for Challenge Provider to request focus for UX purposes.




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
  "method": "pinchallenge.challengeFocus",
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

### challengeResponse

Internal API for Challenge Provider to send back response.



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `response` | [`ProviderResponse`](#providerresponse) | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example #1



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "pinchallenge.challengeResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": {
        "granted": true,
        "reason": "correctPin"
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

<details>
    <summary>More examples...</summary>
Example #2



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "pinchallenge.challengeResponse",
  "params": {
    "response": {
      "correlationId": "123",
      "result": {
        "granted": false,
        "reason": "cancelled"
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

</details>



---

### challengeError

Internal API for Challenge Provider to send back error.



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
  "method": "pinchallenge.challengeError",
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
### onRequestChallenge

Registers as a provider for when the user should be challenged in order to confirm access to a capability through a pin prompt



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`PinChallengeProviderRequest`](#pinchallengeproviderrequest) | The request to challenge the user |


**Examples**

Default Example



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "pinchallenge.onRequestChallenge",
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
    "parameters": {
      "capability": "xrn:firebolt:capability:commerce::purchase",
      "requestor": {
        "id": "ReferenceApp",
        "name": "Firebolt Reference App"
      },
      "pinSpace": "purchase"
    }
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

### ChallengeProvider
The provider interface for the `xrn:firebolt:capability:usergrant:pinchallenge` capability.

```typescript
interface ChallengeProvider {
	challenge(parameters?: PinChallenge, session?: FocusableProviderSession): Promise<PinChallengeResult>
}

```

Usage:

```typescript
PinChallenge.provide('xrn:firebolt:capability:usergrant:pinchallenge', provider: ChallengeProvider | object)
```

### challenge

Registers as a provider for when the user should be challenged in order to confirm access to a capability through a pin prompt



Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `parameters` | [`PinChallenge`](#pinchallenge) | false |   |
| `session` | `FocusableProviderSession` | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`PinChallengeResult`](#pinchallengeresult) |  |


**Examples**

undefined



<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "pinchallenge.challenge",
  "params": {
    "parameters": {
      "capability": "xrn:firebolt:capability:commerce::purchase",
      "requestor": {
        "id": "ReferenceApp",
        "name": "Firebolt Reference App"
      },
      "pinSpace": "purchase"
    },
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
    "granted": true,
    "reason": "correctPin"
  }
}
```

</details>




---



#### Examples

**Register your app to provide the `xrn:firebolt:capability:usergrant:pinchallenge` capability.**

```javascript
import { PinChallenge } from '@firebolt-js/manage-sdk'

class MyChallengeProvider {

    async challenge(parameters, session) {
        return await Promise.resolve({
            "granted": true,
            "reason": "correctPin"
        })
    }

}

PinChallenge.provide('xrn:firebolt:capability:usergrant:pinchallenge', new MyChallengeProvider())
```

<details>
    <summary>JSON-RPC</summary>

**Register to recieve each provider API**

Request:

```json

{
    "id": 1,
    "method": "pinchallenge.onRequestChallenge",
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
        "event": "PinChallenge.onRequestChallenge"
    }            
 
}

```



**Asynchronous event to initiate challenge()**

Event Response:

```json
{
    "id": 1,
    "result": {
        "correlationId": "abc",
        "parameters": {
            "capability": "xrn:firebolt:capability:commerce::purchase",
            "requestor": {
                "id": "ReferenceApp",
                "name": "Firebolt Reference App"
            },
            "pinSpace": "purchase"
        }
    }
}
```

**App initiated response to event**

Request:

```json
{
    "id": 2,
    "method": "pinchallenge.challengeResponse",
    "params": {
        "correlationId": "abc",
        "result": {
            "granted": true,
            "reason": "correctPin"
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

### ProviderResponse


```typescript
type ProviderResponse = {
  correlationId: string    // The id that was passed in to the event that triggered a provider method to be called

}
```



---

### ChallengeRequestor


```typescript
type ChallengeRequestor = {
  id: string                 // The id of the app that requested the challenge
  name: string               // The name of the app that requested the challenge
}
```



---

### ProviderRequest


```typescript
type ProviderRequest = {
  correlationId: string   // The id that was passed in to the event that triggered a provider method to be called
  parameters?: object     // The result of the provider response.
}
```



---

### PinChallenge


```typescript
type PinChallenge = {
  pinSpace: 'purchase' | 'content'  // The pin space that this challenge is for
  capability?: string               // The capability that is gated by a pin challenge
  requestor: ChallengeRequestor
}
```



---

### PinChallengeProviderRequest


```typescript
type PinChallengeProviderRequest = {
  correlationId: string               // The id that was passed in to the event that triggered a provider method to be called
  parameters: PinChallenge
}
```



---

### ResultReason


The reason for the result of challenging the user

```typescript
type ResultReason = 'noPinRequired' | 'noPinRequiredWindow' | 'exceededPinFailures' | 'correctPin' | 'cancelled'
```



---

### PinChallengeResult


```typescript
type PinChallengeResult = {
  granted: boolean           // Whether the user succeeded in the pin challenge
  reason: ResultReason       // The reason for the result of challenging the user
}
```



---


