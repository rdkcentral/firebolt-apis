---
title: Device
---

# Device Module
---
Version 0.8.0

## Overview
 A module for querying about the device and it's capabilities.

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [device.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/device.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [audio](#audio)
    - [distributor](#distributor)
    - [hdcp](#hdcp)
    - [hdr](#hdr)
    - [id](#id)
    - [listen](#listen)
    - [make](#make)
    - [model](#model)
    - [name](#name)
    - [network](#network)
    - [once](#once)
    - [platform](#platform)
    - [screenResolution](#screenresolution)
    - [sku](#sku)
    - [type](#type)
    - [uid](#uid)
    - [version](#version)
    - [videoResolution](#videoresolution)

 - [Events](#events)

    - [Additional Events](#additional-events)

 - [Schemas](#schemas)
    - [Resolution](#resolution)
    - [NetworkType](#networktype)
    - [NetworkState](#networkstate)
    - [AudioProfiles](#audioprofiles)

<span></span>

## Usage
To use the Device module, you can import it into your project from the Firebolt SDK:

```javascript
import { Device } from '@firebolt-js/sdk'
```


## Methods
### audio
Get the supported audio profiles



To get the value, call the method with no parameters:


```typescript
function audio(): Promise<AudioProfiles>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`AudioProfiles`](#audioprofiles) | the supported audio profiles |


**Examples**

Getting the supported audio profiles

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.audio()
    .then(supportedAudioProfiles => {
        console.log(supportedAudioProfiles)
    })
```
Value of `supportedAudioProfiles`:

```javascript
{
  "stereo": true,
  "dolbyDigital5.1": true,
  "dolbyDigital5.1+": true,
  "dolbyAtmos": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.audio",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "stereo": true,
    "dolbyDigital5.1": true,
    "dolbyDigital5.1+": true,
    "dolbyAtmos": true
  }
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function audio(subscriber: (supportedAudioProfiles: AudioProfiles) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for audio changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `supportedAudioProfiles` | [`AudioProfiles`](#audioprofiles) | Yes | the supported audio profiles  |

**Examples**

Getting the supported audio profiles


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.audio(supportedAudioProfiles => {
  // property value was changed
  console.log(supportedAudioProfiles)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
})
```

value of `supportedAudioProfiles`:

```javascript
{
  "stereo": true,
  "dolbyDigital5.1": true,
  "dolbyDigital5.1+": true,
  "dolbyAtmos": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.onAudioChanged",
  "params": {
    "listen": true
  }
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
  "result": {
    "stereo": true,
    "dolbyDigital5.1": true,
    "dolbyDigital5.1+": true,
    "dolbyAtmos": true
  }
}
```

</details>



---


### distributor
Get the distributor ID for this device



To get the value, call the method with no parameters:


```typescript
function distributor(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the distributor ID |


**Examples**

Getting the distributor ID

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.distributor()
    .then(distributorId => {
        console.log(distributorId)
    })
```
Value of `distributorId`:

```javascript
"Company"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.distributor",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Company"
}
```

</details>








### hdcp
Get the supported HDCP profiles



To get the value, call the method with no parameters:


```typescript
function hdcp(): Promise<BooleanMap>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`BooleanMap`](../schemas/types#/definitions/booleanmap) | the supported HDCP profiles |


**Examples**

Getting the supported HDCP profiles

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.hdcp()
    .then(supportedHdcpProfiles => {
        console.log(supportedHdcpProfiles)
    })
```
Value of `supportedHdcpProfiles`:

```javascript
{
  "hdcp1.4": true,
  "hdcp2.2": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.hdcp",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "hdcp1.4": true,
    "hdcp2.2": true
  }
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function hdcp(subscriber: (supportedHdcpProfiles: BooleanMap) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for hdcp changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `supportedHdcpProfiles` | [`BooleanMap`](../schemas/types#/definitions/booleanmap) | Yes | the supported HDCP profiles  |

**Examples**

Getting the supported HDCP profiles


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.hdcp(supportedHdcpProfiles => {
  // property value was changed
  console.log(supportedHdcpProfiles)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
})
```

value of `supportedHdcpProfiles`:

```javascript
{
  "hdcp1.4": true,
  "hdcp2.2": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.onHdcpChanged",
  "params": {
    "listen": true
  }
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
  "result": {
    "hdcp1.4": true,
    "hdcp2.2": true
  }
}
```

</details>



---


### hdr
Get the supported HDR profiles



To get the value, call the method with no parameters:


```typescript
function hdr(): Promise<BooleanMap>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`BooleanMap`](../schemas/types#/definitions/booleanmap) | the supported HDR profiles |


**Examples**

Getting the supported HDR profiles

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.hdr()
    .then(supportedHdrProfiles => {
        console.log(supportedHdrProfiles)
    })
```
Value of `supportedHdrProfiles`:

```javascript
{
  "hdr10": true,
  "hdr10Plus": true,
  "dolbyVision": true,
  "hlg": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.hdr",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "hdr10": true,
    "hdr10Plus": true,
    "dolbyVision": true,
    "hlg": true
  }
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function hdr(subscriber: (supportedHdrProfiles: BooleanMap) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for hdr changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `supportedHdrProfiles` | [`BooleanMap`](../schemas/types#/definitions/booleanmap) | Yes | the supported HDR profiles  |

**Examples**

Getting the supported HDR profiles


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.hdr(supportedHdrProfiles => {
  // property value was changed
  console.log(supportedHdrProfiles)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
})
```

value of `supportedHdrProfiles`:

```javascript
{
  "hdr10": true,
  "hdr10Plus": true,
  "dolbyVision": true,
  "hlg": true
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.onHdrChanged",
  "params": {
    "listen": true
  }
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
  "result": {
    "hdr10": true,
    "hdr10Plus": true,
    "dolbyVision": true,
    "hlg": true
  }
}
```

</details>



---


### id
Get the platform back-office device identifier



To get the value, call the method with no parameters:


```typescript
function id(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the id |


**Examples**

Default Example

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.id()
    .then(id => {
        console.log(id)
    })
```
Value of `id`:

```javascript
"123"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.id",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "123"
}
```

</details>








### listen
Listen for events from this module.

To listen to a specific event pass the event name as the first parameter:


```typescript
Device.listen(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Device.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Device.listen((event: string, data: any) => void): Promise<number>
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
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Device.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

---

### make
Get the device make



To get the value, call the method with no parameters:


```typescript
function make(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device make |


**Examples**

Getting the device make

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.make()
    .then(make => {
        console.log(make)
    })
```
Value of `make`:

```javascript
"Arris"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.make",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "Arris"
}
```

</details>








### model
Get the device model



To get the value, call the method with no parameters:


```typescript
function model(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device model |


**Examples**

Getting the device model

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.model()
    .then(model => {
        console.log(model)
    })
```
Value of `model`:

```javascript
"xi6"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.model",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "xi6"
}
```

</details>








### name
The human readable name of the device



To get the value, call the method with no parameters:


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
import { Device } from '@firebolt-js/sdk'

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







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function name(subscriber: (value: string) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for name changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `value` | `string` | Yes | the device friendly-name  |

**Examples**

Example value for device name


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.name(value => {
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
  "method": "device.onNameChanged",
  "params": {
    "listen": true
  }
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


### network
Get the current network status and type



To get the value, call the method with no parameters:


```typescript
function network(): Promise<object>
```


Promise resolution:

the status and type

| Field | Type | Description |
| ----- | ---- | ----------- |
| `state` | [`NetworkState`](#networkstate) |  |
| `type` | [`NetworkType`](#networktype) |  |


**Examples**

Getting the network info

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.network()
    .then(networkInfo => {
        console.log(networkInfo)
    })
```
Value of `networkInfo`:

```javascript
{
  "state": "connected",
  "type": "wifi"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.network",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "state": "connected",
    "type": "wifi"
  }
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function network(subscriber: (networkInfo: object) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for network changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `networkInfo` | `object` | Yes | the status and type  |

**Examples**

Getting the network info


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.network(networkInfo => {
  // property value was changed
  console.log(networkInfo)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
})
```

value of `networkInfo`:

```javascript
{
  "state": "connected",
  "type": "wifi"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.onNetworkChanged",
  "params": {
    "listen": true
  }
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
  "result": {
    "state": "connected",
    "type": "wifi"
  }
}
```

</details>



---


### once
Listen for only one occurance of an event from this module. The callback will be cleared after one event.

To listen to a specific event pass the event name as the first parameter:


```typescript
Device.once(event: string, (data: any) => void): Promise<number>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `event` | `string` | Yes | The event to listen for, see [Events](#events). |
| *callback* | `function` | Yes | A function that will be invoked when the event occurs. |

Promise resolution:

| Type | Description |
|------|-------------|
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Device.clear(id)` |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `data` | `any` | Yes | The event data, which depends on which event is firing, see [Events](#events). |

To listen to all events from this module  pass only a callback, without specifying an event name:


```typescript
Device.once((event: string, data: any) => void): Promise<number>
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
| `number` | Listener ID to clear the callback method and stop receiving the event, e.g. `Device.clear(id)` |

See [Listening for events](../../docs/listening-for-events/) for more information and examples.

---

### platform
Get the platform ID for this device



To get the value, call the method with no parameters:


```typescript
function platform(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the platform ID |


**Examples**

Getting the platform ID

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.platform()
    .then(platformId => {
        console.log(platformId)
    })
```
Value of `platformId`:

```javascript
"WPE"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.platform",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "WPE"
}
```

</details>








### screenResolution
Get the current screen resolution



To get the value, call the method with no parameters:


```typescript
function screenResolution(): Promise<[number, number]>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `[number, number]` | the resolution |


**Examples**

Getting the screen resolution

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.screenResolution()
    .then(screenResolution => {
        console.log(screenResolution)
    })
```
Value of `screenResolution`:

```javascript
[
  1920,
  1080
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.screenResolution",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    1920,
    1080
  ]
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function screenResolution(subscriber: (screenResolution: [number, number]) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for screenResolution changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `screenResolution` | `[number, number]` | Yes | the resolution  |

**Examples**

Getting the screen resolution


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.screenResolution(screenResolution => {
  // property value was changed
  console.log(screenResolution)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
})
```

value of `screenResolution`:

```javascript
[
  1920,
  1080
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.onScreenResolutionChanged",
  "params": {
    "listen": true
  }
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
  "result": [
    1920,
    1080
  ]
}
```

</details>



---


### sku
Get the device sku



To get the value, call the method with no parameters:


```typescript
function sku(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device sku |


**Examples**

Getting the device sku

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.sku()
    .then(sku => {
        console.log(sku)
    })
```
Value of `sku`:

```javascript
"AX061AEI"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.sku",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "AX061AEI"
}
```

</details>








### type
Get the device type



To get the value, call the method with no parameters:


```typescript
function type(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | the device type |


**Examples**

Getting the device type

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.type()
    .then(deviceType => {
        console.log(deviceType)
    })
```
Value of `deviceType`:

```javascript
"STB"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.type",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "STB"
}
```

</details>








### uid
Gets a unique id for the current app & device



To get the value, call the method with no parameters:


```typescript
function uid(): Promise<string>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `string` | a unique ID |


**Examples**

Getting the unique ID

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.uid()
    .then(uniqueId => {
        console.log(uniqueId)
    })
```
Value of `uniqueId`:

```javascript
"ee6723b8-7ab3-462c-8d93-dbf61227998e"
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.uid",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": "ee6723b8-7ab3-462c-8d93-dbf61227998e"
}
```

</details>








### version
Get the SDK, OS and other version info



To get the value, call the method with no parameters:


```typescript
function version(): Promise<object>
```


Promise resolution:

the versions

| Field | Type | Description |
| ----- | ---- | ----------- |
| `sdk` | [`SemanticVersion`](../schemas/types#/definitions/semanticversion) | The Firebolt SDK version |
| `api` | [`SemanticVersion`](../schemas/types#/definitions/semanticversion) | The lateset Firebolt API vresion supported by the curent device. |
| `firmware` | [`SemanticVersion`](../schemas/types#/definitions/semanticversion) | The device firmware version. |
| `os` | [`SemanticVersion`](../schemas/types#/definitions/semanticversion) | **Deprecated** Use `firmware`, instead. |
| `debug` | `string` | Detail version as a string, for debugging purposes |


**Examples**

Getting the os and sdk versions

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.version()
    .then(versions => {
        console.log(versions)
    })
```
Value of `versions`:

```javascript
{
  "sdk": {
    "major": 0,
    "minor": 8,
    "patch": 0,
    "readable": "Firebolt JS SDK v0.8.0"
  },
  "api": {
    "major": 0,
    "minor": 8,
    "patch": 0,
    "readable": "Firebolt API v0.8.0"
  },
  "firmware": {
    "major": 1,
    "minor": 2,
    "patch": 3,
    "readable": "Device Firmware v1.2.3"
  },
  "os": {
    "major": 0,
    "minor": 1,
    "patch": 0,
    "readable": "Firebolt OS v0.1.0"
  },
  "debug": "Non-parsable build info for error logging only."
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.version",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "sdk": {
      "major": 0,
      "minor": 8,
      "patch": 0,
      "readable": "Firebolt JS SDK v0.8.0"
    },
    "api": {
      "major": 0,
      "minor": 8,
      "patch": 0,
      "readable": "Firebolt API v0.8.0"
    },
    "firmware": {
      "major": 1,
      "minor": 2,
      "patch": 3,
      "readable": "Device Firmware v1.2.3"
    },
    "os": {
      "major": 0,
      "minor": 1,
      "patch": 0,
      "readable": "Firebolt OS v0.1.0"
    },
    "debug": "Non-parsable build info for error logging only."
  }
}
```

</details>








### videoResolution
Get the current video resolution



To get the value, call the method with no parameters:


```typescript
function videoResolution(): Promise<[number, number]>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| `[number, number]` | the resolution |


**Examples**

Getting the video resolution

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.videoResolution()
    .then(videoResolution => {
        console.log(videoResolution)
    })
```
Value of `videoResolution`:

```javascript
[
  1920,
  1080
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.videoResolution",
  "params": {}
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": [
    1920,
    1080
  ]
}
```

</details>







To subscribe to notifications when the value changes, pass a function as the only parameter:


```typescript
function videoResolution(subscriber: (videoResolution: [number, number]) => void): Promise<boolean>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `subscriber` | `Function` | Yes | A callback that gets invoked when the value for videoResolution changes |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `videoResolution` | `[number, number]` | Yes | the resolution  |

**Examples**

Getting the video resolution


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.videoResolution(videoResolution => {
  // property value was changed
  console.log(videoResolution)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
})
```

value of `videoResolution`:

```javascript
[
  1920,
  1080
]
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.onVideoResolutionChanged",
  "params": {
    "listen": true
  }
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
  "result": [
    1920,
    1080
  ]
}
```

</details>



---







## Events

### deviceNameChanged
This API is **deprecated** since version 0.6.0. Use `Device.name()` instead.

Get the human readable name of the device


See also: [listen()](#listen), [once()](#listen), [clear()](#listen).

Event value:

| Type | Description |
| ---- | ----------- |
| `string` | the device friendly-name |


**Examples**

Getting the device name:

JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.listen('deviceNameChanged', value => {
  console.log(value)
})
```
Value of `value`

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
| hdcpChanged | onHdcpChanged | [BooleanMap](../schemas/types#/definitions/booleanmap) | [hdcp](#hdcp) |
| hdrChanged | onHdrChanged | [BooleanMap](../schemas/types#/definitions/booleanmap) | [hdr](#hdr) |
| audioChanged | onAudioChanged | [AudioProfiles](#audioprofiles) | [audio](#audio) |
| screenResolutionChanged | onScreenResolutionChanged | [number, number] | [screenResolution](#screenresolution) |
| videoResolutionChanged | onVideoResolutionChanged | [number, number] | [videoResolution](#videoresolution) |
| nameChanged | onNameChanged | string | [name](#name) |
| networkChanged | onNetworkChanged | object | [network](#network) |







## Schemas

### Resolution


```typescript
type Resolution = [number, number]
```



---

### NetworkType


The type of network that is currently active

```typescript
type NetworkType = 'wifi' | 'ethernet' | 'hybrid'
```



---

### NetworkState


The type of network that is currently active

```typescript
type NetworkState = 'connected' | 'disconnected'
```



---

### AudioProfiles


```typescript
type AudioProfiles = {
  stereo: boolean
  "dolbyDigital5.1": boolean
  "dolbyDigital7.1": boolean
  "dolbyDigital5.1+": boolean
  "dolbyDigital7.1+": boolean
  dolbyAtmos: boolean
}
```

See also: 

 - [BooleanMap](../schemas/types#booleanmap)
 - [AudioProfile](../schemas/types#audioprofile)

---


