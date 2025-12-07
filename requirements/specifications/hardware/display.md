# Display

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor | Organization |
| ----------- | ------------ |
| Joe Martin  | Comcast      |

## 1. Overview

Content partners want to be able to get various details of the device's connected display, including its supported video modes, optimal/native resolution and physical dimensions.  These properties provide content partners with greater insight into the video capabilities of their users.

Partners also want an API that provides consistent behavior regardless of whether the display is internal or externally connected (e.g., via HDMI).

### 1.1. User Stories

As an app, I want to...

- Get the physical dimensions of the display, in centimeters
- Get the advertised video modes supported by the display
- Get the maximum HDCP version supported by the display
- Get the native/optimal resolution of the display, in pixels
- Get the colorimetry values supported by the display
- Get the raw EDID/DisplayID value from the display
- Get whether filmmaker mode is supported by the display

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
- [2. Table of Contents](#2-table-of-contents)
- [3. Constants, Types, and Schemas](#3-constants-types-and-schemas)
  - [3.1. HDCP Versions](#31-hdcp-versions)
- [4. Display Support](#4-display-support)
  - [4.1. Display Size](#41-display-size)
  - [4.2. Colorimetry](#42-colorimetry)
  - [4.3. Native Resolution](#43-native-resolution)
  - [4.4. Video Modes Supported](#44-video-modes-supported)
  - [4.5. Filmmaker Mode Support](#45-filmmaker-mode-support)
  - [4.6. Maximum HDCP Version](#46-maximum-hdcp-version)
  - [4.7. EDID/DisplayID](#47-ediddisplayid)

## 3. Constants, Types, and Schemas

### 3.1. HDCP Versions

The Firebolt `Media` module **MUST** have an `HdcpVersion` enumeration:

| Name  | Description |
| ----- | ----------- |
| `1.4` | HD          |
| `2.2` | 4K          |
| `2.3` | 8K          |

## 4. Display Support

Apps need to know various capabilties of the currently connected or built-in display.

These will be surfaced in the `Display` module.

### 4.1. Display Size

The `Display` module **MUST** have a `size` method that returns a `Types.Dimensions` object describing the physical width and height of the connected (or built-in) display, in centimeters.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.size()
//> { "width": 157, "height": 91 }
```

### 4.2. Colorimetry

The `Display` module **MUST** have a `colorimetry` method that returns an array of `Media.Colorimetry` values describing the supported colorimetry values of the connected (or built-in) display.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.colorimetry()
//> ["BT2020RGB", "BT2020YCC", "xvYCC601", "xvYCC709"]
```

### 4.3. Native Resolution

The `Display` module **MUST** have an `nativeResolution` method that returns a `Types.Dimensions` object describing the `width` and `height` of the connected (or built-in) display's native resolution as numbers, in pixels.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.nativeResolution()
//> { "width": 1920, "height": 1080 }
```

### 4.4. Video Modes Supported

The `Display` module **MUST** have a `videoModes` method that returns an array of `Media.VideoMode` values describing the video modes supported by the connected (or built-in) display.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.videoModes()
//> ["720p50", "720p60", "1080p50", "1080p60"]
```

### 4.5. Filmmaker Mode Support

The `Display` module **MUST** have a `filmmakerMode` method that returns a boolean denoting whether or not filmmaker mode is supported by the connected (or built-in) display.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.filmmakerMode()
//> true
```

### 4.6. Maximum HDCP Version

The `Display` module **MUST** have a `maxHdcpVersion` method that returns a `Media.HdcpVersion` value denoting the maximum HDCP version supported by the connected (or built-in) display.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.maxHdcpVersion()
//> "2.2"
```

### 4.7. EDID/DisplayID

The `Display` module **MUST** have a `edid` method that returns a hex string denoting the EDID/DisplayID of the connected (or built-in) display.

If no display is present, a JSON-RPC error response of `{"code": -40400, "message": "No display connected"}` **MUST** be returned.

Access to this method **MUST** require the `use` role of the `xrn:firebolt:capability:display:info` capability.

```javascript
Display.edid()
//> "00ffffffffffff00061044a000000000241d..."
```
