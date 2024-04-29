# Media Info Requirements

Document Status: Candidate Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Anthony Borzota | Comcast        |
| Jeremy LaCivita | Comcast        |
| Stuart Harris   | Sky            |
| Farhan Mood     | Liberty Global            |

## 1. Overview
App developers need to know which audio and video formats can be successfully played on a Firebolt device.

Video formats include...

**TODO**: Rewrite this section.
**TODO**: check Farhan's emails!!

Apps may need to know what media format, e.g. HDR profile or video codec, is currently playing.

An app may need to check IP video playback that it has initiated to see if Dolby Audio is in fact active (as opposed to just present in the encoded data) in order to display metadata or badges to the user. Apps may also be playing [user-cultivated media](./media-access.md), and therefor have no metadata about the format of the files.

A first-party app may need to check all [Media Pipelines](./media-pipeline.md) for media format characteristics to display a global badge.

Additionally, apps may need to know what is supported by the device, *before* initiating any media playback.

As a W3C-based platform, there is no standard API for detecting media
formats or codecs that works in all cases, short of inspecting the bytes
of the media in the app itself.

To solve this, Firebolt APIs will be created to detect the formats and
codecs currently being decoded by the [Media
Pipeline](./media-pipeline.md) and Firebolt APIs will be created to query device support for those formats.

### 1.1. User Stories

### 1.2. As an OTT App developer

I want to know what is supported by the device and it's active AV chain:

- I want to know if a video or audio format (Dolby Vision, Dolby Atmos, HEVC, etc.) will work if playback is attempted.
- I want to know if a format profile or level (HEVC Main 10, VP9 Profile 2, etc.) is supported.
- I want to know how many audio output channels (e.g. 7.1, 5.1) are available.
- I want to know what resolutions and framerates are supported (e.g. 1080p60).

I want to know what kind of content I'm currently playing:

- I want to know which video or audio format the media I'm currently playing is sending to the decoder.
- I want to know which video or audio format profile or level the media I'm currently playing is sending to the decoder.
- I want to know how many audio output channels (e.g. 7.1, 5.1) are currently being sent to the decoder.
- I want to know what resolution and framerate is currently being sent to the decoder.

### 1.3. As a first-party App developer

I want to show an audio/videophile overlay with detailed information:

- I want to know all video or audio formats that are currently being sent to a decoder.
- I want to know all video or audio format profiles/levels currently being sent to a decoder.
- I want to know all audio output channel profiles (e.g. 7.1, 5.1) currently being sent to a decoder.
- I want to know all resolution and framerates currently being sent to a decoder.

I want to know what my device *would* support if i upgraded my AV peripherals:

- I want to know if a video or audio format (Dolby Vision, Dolby Atmos, HEVC, etc.) *would* work with upgraded peripherals.
- I want to know if a codec profile-level (HEVC Main 10, VP9 Profile 2, etc.) *would* work with upgraded peripherals.
- I want to know how many audio output channels (e.g. 7.1, 5.1) *would* be available with upgraded peripherals.
- I want to know what resolutions and framerates *would* be supported with upgraded peripherals. (e.g. 1080p60).

