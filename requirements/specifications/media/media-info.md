# Media Info Requirements

Document Status: Candidate Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Anthony Borzota | Comcast        |
| Jeremy LaCivita | Comcast        |
| Stuart Harris   | Sky            |
| Joe Martin      | Comcast        |
| Farhan Mood     | Liberty Global |

## 1. Overview

App developers need to know which audio and video formats can be successfully played on a Firebolt device and its attached display.

An audio format includes values such as the audio container, codec, codec level, and bit rate of the audio stream.

A video format may include values such as the video container, codec, HDR profile, and resolution of the video stream.

Further, apps may also need to know about the media format currently playing in the media pipeline.

An app may need to check IP video playback that it has initiated to see if Dolby Audio is in fact active (as opposed to just present in the encoded data) in order to display metadata or badges to the user. Apps may also be playing [user-cultivated media](./media-access.md), and therefore have no metadata about the format of the files.

A first-party app may need to check all [Media Pipelines](./media-pipeline.md) for media format characteristics to display a global badge.

Additionally, apps may need to know what is supported by the device, *before* initiating any media playback.

To solve this, Firebolt APIs will be created to detect the formats and codecs currently being decoded by the [Media Pipeline](./media-pipeline.md).  Firebolt APIs will also be created to query whether the device supports playing content of various formats.

### 1.1. User Stories

#### 1.1.1. As an OTT App developer

I want to know what is supported by the device and it's active AV chain:

- I want to know if a video or audio format (Dolby Vision, Dolby Atmos, HEVC, etc.) will work if playback is attempted.
- I want to know if a format profile or level (HEVC Main 10, VP9 Profile 2, etc.) is supported.
- I want to know how many audio output channels (e.g. 7.1, 5.1) are available.
- I want to know what resolutions and frame rates are supported (e.g. 1080p60).

I want to know what kind of content I'm currently playing:

- I want to know which video or audio format the media I'm currently playing is sending to the decoder.
- I want to know which video or audio format profile or level the media I'm currently playing is being sent to the decoder.
- I want to know how many audio output channels (e.g. 7.1, 5.1) are currently being sent to the decoder.
- I want to know what resolution and frame rate is currently being sent to the decoder.

#### 1.1.2. As a first-party App developer

I want to show an audio/videophile overlay with detailed information:

