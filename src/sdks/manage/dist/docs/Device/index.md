Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [device.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/device.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [developerMode](#developermode)
    - [listen](#listen)
    - [name](#name)
    - [once](#once)
    - [provision](#provision)
    - [Additional Methods](#additional-methods)    
 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [ListenResponse](#listenresponse)

<span></span>

## Usage
To use the Device module, you can import it into your project from the Firebolt SDK:

```javascript
import { Device } from '@firebolt-js/manage-sdk'
```


## Methods
### developerMode
Whether or not developer mode is enabled.



To get the value of `developerMode` call the method like this:


```typescript
function developerMode(): Promise<boolean>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `boolean` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.developerMode()
    .then(developerMode => {
        console.log(developerMode)
    })
```
Value of `developerMode`:

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
  "method": "device.developerMode",
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





To set the value of `developerMode` call the method like this:


```typescript
function developerMode(value: boolean): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Default Example


JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.developerMode(true)
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.developerMode",
  "params": {
    "value": true
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





To subscribe to notifications when the value changes, call the method like this:


```typescript
function developerMode ( subscriber: (developerMode) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `developerMode` | `boolean` | Yes | undefined |

**Examples**

Default Example


JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.developerMode( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
})
```

value of `value`:

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
  "method": "device.developerMode",
  "params": {}
}
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
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": true
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

### name
The human readable name of the device



To get the value of `name` call the method like this:


```typescript
function name(): Promise<string>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device friendly-name |


**Examples**

Example value for device name

JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.name()
    .then(value => {
        console.log(value)
    })
```
Value of `value`:

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
  "method": "device.name",
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





To set the value of `name` call the method like this:


```typescript
function name(value: string): Promise<null>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device friendly-name  |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Example value for device name


JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.name("Living Room")
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.name",
  "params": {
    "value": "Living Room"
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





To subscribe to notifications when the value changes, call the method like this:


```typescript
function name ( subscriber: (value) => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | Yes | the device friendly-name |

**Examples**

Example value for device name


JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.name( (value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
})
```

value of `value`:

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
  "method": "device.name",
  "params": {}
}
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
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Living Room"
}
```

</details>



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

### provision

Used by a distributor to push provision info to firebolt.

```typescript
function provision(accountId: string, deviceId: string, distributorId?: string): Promise<void>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `accountId` | `string` | true | The id of the account that is device is attached to in the back office.  |
| `deviceId` | `string` | true | The id of the device in the back office.  |
| `distributorId` | `string` | false | The id of the distributor in the back office.  |


Promise resolution:

```javascript
void
```

**Examples**

Default Example

JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.provision("12345678910", "987654321111", null)
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
  "method": "device.provision",
  "params": {
    "accountId": "12345678910",
    "deviceId": "987654321111"
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
With distributor id

JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.provision("12345678910", "987654321111", "global_partner")
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
  "method": "device.provision",
  "params": {
    "accountId": "12345678910",
    "deviceId": "987654321111",
    "distributorId": "global_partner"
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



### Additional methods
The following methods are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Parameters | Documentation |
|------------|-----|------------|---------------|
### name

The human readable name of the device

```typescript
function name(value: string): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | true | the device friendly-name  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Example value for device name

JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.name("Living Room")
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
  "method": "device.name",
  "params": {
    "value": "Living Room"
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

### developerMode

Whether or not developer mode is enabled.

```typescript
function developerMode(value: boolean): Promise<null>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `null` |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.developerMode(true)
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
  "method": "device.developerMode",
  "params": {
    "value": true
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

### onDeviceNameChanged

This API is **deprecated** since version 0.6.0. Use `Device.name()` instead.

Get the human readable name of the device

```typescript
function onDeviceNameChanged(listen: boolean): Promise<ListenResponse>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `listen` | `boolean` | true |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the device friendly-name |


**Examples**

Getting the device name

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.listen('deviceNameChanged', value => {
  console.log(value)
})
```
Value of `value`:

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
  "method": "device.onDeviceNameChanged",
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
  "result": "Living Room"
}
```

</details>




---




### Additional events
The following events are documented as part of a related set of method APIs.

For more information, follow the links under the "Documentation" column.

| JavaScript | RPC | Payload | Documentation |
|------------|-----|---------|---------------|
### name

The human readable name of the device

```typescript
function name(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the device friendly-name |


**Examples**

Example value for device name

JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.name()
    .then(value => {
        console.log(value)
    })
```
Value of `value`:

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
  "method": "device.name",
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

### developerMode

Whether or not developer mode is enabled.

```typescript
function developerMode(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) |  |


**Examples**

Default Example

JavaScript:

```javascript
import { Device } from '@firebolt-js/manage-sdk'

Device.developerMode()
    .then(developerMode => {
        console.log(developerMode)
    })
```
Value of `developerMode`:

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
  "method": "device.developerMode",
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








## Schemas

### ListenResponse


```typescript
type ListenResponse = {
  event: string
  listening: boolean
}
```



---


