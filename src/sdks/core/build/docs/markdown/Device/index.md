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
    - [SemanticVersion](#semanticversion)
    - [ListenResponse](#listenresponse)
    - [Resolution](#resolution)
    - [NetworkType](#networktype)
    - [NetworkState](#networkstate)
    - [AudioProfiles](#audioprofiles)
    - [BooleanMap](#booleanmap)
    - [AudioProfile](#audioprofile)

<span></span>

## Usage
To use the Device module, you can import it into your project from the Firebolt SDK:

```javascript
import { Device } from '@firebolt-js/sdk'
```


## Methods
### audio
Get the supported audio profiles



To get the value of `audio` call the method like this:


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





To set the value of `audio` call the method like this:


```typescript
function audio(): Promise<ListenResponse | AudioProfiles>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Getting the supported audio profiles


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.audio(true)
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function audio (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.audio((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### distributor
Get the distributor ID for this device



To get the value of `distributor` call the method like this:


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




To set the value of `distributor` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.distributor()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function distributor (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.distributor((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### hdcp
Get the supported HDCP profiles



To get the value of `hdcp` call the method like this:


```typescript
function hdcp(): Promise<object>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | the supported HDCP profiles |


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





To set the value of `hdcp` call the method like this:


```typescript
function hdcp(): Promise<ListenResponse | object>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Getting the supported HDCP profiles


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.hdcp(true)
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function hdcp (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.hdcp((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### hdr
Get the supported HDR profiles



To get the value of `hdr` call the method like this:


```typescript
function hdr(): Promise<object>
```




Promise resolution:

| Type | Description |
| ---- | ----------- |
| `object` | the supported HDR profiles |


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





To set the value of `hdr` call the method like this:


```typescript
function hdr(): Promise<ListenResponse | object>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Getting the supported HDR profiles


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.hdr(true)
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function hdr (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.hdr((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### id
Get the platform back-office device identifier



To get the value of `id` call the method like this:


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




To set the value of `id` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.id()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function id (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.id((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### make
Get the device make



To get the value of `make` call the method like this:


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




To set the value of `make` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.make()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function make (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.make((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### model
Get the device model



To get the value of `model` call the method like this:


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




To set the value of `model` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.model()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function model (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.model((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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





To set the value of `name` call the method like this:


```typescript
function name(): Promise<ListenResponse | string>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Example value for device name


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.name(true)
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function name (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.name((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### network
Get the current network status and type



To get the value of `network` call the method like this:


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





To set the value of `network` call the method like this:


```typescript
function network(): Promise<ListenResponse | object>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Getting the network info


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.network(true)
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function network (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.network((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### platform
Get the platform ID for this device



To get the value of `platform` call the method like this:


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




To set the value of `platform` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.platform()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function platform (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.platform((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### screenResolution
Get the current screen resolution



To get the value of `screenResolution` call the method like this:


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





To set the value of `screenResolution` call the method like this:


```typescript
function screenResolution(): Promise<ListenResponse | [number, number]>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Getting the screen resolution


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.screenResolution(true)
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function screenResolution (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.screenResolution((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### sku
Get the device sku



To get the value of `sku` call the method like this:


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




To set the value of `sku` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.sku()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function sku (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.sku((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### type
Get the device type



To get the value of `type` call the method like this:


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




To set the value of `type` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.type()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function type (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.type((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### uid
Gets a unique id for the current app & device



To get the value of `uid` call the method like this:


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




To set the value of `uid` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.uid()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function uid (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.uid((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### version
Get the SDK, OS and other version info



To get the value of `version` call the method like this:


```typescript
function version(): Promise<object>
```




Promise resolution:

the versions

| Field | Type | Description |
| ----- | ---- | ----------- |
| `sdk` | [`SemanticVersion`](#semanticversion) | The Firebolt SDK version |
| `api` | [`SemanticVersion`](#semanticversion) | The lateset Firebolt API version supported by the curent device. |
| `firmware` | [`SemanticVersion`](#semanticversion) | The device firmware version. |
| `os` | [`SemanticVersion`](#semanticversion) | **Deprecated** Use `firmware`, instead. |
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




To set the value of `version` call the method like this:


```typescript
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.version()
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
```

Response:

```json
```

</details>

To subscribe to notifications when the value changes, call the method like this:


```typescript
function version (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.version((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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

### videoResolution
Get the current video resolution



To get the value of `videoResolution` call the method like this:


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





To set the value of `videoResolution` call the method like this:


```typescript
function videoResolution(): Promise<ListenResponse | [number, number]>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |

Promise resolution:

| Type | Summary |
| ---- | ------- |
| `void` | Promise resolves with no value when the operation is complete. |

**Examples**

Getting the video resolution


JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.videoResolution(true)
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




To subscribe to notifications when the value changes, call the method like this:


```typescript
function videoResolution (subscriber: () => void): Promise<listenerId>
```


Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | | | |
| `subscriber`           | `function`             | Yes                      | Callback to execute when the value changes. |


Promise resolution:

| Type | Summary |
| ---- | ------- |
| `listenerId` | The id of the listener that can be used with Device.clear(listenerId) to unsubscribe |

Callback parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `` | `|

**Examples**



JavaScript:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.videoResolution((value) => {
  // property value was changed
  console.log(value)
}).then(listenerId => {
  // you can clear this listener w/ Device.clear(listenerId)
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




---

### hdcp

Get the supported HDCP profiles

```typescript
function hdcp(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the supported HDCP profiles |


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




---

### hdr

Get the supported HDR profiles

```typescript
function hdr(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the supported HDR profiles |


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




---

### audio

Get the supported audio profiles

```typescript
function audio(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the supported audio profiles |


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




---

### screenResolution

Get the current screen resolution

```typescript
function screenResolution(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the resolution |


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




---

### videoResolution

Get the current video resolution

```typescript
function videoResolution(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the resolution |


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




---

### network

Get the current network status and type

```typescript
function network(): Promise<ListenResponse>
```


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`ListenResponse`](#listenresponse) | the status and type |


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




---








## Schemas

### SemanticVersion


```typescript
type SemanticVersion = {
  major: number
  minor: number
  patch: number
  readable: string
}
```



---

### ListenResponse


```typescript
type ListenResponse = {
  event: string
  listening: boolean
}
```



---

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
  [property: string]: boolean
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

### AudioProfile


```typescript
type AudioProfile = 'stereo' | 'dolbyDigital5.1' | 'dolbyDigital7.1' | 'dolbyDigital5.1+' | 'dolbyDigital7.1+' | 'dolbyAtmos'
```



---


