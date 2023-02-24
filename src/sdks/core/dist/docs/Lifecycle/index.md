Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [lifecycle.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/lifecycle.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [close](#close)
    - [finished](#finished)
    - [listen](#listen)
    - [once](#once)
    - [ready](#ready)
    - [state](#state)

 - [Events](#events)



 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)
    - [LifecycleEvent](#lifecycleevent)
    - [CloseReason](#closereason)
    - [LifecycleState](#lifecyclestate)

<span></span>

## Usage
To use the Lifecycle module, you can import it into your project from the Firebolt SDK:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'
```


## Methods
### close

Request that the platform move your app out of focus

```typescript
function close(reason: CloseReason): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `reason` | [`CloseReason`](#closereason) | true | The reason the app is requesting to be closed  |


Promise resolution:

```javascript
void
```

**Examples**

Close the app when the user presses back on the app home screen

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.close("remoteButton")
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
  "method": "lifecycle.close",
  "params": {
    "reason": "remoteButton"
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
Close the app when the user selects an exit menu item

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.close("userExit")
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
  "method": "lifecycle.close",
  "params": {
    "reason": "userExit"
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

### finished

Notify the platform that the app is done unloading

```typescript
function finished(): Promise<void>
```


Promise resolution:

```javascript
void
```

**Examples**

Default Example

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.finished()
    .then(results => {
        console.log(results)
    })
```
Value of `results`:

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
  "method": "lifecycle.finished",
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

### ready

Notify the platform that the app is ready

```typescript
function ready(): Promise<void>
```


Promise resolution:

```javascript
void
```

**Examples**

Let the platform know that your app is ready

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.ready()
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
  "method": "lifecycle.ready",
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

### state

Get the current state of the app. This function is **synchronous**.

```typescript
function state(): LifecycleState
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`LifecycleState`](#lifecyclestate) | The application lifecycle state |


**Examples**

Default Example

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.state()
    .then(state => {
        console.log(state)
    })
```
Value of `state`:

```javascript
"foreground"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.state",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "foreground"
}
```

</details>




---






## Events

### onBackground

Listen to the background event

```typescript
function onBackground(listen: boolean): Promise<ListenResponse>
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
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('background', value => {
  console.log(value)
})
```
Value of `value`:

```javascript
{
  "state": "background",
  "previous": "foreground"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onBackground",
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
    "state": "background",
    "previous": "foreground"
  }
}
```

</details>




---

### onForeground

Listen to the foreground event

```typescript
function onForeground(listen: boolean): Promise<ListenResponse>
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
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('foreground', value => {
  console.log(value)
})
```
Value of `value`:

```javascript
{
  "state": "foreground",
  "previous": "inactive"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onForeground",
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
    "state": "foreground",
    "previous": "inactive"
  }
}
```

</details>

<details>
    <summary>More examples...</summary>
Move to foreground via remote branded buton

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('foreground', value => {
  console.log(value)
})
```
Value of `value`:

```javascript
{
  "state": "foreground",
  "previous": "inactive",
  "source": "remote"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onForeground",
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
    "state": "foreground",
    "previous": "inactive",
    "source": "remote"
  }
}
```

</details>

</details>



---

### onInactive

Listen to the inactive event

```typescript
function onInactive(listen: boolean): Promise<ListenResponse>
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
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('inactive', value => {
  console.log(value)
})
```
Value of `value`:

```javascript
{
  "state": "inactive",
  "previous": "initializing"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onInactive",
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
    "state": "inactive",
    "previous": "initializing"
  }
}
```

</details>




---

### onSuspended

Listen to the suspended event

```typescript
function onSuspended(listen: boolean): Promise<ListenResponse>
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
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('suspended', value => {
  console.log(value)
})
```
Value of `value`:

```javascript
{
  "state": "suspended",
  "previous": "inactive"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onSuspended",
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
    "state": "suspended",
    "previous": "inactive"
  }
}
```

</details>




---

### onUnloading

Listen to the unloading event

```typescript
function onUnloading(listen: boolean): Promise<ListenResponse>
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
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('unloading', value => {
  console.log(value)
})
```
Value of `value`:

```javascript
{
  "state": "unloading",
  "previous": "inactive"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "lifecycle.onUnloading",
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
    "state": "unloading",
    "previous": "inactive"
  }
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

### LifecycleEvent


A an object describing the previous and current states

```typescript
type LifecycleEvent = {
  state: LifecycleState        // The application lifecycle state
  previous: LifecycleState     // The application lifecycle state
  source?: 'voice' | 'remote'  // The source of the lifecycle change.
}
```



---

### CloseReason


The application close reason

```typescript
type CloseReason = 'remoteButton' | 'userExit' | 'done' | 'error'
```



---

### LifecycleState


The application lifecycle state

```typescript
type LifecycleState = 'initializing' | 'inactive' | 'foreground' | 'background' | 'unloading' | 'suspended'
```



---