## 2. Table of Contents
- [Media Info Requirements](#media-info-requirements)
  - [1. Overview](#1-overview)
    - [1.1. User Stories](#11-user-stories)
    - [1.2. As an OTT App developer](#12-as-an-ott-app-developer)
    - [1.3. As a first-party App developer](#13-as-a-first-party-app-developer)
  - [2. Table of Contents](#2-table-of-contents)
  - [3. Format MimeTypes](#3-format-mimetypes)
  - [Resolutions](#resolutions)
  - [4. Device Media Support](#4-device-media-support)
    - [4.1. Negotiated Media Support](#41-negotiated-media-support)
      - [4.1.1. Video Format Supported](#411-video-format-supported)
      - [4.1.2. Audio Format Supported](#412-audio-format-supported)
      - [4.2.3. Hdr Supported](#423-hdr-supported)
  - [5. Display Properties](#5-display-properties)
    - [5.1. Color Information...](#51-color-information)
    - [5.2. Display Width and Height](#52-display-width-and-height)
    - [5.3. Current and Optimal Resolution](#53-current-and-optimal-resolution)
    - [5.4. Supported Resolutions](#54-supported-resolutions)
    - [5.5. Device Supported Resolutions](#55-device-supported-resolutions)
    - [5.7. Use Source Framerate](#57-use-source-framerate)
  - [6. Audio Output Properties](#6-audio-output-properties)
    - [6.1. Mode](#61-mode)
  - [7. Media Info](#7-media-info)
    - [7.1. MediaInfo for current app](#71-mediainfo-for-current-app)
      - [7.1.1. Video Format](#711-video-format)
      - [7.1.2. Audio Format](#712-audio-format)
    - [7.2. Global MediaInfo](#72-global-mediainfo)
      - [7.2.1. Active Video Formats](#721-active-video-formats)
      - [7.2.2. Active Audio Formats](#722-active-audio-formats)

## 3. Format MimeTypes
The Firebolt `Media` module **MUST** have a `Formats` enumeration audio and video formats:

| Name             | Value                  | Notes |
| ---------------- | ---------------------- |------ |
| `AUDIO_AAC`      | `audio/mp4a-latm`      |
| `AUDIO_AC3`      | `audio/ac3`            |
| `AUDIO_AC4`      | `audio/ac4`            |
| `AUDIO_DOLBY_MAT`| `audio/vnd.dolby.mat`  | on-device format |
| `AUDIO_DTS`      | `audio/vnd.dts`        |
| `AUDIO_DTS_X`    | `audio/vnd.dts.uhd;profile=p2` |
| `AUDIO_EAC3`     | `audio/eac3`           | Note we call this AC3+ in RDK... |
| `AUDIO_MPEG`     | `audio/mpeg`           |
| `AUDIO_MPEG1`    | `audio/mpeg-L1`        |
| `AUDIO_MPEG2`    | `audio/mpeg-L2`        |
| `AUDIO_MPEG4`    | `audio/mp4`            |
| `AUDIO_OPUS`     | `audio/opus`           |
| `AUDIO_OGG`      | `audio/ogg`            |
| `AUDIO_TRUEHD`   | `audio/true-hd`        |
| `AUDIO_WAV`      | `audio/wav`            |
| `VIDEO_AV1`      | `video/av01`           |
| `VIDEO_DOLBYVISION`| `video/dolbyVision`    |
| `VIDEO_H263`     | `video/3gpp`           |
| `VIDEO_H264`     | `video/avc`            |
| `VIDEO_H265`     | `video/hevc`           |
| `VIDEO_H265_M10` | `video/hevc;profile=main10`           |
| `VIDEO_MPEG`     | `video/mpeg`           |
| `VIDEO_VP8`      | `video/x-vnd.on2.vp8`  |
| `VIDEO_VP9`      | `video/x-vnd.on2.vp9`  |
| `VIDEO_VP9_P2`   | `video/x-vnd.on2.vp9;profile=p2`  |
| `VIDEO_VP10`     | `video/x-vnd.on2.vp10` |
| `VIDEO_VC1`      | `video/wvc1`           |
| `UNKNOWN`        | `unknown`              |
| `NONE`           | `none`                 |

**TODO**: remove ;profile= codecs

**TODO**: Atmos is not always MAT... MAT -> PCM version of Atmos. Can also be carried over AC4 EAC3, AC3+, DolbyTrueHD

## Resolutions
The `Display.Resolution` enum **MUST** have one of the following values:

- `"480i"`
- `"480p"`
- `"576i25"`
- `"576p50"`
- `"576p60"`
- `"720p50"`
- `"720p"`
- `"1080i50"`
- `"1080i"`
- `"1080p24"`
- `"1080p25"`
- `"1080p30"`
- `"1080p50"`
- `"1080p"`
- `UHD`         // convenience value for `2160p*`
- `"2160p24"`
- `"2160p25"`
- `"2160p30"`
- `"2160p50"`
- `"2160p60"`
- `"4320p60"`

## 4. Device Media Support
Apps need to know what types of media the device supports.

### 4.1. Negotiated Media Support
Apps need to know what types of media support the current *device configuration*,
e.g. a Firebolt STB connected to an HDMI television, is capable of.

To facilitate this, the `Device` module will have a set of methods that
return all possible values supported by the current device configuration.

These values change and different AV inputs are activated or connected.

#### 4.1.1. Video Format Supported

The `Device` module **MUST** have a `videoFormatSupported` API that returns
`true` or `false` depending on whether the format specified is supported by
the current device configuration. This API **MUST** return `boolean`.

```javascript
const hdr10plusWithH265 = videoFormatSupported(Media.Formats.VIDEO_H265_M10, { resolution: '1080p30' } )
const hdr10plusWithVP9 = videoFormatSupported(Media.Formats.VIDEO_VP9_P2)
```

**TODO**: clear this up:

When calling videoFormatSupported with a `resolution` parameter, then the Display support for that resolution is factored into the response.

The `videoFormatSupported` API **MUST** have an `options` parameter
which **MUST** be an object with zero or more of the following properties:

| Property | Type | Description |
|----------|------|-------------|
| codec    | `string` | the Codec |
| profile  | `string` | the Codec profile: <br>**h.265**: "main", "high", "main10"<br>**vp9**: "p0", "p2"<br>**AAC**: "mp2lc", "mp4he" |
| level    | `string`   | the Codec level: <br>**h.265**: "4.1", "4.2", "5.0", "5.1"<br>**vp9**:"3.0", "3.1", "4.0", "4.1", "5.0", "5.1" |
| atmos    | `boolean` | Whether or not Dolby Atmos support for the given format is being requested |
| resolution | `Display.Resolution` | The Resolution, e.g. `1080p` of the support being requested. |
| hdr      | HDRProfile | The HDR profile that support is being checked for. |

```javascript
videoFormatSupported('', {})
```

The `codec` property **MUST** be one of the following values:

- `VIDEO_AV1`
- `VIDEO_DOLBYVISION`
- `VIDEO_H263`
- `VIDEO_H264`
- `VIDEO_H265`
- `VIDEO_MPEG`
- `VIDEO_VP8`
- `VIDEO_VP9`
- `VIDEO_VP9_P2`
- `VIDEO_VP10`
- `VIDEO_VC1`

**TODO**: Add HDRProfile
**TODO**: Roku also has: Container

The `videoFormatSupported` API **MUST NOT**
return `true` unless the format specified is supported with **all** of the properties specified
by `options` *all at the same time*.

Use of the `videoFormatSupported` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

#### 4.1.2. Audio Format Supported

The `Device` module **MUST** have an `audioFormatSupported` API that returns
`true` or `false` depending on whether the format specified is supported by
the current device configuration. This API **MUST** return a `boolean`.

The `audioFormatSupported` API **MUST** have a required `format` parameter which
**MUST** be one of the following values:

- `AUDIO_AAC`
- `AUDIO_AC3`
- `AUDIO_AC4`
- `AUDIO_DOLBY_MAT`
- `AUDIO_DTS`
- `AUDIO_DTS_X`
- `AUDIO_EAC3`
- `AUDIO_MPEG`
- `AUDIO_MPEG1`
- `AUDIO_MPEG2`
- `AUDIO_MPEG4`
- `AUDIO_OPUS`
- `AUDIO_OGG`
- `AUDIO_TRUEHD`
- `AUDIO_WAV`

**NOTE**: MAT is decoded on the device, it's not a format you'd have encoded content on a CDN

```javascript
if (audioFormatSupported('AUDIO_AC4', { atmos: true })) {
  // show badges
}
```

The `audioFormatSupported` API **MUST** have an optional `options` parameter
which **MUST** be an object with zero or more of the following properties:

| Property | Type | Description |
|----------|------|-------------|
| profile  | `string` | the Codec profile: <br>**AAC**: "mp2lc", "mp4he" |
| level    | `string   | the Codec level. |
| atmos    | `boolean` | Whether or not Dolby Atmos support for the given format is being requested |
| channels | `int` | Required number of audio channels |
| sampleRate | `int` | The sample rate being requested. |
| mode     | `AudioOutput.Mode` | Specify which mode should be used to evaluate the request. Defaults to the current mode if not specified. |

**TODO**: Roku also has: Container, Bitrate

If the `options` parameter is provided, then the `audioFormatSupported` API **MUST NOT**
return `true` unless the format specified is supported with **all** of the properties specified
by `options` *all at the same time*.

Use of the `audioFormatSupported` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

#### 4.2.3. Hdr Supported
Device module...

## 5. Display Properties

Apps need to know various aspects of the current (or built in) display on a device.

These will be surfaced in a new `Display` module.

Access to these APIs is governed by the `xrn:firebolt:capability:display:info` capability.

### 5.1. Color Information...
Expose this so apps can check
BT2020 BT709

**TODO**: ^^

### 5.2. Display Width and Height

The `Display` module **MUST** have a `width` and `height` method that return the width and height of the display, in centimeters from the HDMI edid.

For built-in displays `width` and `height` **MUST** also be provided.

### 5.3. Current and Optimal Resolution

The `Display` module **MUST** have a `currentResolution` and  `optimalResolution` method that returns a valid resolution for either the current state of the display, or the displays optimal resolution value.

This method **MUST** return a value from the `Display.Resolution` enum.

The `optimalResolution` **MUST** come from the HDMI edid.

For built-in displays `optimalResolution` **MUST** also be provided.

### 5.4. Supported Resolutions

The `Display` module **MUST** have a `supportedResolutions` method that returns an array of valid resolutions that the display supports.

This method **MUST** return a value from the `Display.Resolution` enum.

### 5.5. Device Supported Resolutions
The `Device` module **MUST** have a `supportedResolutions` method that returns an array of valid resolutions that the device supports, regardless of any connected display.

This method **MUST** return an array with one or more of the following values from the `Display.Resolution` enum.

### 5.7. Use Source Framerate
The `Display` module **MUST** have a boolean `useSourceFrameRate` API.

This API **MUST** return `true` if the hdmi output frame rate is set to follow video source frame rate.

Otherwise, this API **MUST** return false.

## 6. Audio Output Properties
Apps need to know various aspects of the current (or built in) audio output system on a device.

These will be surfaced in a new `AudioOutput` module.

Access to these APIs is governed by the `xrn:firebolt:capability:audio-output:info` capability.

### 6.1. Mode
The `AudioOutput` module  **MUST** include a `mode` string API that returns an `AudioOutput.Mode` enum that is one of the following values:

- `AUTO`
- `SURROUND`
- `STEREO`
- `PASSTHROUGH`
- `UNKNOWN`
- `NONE`

## 7. Media Info

The Firebolt `MediaInfo` module consists of APIs to get information
about any media actively being decoded by the Media Pipeline or an active HDMI input.

### 7.1. MediaInfo for current app

Apps need a way to query the media info for media currently being played
by the app. All of the following methods take a single `pipeline`
parameter, which identifies the Media Pipeline in the current app's scope
that is being queried, e.g.:

```javascript
import { MediaInfo } from '@firebolt-js/sdk'

MediaInfo.videoFormat(1) // return the video codec in the current app's media pipeline 1
MediaInfo.videoFormat(2) // return the video codec in the current app's media pipeline 2
```

**TODO**: where do we map video tags to ids? need a spec for this? same spec, new spec?
JL: i linked to the Media Pipeline spec and merged it into this branch... we should review.

The `pipeline` parameter is required for the JSON-RPC request, however, the Firebolt SDK **SHOULD** provide a default value of `1` if it is not provided by the calling app.

For example:

```javascript
MediaInfo.videoCodec()
```

Would query the video codec for the app's pipeline `1` in JavaScript, which supports default values for parameters.

#### 7.1.1. Video Format

The `MediaInfo` module **MUST** have a `videoFormat` API that returns an `object` with the
video codec, e.g., H.265, VP9, etc., and resolution of the media currently in the
media pipeline (either playing or paused).

The `videoFormat` result **MUST** have a `type` property with one of the following values from the `Media.Formats` enum:

- `VIDEO_AV1`
- `VIDEO_DOLBYVISION`
- `VIDEO_H263`
- `VIDEO_H264`
- `VIDEO_H265`
- `VIDEO_H265_M10`
- `VIDEO_MPEG`
- `VIDEO_VP8`
- `VIDEO_VP9`
- `VIDEO_VP9_P2`
- `VIDEO_VP10`
- `VIDEO_VC1`
- `UNKNOWN`
- `NONE`

The `videoFormat` result **MUST** have an `hdr` array property with zero or more of the following values:

| Enumeration                   | Notes |
| ----------------------------- | ----- |
| `HDR_DOLBYVISION`             | Only true for the VIDEO_DOLBYVISION format  |
| `HDR_HDR10`                   | Any format that supports HDR10 metadata    |
| `HDR_HDR10PLUS`               | Any format that supports HDR10+ metadata   |
| `HDR_ST2084`                  | Any format that supports ST2084 color transfer |
| `HDR_HLG`                     | Any format that supports HLG color transfer |

If a value is included the `hdr` array then the media currently in the media pipeline **MUST** include the denoted HDR metadata in the decoded video.

The `videoFormat` result **MUST** have a `resolution` string property with one of the `Display.Resolution` values.

The `videoFormat` result **MAY** have a `profile` string property that denotes the profile of the codec.

The `videoFormat` result **MAY** have a `level` string property that denotes the level of the codec.

The `videoFormat` API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onVideoFormatChanged` notification.

Use of the `videoFormat` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:video-format` capability.

#### 7.1.2. Audio Format

The `MediaInfo` module **MUST** have a `audioFormat` API that returns an `object` with the
audio codec, e.g., AAC, AC3, etc., and sample rate of the media currently in the
media pipeline (either playing or paused).

The `audioFormat` result **MUST** have a `type` property with one of the following values from the `Media.Formats` enum:

- `AUDIO_AAC`
- `AUDIO_AC3`
- `AUDIO_AC4`
- `AUDIO_DOLBY_MAT`
- `AUDIO_DTS`
- `AUDIO_DTS_X`
- `AUDIO_EAC3`
- `AUDIO_MPEG`
- `AUDIO_MPEG1`
- `AUDIO_MPEG2`
- `AUDIO_MPEG4`
- `AUDIO_OPUS`
- `AUDIO_OGG`
- `AUDIO_TRUEHD`
- `AUDIO_WAV`


The `audioFormat` result **MUST** have a `channels` integer property that denotes the number of audio channels.

The `audioFormat` result **MUST** have a `sampleRate` integer property that denotes the audio sample rate.

The `audioFormat` result **MAY** have a `profile` string property that denotes the profile of the codec.

The `audioFormat` result **MAY** have a `level` string property that denotes the level of the codec.

The `audioFormat` API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioFormatChanged` notification.

Use of the `audioFormat` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:audio-format` capability.

### 7.2. Global MediaInfo

First party apps need a way to query which media formats are currently being output to the [media pipeline](./media-pipeline.md), without caring about which pipeline.

#### 7.2.1. Active Video Formats
The `MediaInfo` module **MUST** have a `activeVideoFormats` API that returns an array of `objects` with the video codec, e.g., H.265, VP9, etc., of the media currently in each media pipeline (either playing or paused).

Each item in the `activeVideoFormats` result array **MUST** conform to the same requirements as the indivual results from the [`videoFormat` API](#611-video-format).

Additionally, the `MediaInfo` module **MUST** have an `onActiveVideoFormatsChanged` notifier that fires whenever any pipeline starts, stops, or changes its current video format.

Example:

```typescript
const isDolbyVision:boolean = await MediaInfo.activeVideoFormats().find(f => f.type === Media.Formats.VIDEO_DOLBYVISION)

MediaInfo.activeVideoFormats((active) => {
  const dolbyVision = active.find(f => f.type === Media.Formats.VIDEO_DOLBYVISION)
  console.log('Dolby Vision is now ' + (dolbyVision ? 'active' : 'inactive') + '.')
})
```

Access to these APIs is gated by `manage` access to the `xrn:firebolt:capability:media-info:video-format` capability.

#### 7.2.2. Active Audio Formats
The `MediaInfo` module **MUST** have a `activeAudioFormats` API that returns an `object` with the audio codec, e.g., AAC, AC3, etc., of the media currently in the media pipeline (either playing or paused).

Each item in the `activeAudioFormats` result array **MUST** conform to the same requirements as the indivual results from the [`audioFormat` API](#612-audio-format).

Additionally, the `MediaInfo` module **MUST** have an `onActiveAudioFormatsChanged` notifier that fires whenever any pipeline starts, stops, or changes its current audio format.

Example:

```typescript
const isDolbyAtmos:boolean = await MediaInfo.activeAudioFormats().find(f => f.type === Media.Formats.AUDIO_DOLBY_MAT)

MediaInfo.activeVideoFormats((active) => {
  const dolbyAtmos = active.find(f => f.type === Media.Formats.AUDIO_DOLBY_MAT)
  console.log('Dolby Vision is now ' + (dolbyAtmos ? 'active' : 'inactive') + '.')
})
```

Access to these APIs is gated by `manage` access to the `xrn:firebolt:capability:media-info:audio-format` capability.
