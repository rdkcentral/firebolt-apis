# Display

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor | Organization |
| ----------- | ------------ |
| Joe Martin  | Comcast      |

## 1. Overview

Content partners want to be able to get various details of the device, such as the make, model, chipset/SoC, and the type of device. These properties provide content partners with greater insight into the capabilities and characteristics of client devices.

### 1.1. User Stories

As an app, I want to...

- Get the chipset of the device
- Get the available and total system memory capacity of both the system and GPU, in kilobytes
- Get the system uptime of the device, in seconds
- Get whether the device is a TV, STB, or OTT streaming device

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
- [2. Table of Contents](#2-table-of-contents)
- [3. Constants, Types, and Schemas](#3-constants-types-and-schemas)
- [3.2. Interface Types](#32-interface-types)
- [4. Device Support](#4-device-support)
  - [4.1. Device Uptime](#41-device-uptime)
  - [4.2. User Idle Time](#42-user-idle-time)
  - [4.3. Free and Total Memory](#43-free-and-total-memory)
  - [4.4. Chipset/SoC](#44-chipsetsoc)
  - [4.5. Device Type](#45-device-type)

## 3. Constants, Types, and Schemas

## 3.2. Interface Types

The Firebolt `Types` module **MUST** have an `DeviceType` enumeration:

- `ott`
- `stb`
- `tv`

## 4. Device Support

Apps need to know various properties of the device.

These will be surfaced in the `Device` module.

### 4.1. Device Uptime

The `Device` module **MUST** have an `uptime` method that returns an integer denoting the system uptime, in seconds (since last boot).

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:device:info` capability.

```javascript
Device.uptime()
//> 86400
```

### 4.2. User Idle Time

The `Device` module **MUST** have a `userIdleTime` method that returns an integer denoting the time elapsed since last user interaction, in seconds.

The user idle timer value **MUST** be reset to zero each time the user interacts with the device.

> TOOD: Add a note about what types of events reset this time.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:device:useridletime` capability.

```javascript
Display.userIdleTime()
//> 600
```

### 4.3. Free and Total Memory

The `Device` module **MUST** have a `memory` method that returns an object denoting the device's current memory consumption and total capacity, in kilobytes.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:device:info` capability.

```javascript
Device.memory()
//> {
//>   totalSystemMemoryKb: 999...
//>   usedSystemlMemoryKb: 999...
//>   totalVideoMemoryKb: 999...
//>   usedVideoMemoryKb: 999...
//> }
```

### 4.4. Chipset/SoC

The `Device` module **MUST** have a `chipset` method that returns a string denoting the chipset/SoC of the device.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:device:info` capability.

```javascript
Device.chipset()
//> "BCM2712"
```

### 4.5. Device Type

The `Device` module **MUST** have a `type` method that returns a `Types.DeviceType` value denoting the device type.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:device:info` capability.

```javascript
Device.type()
//> "tv""
```
