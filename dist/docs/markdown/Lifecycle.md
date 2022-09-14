---
title: Lifecycle
---

# Lifecycle Module
---
Version 0.8.0

## Overview
 Methods and events for responding to lifecycle changes in your app

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
    - [LifecycleEvent](#lifecycleevent)

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
| `reason` | [`CloseReason`](../schemas/lifecycle#/definitions/closereason) | true | The reason the app is requesting to be closed  |


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

To listen to a specific event pass the event name as the first parameter:


```typescript
Lifecycle.listen(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Lifecycle.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Lifecycle.listen((event: string, data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. The event data depends on which event is firing, see [Events](#events). |


Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event that has occured listen for, see [Events](#events). |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |


Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Lifecycle.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

---

### once
Listen for only one occurance of an event from this module. The callback will be cleared after one event.

To listen to a specific event pass the event name as the first parameter:


```typescript
Lifecycle.once(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Lifecycle.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Lifecycle.once((event: string, data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. The event data depends on which event is firing, see [Events](#events). |


Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event that has occured listen for, see [Events](#events). |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |


Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Lifecycle.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

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
| [`LifecycleState`](../schemas/lifecycle#/definitions/lifecyclestate) | The application lifecycle state |


**Examples**

Default Example

JavaScript:

```javascript
import { Lifecycle } from ''

const state = Lifecycle.state()
console.log(state)
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

### background
Listen to the background event


See also: [listen()](#listen), [once()](#listen), [clear()](#listen).

Event value:

| Type | Description |
| ---- | ----------- |
| [`LifecycleEvent`](#lifecycleevent) | A an object describing the previous and current states |


**Examples**

Default Example:

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('background', value => {
  console.log(value)
})
```
Value of `value`

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

### foreground
Listen to the foreground event


See also: [listen()](#listen), [once()](#listen), [clear()](#listen).

Event value:

| Type | Description |
| ---- | ----------- |
| [`LifecycleEvent`](#lifecycleevent) | A an object describing the previous and current states |


**Examples**

Default Example:

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('foreground', value => {
  console.log(value)
})
```
Value of `value`

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
Move to foreground via remote branded buton:

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('foreground', value => {
  console.log(value)
})
```
Value of `value`

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

### inactive
Listen to the inactive event


See also: [listen()](#listen), [once()](#listen), [clear()](#listen).

Event value:

| Type | Description |
| ---- | ----------- |
| [`LifecycleEvent`](#lifecycleevent) | A an object describing the previous and current states |


**Examples**

Default Example:

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('inactive', value => {
  console.log(value)
})
```
Value of `value`

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

### suspended
Listen to the suspended event


See also: [listen()](#listen), [once()](#listen), [clear()](#listen).

Event value:

| Type | Description |
| ---- | ----------- |
| [`LifecycleEvent`](#lifecycleevent) | A an object describing the previous and current states |


**Examples**

Default Example:

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('suspended', value => {
  console.log(value)
})
```
Value of `value`

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

### unloading
Listen to the unloading event


See also: [listen()](#listen), [once()](#listen), [clear()](#listen).

Event value:

| Type | Description |
| ---- | ----------- |
| [`LifecycleEvent`](#lifecycleevent) | A an object describing the previous and current states |


**Examples**

Default Example:

JavaScript:

```javascript
import { Lifecycle } from '@firebolt-js/sdk'

Lifecycle.listen('unloading', value => {
  console.log(value)
})
```
Value of `value`

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

### LifecycleEvent


A an object describing the previous and current states

```typescript
type LifecycleEvent = {
  state: LifecycleState        // The application lifecycle state
  previous: LifecycleState     // The application lifecycle state
  source?: 'voice' | 'remote'  // The source of the lifecycle change.
}
```

See also: 

 - [LifecycleState](../schemas/lifecycle#lifecyclestate)

---


