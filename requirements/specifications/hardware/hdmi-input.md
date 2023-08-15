# HDMIInput

Document Status: Candidate Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor         | Organization   |
| ------------------- | -------------- |
| Jeremy LaCivita     | Comcast        |
| Lucien Kennedy-Lamb | Sky            |

## 1. Overview
This document describes the requirements for managing HDMI inputs on a Firebolt device. These APIs are generally useful for managing an HDMI sink device, e.g. a TV.

This document is written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt), specifically:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. HDMI Input Ports](#3-hdmi-input-ports)
  - [3.1. Get Port](#31-get-port)
- [5. Low Latency](#5-low-latency)
  - [5.1. Low Latency Mode](#51-low-latency-mode)
    - [5.1.1. Low Latency Mode Notification](#511-low-latency-mode-notification)
  - [5.2. Input Source Device Auto Low Latency Mode Notification](#52-input-source-device-auto-low-latency-mode-notification)
  - [5.3. Input Port Auto Low Latency Mode Support](#53-input-port-auto-low-latency-mode-support)
    - [5.3.1. Input Port Auto Low Latency Mode Support Changed Notification](#531-input-port-auto-low-latency-mode-support-changed-notification)
- [6. Port Signal Notification](#6-port-signal-notification)
- [7. Input Source OSD Name Notification](#7-input-source-osd-name-notification)

## 3. HDMI Input Ports
The `HDMIInput` module **MUST** have a `ports` method that lists all physical HDMI input ports on the device.

The `ports` API **MUST** return an array of `HDMIPort` objects.

The properties of each `HDMIPort` object **MUST** have values that are implicit to the physical port itself, and not not dependent on any connected HDMI device.

An example response:

```json
[
    {
        "port": "HDMI1",
        "connected": true,
        "signal": "unknown",
        "arcCapable": true,
        "arcConnected": true,
        "autoLowLatencyModeCapable": true,
        "autoLowLatencyModeSignalled": true,
        "edidVersion": "2.0"
    }
]
```

**TODO**: rename all the events to match ^^
**TODO**: move sources() to CEC branch

The `HDMIPort` object **MUST** have a `port` string property, which is the unique ID of that port.

The `port` property **MUST** match the pattern:

 ```regexp
 /^HDMI[0-9]+$/
 ```

The `HDMIPort` object **MUST** have a `connected` boolean property, which is true if that port has a device connected, false otherwise.

The `HDMIPort` object **MUST** have a `signal` string property, which denotes the signal strength and validity.

The `signal` property **MUST** be one of the following values:

- `"unknown"` - the HDMI input port is not switched, so the signal state is unknown.
- `"none"` - no signal from the HDMI input device.
- `"stable"` - the signal is stable and should provide good audio and viddeo.
- `"unstable"` - the signal is unstable and could exhibit broken audio and video.
- `"unsupported"` - the signal is not at a supported speed/resolution.

The `HDMIPort` object **MUST** have an `arcCapable` boolean property, which is true if this HDMI port supports ARC and/or eARC device connections.

The `HDMIPort` object **MUST** have an `arcConnected` boolean property, which is true if the connected HDMI device supports ARC and/or eARC device connections.

The `HDMIPort` object **MUST** have an `edidVersion` string property which is the selected E-EDID version "1.4" or "2.0" for the port.

The `edidVersion` property **MUST** be on of the following values:

- `"1.4"`
- `"2.0"`
- `"unknown"`

If the `edidVersion` is `"2.0"` then the `HDMIPort` object:

> **MUST** have an `autoLowLatencyModeCapable` boolean property, which is true if the E-EDID has ALLM support advertised and false otherwise.
>
> **MUST** have an `autoLowLatencyModelSignalled` boolean proeprty, which is true if the port is receiving an ALLM signal from a downstream source device, and false otherwise.

If the `ediddersion` is `"1.4"` or `"unknown"` then the `HDMIPort` object:

 > **MUST** have the `autoLowLatencyModeCapable` boolean property set to `false`.
 >
 > **MUST** have the `autoLowLatencyModelSignaled` boolean proeprty set to `false`

The `"unknown"` value of the `edidVersion` property **SHOULD** be reserved for edge cases, such as a test device with a newer version of HDMI ports than the device software supports.

### 3.1. Get Port
The `HDMIInput` module **MUST** have a `port` method that returns info on a single HDMI port.

The `port` API **MUST** return an `HDMIPort` object that corresponds to the provided `portId` parameter.

```javascript
HDMIInput.port('HDMI1')
```

## 5. Low Latency
Low Latency refers to a set of functionaly that combine to provide manual or automatic activation of HDMI Low Latency Mode.

Low latency mode switches the device to shorten the overall processing time of HDMI A/V signals.
Depending on the platform some video processing features may be dropped such as MPEG noise reduction.

### 5.1. Low Latency Mode
The `HDMIInput` module **MUST** have a boolean property named `lowLatencyMode`, with a getter, setter, and notification subscriber.

Enabling this property turns on the underlying low latency mode feature for the Firebolt device.

Low latency mode switches the device to shorten the overall processing time of HDMI A/V signals.
Depending on the platform some video processing features may be dropped such as MPEG noise reduction.

#### 5.1.1. Low Latency Mode Notification
Whenever the underlying HDMI implementation executes an LLM change (either on or off), this notification **MUST** fire:

`HDMIInput.onLowLatencyModeChanged`


### 5.2. Input Source Device Auto Low Latency Mode Notification
The `HDMIInput` module **MUST** have an `onSourceAutoLowLatencyModeChanged` notification that fires when any HDMI input device changes its advertising for ALLM.

This notification **MUST** have an object payload.

The object payload **MUST** have a `port` string property that denotes which input port has detected a change to the ALLM advertising.

**TODO**: is advertising appropriate for the device or just the port? Signalling was confusing, since we also have a signal proprty.

The `port` property **MUST** match the pattern:

 ```regexp
 /^HDMI[0-9]+$/
 ```

The object payload **MUST** have an `autoLowLatencyMode` boolean property that denotes the updated value, true or false, of the ALLM setting.

Example payload:

```json
  {
      "port": "HDMI1",
      "autoLowLatencyMode": true
  }
```

### 5.3. Input Port Auto Low Latency Mode Support
The `HDMIInput` module **MUST** have a boolean property `portAutoLowLatencyMode` reflects the HDMI port setting for advertising ALLM support in its E-EDID.

The `portAutoLowLatencyMode` property takes a string context parameter, `port` to identify the HDMI port.

The `port` parameter must match the pattern:

```regexp
 /^HDMI[0-9]+$/
 ```

Changing this property turns on/off the underlying auto low latency mode advertisement in any HDMI port E-EDID of version >= v2.0.

To change the property:

```javascript
function portAutoLowLatencyMode(port: string, autoLowLatencyMode: boolean)
```

#### 5.3.1. Input Port Auto Low Latency Mode Support Changed Notification
Whenever the underlying HDMI implementation executes an ALLM support change (either on or off), this notification must fire:

`HDMIInput.onPortAutoLowLatencyModeChanged`

To listen for port ALLM notifications:

```javascript
HDMIInput.portAutoLowLatencyModeChanged() (data) => {
  console.log('Port ' + data.port + ' ALLM changed to ' + data.autoLowLatencyMode)
})
```

**TODO**: This is different than how we currently do context parameters on events. Will need some Firebolt SDK work to generate this API.

`autoLowLatencyModeSupport` - whether or not ALLM is advertised as supported in the E-EDID for the port.

`port` - the HDMI port that had an E-EDID ALLM advertisement change.

## 6. Port Signal Notification
The `HDMIInput` module **MUST** have an `onPortSignalChanged` notification that fires when any HDMI port signal changes status.

This notification **MUST** have an object payload.

The object payload **MUST** have a `port` string property that denotes which input port has detected a change to the ALLM signaling.

The `port` property **MUST** match the pattern:

 ```regexp
 /^HDMI[0-9]+$/
 ```

The object payload **MUST** have a `signal` string property that denotes the updated value of the input device signal.

The `signal` property **MUST** be one of the following values:

- `"unknown"` - the HDMI input port is not switched, so the signal state is unknown.
- `"none"` - no signal from the HDMI input device.
- `"stable"` - the signal is stable and should provide good audio and viddeo.
- `"unstable"` - the signal is unstable and could exhibit broken audio and video.
- `"unsupported"` - the signal is not at a supported speed/resolution.

Example payload:

```json
  {
      "port": "HDMI1",
      "signal": "stable"
  }
```

## 7. Input Source OSD Name Notification
The `HDMIInput` module **MUST** have an `onSourceOSDNameChanged` notification that fires when any HDMI input device changes its OSD Name.

This notification **MUST** have an object payload.

The object payload **MUST** have a `port` string property that denotes which input port has detected a change to the ALLM signaling.

The `port` property **MUST** match the pattern:

 ```regexp
 /^HDMI[0-9]+$/
 ```

The object payload **MUST** have an `osdName` string property that denotes the updated value of the input device OSD Name.

Example payload:

```json
  {
      "port": "HDMI1",
      "osdName": "XBox"
  }
```