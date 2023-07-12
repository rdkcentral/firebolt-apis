# HDMI

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
- [3. HDMI Ports](#3-hdmi-ports)
- [4. HDMI Inputs](#4-hdmi-inputs)
- [5. Low Latency Mode](#5-low-latency-mode)
  - [5.1. Auto Low Latency Mode](#51-auto-low-latency-mode)
- [6. CEC Events](#6-cec-events)

## 3. HDMI Ports
List HDMI ports. All attributes are imlpicit to the port, and the input signal has no effect on these values.

```json
[
    {
        "port": "HDMI1",
        "title": "PlayStation 4",
        "available": true,
        "version": "2.1",
        "cec": true,
        "arc": true,
        "autoLowLatencyMode": true
    }
]
```

## 4. HDMI Inputs
List HDMI inputs. All attributes are the cross product of the port the input is plugged into and the input device itself.

Most frequent opperations will leverage HDMI.inputs(), but occaisionaly it might be useful to use HDMI.ports, e.g. to let the user know that they plugged their Soundbar into the wrong port.

```json
[
    {
        "port": "HDMI1",
        "title": "PlayStation 4",
        "version": "2.0",
        "cec": true,
        "arc": true,
        "autoLowLatencyMode": true
    }
]
```

Input.version is the negotiated version between the conntected device and the port.
Input.cec, arc, and autoLowLatency are true only if both the connected device and the port support them.

**NOTE**: is it useful (or even possible) to know if a port does not support cec, arc, or allm?

## 5. Low Latency Mode
A property named `HDMI.lowLatencyMode`, with a getter, setter, and notification subscriber.

Changing this property turns on the underlying low latency mode feature.

When this property changes, the notification should also fire to all listening apps.

**NOTE**: is the low latency mode only supported by HDMI? (not talking ALLM, just manual LLM).

### 5.1. Auto Low Latency Mode
Whenever the underlying HDMI implementation executes an ALLM (either on or off), this notification must fire:

`HDMI.onLowLatencyModeChanged`

payload:

```json
  {
      "lowLatencyMode": true,
      "reason": "auto",
      "port": "HDMI1"
  }
```

`lowLatencyMode` - whether or not llm is enabled.
`reason` - whether this change was done via an ALLM message over HDMI, or some other manual means. ('auto' or 'manual')
`port` - the HDMI port that sent the ALLM if reason is 'auto'

## 6. CEC Events
Not quite clear to me which CEC events need to bubble up to the Firebolt layer, and which ones should be silently handled by RDK. need more research, perhaps a separate working group...

i'm thinking we want a specific event for each CEC message, so that we can define separate schemas for the operands of each message.

More to come... but maybe not top priority?

