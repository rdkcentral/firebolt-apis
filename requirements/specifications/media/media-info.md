# Media Info Requirements

Document Status: Candidate Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Anthony Borzota | Comcast        |
| Jeremy LaCivita | Comcast        |
| Stuart Harris   | Sky            |
| Farhan Mood     | Liberty Global            |

**TODO**: Get Feedback from Apps community
**TODO**: How do we make this API simple for javasscript devs w/out taking away the power?
**TODO**: Check non-Android TV APIs, e.g. Roku, etc.

## 1. Overview
App developers need to know which audio and video formats can be successfully played on a Firebolt device.

Video formats include... 

**TODO**: Rewrite this section.

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
- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
  - [1.2. As an OTT App developer](#12-as-an-ott-app-developer)
  - [1.3. As a first-party App developer](#13-as-a-first-party-app-developer)
- [2. Table of Contents](#2-table-of-contents)
- [3. Format MimeTypes](#3-format-mimetypes)
- [4. Device Media Support](#4-device-media-support)
  - [4.1. Negotiated Media Support](#41-negotiated-media-support)
    - [4.1.1. Video Format Supported](#411-video-format-supported)
    - [4.1.2. Audio Format Supported](#412-audio-format-supported)
  - [4.2. Implicit Media Support](#42-implicit-media-support)
    - [4.2.1. Video Format Possible](#421-video-format-possible)
    - [4.2.2. Audio Format Possible](#422-audio-format-possible)
- [5. Display Properties](#5-display-properties)
  - [5.1. Display Width and Height](#51-display-width-and-height)
  - [5.2. Current and Optimal Resolution](#52-current-and-optimal-resolution)
  - [5.3. Supported Resolutions](#53-supported-resolutions)
  - [5.4. Supported HDR Profiles](#54-supported-hdr-profiles)
  - [5.5. Use Source Framerate](#55-use-source-framerate)
- [6. Audio Output Properties](#6-audio-output-properties)
  - [6.1. Mode](#61-mode)
- [7. Media Info](#7-media-info)
  - [7.1. MediaInfo for current app](#71-mediainfo-for-current-app)
    - [7.1.1. Video Format](#711-video-format)
    - [7.1.2. Audio Format](#712-audio-format)
  - [7.2. Global MediaInfo](#72-global-mediainfo)
    - [7.2.1. Active Video Formats](#721-active-video-formats)
    - [7.2.2. Active Audio Formats](#722-active-audio-formats)
- [8. Device Media Settings](#8-device-media-settings)
  - [8.1. Audio Settings](#81-audio-settings)
- [9. Notes](#9-notes)

## 3. Format MimeTypes
The Firebolt `Media` module **MUST** have a `Formats` enumeration audio and video formats:

| Name             | Value                  | Notes |
| ---------------- | ---------------------- |------ |
| `AUDIO_AAC`      | `audio/mp4a-latm`      |
| `AUDIO_AC3`      | `audio/ac3`            |
| `AUDIO_AC4`      | `audio/ac4`            |
| `AUDIO_DOLBY_MAT`| `audio/vnd.dolby.mat`  | Dolby Metadata-enhanced Audio Transmission, e.g. Dolby Atmos |
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

**TODO**: Atmos is not always MAT... MAT -> PCM version of Atmos. Can also be carried over AC4 EAC3 DolbyTrueHD

## 4. Device Media Support
Apps need to know what types of media the device supports.

There are two sets of supported media in question:

- What the device has negotiated as supported with other connected devices, e.g. an HDMI Soundbar
- What the device is implicitly supports

For example, a Firebolt device capable of Dolby Atmos connected to a soundbar that is only capable of Dolby Audio might want to display a notification to the user, e.g.:

```javascript
const device = await Device.audioFormatPossible(Media.Formats.AUDIO_DOLBY_MAT)
const negotiated = await Device.audioFormatSupported(Media.Formats.AUDIO_DOLBY_MAT)

if (device && !negotiated) {
  console.log("Warning, your soundbar does not support Dolby Atmos!")
}
```

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
const hdr10plusWithH265 = videoFormatSupported(Media.Formats.VIDEO_H265_M10, '1080p30')
const hdr10plusWithVP9 = videoFormatSupported(Media.Formats.VIDEO_VP9_P2)
```

The `videoFormatSupported` API **MUST** have a required `format` parameter which
**MUST** be one of the following values:

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

The `videoFormatSupported` API **MUST** have an optional `resolution` parameter
which **MUST** be a string from the following values:

- `480i`
- `480p`
- `576i`
- `576p`
- `576p50`
- `720p`
- `720p50`
- `1080i`
- `1080p`
- `1080p24`
- `1080i25`
- `1080p30`
- `1080i50`
- `1080p50`
- `1080p60`
- `2160p30`
- `2160p50`
- `2160p60`

If the `resolution` parameter is provided, then the `videoFormatSupported` API **MUST NOT**
return `true` unless the resolution, and framerate if included, are supported by the format specified.

Use of the `videoFormatSupported` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

#### 4.1.2. Audio Format Supported

The `Device` module **MUST** have an `audioFormatSupported` API that returns
`true` or `false` depending on whether the format specified is supported by
the current device configuration. This API **MUST** return `boolean`.

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

The `audioFormatSupported` API **MUST** have an optional `sampleRate` parameter
which **MUST** be a string from the following values:

- TBD

If the `sampleRate` parameter is provided, then the `audioFormatSupported` API **MUST NOT**
return `true` unless the resolution, and framerate if included, are supported by the format specified.

Use of the `videoFormatSupported` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

### 4.2. Implicit Media Support
Apps may also need to know what types of media support the device implicitly has,
regardless of other connected devices.

To facilitate this, the `Device` module will have a set of methods that
return all possible values supported by the device. These APIs will have the same names as [Negotiated Media Support APIs](#41-negotiated-media-support) but end w/ `Possible` instead of `Supported` to denote that all device supported values are evaluated, not just the currently negotiated values.

These APIs require the same capability permissions as their [Negotiated Media Support APIs](#41-negotiated-media-support) counterparts.

These values never change without a restart.

#### 4.2.1. Video Format Possible
The `Device` module **MUST** have a `videoFormatPossible` API that returns
`true` or `false` depending on whether the format specified is supported by
the device, regardless of configuration. This API **MUST** return `boolean`.

```javascript
const hdr10plusWithH265 = videoFormatPossible(Media.Formats.VIDEO_H265_M10, '1080p30')
const hdr10plusWithVP9 = videoFormatPossible(Media.Formats.VIDEO_VP9_P2)
```
The `videoFormatPossible` **MUST** support the same parameters as the [`videoFormatSupported` API](#411-video-format-supported).

#### 4.2.2. Audio Format Possible
The `Device` module **MUST** have a `audioFormatPossible` API that returns
`true` or `false` depending on whether the format specified is supported by
the device, regardless of configuration. This API **MUST** return `boolean`.

The `audioFormatPossible` **MUST** support the same parameters as the [`audioFormatSupported` API](#412-audio-format-supported).

## 5. Display Properties

Apps need to know various aspects of the current (or built in) display on a device.

These will be surfaced in a new `Display` module.

Access to these APIs is governed by the `xrn:firebolt:capability:display:info` capability.

### 5.1. Display Width and Height

The `Display` module **MUST** have a `width` and `height` method that return the width and height of the display, in centimeters.

**TODO**: Does HDMI tell you this on a STB?

### 5.2. Current and Optimal Resolution

The `Display` module **MUST** have a `currentResolution` and  `optimalResolution` method that returns a valid resolution for either the current state of the display, or the displays optimal resolution value.

These methods **MUST** return one of the following values:

- `1080p24`
- `1080i25`
- `1080p30`
- `1080i50`
- `1080p50`
- `1080p60`
- `2160p30`
- `2160p50`
- `2160p60`

TODO: get final list...
TODO: Roku does width & height, and doesn't include framerate

### 5.3. Supported Resolutions
 
The `Display` module **MUST** have a `supportedResolutions` method that returns an array of valid resolutions that the display supports.

These methods **MUST** return an array with one or more of the following values:

- `1080p24`
- `1080i25`
- `1080p30`
- `1080i50`
- `1080p50`
- `1080p60`
- `2160p30`
- `2160p50`
- `2160p60`

### 5.4. Supported HDR Profiles
The `Display` module **MUST** have an `hdr` method that returns an array of valid HDR profiles that the display supports.

The array **MUST** have one or more of the following values:

| Enumeration                   | Notes |
| ----------------------------- | ----- |
| `HDR_DOLBYVISION`             | Only true for the VIDEO_DOLBYVISION format  |
| `HDR_HDR10`                   | Any format that supports HDR10 metadata    |
| `HDR_HDR10PLUS`               | Any format that supports HDR10+ metadata   |
| `HDR_ST2084`                  | Any format that supports ST2084 color transfer |
| `HDR_HLG`                     | Any format that supports HLG color transfer |

### 5.5. Use Source Framerate
The `Display` module **MUST** have a boolean `useSourceFrameRate` API.

This API **MUST** return `true` if the hdmi output frame rate is set to follow video source frame rate.

Otherwise, this API **MUST** return false.

## 6. Audio Output Properties
Apps need to know various aspects of the current (or built in) audio output system on a device.

These will be surfaced in a new `AudioOutput` module.

Access to these APIs is governed by the `xrn:firebolt:capability:audio-output:info` capability.

### 6.1. Mode
The `AudioOutput` module  **MUST** include a `mode` string API that returns one of the following values:

- `MONO`
- `STEREO`
- `SURROUND`
- `PASSTHROUGH`
- `AUTO`
- `STEREO_SURROUND_MAT_FOLLOW`
- `UNKNOWN`
- `NONE`

**TODO**: is this all of them?

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

The `videoFormat` result **MUST** have a `resolution` string property with one of the following values:

- `480i`
- `480p`
- `576i`
- `576p`
- `576p50`
- `720p`
- `720p50`
- `1080i`
- `1080p`
- `1080p24`
- `1080i25`
- `1080p30`
- `1080i50`
- `1080p50`
- `1080p60`
- `2160p30`
- `2160p50`
- `2160p60`
- `UNKNOWN`
- `NONE`

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

**TODO**: Roku has format, codec, profile, level...

The `audioFormat` result **MUST** have a `channels` string property with one of the following values:

| Enumeration                   | Notes |
| ----------------------------- | ----- |
| `CHANNELS_MONO`               | |
| `CHANNELS_STEREO`             | |
| `CHANNELS_SURROUND_5_1`       | |
| `CHANNELS_SURROUND_7_1`       | |

**TODO**: get all values...

The `audioFormat` result **MUST** have a `sampleRate` string property with one of the following values:

- TBD

The `audioFormat` API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioFormatChanged` notification.

Use of the `audioFormat` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:audio-format` capability.

### 7.2. Global MediaInfo

First party apps need a way to query which media formats are currently being output to the [media pipeline](./media-pipeline.md), without caring about which pipeline.

#### 7.2.1. Active Video Formats
The `MediaInfo` module **MUST** have a `activeVideoFormats` API that returns an array of `objects` with the video codec, e.g., H.265, VP9, etc., and sample rate of the media currently in each media pipeline (either playing or paused).

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
The `MediaInfo` module **MUST** have a `activeAudioFormats` API that returns an `object` with the audio codec, e.g., AAC, AC3, etc., and sample rate of the media currently in the
media pipeline (either playing or paused).

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

**TODO**: Group Audio & Video from output 1, output 2, etc.

JL: no, we're trying to support on screen badges here, not more complex use cases

**TODO**: Add display dimensions to video formats in this array, so we know how big they are

JL: it's in there via `resolution`

**TODO**: How do i use this api for just the "main" screen and ignore the other.

JL: we can add a param where you specify the pipeline or display? Out of scope?

## 8. Device Media Settings

### 8.1. Audio Settings
The `Device` module **MUST** have an `audioSettings` API that returns
the Device's current audio settings.

The audioSettings **MUST** include a `mode` string property with one of the following values:

- `MONO`
- `STEREO`
- `SURROUND`
- `PASSTHROUGH`
- `AUTO`
- `STEREO_SURROUND_MAT_FOLLOW`
- `UNKNOWN`
- `NONE`

## 9. Notes

| API           | Current App | Any Pipeline | Globally | Supported by Chain | Supported by Device |
|---------------|-------------|--------------|----------|--------------------|---------------------|
| Video Codec   |  | | | | | 
| Audio Codec   | | | | | | 
| Dynamic Range | | | | | | 
| Audio Profile | | | | | | 
| Resolution    | | | | | | 

he encoding format for this AudioProfile.

Value is

- AudioFormat.ENCODING_DEFAULT
- AudioFormat.ENCODING_PCM_16BIT
- AudioFormat.ENCODING_PCM_8BIT
- AudioFormat.ENCODING_PCM_FLOAT,
- AudioFormat.ENCODING_AC3
- AudioFormat.ENCODING_E_AC3
- AudioFormat.ENCODING_DTS
- AudioFormat.ENCODING_DTS_HD
- AudioFormat.ENCODING_MP3
- AudioFormat.ENCODING_AAC_LC
- AudioFormat.ENCODING_AAC_HE_V1
- AudioFormat.ENCODING_AAC_HE_V2
- AudioFormat.ENCODING_IEC61937
- AudioFormat.ENCODING_DOLBY_TRUEHD
- AudioFormat.ENCODING_AAC_ELD
- AudioFormat.ENCODING_AAC_XHE
- AudioFormat.ENCODING_AC4
- AudioFormat.ENCODING_E_AC3_JOC
- AudioFormat.ENCODING_DOLBY_MAT
- AudioFormat.ENCODING_OPUS
- AudioFormat.ENCODING_PCM_24BIT_PACKED
- AudioFormat.ENCODING_PCM_32BIT
- AudioFormat.ENCODING_MPEGH_BL_L3
- AudioFormat.ENCODING_MPEGH_BL_L4
- AudioFormat.ENCODING_MPEGH_LC_L3
- AudioFormat.ENCODING_MPEGH_LC_L4
- AudioFormat.ENCODING_DTS_UHD_P1
- AudioFormat.ENCODING_DRA
- AudioFormat.ENCODING_DTS_HD_MA
- AudioFormat.ENCODING_DTS_UHD_P2
- AudioFormat.ENCODING_DSD


"Dolby Audio":

- AudioFormat.ENCODING_AC3
- AudioFormat.ENCODING_E_AC3
- AudioFormat.ENCODING_E_AC3_JOC

"atmos" -> ENCODING_E_AC3_JOC

Surround has nothing to do w/ codec:

Need `audioChannels()` API that returns stereo, mono, 5.1, 7.1, etc.

On Android, there are Audio Formats, and formats ahve profiles. profiles have channels/sample rates.

https://developer.android.com/reference/android/media/AudioFormat

Video Codecs have Codec Levels/profiles:
https://developer.android.com/reference/android/media/MediaFormat#KEY_HDR10_PLUS_INFO