- I want to know all video or audio formats that are currently being sent to a decoder.
- I want to know all video or audio format profiles/levels currently being sent to a decoder.
- I want to know all audio output channel profiles (e.g. 7.1, 5.1) currently being sent to a decoder.
- I want to know all resolution and framerates currently being sent to a decoder.

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
    - [1.1.1. As an OTT App developer](#111-as-an-ott-app-developer)
    - [1.1.2. As a first-party App developer](#112-as-a-first-party-app-developer)
- [2. Table of Contents](#2-table-of-contents)
- [3. Media Constants and Schemas](#3-media-constants-and-schemas)
  - [3.1. Media Container Types](#31-media-container-types)
  - [3.2. Media Codecs](#32-media-codecs)
  - [3.3. Resolutions](#33-resolutions)
  - [3.4. Resolution User-Friendly Name](#34-resolution-user-friendly-name)
  - [3.5. Video Modes](#35-video-modes)
  - [3.6. Media HDR Profiles](#36-media-hdr-profiles)
  - [3.7. Colorimetry](#37-colorimetry)
  - [3.8. Audio Output Mode](#38-audio-output-mode)
- [4. Device Media Support](#4-device-media-support)
  - [4.1. Video Format Supported](#41-video-format-supported)
  - [4.2. Audio Format Supported](#42-audio-format-supported)
- [5. Display Properties](#5-display-properties)
  - [5.1. Supported HDR Profiles](#51-supported-hdr-profiles)
  - [5.2. Color Depth](#52-color-depth)
  - [5.3. Display Size](#53-display-size)
  - [5.4. Display Resolution](#54-display-resolution)
  - [5.5. Display Resolution Name](#55-display-resolution-name)
  - [5.6. Refresh Rate](#56-refresh-rate)
  - [5.7. Colorimetry](#57-colorimetry)
  - [5.8. Manufacturer](#58-manufacturer)
  - [5.9. Product Name](#59-product-name)
  - [5.10. Source Physical Address](#510-source-physical-address)
- [6. Device Properties](#6-device-properties)
  - [6.1. Current Audio Mode](#61-current-audio-mode)
  - [6.2. Current Video Mode](#62-current-video-mode)
  - [6.3. Supported Video Modes](#63-supported-video-modes)
  - [6.4. Video Resolution](#64-video-resolution)
  - [6.5. Current HDR Profile](#65-current-hdr-profile)
  - [6.6. Supported HDR Profiles](#66-supported-hdr-profiles)
  - [6.7. Supported HDCP Version](#67-supported-hdcp-version)
  - [6.8. Source Frame Rate Used](#68-source-frame-rate-used)
  - [6.9. On Audio Output Changed](#69-on-audio-output-changed)
  - [6.10. On Video Output Changed](#610-on-video-output-changed)
- [7. Media Info](#7-media-info)
  - [7.1. MediaInfo for Current App](#71-mediainfo-for-current-app)
    - [7.1.1. Video Format](#711-video-format)
    - [7.1.2. Audio Format](#712-audio-format)
  - [7.2. Global MediaInfo](#72-global-mediainfo)
    - [7.2.1. Active Video Formats](#721-active-video-formats)
    - [7.2.2. Active Audio Formats](#722-active-audio-formats)

## 3. Media Constants and Schemas

### 3.1. Media Container Types

The Firebolt `Media` module **MUST** have an `AudioContainer` enumeration of the following media container content types:

| Name         | Description                                                                                                                    |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------ |
| `audio/mp4`  | [MP4 Audio](https://developer.mozilla.org/en-US/docs/Web/Media/Formats/Containers#mpeg-4_mp4)                                  |
| `audio/mpeg` | [Moving Picture Experts Group (MPEG1/MPEG2)](https://developer.mozilla.org/en-US/docs/Web/Media/Formats/Containers#mpegmpeg-2) |
| `audio/ogg`  | [OGG](https://developer.mozilla.org/en-US/docs/Web/Media/Formats/Containers#ogg)                                               |
| `audio/webm` | [Web Media](https://developer.mozilla.org/en-US/docs/Web/Media/Formats/Containers#webm)                                        |

The Firebolt `Media` module **MUST** have a `VideoContainer` enumeration of the following media container content types:

| Name         | Description                                                                                                                    |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------ |
| `video/mp2t` | [MPEG transport stream](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types)              |
| `video/mp4`  | [MP4 Audio](https://developer.mozilla.org/en-US/docs/Web/Media/Formats/)                                                       |
| `video/mpeg` | [Moving Picture Experts Group (MPEG1/MPEG2)](https://developer.mozilla.org/en-US/docs/Web/Media/Formats/Containers#mpegmpeg-2) |
| `video/webm` | [Web Media](https://developer.mozilla.org/en-US/docs/Web/Media/Formats/Containers#webm)                                        |

### 3.2. Media Codecs

The Firebolt `Media` module **MUST** have an `AudioCodec` enumeration:

| Name     | Description                                    |
| -------- | ---------------------------------------------- |
| `aac`    | Advanced Audio Coding                          |
| `ac3`    | Dolby Digital / Dolby Audio Codec 3            |
| `ac4`    | Dolby Audio Codec 4                            |
| `dts-x`  | Digital Theater Systems X                      |
| `eac3`   | Dolby Digital Plus / Dolby Enhanced AC-3 / DD+ |
| `mpeg3`  | MPEG-1 Part 3 & MPEG-2 Part 3                  |
| `opus`   | IETF Opus                                      |
| `truehd` | Dolby TrueHD / MLP                             |
| `vorbis` | Xiph.org Vorbis                                |

The Firebolt `Media` module **MUST** have a `VideoCodec` enumeration:

| Name    | Description                          |
| ------- | ------------------------------------ |
| `av1`   | AOMedia Video 1                      |
| `avc`   | Advanced Video Coding (H.264)        |
| `hevc`  | High Efficiency Video Coding (H.265) |
| `mpeg1` | MPEG-1 Part 2 Visual                 |
| `mpeg2` | MPEG-2 Part 2 Visual                 |
| `vp8`   | Video Processor 8                    |
| `vp9`   | Video Processor 9                    |
| `vp10`  | Video Processor 10                   |

### 3.3. Resolutions

For the purposes of the Firebolt API, a `Resolution` shall be defined by two values: the width and height, in pixels.

For example, the resolution for a display may be defined as `[1920, 1080]`.

Any methods relating to a resolution (such as the supported resolution of a display or the output resolution of a device) **MUST** return two values: the width and height.

### 3.4. Resolution User-Friendly Name

The Firebolt `Media` module **MUST** have a `ResolutionName` enumeration:

| Class     | Applicable Resolutions |
| --------- | ---------------------- |
| `sd`      | `576p` and lower       |
| `hd`      | `720p`                 |
| `fhd`     | `1080p`                |
| `uhd`     | `2160` and higher      |
| `unknown` | unknown or no display  |

### 3.5. Video Modes

For the purposes of the Firebolt API, a `VideoMode` shall be defined as the shorthand vertical resolution and frame rate of video content.

The Firebolt `Media` module **MUST** have a `VideoMode` enumeration:

- `480i`
- `480p`
- `576i25`
- `576p50`
- `576p60`
- `720p50`
- `720p60`
- `1080i50`
- `1080i60`
- `1080p24`
- `1080p25`
- `1080p30`
- `1080p50`
- `1080p60`
- `2160p24`
- `2160p25`
- `2160p30`
- `2160p50`
- `2160p60`
- `4320p60`
- `unknown`

Any methods relating to the video mode (such as a device's video output mode) **MUST** return `Media.VideoMode` values.

### 3.6. Media HDR Profiles

The Firebolt `Media` module **MUST** have an `HDRProfile` enumeration:

- `dolbyVision`
- `hdr10`
- `hdr10plus`
- `hlg`
- `sdr`
- `unknown`

### 3.7. Colorimetry

The Firebolt `Media` module **MUST** have an `Colorimetry` enumeration:

- `BT2020cYCC`
- `BT2020RGB`
- `BT2020YCC`
- `DCI-P3`
- `ICtCp`
- `opRGB`
- `opYCC601`
- `sYCC601`
- `xvYCC601`
- `xvYCC709`
- `unknown`

### 3.8. Audio Output Mode

The Firebolt `Media` module **MUST** have an `AudioMode` enumeration:

- `auto`
- `mono`
- `none`
- `passthrough`
- `stereo`
- `surround`
- `unknown`

## 4. Device Media Support

Apps need to know what types of media support the device is capable of.

To facilitate this, the `Device` module will have a set of methods that return possible media capabilities supported by the current device configuration.

These values do not change without a settings change or a firmware update.

### 4.1. Video Format Supported

The `Device` module **MUST** have a `videoFormatSupported` API that returns `true` or `false` depending on whether the format specified is supported by the current device and its AV chain. This API **MUST** return `boolean`.

```javascript
const hdr10plusWithH265 = Device.videoFormatSupported(Media.VideoCodec.HEVC, {
  profile: "main10",
  hdr: Media.HDRProfile.HDR10_PLUS
})
//> true

const hdr10plusWithVP9 = Device.videoFormatSupported(Media.VideoCodec.VP9, {
  profile: "p2",
  hdr: Media.HDRProfile.HDR10_PLUS,
  resolution: [3840, 2160]
})
//> true
```

The `videoFormatSupported` API **MUST** have a required `codec` parameter with the type `Media.VideoCodec`.

The `videoFormatSupported` API **MUST** have an optional `info` parameter which **MUST** be an object with zero or more of the following properties:

| Property     | Type                   | Description                                                                                                   |
| ------------ | ---------------------- | ------------------------------------------------------------------------------------------------------------- |
| `container`  | `Media.VideoContainer` | The content container format                                                                                  |
| `hdr`        | `Media.HDRProfile`     | The HDR profile that support is being checked for                                                             |
| `level`      | `string`               | The codec level: <br>**hevc**: `4.1`, `4.2`, `5.0`, `5.1`<br>**vp9**:`3.0`, `3.1`, `4.0`, `4.1`, `5.0`, `5.1` |
| `profile`    | `string`               | The codec profile: <br>**hevc**: `main`, `high`, `main10`<br>**vp9**: `p0`, `p2`                              |
| `resolution` | `array`                | The resolution in width and height (e.g. `[1920, 1080]`) of the media content being requested                 |

> **NOTE**: A device supporting a particular HDR profile and resolution does not mean that the current display also supports that profile and resolution. See `Display.hdrProfiles()` for more info on detecting display HDR support.

The `videoFormatSupported` API **MUST NOT** return `true` unless the format specified is supported with **all** of the properties specified in `options` *at the same time*.

Use of the `videoFormatSupported` API requires access to the `use` role of the `xrn:firebolt:capability:device:info` capability.

### 4.2. Audio Format Supported

The `Device` module **MUST** have an `audioFormatSupported` API that returns `true` or `false` depending on whether the format specified is supported by the current device configuration and its AV chain. This API **MUST** return a `boolean`.

```javascript
const atmosWithAC4 = Device.audioFormatSupported(Media.AudioCodec.AC4, {
  atmos: true
})
//> true

const atmosWithTrueHD = Device.audioFormatSupported(Media.AudioCodec.TRUEHD, {
  atmos: true
})
//> true

const noAtmosOverMono = Device.audioFormatSupported(Media.AudioCodec.TRUEHD, {
  atmos: true
  mode: 'mono'
})
//> false (mono output not supported with dolby atmos)
```

The `audioFormatSupported` API **MUST** have a required `codec` parameter with the type `Media.AudioCodec`.

The `audioFormatSupported` API **MUST** have an optional `options` parameter which **MUST** be an object with zero or more of the following properties:

| Property       | Type              | Description                                                                |
| -------------- | ----------------- | -------------------------------------------------------------------------- |
| `atmos`        | `boolean`         | Whether or not Dolby Atmos support for the given format is being requested |
| `codecLevel`   | `string`          | The codec level                                                            |
| `codecProfile` | `string`          | The codec profile: <br>**aac**: `mp2lc`, `mp4he`                           |
| `container`    | `Media.Container` | The container format type                                                  |
| `sampleRate`   | `number`          | The sample rate being requested, in kHz                                    |

If the `options` parameter is provided, then the `audioFormatSupported` API **MUST NOT** return `true` unless the format specified is supported with **all** of the properties specified by `options` *all at the same time*.

As multiple audio output modes may be set at the same time, the response **MUST** be based on the best possible audio configuration supported by the device.  For instance, if the device is configured for stereo output (which cannot support Atmos) but the AV chain supports Surround 5.1 (which can support Atmos), the latter would be considered the best possible audio configuration and thus used as the basis for the decision.

Use of the `audioFormatSupported` API requires access to the `use` role of the `xrn:firebolt:capability:device:info` capability.

## 5. Display Properties

Apps need to know various aspects of the current (or built-in) display on a device.

These will be surfaced in a new `Display` module.

Access to these APIs is governed by the `xrn:firebolt:capability:display:info` capability.

### 5.1. Supported HDR Profiles

The `Display` module **MUST** have an `hdrProfiles` method that returns the display's supported HDR profiles as an array of `Media.HDRProfile` values.

If no display is present, an empty array is returned.

```javascript
Display.hdrProfiles()
//> ["dolbyVision", "hdr10", "hdr10plus", "hlg", "sdr"]
```

### 5.2. Color Depth

The `Display` module **MUST** have a `colorDepth` method that returns a numerical value.

If no display is present, a value of zero is returned.

```javascript
Display.colorDepth()
//> 10
```

### 5.3. Display Size

The `Display` module **MUST** have a `size` method that returns the width and height of the display, in centimeters.

If no display is present, a value of zero is returned for both the width and height.

```javascript
Display.size()
//> [157, 91]
```

### 5.4. Display Resolution

The `Display` module **MUST** have a `resolution` method that returns the width and height of the display's native resolution.

If no display is present, both returned values **MUST** be zero.

```javascript
Display.resolution()
//> [1920, 1080]
```

### 5.5. Display Resolution Name

The `Display` module **MUST** have a `resolutionName` method that returns a user-friendly name of the display's resolution as defined by `Media.ResolutionName`.

If no display is present, a value of `unknown` is returned.

```javascript
Display.resolutionName()
//> "uhd"
```

### 5.6. Refresh Rate

The `Display` module **MUST** have a `refreshRate` method that returns an number value for the optimal refresh rate that the display supports (in Hz).

If no display is present, a value of zero is returned.

```javascript
Display.refreshRate()
//> 120
```

### 5.7. Colorimetry

The `Display` module **MUST** have a `colorimetry` method that returns the display's supported colorimetry values as an array of `Media.Colorimetry` values.

If no display is present, an empty array is returned.

```javascript
Display.colorimetry()
//> ["BT2020RGB", "BT2020YCC", "xvYCC601", "xvYCC709"]
```

### 5.8. Manufacturer

The `Display` module **MUST** have a `manufacturer` method that returns the display's manufacturer.

If no display is present, an empty string is returned.

```javascript
Display.manufacturer()
//> "Samsung Electric Company"
```

### 5.9. Product Name

The `Display` module **MUST** have a `productName` method that returns the display's product name / model number.

If no display is present, an empty string is returned.

```javascript
Display.productName()
//> "Q80A"
```

### 5.10. Source Physical Address

The `Display` module **MUST** have a `sourcePhysicalAddress` method that returns the display's source physical address.

If no display is present, an empty string is returned.

```javascript
Display.sourcePhysicalAddress()
//> "3.0.0.0"
```

## 6. Device Properties

Apps need to know various aspects of the device, including its media playing capabilities.

These will be surfaced in the `Device` module.

Access to these APIs is governed by the `xrn:firebolt:capability:device:info` capability.

### 6.1. Current Audio Mode

The `Device` module **MUST** include an `audioMode` API that returns the currently configured audio output mode on the device.

The API **MUST** return a value from the `Media.AudioMode` enum.

### 6.2. Current Video Mode

The `Device` module **MUST** have a `videoMode` method that returns the current video modes used by the device.

This method **MUST** return a value from the `Media.VideoMode` enum.

If no display is present, a value of `unknown` is returned.

```javascript
Device.videoMode()
//> 1080p60
```

### 6.3. Supported Video Modes

The `Device` module **MUST** have a `videoModes` method that returns an array of valid video modes that the device and display together support.

This method **MUST** return an array with one or more values from the `Media.VideoMode` enum.

```javascript
Device.supportedVideoModes()
//> ["720p50", "720p60", "1080p50", "1080p60"]
```

### 6.4. Video Resolution

The `Device` module **MUST** have a `videoResolution` method that returns the width and height of the current video output resolution.

If no display is present, both returned values **MUST** be zero.

```javascript
Device.videoResolution()
//> [1920, 1080]
```

### 6.5. Current HDR Profile

The `Device` module **MUST** have a `hdrProfile` method that returns the HDR profile currently used by the device for video output.

This method **MUST** return a value from the `Media.HDRProfile` enum.

```javascript
Device.hdrProfile()
//> "hdr10plus"
```

### 6.6. Supported HDR Profiles

The `Device` module **MUST** have an `hdrProfiles` method that returns the HDR profiles that the device supports, regardless of any connected display.

```javascript
Device.hdrProfile()
//> ["hdr10", "hdr10plus", "hlg", "sdr"]
```

### 6.7. Supported HDCP Version

The `Device` module **MUST** have a `hdcpVersion` method that returns the latest HDCP version supported by the device.

This method **MUST** return a value such as:

- `1.4`
- `2.2`
- `unknown`

```javascript
Device.hdcpVersion()
//> "2.2"
```

### 6.8. Source Frame Rate Used

The `Device` module **MUST** have a boolean `sourceFrameRateUsed` API.

This API **MUST** return `true` if the HDMI output frame rate is set to follow the video source's frame rate.

Otherwise, this API **MUST** return `false`.

```javascript
Device.sourceFrameRateUsed()
//> true
```

### 6.9. On Audio Output Changed

The `Device` module **MUST** have an `onAudioOutputChanged` event API.

This event must notify listeners when any of the following properties have changed:

- `Device.audioMode`

> TODO: Add more here

This API **MUST** return the current property values of the above.

```javascript
Device.onAudioOutputChanged()
//> {
//>   "audioMode": "stereo"
//> }
```

### 6.10. On Video Output Changed

The `Device` module **MUST** have an `onVideoOutputChanged` event API.

This event must notify listeners when any of the following properties have changed:

- `Device.hdrProfile`
- `Device.sourceFrameRateUsed`
- `Device.videoMode`

This API **MUST** return the current property values of the above.

```javascript
Device.onAudioOutputChanged()
//> {
//>   "hdrProfile": "hlg",
//>   "sourceFrameRateUsed": false,
//>   "videoMode": "1080p60",
//> }
```

## 7. Media Info

The Firebolt `MediaInfo` module consists of APIs to get information about any media actively being decoded by the Media Pipeline or an active HDMI input.

### 7.1. MediaInfo for Current App

Apps need a way to query the media info for media currently being played by the app. All of the following methods take a single `pipeline` parameter, which identifies the Media Pipeline in the current app's scope that is being queried, e.g.:

```javascript
MediaInfo.videoFormat(1) // return the video format in the current app's media pipeline 1
MediaInfo.videoFormat(2) // return the video format in the current app's media pipeline 2
```

**TODO**: where do we map video tags to ids? need a spec for this? same spec, new spec?
JL: i linked to the Media Pipeline spec and merged it into this branch... we should review.

The `pipeline` parameter is required for the JSON-RPC request, however, the Firebolt SDK **SHOULD** provide a default value of `1` if not provided by the calling app.

For example, the following would query the video format for the app's pipeline `1` in JavaScript (which supports default values for parameters).

```javascript
MediaInfo.videoFormat()
```

#### 7.1.1. Video Format

The `MediaInfo` module **MUST** have a `videoFormat` API that returns an `object` with the video codec (e.g. `avc`, `vp9`, etc.) and resolution of the media currently in the media pipeline (either playing or paused).

The `videoFormat` result **MUST** have an `pipelineId` integer property that denotes the media pipeline/session ID.

The `videoFormat` result **MUST** have a `codec` property with one of the values from the `Media.VideoCodec` enum.

The `videoFormat` result **MUST** have an `hdr` array property with zero or more `Media.HDRProfile` values.

If a value is included in the `hdr` array then the media currently in the media pipeline **MUST** include the denoted HDR metadata in the decoded video.

The `videoFormat` result **MUST** have a `resolution` property with a `Media.Dimensions` value.

The `videoFormat` result **MAY** have a `codecProfile` string property that denotes the profile of the codec.

The `videoFormat` result **MAY** have a `codecLevel` string property that denotes the level of the codec.

The `videoFormat` API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onVideoFormatChanged` notification.

Use of the `videoFormat` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:video-format` capability.

```javascript
MediaInfo.videoFormat(1)
/*
{
  "pipelineId": 1,
  "codec": "hevc",
  "codecLevel": "4.2",
  "codecProfile": "main",
  "container": "video/mp4",
  "frameRate": 30,
  "hdr": [
    "hdr10"
  ],
  "resolution": [
    1920,
    1080
  ]
}
*/
```

#### 7.1.2. Audio Format

The `MediaInfo` module **MUST** have a `audioFormat` API that returns an `object` with the below values describing media currently in the media pipeline (either playing or paused).

The `audioFormat` result **MUST** have an `pipelineId` integer property that denotes the media pipeline/session ID.

The `audioFormat` result **MUST** have a `biteRate` number property that denotes the audio bit rate.

The `audioFormat` result **MUST** have a `channels` string property that denotes the audio output channels.

The `audioFormat` result **MUST** have a `codec` property with one of the values from the `Media.AudioCodec` enum.

The `audioFormat` result **MUST** have a `sampleRate` number property that denotes the audio sample rate.

The `audioFormat` result **MAY** have a `codecLevel` string property that denotes the level of the codec.

The `audioFormat` result **MAY** have a `codecProfile` string property that denotes the profile of the codec.

The `audioFormat` API **MUST** be a Firebolt `property:readonly` API, and have a corresponding `onAudioFormatChanged` notification.

Use of the `audioFormat` APIs require access to the `use` role of the `xrn:firebolt:capability:media-info:audio-format` capability.

```javascript
MediaInfo.audioFormat(1)
/*
{
  "pipelineId": 1,
  "bitRate": 128,
  "channels": 2,
  "codec": "aac",
  "container": "audio/mp4",
  "sampleRate": 48
}
*/
```

### 7.2. Global MediaInfo

First party apps need a way to query which media formats are currently being output to the [media pipeline](./media-pipeline.md), without caring about which pipeline.

#### 7.2.1. Active Video Formats

The `MediaInfo` module **MUST** have a `activeVideoFormats` API that returns an array of `objects` for all media currently in the media pipeline (either playing or paused).

Each item in the `activeVideoFormats` result array **MUST** conform to the same requirements as the individual results from the [`videoFormat` API](#611-video-format).

Additionally, the `MediaInfo` module **MUST** have an `onActiveVideoFormatsChanged` notifier that fires whenever any pipeline starts, stops, or changes its current video format.

Example:

```javascript
MediaInfo.activeVideoFormats().find(f => f.codec === Media.VideoCodec.HEVC)
/*
[
  {
    "id": 1,
    "codec": "hevc",
    "codecLevel": "4.2",
    "codecProfile": "main",
    "container": "video/mp4",
    "frameRate": 30,
    "hdr": [
        "hdr10"
    ],
    "resolution": [
        1920,
        1080
    ]
  }
]
*/
```

Access to these APIs is gated by `manage` access to the `xrn:firebolt:capability:media-info:video-format` capability.

#### 7.2.2. Active Audio Formats

The `MediaInfo` module **MUST** have a `activeAudioFormats` API that returns an array of `objects` for all media currently in the media pipeline (either playing or paused).

Each item in the `activeAudioFormats` result array **MUST** conform to the same requirements as the individual results from the [`audioFormat` API](#612-audio-format).

Additionally, the `MediaInfo` module **MUST** have an `onActiveAudioFormatsChanged` notifier that fires whenever any pipeline starts, stops, or changes its current audio format.

Example:

```javascript
MediaInfo.activeAudioFormats().find(f => f.codec === Media.AudioCodec.AAC)
/*
[
  {
    "id": 1,
    "bitRate": 128,
    "channels": 2,
    "codec": "aac",
    "container": "audio/mp4",
    "sampleRate": 48
  }
]
*/
```

Access to these APIs is gated by `manage` access to the `xrn:firebolt:capability:media-info:audio-format` capability.
