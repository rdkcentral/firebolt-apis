Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [accessory.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/accessory.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [pair](#pair)
    - [list](#list)



 - [Schemas](#schemas)
    - [AccessoryList](#accessorylist)
    - [AccessoryPairingTimeout](#accessorypairingtimeout)
    - [AccessoryType](#accessorytype)
    - [AccessoryTypeListParam](#accessorytypelistparam)
    - [AccessoryProtocol](#accessoryprotocol)
    - [AccessoryProtocolListParam](#accessoryprotocollistparam)
    - [AccessoryInfo](#accessoryinfo)

<span></span>

## Usage
To use the Accessory module, you can import it into your project from the Firebolt SDK:

```javascript
import { Accessory } from '@firebolt-js/manage-sdk'
```


## Methods
### pair

Pair an accessory with the device.

```typescript
function pair(type?: AccessoryType, protocol?: AccessoryProtocol, timeout?: AccessoryPairingTimeout): Promise<AccessoryInfo>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `type` | [`AccessoryType`](#accessorytype) | false |   |
| `protocol` | [`AccessoryProtocol`](#accessoryprotocol) | false |   |
| `timeout` | [`AccessoryPairingTimeout`](#accessorypairingtimeout) | false |  <br/>minumum: 0
maximum: 9999 |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`AccessoryInfo`](#accessoryinfo) | Properties of a paired accessory. |


**Examples**

Pair a Bluetooth Remote

JavaScript:

```javascript
import { Accessory } from '@firebolt-js/manage-sdk'

Accessory.pair("Remote", "BluetoothLE", 180)
    .then(pairedAccessory => {
        console.log(pairedAccessory)
    })
```
Value of `pairedAccessory`:

```javascript
{
  "type": "Remote",
  "make": "UEI",
  "model": "PR1",
  "protocol": "BluetoothLE"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessory.pair",
  "params": {
    "type": "Remote",
    "protocol": "BluetoothLE",
    "timeout": 180
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "type": "Remote",
    "make": "UEI",
    "model": "PR1",
    "protocol": "BluetoothLE"
  }
}
```

</details>

<details>
    <summary>More examples...</summary>
Pair a Bluetooth Speaker

JavaScript:

```javascript
import { Accessory } from '@firebolt-js/manage-sdk'

Accessory.pair("Speaker", "BluetoothLE", 180)
    .then(pairedAccessory => {
        console.log(pairedAccessory)
    })
```
Value of `pairedAccessory`:

```javascript
{
  "type": "Speaker",
  "make": "Sonos",
  "model": "V120",
  "protocol": "BluetoothLE"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessory.pair",
  "params": {
    "type": "Speaker",
    "protocol": "BluetoothLE",
    "timeout": 180
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "type": "Speaker",
    "make": "Sonos",
    "model": "V120",
    "protocol": "BluetoothLE"
  }
}
```

</details>

Pair a RF Remote

JavaScript:

```javascript
import { Accessory } from '@firebolt-js/manage-sdk'

Accessory.pair("Remote", "RF4CE", 180)
    .then(pairedAccessory => {
        console.log(pairedAccessory)
    })
```
Value of `pairedAccessory`:

```javascript
{
  "type": "Remote",
  "make": "UEI",
  "model": "15",
  "protocol": "RF4CE"
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessory.pair",
  "params": {
    "type": "Remote",
    "protocol": "RF4CE",
    "timeout": 180
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "type": "Remote",
    "make": "UEI",
    "model": "15",
    "protocol": "RF4CE"
  }
}
```

</details>

</details>



---

### list

Provides a list of Accesories paired to the device.

```typescript
function list(type?: AccessoryTypeListParam, protocol?: AccessoryProtocolListParam): Promise<AccessoryList>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `type` | [`AccessoryTypeListParam`](#accessorytypelistparam) | false |   |
| `protocol` | [`AccessoryProtocolListParam`](#accessoryprotocollistparam) | false | Defines the mechanism by which accessory will connect to the device.  |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`AccessoryList`](#accessorylist) | Contains a list of Accessories paired to the device. |


**Examples**

List all Accessories.

JavaScript:

```javascript
import { Accessory } from '@firebolt-js/manage-sdk'

Accessory.list("All", "All")
    .then(list => {
        console.log(list)
    })
```
Value of `list`:

```javascript
{
  "list": [
    {
      "type": "Remote",
      "make": "uei",
      "model": "PR1",
      "protocol": "BluetoothLE"
    },
    {
      "type": "Speaker",
      "make": "Sonos",
      "model": "V120",
      "protocol": "BluetoothLE"
    }
  ]
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessory.list",
  "params": {
    "type": "All",
    "protocol": "All"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "list": [
      {
        "type": "Remote",
        "make": "uei",
        "model": "PR1",
        "protocol": "BluetoothLE"
      },
      {
        "type": "Speaker",
        "make": "Sonos",
        "model": "V120",
        "protocol": "BluetoothLE"
      }
    ]
  }
}
```

</details>

<details>
    <summary>More examples...</summary>
List Bluetooth accessories

JavaScript:

```javascript
import { Accessory } from '@firebolt-js/manage-sdk'

Accessory.list("All", "BluetoothLE")
    .then(list => {
        console.log(list)
    })
```
Value of `list`:

```javascript
{
  "list": [
    {
      "type": "Remote",
      "make": "uei",
      "model": "PR1",
      "protocol": "BluetoothLE"
    },
    {
      "type": "Speaker",
      "make": "Sonos",
      "model": "V120",
      "protocol": "BluetoothLE"
    }
  ]
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessory.list",
  "params": {
    "type": "All",
    "protocol": "BluetoothLE"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "list": [
      {
        "type": "Remote",
        "make": "uei",
        "model": "PR1",
        "protocol": "BluetoothLE"
      },
      {
        "type": "Speaker",
        "make": "Sonos",
        "model": "V120",
        "protocol": "BluetoothLE"
      }
    ]
  }
}
```

</details>

List only Bluetooth Remotes

JavaScript:

```javascript
import { Accessory } from '@firebolt-js/manage-sdk'

Accessory.list("Remote", "BluetoothLE")
    .then(list => {
        console.log(list)
    })
```
Value of `list`:

```javascript
{
  "list": [
    {
      "type": "Remote",
      "make": "uei",
      "model": "PR1",
      "protocol": "BluetoothLE"
    }
  ]
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessory.list",
  "params": {
    "type": "Remote",
    "protocol": "BluetoothLE"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "list": [
      {
        "type": "Remote",
        "make": "uei",
        "model": "PR1",
        "protocol": "BluetoothLE"
      }
    ]
  }
}
```

</details>

List only Bluetooth Speakers

JavaScript:

```javascript
import { Accessory } from '@firebolt-js/manage-sdk'

Accessory.list("Speaker", "BluetoothLE")
    .then(list => {
        console.log(list)
    })
```
Value of `list`:

```javascript
{
  "list": [
    {
      "type": "Speaker",
      "make": "Sonos",
      "model": "V120",
      "protocol": "BluetoothLE"
    }
  ]
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessory.list",
  "params": {
    "type": "Speaker",
    "protocol": "BluetoothLE"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "list": [
      {
        "type": "Speaker",
        "make": "Sonos",
        "model": "V120",
        "protocol": "BluetoothLE"
      }
    ]
  }
}
```

</details>

List only RF Remote

JavaScript:

```javascript
import { Accessory } from '@firebolt-js/manage-sdk'

Accessory.list("Remote", "RF4CE")
    .then(list => {
        console.log(list)
    })
```
Value of `list`:

```javascript
{
  "list": [
    {
      "type": "Remote",
      "make": "uei",
      "model": "XR15",
      "protocol": "RF4CE"
    }
  ]
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "accessory.list",
  "params": {
    "type": "Remote",
    "protocol": "RF4CE"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "list": [
      {
        "type": "Remote",
        "make": "uei",
        "model": "XR15",
        "protocol": "RF4CE"
      }
    ]
  }
}
```

</details>

</details>



---










## Schemas

### AccessoryList


Contains a list of Accessories paired to the device.

```typescript
type AccessoryList = {
  list?: AccessoryInfo[]
}
```



---

### AccessoryPairingTimeout


Defines the timeout in seconds. If the threshold for timeout is passed without a result it will throw an error.

```typescript
type AccessoryPairingTimeout = number
```



---

### AccessoryType


Type of the device Remote,Speaker or Other

```typescript
type AccessoryType = 'Remote' | 'Speaker' | 'Other'
```



---

### AccessoryTypeListParam


Type of the device Remote,Speaker or Other

```typescript
type AccessoryTypeListParam = 'Remote' | 'Speaker' | 'All'
```



---

### AccessoryProtocol


Mechanism to connect the accessory to the device

```typescript
type AccessoryProtocol = 'BluetoothLE' | 'RF4CE'
```



---

### AccessoryProtocolListParam


Mechanism to connect the accessory to the device

```typescript
type AccessoryProtocolListParam = 'BluetoothLE' | 'RF4CE' | 'All'
```



---

### AccessoryInfo


Properties of a paired accessory.

```typescript
type AccessoryInfo = {
  type?: AccessoryType          // Type of the device Remote,Speaker or Other
  make?: string                 // Name of the manufacturer of the accessory
  model?: string                // Model name of the accessory
  protocol?: AccessoryProtocol  // Mechanism to connect the accessory to the device
}
```



---


