# Networking Requirements

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Bart Catrysse   | Liberty Global |
| Brian Chow      | Sky            |
| Jeremy LaCivita | Comcast        |
| Joe Martin      | Comcast        |

## 1. Overview

To provide the best experience to users, content partners want to understand details about a device's network connection, such as the device's connection state, connection type, and that connection's performance capabilities.  Content partners also want to be notified of key changes to the device's connection, such as connect/disconnect events or IP changes.  This data can be used to gauge how those changes may impact the user's experience and react appropriately.

App partners also have different requirements of what network details are made available to them.  For instance, most app partners simply want to know the device's current connection state, type, and be notified of changes to that connection.  Other app partners may have more sophisticated needs, requiring access to details on the the configurations of all available network interfaces, including interface MACs, IPs, and wireless connection details.

This information can be used to gracefully handle cases when the device has poor or no network connectivity, provide valuable data into how the user's network performance is impacting their experience, and to unlock more advanced networking features on the device (such as Wake-on-LAN functionality).

These APIs will be surfaced in the Firebolt `Network` module.

### 1.1. User Stories

As an app, I want to...

- Get the device's network connection state and connection type
- Get details on each of the device's interfaces, such as name, MAC address, and IP configuration
- Get details on the wireless connection, such as SSID and signal strength
- Be notified of key changes to the device's network connection, such as connection state, TCP/IP configuration, or wireless signal

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
- [2. Table of Contents](#2-table-of-contents)
- [3. Constants, Types, and Schemas](#3-constants-types-and-schemas)
  - [3.1. Connection States](#31-connection-states)
  - [3.2. Interface Types](#32-interface-types)
  - [3.3 Ethernet Standards](#33-ethernet-standards)
  - [3.4. Wireless Standards](#34-wireless-standards)
- [4. Network APIs](#4-network-apis)
  - [4.1. Connection Status](#41-connection-status)
  - [4.2. Interfaces](#42-interfaces)
  - [4.3. IP Properties](#43-ip-properties)
  - [4.4. Wifi Status](#44-wifi-status)
  - [4.5. Wifi Signal Strength Change Event](#45-wifi-signal-strength-change-event)

## 3. Constants, Types, and Schemas

### 3.1. Connection States

The Firebolt `Network` module **MUST** have a `ConnectionState` enumeration:

- `connected`
- `disconnected`
- `unknown`

### 3.2. Interface Types

The Firebolt `Network` module **MUST** have an `InterfaceType` enumeration:

- `ethernet`
- `wifi`
- `other`
- `unknown`

### 3.3 Ethernet Standards

The Firebolt `Network` module **MUST** have an `EthernetStandard` enumeration:

- `Fast Ethernet`
- `Gibabit Ethernet`
- `10 Gigabit Ethernet`

### 3.4. Wireless Standards

The Firebolt `Network` module **MUST** have an `WirelessStandard` enumeration:

| Name       | Description   |
| ---------- | ------------- |
| `802.11ac` |               |
| `802.11ax` |               |
| `802.11be` |               |
| `802.11n`  |               |
| `legacy`   | `802.11a/b/g` |

## 4. Network APIs

Apps need to get various details about the device's network configuration and capabilities, such as whether the device is connected to a network, what type of connection is used, and details on the network interfaces available on the device.

Apps also need to be aware of changes to the device's network connection that may occur, either through user-initiated changes or via external factors.

To facilitate this, the `Network` module will surface methods that provide various details of the device's connection to the local network while also allowing apps to subscribe to various events triggered by key changes to the network connection.

### 4.1. Connection Status

The `Network` module **MUST** have a `connectionStatus` method that returns an object describing the device's current network connection status.

This method **MUST** return the following properties:

| Property    | Type      |
| ----------- | --------- |
| `connected` | `boolean` |

The following properties are **OPTIONAL**:

| Property | Type                    |
| -------- | ----------------------- |
| `type`   | `Network.InterfaceType` |

The result **MUST** be based on the device's preferred/default network interface.

If the device's preferred interface has both an active network connection and valid IP configuration, the `connected` value **MUST** be `true`, otherwise `false` is returned.

If `connected` is `true`, `type` **MUST** be one of: `ethernet`, `wifi`, or `other`.

If `connected` is `false`, `type` **MUST NOT** be returned.

This method **MUST** have a corresponding `onStatusChanged` event returning the properties listed above to notify listeners when any of the properties have changed and taken effect.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:network:connectionstatus` capability.

```javascript
Network.connectionStatus()
//> {
//>   "connected": true,
//>   "type": "wifi"
//> }
```

### 4.2. Interfaces

The `Network` module **MUST** have an `interfaces` method that describes each network interface on the device.

This method **MUST** return an array of objects with the following properties:

| Property           | Type                                                 | Description                                                                      |
| ------------------ | ---------------------------------------------------- | -------------------------------------------------------------------------------- |
| `capability`       | `Network.EthernetStandard`</br>or `WirelessStandard` | The connection capability of the interface (e.g. `Gibabit Ethernet`, `802.11ac`) |
| `connectionState`  | `Network.ConnectionState`                            |                                                                                  |
| `interfaceName`    | `string`                                             |                                                                                  |
| `macAddress`       | `string`                                             |                                                                                  |
| `preferred`        | `boolean`                                            | Whether the interface is the preferred/default interface for routing             |
| `type`             | `Network.InterfaceType`                              | The generalized type of interface (e.g. `ethernet` or `wifi`)                    |
| `wakeOnLanEnabled` | `boolean`                                            |                                                                                  |

If `connectionState` is `disconnected`, `preferred` **MUST** be `false`.

This method **MUST** have a corresponding `onInterfaceChanged` event returning an object with the properties listed above to notify listeners when an interface's properties have changed and taken effect.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:network:interfaces` capability.

```javascript
Network.interfaces()
//> [
//>   {
//>     capability: "802.11ac",
//>     connectionState: "disconnected",
//>     interfaceName: "wifi0",
//>     macAddress: "00:00:00:00:00:00",
//>     preferred: false,
//>     type: "wifi",
//>     wakeOnLanEnabled: true
//>   },
//>   {
//>     capability: "Gibabit Ethernet",
//>     connectionState: "connected",
//>     interfaceName: "eth0",
//>     macAddress: "00:00:00:00:00:00",
//>     preferred: true,
//>     type: "ethernet",
//>     wakeOnLanEnabled: true
//>   },
//> ]
```

### 4.3. IP Properties

The `Network` module **MUST** have an `ipProperties` method that returns an object describing the TCP/IP properties of an interface.

This method **MUST** return the following properties:

| Property           | Type       |
| ------------------ | ---------- |
| `interfaceName`    | `string`   |
| `ipv4Addresses`    | `[]string` |
| `ipv4DNSAddresses` | `[]string` |
| `ipv6Addresses`    | `[]string` |
| `ipv6DNSAddresses` | `[]string` |

The method **MUST** require a `string` parameter denoting the interface name on which the result shall be based.

The values returned in `ipv4Addresses` and `ipv6Addresses` **MUST** be presented in CIDR notation.

If an invalid interface name is provided, a `-40404 / Interface not found` JSON-RPC error **MUST** be returned.

This method **MUST** have a corresponding `onIpPropertiesChanged` event returning the properties listed above to notify listeners of changes to an interface's IP properties.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:network:ipproperties` capability.

```javascript
Network.ipProperties("eth0")
//> {
//>   interfaceName: "eth0",
//>   ipv4Addresses: ["192.168.1.100/24"],
//>   ipv4DNSAddresses: ["75.75.75.75"],
//>   ipv6Addresses: ["2001:db8:abcd:0012::0/64"],
//>   ipv6DNSAddresses: ["2001:558:feed::1"]
//> }
```

### 4.4. Wifi Status

The `Network` module **MUST** have a `wifiStatus` method that returns an object describing an interface's connection status to a wireless network.

The method **MUST** support a required `string` parameter denoting the interface name of which the result is based.

This method **MUST** return the following properties:

| Property          | Type                      |
| ----------------- | ------------------------- |
| `connectionState` | `Network.ConnectionState` |
| `interfaceName`   | `string`                  |

The following properties are **OPTIONAL**:

| Property         | Type                       | Description                             |
| ---------------- | -------------------------- | --------------------------------------- |
| `mode`           | `Network.WirelessStandard` | Current wireless mode (e.g. `802.11ac`) |
| `signalStrength` | `integer`                  | Signal strength / RSSI value (in dBm)   |
| `ssid`           | `string`                   | Wireless network name                   |

If no wireless interface matches the provided name, a `-40404 / Wireless interface not found` JSON-RPC error **MUST** be returned.

If the wireless interface is not connected to a network, `connectionState` **MUST** be `disconnected`.

If the wireless interface is not connected to a network, `mode`, `signalStrength` and `ssid` **MUST NOT** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:network:wifistatus` capability.

```javascript
Network.wifiStatus("wifi0")
//> {
//>  connectionState: "connected",
//>  interfaceName: "wifi0",
//>  mode: "802.11ac",
//>  signalStrength: -50,
//>  ssid: "MyNetwork"
//> }
```

### 4.5. Wifi Signal Strength Change Event

The `Network` module **MUST** have an `onWifiSignalStrengthChange` event to notify listeners of a significant change in the device's wireless connection signal strength.

The method **MUST** support a required `integer` parameter denoting a time interval, in milliseconds, after which the current RSSI is compared to the previous to determine if the signal strength crossed a threshold.

The thresholds may be operator-dependent, but a general guide may be:

| RSSI Threshold (in dBm) | Description |
| ----------------------- | ----------- |
| -50 and higher          | Excellent   |
| -50 to -60              | Good        |
| -60 to -67              | Fair        |
| Below -67               | Weak        |

This method **MUST** return the following properties:

| Property        | Type      | Description                                    |
| --------------- | --------- | ---------------------------------------------- |
| `interfaceName` | `string`  |                                                |
| `currentValue`  | `integer` | Current signal strength / RSSI value (in dBm)  |
| `previousValue` | `integer` | Previous signal strength / RSSI value (in dBm) |

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:network:onwifisignalstrengthchange` capability.

```javascript
Network.onWifiSignalStrengthChange(10000)
//> {
//>  interfaceName: "wifi0",
//>  currentValue: -60,
//>  previousValue: -50
//> }
```
