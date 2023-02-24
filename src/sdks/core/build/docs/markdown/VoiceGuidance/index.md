Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [voiceguidance.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/voiceguidance.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [enabled](#enabled)
    - [listen](#listen)
    - [once](#once)
    - [speed](#speed)

 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [VoiceSpeed](#voicespeed)

<span></span>

## Usage
To use the VoiceGuidance module, you can import it into your project from the Firebolt SDK:

```javascript
import { VoiceGuidance } from '@firebolt-js/sdk'
```


## Methods
### enabled
Whether or not voice-guidance is enabled.



To get the value of `enabled` call the method like this:


```typescript
function enabled(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { VoiceGuidance } from '@firebolt-js/sdk'

VoiceGuidance.enabled()
    .then(enabled => {
        console.log(enabled)
    })
```
Value of `enabled`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "voiceguidance.enabled",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>





To set the value of `enabled` call the method like this:


```typescript
function enabled(): Promise<ListenResponse | boolean>
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
import { VoiceGuidance } from '@firebolt-js/sdk'

VoiceGuidance.enabled(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "voiceguidance.enabled",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function enabled (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with VoiceGuidance.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { VoiceGuidance } from '@firebolt-js/sdk'

VoiceGuidance.enabled((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ VoiceGuidance.clear(listenerId)
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

### speed
The speed at which voice guidance speech will be read back to the user.



To get the value of `speed` call the method like this:


```typescript
function speed(): Promise<VoiceSpeed>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`VoiceSpeed`](#voicespeed) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { VoiceGuidance } from '@firebolt-js/sdk'

VoiceGuidance.speed()
    .then(speed => {
        console.log(speed)
    })
```
Value of `speed`:

```javascript
1
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "voiceguidance.speed",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 1
}
```

</details>





To set the value of `speed` call the method like this:


```typescript
function speed(): Promise<ListenResponse | VoiceSpeed>
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
import { VoiceGuidance } from '@firebolt-js/sdk'

VoiceGuidance.speed(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "voiceguidance.speed",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 1
}
```

</details>




To subscribe to notifications when the value changes, call the method like this:


```typescript
function speed (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with VoiceGuidance.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { VoiceGuidance } from '@firebolt-js/sdk'

VoiceGuidance.speed((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ VoiceGuidance.clear(listenerId)
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






## Events



### Additional events
The following events are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Payload | Documentation |
|------------|-----|---------|---------------|
### enabled

Whether or not voice-guidance is enabled.

```typescript
function enabled(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { VoiceGuidance } from '@firebolt-js/sdk'

VoiceGuidance.enabled()
    .then(enabled => {
        console.log(enabled)
    })
```
Value of `enabled`:

```javascript
true
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "voiceguidance.enabled",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
}
```

</details>




---

### speed

The speed at which voice guidance speech will be read back to the user.

```typescript
function speed(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { VoiceGuidance } from '@firebolt-js/sdk'

VoiceGuidance.speed()
    .then(speed => {
        console.log(speed)
    })
```
Value of `speed`:

```javascript
1
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "voiceguidance.speed",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": 1
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

### VoiceSpeed


```typescript
type VoiceSpeed = number
```



---


