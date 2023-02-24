Version undefined

## Overview
 

## OpenRPC
Firebolt APIs are maintained in the [rdkcentral/firebolt-core-sdk](https://github.com/rdkcentral/firebolt-core-sdk) GitHub repository.

You can see this API in the [wifi.json](https://github.com/rdkcentral/firebolt-core-sdk/blob/main/src/modules/wifi.json) OpenRPC JSON-Schema document. 

## Table of Contents
 - [Overview](#overview)
 - [OpenRPC](#openrpc)
 - [Usage](#usage)
 - [Methods](#methods)
    - [scan](#scan)
    - [connect](#connect)
    - [disconnect](#disconnect)
    - [wps](#wps)



 - [Schemas](#schemas)
    - [AccessPointList](#accesspointlist)
    - [WifiSecurityMode](#wifisecuritymode)
    - [WifiSignalStrength](#wifisignalstrength)
    - [WifiFrequency](#wififrequency)
    - [AccessPoint](#accesspoint)
    - [WPSSecurityPin](#wpssecuritypin)
    - [Timeout](#timeout)

<span></span>

## Usage
To use the Wifi module, you can import it into your project from the Firebolt SDK:

```javascript
import { Wifi } from '@firebolt-js/manage-sdk'
```


## Methods
### scan

Scan available wifi networks in the location.

```typescript
function scan(timeout?: Timeout): Promise<AccessPointList>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `timeout` | [`Timeout`](#timeout) | false |  <br/>minumum: 0
maximum: 9999 |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`AccessPointList`](#accesspointlist) | List of scanned Wifi networks available near the device. |


**Examples**

Successful Wifi List

JavaScript:

```javascript
import { Wifi } from '@firebolt-js/manage-sdk'

Wifi.scan(30)
    .then(list => {
        console.log(list)
    })
```
Value of `list`:

```javascript
{
  "list": [
    {
      "ssid": "DND",
      "security": "wpa2Psk",
      "signalStrength": -70,
      "frequency": 2.4
    },
    {
      "ssid": "Fortnite",
      "security": "WPA2_ENTERPRISE_AES",
      "signalStrength": -70,
      "frequency": 5
    },
    {
      "ssid": "Guardian",
      "security": "none",
      "signalStrength": -70,
      "frequency": 2.4
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
  "method": "wifi.scan",
  "params": {
    "timeout": 30
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
        "ssid": "DND",
        "security": "wpa2Psk",
        "signalStrength": -70,
        "frequency": 2.4
      },
      {
        "ssid": "Fortnite",
        "security": "WPA2_ENTERPRISE_AES",
        "signalStrength": -70,
        "frequency": 5
      },
      {
        "ssid": "Guardian",
        "security": "none",
        "signalStrength": -70,
        "frequency": 2.4
      }
    ]
  }
}
```

</details>




---

### connect

Connect the device to the specified SSID.

```typescript
function connect(ssid?: string, passphrase?: string, security?: WifiSecurityMode): Promise<AccessPoint>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `ssid` | `string` | false |   |
| `passphrase` | `string` | false |   |
| `security` | [`WifiSecurityMode`](#wifisecuritymode) | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`AccessPoint`](#accesspoint) | Properties of a scanned wifi list item. |


**Examples**

Connect to a wpa2Psk Wifi with password

JavaScript:

```javascript
import { Wifi } from '@firebolt-js/manage-sdk'

Wifi.connect("DND", "gargoyle", "wpa2Psk")
    .then(connectedWifi => {
        console.log(connectedWifi)
    })
```
Value of `connectedWifi`:

```javascript
{
  "ssid": "DND",
  "security": "wpa2Psk",
  "signalStrength": -70,
  "frequency": 2.4
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "wifi.connect",
  "params": {
    "ssid": "DND",
    "passphrase": "gargoyle",
    "security": "wpa2Psk"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "ssid": "DND",
    "security": "wpa2Psk",
    "signalStrength": -70,
    "frequency": 2.4
  }
}
```

</details>

<details>
    <summary>More examples...</summary>
Connect to a WPA2 PSK Wifi with password

JavaScript:

```javascript
import { Wifi } from '@firebolt-js/manage-sdk'

Wifi.connect("Guardian WIFI", "", "none")
    .then(connectedWifi => {
        console.log(connectedWifi)
    })
```
Value of `connectedWifi`:

```javascript
{
  "ssid": "Guardian WIFI",
  "security": "none",
  "signalStrength": -70,
  "frequency": 2.4
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "wifi.connect",
  "params": {
    "ssid": "Guardian WIFI",
    "passphrase": "",
    "security": "none"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "ssid": "Guardian WIFI",
    "security": "none",
    "signalStrength": -70,
    "frequency": 2.4
  }
}
```

</details>

</details>



---

### disconnect

Disconnect the device if connected via WIFI.

```typescript
function disconnect(): Promise<void>
```


Promise resolution:

```javascript
void
```

**Examples**

Disconnect

JavaScript:

```javascript
import { Wifi } from '@firebolt-js/manage-sdk'

Wifi.disconnect()
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
  "method": "wifi.disconnect",
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

### wps

Connect to WPS

```typescript
function wps(security?: WPSSecurityPin): Promise<AccessPoint>
```

Parameters:

| Param                  | Type                 | Required                 | Summary                 |
| ---------------------- | -------------------- | ------------------------ | ----------------------- |
| `security` | [`WPSSecurityPin`](#wpssecuritypin) | false |   |


Promise resolution:

| Type | Description |
| ---- | ----------- |
| [`AccessPoint`](#accesspoint) | Properties of a scanned wifi list item. |


**Examples**

Connect to a WPS Wifi router

JavaScript:

```javascript
import { Wifi } from '@firebolt-js/manage-sdk'

Wifi.wps("pushButton")
    .then(connectedWifi => {
        console.log(connectedWifi)
    })
```
Value of `connectedWifi`:

```javascript
{
  "ssid": "DND",
  "security": "wpa2Psk",
  "signalStrength": -70,
  "frequency": 2.4
}
```


<details>
  <summary>JSON-RPC:</summary>

Request:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "wifi.wps",
  "params": {
    "security": "pushButton"
  }
}
```

Response:

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "result": {
    "ssid": "DND",
    "security": "wpa2Psk",
    "signalStrength": -70,
    "frequency": 2.4
  }
}
```

</details>




---










## Schemas

### AccessPointList


List of scanned Wifi networks available near the device.

```typescript
type AccessPointList = {
  list?: AccessPoint[]
}
```



---

### WifiSecurityMode


Security Mode supported for Wifi

```typescript
type WifiSecurityMode = 'none' | 'wep64' | 'wep128' | 'wpaPskTkip' | 'wpaPskAes' | 'wpa2PskTkip' | 'wpa2PskAes' | 'wpaEnterpriseTkip' | 'wpaEnterpriseAes' | 'wpa2EnterpriseTkip' | 'wpa2EnterpriseAes' | 'wpa2Psk' | 'wpa2Enterprise' | 'wpa3PskAes' | 'wpa3Sae'
```



---

### WifiSignalStrength


Strength of Wifi signal, value is negative based on RSSI specification.

```typescript
type WifiSignalStrength = number
```



---

### WifiFrequency


Wifi Frequency in Ghz, example 2.4Ghz and 5Ghz.

```typescript
type WifiFrequency = number
```



---

### AccessPoint


Properties of a scanned wifi list item.

```typescript
type AccessPoint = {
  ssid?: string                        // Name of the wifi.
  securityMode?: WifiSecurityMode      // Security Mode supported for Wifi
  signalStrength?: WifiSignalStrength  // Strength of Wifi signal, value is negative based on RSSI specification.
  frequency?: WifiFrequency            // Wifi Frequency in Ghz, example 2.4Ghz and 5Ghz.
}
```



---

### WPSSecurityPin


Security pin type for WPS(Wifi Protected Setup).

```typescript
type WPSSecurityPin = 'pushButton' | 'pin' | 'manufacturerPin'
```



---

### Timeout


Defines the timeout in seconds. If the threshold for timeout is passed for any operation without a result it will throw an error.

```typescript
type Timeout = number
```



---


