# HDMIInput

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor         | Organization   |
| ------------------- | -------------- |
| Jeremy LaCivita     | Comcast        |
| Lucien Kennedy-Lamb | Sky            |

## 1. Overview

This document is written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt), specifically:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. HDMI Input Ports](#3-hdmi-input-ports)
- [4. HDMI Input Devices](#4-hdmi-input-devices)
- [5. Low Latency Mode](#5-low-latency-mode)
  - [5.1. Low Latency Mode Notification](#51-low-latency-mode-notification)
- [6. Auto Low Latency Mode Notification](#6-auto-low-latency-mode-notification)
- [7. Auto Low Latency Mode Support](#7-auto-low-latency-mode-support)
  - [7.1. Auto Low Latency Mode Support Changed Notification](#71-auto-low-latency-mode-support-changed-notification)
- [8. HDMI CEC Events](#8-hdmi-cec-events)
- [9. CEC Commands](#9-cec-commands)

## 3. HDMI Input Ports
Lists HDMI input ports. HDMIInput.ports() lists all attributes that are implicit to the port and not dependent on any connected HDMI input device.

```json
[
    {
        "port": "HDMI1",
        "arc": true,
        "edidVersion": "2.0",
        "autoLowLatencyMode": true
    }
]
```

`port` - the unique ID of the port.

`arc` - true if this HDMI port supports ARC and/or eARC device connections.

`edidVersion` - the selected E-EDID version "1.4" or "2.0" for the port.

`autoLowLatencyMode` - true if the E-EDID has ALLM support advertised. Only valid for >= v2.0 E-EDID configured ports.

**NOTE** API to get allowed values in edidVersion

## 4. HDMI Input Devices
Lists HDMI input devices. 
All attributes are the cross product of the port the input is plugged into and the input device itself.

Most frequent operations will leverage HDMIInput.devices(), but occassionally it might be useful to use HDMIInput.ports(), 
e.g. to let the user know that they plugged their Soundbar into the wrong port.

Luc> Where the HDMI standard uses values-as-enums, is the best approach to surface these values in Firebolt or convert to string enums?
Where a new version of HDMI appears, the values hold, but we won't be able to represent it as a string enum.
e.g. [CEC Version] is encoded as a byte, but shown below as a string "Version 2.0"

JL> JanP. recently proposed that all enums that identify techniclogies have an UNKNOWN value, which would be used if we don't recognize one. This also allows older SDKs to get newer values and map to something. I suggest we adopt that here.

```json
[
    {
        "port": "HDMI1",
        "signal": "unknown",
        "osdName": "PlayStation 4",
        "cecVersion": "Version 2.0"
        "logicalAddress": 4,
        "physicalAddress": "a.b.c.d",
        "arc": true,
        "autoLowLatencyMode": true
    }
]
```

`port` - the unique ID of the port.

`signal` - can be one of these enumerated values:
* "unknown" - the HDMI input port is not switched, so the signal state is presently unknown.
* "none" - no signal from the HDMI input device.
* "stable" - good signal.
* "unstable" - the signal is unstable and could exhibit broken audio and video.
* "unsupported" - the signal is not at a supported speed/resolution.

`osdName` - the display name of the HDMI input device.

`cecVersion` - the version of the CEC protocol advertised by the HDMI input device, can be one of:
* "" - unknown version
* "Version 1.3a"
* "Version 1.4" - Version 1.4, 1.4a or 1.4b.
* "Version 2.0"
``

**NOTE**: is it useful (or even possible) to know if a port does not support cec, arc, or allm?


## 5. Low Latency Mode
A property named `HDMIInput.lowLatencyMode`, with a getter, setter, and notification subscriber.

Enabling this property turns on the underlying low latency mode feature.
Low latency mode switches the device to shorten the overall processing time of HDMI A/V signals.
Depending on the platform some video processing features may be dropped such as MPEG noise reduction.

### 5.1. Low Latency Mode Notification
Whenever the underlying HDMI implementation executes an LLM change (either on or off), this notification must fire:

`HDMIInput.onLowLatencyModeChanged`

payload:

```json
  {
      "lowLatencyMode": true
  }
```

`lowLatencyMode` - whether or not LLM is enabled.

## 6. Auto Low Latency Mode Notification
When a HDMIInput.devices() property named `autoLowLatencyMode` changes then this notification must fire:

`HDMIInput.onDeviceAutoLowLatencyModeChanged`

payload:

```json
  {
      "autoLowLatencyMode": true,
      "port": "HDMI1"
  }
```

`autoLowLatencyMode` - whether or not ALLM is signalled on the port from the HDMI input device.

`port` - the HDMI port that detected a change to ALLM signalling.

**NOTE** Add events for signal and osdName

## 7. Auto Low Latency Mode Support
The property `HDMIInput.ports() autoLowLatencyModeSupport` reflects the HDMI port setting for advertising ALLM support in its E-EDID.

Changing this property turns on/off the underlying auto low latency mode advertisement in any HDMI port E-EDID of version >= v2.0.

To change the property:

```javascript
function setPortAutoLowLatencyMode(port: string, autoLowLatencyMode: boolean)
```

### 7.1. Auto Low Latency Mode Support Changed Notification
**NOTE** Is this needed, if there is a change notify for HDMIInputs.devices() ?

Whenever the underlying HDMI implementation executes an ALLM support change (either on or off), this notification must fire:

`HDMIInput.onPortAutoLowLatencyModeChanged`

payload:

```json
  {
      "autoLowLatencyMode": true,
      "port": "HDMI1"
  }
```

`autoLowLatencyModeSupport` - whether or not ALLM is advertised as supported in the E-EDID for the port.

`port` - the HDMI port that had an E-EDID ALLM advertisement change.

## 8. HDMI CEC Events
AS has a very basic model compared to the HDMI 2.1 spec...

i'm thinking we want a specific event for each CEC message, so that we can define separate schemas for the operands of each message.

More to come... but maybe not top priority?

CEC relates to both HDMIInput and HDMIOutput, because CEC is a bus mechanism where all devices share the same command set.

Should we have 3 Firebolt APIs: HDMIInput, HDMIOutput, HDMICEC?

JL> I think splitting Input & Output is a great idea, as it removes a likely source of momentary confusion / headaches for our users
JL> Is there such a thing as a port that is both an input and output port on the same device? If so, is this ARC, or different, or both?
JL> for CEC, don't the devices attached to input ports send most commands, and devices attached to output ports receive them?
JL> I suppose if that is true, we can still have it all in the HDMICEC module, so i'm fine with three modules (and we can always do four if need be)
JL> Proposal: remove CEC so we can upgrade the status of this doc to Candidate Spec and get feedback

TODO: split output & input APIs into separate docs
TODO: do we need to do output requirements now, or can we do them later?

Source LA = logical address, 4-bit unsigned int
Destination LA is omitted, but could be directly addressed to device or broadcast.

```
// CEC control, mapped from Thunder event notifications
* onCECEnabled
* onWakeupFromStandby - needs some thought because of interaction with standby mode

// CEC incoming messages, mapped from Thunder event notifications
* onActiveSource [Source LA], [Physical Address]
* onInactiveSource [Source LA], [Physical Address]
* onImageViewOn [Source LA]
* onTextViewOn [Source LA]
* onReportAudioStatus ?? or through DisplaySettings??
* onFeatureAbort [Source LA], [Dest LA], [Feature Opcode], [Abort Reason]
* onStandby [Source LA]
* ...

// CEC incoming messages, handled internally by Thunder today, but could be exposed up to app if we modify Thunder API
* onLogicalAddress [Source LA], [Physical Address], [Device Type]
* onSetOSDName [Source LA], [ASCII up to 14 chars]
* onCECVersion [Source LA], [CEC Version]
* onDeviceVendorID [Source LA], [Vendor ID]
* onReportPowerStatus [Source LA], [Power Status]
```

## 9. CEC Commands

```
// Commands mapped from Thunder API
* getActiveRoute
* 

// New commands coming as part of HDMI ARC volume control press-and-hold functionality
    * sendUserControlPressed [Dest LA], [UI Command]
    * sendUserControlReleased [Dest LA], [UI Command]
```