Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [secondscreen.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/secondscreen.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [device](#device)
    - [friendlyName](#friendlyname)
    - [listen](#listen)
    - [once](#once)
    - [protocols](#protocols)

 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [BooleanMap](#booleanmap)
    - [SecondScreenEvent](#secondscreenevent)

<span></span>

## Usage
To use the SecondScreen module, you can import it into your project from the Firebolt SDK:

```javascript
import { SecondScreen } from '@firebolt-js/sdk'
```


## Methods
### device

Get the broadcasted id for the device

```typescript
function device(type?: string): Promise<string>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `type` | `string` | false | The type of second screen protocol, e.g. "dial"  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device id |


**Examples**

Default Example

JavaScript:

```javascript
import { SecondScreen } from '@firebolt-js/sdk'

SecondScreen.device(null)
    .then(deviceId => {
        console.log(deviceId)
    })
```
Value of `deviceId`:

```javascript
"device-id"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "secondscreen.device",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "device-id"
}
```

</details>




---

### friendlyName
Get the broadcasted friendly name for the device



To get the value of `friendlyName` call the method like this:


```typescript
function friendlyName(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device friendly-name |


**Examples**

Default Example

JavaScript:

```javascript
import { SecondScreen } from '@firebolt-js/sdk'

SecondScreen.friendlyName()
    .then(friendlyName => {
        console.log(friendlyName)
    })
```
Value of `friendlyName`:

```javascript
"Living Room"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "secondscreen.friendlyName",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Living Room"
}
```

</details>





To set the value of `friendlyName` call the method like this:


```typescript
function friendlyName(): Promise<ListenResponse | string>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { SecondScreen } from '@firebolt-js/sdk'

SecondScreen.friendlyName(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "secondscreen.friendlyName",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Living Room"
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function friendlyName (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with SecondScreen.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { SecondScreen } from '@firebolt-js/sdk'

SecondScreen.friendlyName((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ SecondScreen.clear(listenerId)
})
```

value of `value`:

```javascript
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
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
```

</details>


---

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

### protocols

Get the supported second screen discovery protocols

```typescript
function protocols(): Promise<object>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | the supported protocols |


**Examples**

Default Example

JavaScript:

```javascript
import { SecondScreen } from '@firebolt-js/sdk'

SecondScreen.protocols()
    .then(protocols => {
        console.log(protocols)
    })
```
Value of `protocols`:

```javascript
{
  "dial1.7": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "secondscreen.protocols",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "dial1.7": true
  }
}
```

</details>




---






## Events

### onCloseRequest

Listen to the closeRequest event

```typescript
function onCloseRequest(listen: boolean): Promise<ListenResponse>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { SecondScreen } from '@firebolt-js/sdk'

SecondScreen.listen('closeRequest', closeRequestEvent => {
  console.log(closeRequestEvent)
})
```
Value of `closeRequestEvent`:

```javascript
{
  "type": "dial",
  "version": "1.7"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "secondscreen.onCloseRequest",
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
    "type": "dial",
    "version": "1.7"
  }
}
```

</details>




---

### onLaunchRequest

Listen to the launchRequest event

```typescript
function onLaunchRequest(listen: boolean): Promise<ListenResponse>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | Dispatched when a second screen device on the local network has requested this app to be launched |


**Examples**

Default Example

JavaScript:

```javascript
import { SecondScreen } from '@firebolt-js/sdk'

SecondScreen.listen('launchRequest', launchRequestEvent => {
  console.log(launchRequestEvent)
})
```
Value of `launchRequestEvent`:

```javascript
{
  "type": "dial",
  "version": "1.7",
  "data": "{\"code\":\"AQDPQZiQcb3KQ7gY7yy5tHTMbbkGHR9Zjp-KL53H3eKBZIeAt7O9UKYPu6B21l2UZVmIqkFXDXBmXvK4g2e3EgZtjMNmKPsTltgnRl95DImtOXjSpWtTjSaOkW4w1kZKUTwLKdwVWTzBVH8ERHorvLU6vCGOVHxXt65LNwdl5HKRweShVC1V9QsyvRnQS61ov0UclmrH_xZML2Bt-Q-rZFjey5MjwupIb4x4f53XUJMhjHpDHoIUKrjpdPDQvK2a\",\"friendlyName\":\"Operator_TX061AEI\",\"UDN\":\"608fef11-2800-482a-962b-23a6690c93c1\"}"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "secondscreen.onLaunchRequest",
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
    "type": "dial",
    "version": "1.7",
    "data": "{\"code\":\"AQDPQZiQcb3KQ7gY7yy5tHTMbbkGHR9Zjp-KL53H3eKBZIeAt7O9UKYPu6B21l2UZVmIqkFXDXBmXvK4g2e3EgZtjMNmKPsTltgnRl95DImtOXjSpWtTjSaOkW4w1kZKUTwLKdwVWTzBVH8ERHorvLU6vCGOVHxXt65LNwdl5HKRweShVC1V9QsyvRnQS61ov0UclmrH_xZML2Bt-Q-rZFjey5MjwupIb4x4f53XUJMhjHpDHoIUKrjpdPDQvK2a\",\"friendlyName\":\"Operator_TX061AEI\",\"UDN\":\"608fef11-2800-482a-962b-23a6690c93c1\"}"
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
### friendlyName

Get the broadcasted friendly name for the device

```typescript
function friendlyName(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the device friendly-name |


**Examples**

Default Example

JavaScript:

```javascript
import { SecondScreen } from '@firebolt-js/sdk'

SecondScreen.friendlyName()
    .then(friendlyName => {
        console.log(friendlyName)
    })
```
Value of `friendlyName`:

```javascript
"Living Room"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "secondscreen.friendlyName",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Living Room"
}
```

</details>




---








## Schemas

### ListenResponse


```typescript
type ListenResponse = {
  event: string
  listening: boolean
}
```



---

### BooleanMap


```typescript
type BooleanMap = {
  [property: string]: boolean
}
```



---

### SecondScreenEvent


An a message notification from a second screen device

```typescript
type SecondScreenEvent = {
  type: 'dial'
  version?: string
  data?: string
}
```



---


