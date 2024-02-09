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
- [4. Format Features](#4-format-features)
- [5. Device Media Support](#5-device-media-support)
  - [5.1. Negotiated Media Support](#51-negotiated-media-support)
    - [5.1.1. Video Format Supported](#511-video-format-supported)
    - [5.1.2. Audio Format Supported](#512-audio-format-supported)
  - [5.2. Implicit Media Support](#52-implicit-media-support)
- [6. Media Info](#6-media-info)
  - [6.1. MediaInfo for current app](#61-mediainfo-for-current-app)
    - [6.1.1. Video Format](#611-video-format)
    - [6.1.2. Audio Format](#612-audio-format)
  - [6.2. Global MediaInfo](#62-global-mediainfo)
- [7. Device Media Settings](#7-device-media-settings)
  - [7.1. Audio Settings](#71-audio-settings)
  - [7.2. Video Settings](#72-video-settings)
  - [7.3. Rialto](#73-rialto)
- [8. Notes](#8-notes)

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

## 4. Format Features
The Firebolt `Media` module **MUST** have a `Features` enumeration audio and video format features:

| Name                          | Value           | Notes |
| ----------------------------- | --------------- | ----- |
| `HDR`                         | `hdr`           | Aggregation of any features that starts with `HDR` |
| `HDR_DOLBYVISION`             | `hdrDolbyVision`| Only true for the VIDEO_DOLBYVISION format  |
| `HDR_HDR10`                   | `hdr10`         | Any format that supports HDR10 metadata    |
| `HDR_HDR10PLUS`               | `hdr10plus`     | Any format that supports HDR10+ metadata   |
| `HDR_ST2084`                  | `hdrSt2084`     | Any format that supports ST2084 color transfer |
| `HDR_HLG`                     | `hdrHlg`        | Any format that supports HLG color transfer |

TODO: maybe add AUDIO_DOLBYATOMS feature
TODO: bring back Technicolor

## 5. Device Media Support
Apps need to know what types of media the device supports.

There are two sets of supported media in question:

- What the device has negotiated as supported with other connected devices, e.g. an HDMI Soundbar
- What the device is implicitly supports

For example, a Firebolt device capable of Dolby Atmos connected to a soundbar that is only capable of Dolby Audio might want to display a notification to the user, e.g.:

```javascript
const device = await Device.audioFormatPossible(Media.Formats.AUDIO_DOLBYATMOS)
const negotiated = await Device.audioFormatSupported(Media.Formats.AUDIO_DOLBYATMOS)

if (device && !negotiated) {
  console.log("Warning, your soundbar does not support Dolby Atmos!")
}
```

### 5.1. Negotiated Media Support
Apps need to know what types of media support the current *device configuration*,
e.g. a Firebolt STB connected to an HDMI television, is capable of.

To facilitate this, the `Device` module will have a set of methods that
return all possible values supported by the current device configuration.

These values change and different AV inputs are activated or connected.

#### 5.1.1. Video Format Supported

The `Device` module **MUST** have a `videoFormatSupported` API that returns
`true` or `false` depending on whether the format specified is supported by
the current device configuration. This API **MUST** return `boolean`.

```javascript
const hdr10plusWithH265 = videoFormatSupported(Media.Formats.VIDEO_H265_M10, [ Media.Features.HDR_HDR10Plus ], '1080p30')
const hdr10plusWithVP9 = videoFormatSupported(Media.Formats.VIDEO_VP9_P2, [ Media.Features.HDR_HDR10Plus ])
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

The `videoFormatSupported` API **MUST** have an optional `features` parameter
which **MUST** be an array of zero or more strings from the following values:

| Enumeration                   | Notes |
| ----------------------------- | ----- |
| `HDR`                         | Aggregation of any features that starts with `HDR` |
| `HDR_DOLBYVISION`             | Only true for the VIDEO_DOLBYVISION format  |
| `HDR_HDR10`                   | Any format that supports HDR10 metadata    |
| `HDR_HDR10PLUS`               | Any format that supports HDR10+ metadata   |
| `HDR_ST2084`                  | Any format that supports ST2084 color transfer |
| `HDR_HLG`                     | Any format that supports HLG color transfer |

If the `features` parameter is provided, then the `videoFormatSupported` API **MUST NOT**
return `true` unless all of the features in the array are supported by the format specified.

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

**TODO**: Can plugging in a new TV to a STB change videoCodecs support?

Use of the `videoFormatSupported` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

#### 5.1.2. Audio Format Supported

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

The `audioFormatSupported` API **MUST** have an optional `features` parameter
which **MUST** be an array of zero or more strings from the following values:

| Enumeration                   | Notes |
| ----------------------------- | ----- |
| `CHANNELS_MONO`               | |
| `CHANNELS_STEREO`             | |
| `CHANNELS_SURROUND`           | Aggregation of any SURROUND features |
| `CHANNELS_SURROUND_5_1`       | |
| `CHANNELS_SURROUND_7_1`       | |

TODO: Android has lots more channel configs

If the `features` parameter is provided, then the `audioFormatSupported` API **MUST NOT**
return `true` unless all of the features in the array are supported by the format specified.

The `audioFormatSupported` API **MUST** have an optional `sampleRate` parameter
which **MUST** be a string from the following values:

- TBD

If the `sampleRate` parameter is provided, then the `audioFormatSupported` API **MUST NOT**
return `true` unless the resolution, and framerate if included, are supported by the format specified.

**TODO**: Can plugging in a new TV to a STB change audio formats support?

Use of the `videoFormatSupported` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

### 5.2. Implicit Media Support
Apps may also need to know what types of media support the device implicitly has,
regardless of other connected devices.

To facilitate this, the `Device` module will have a set of methods that
return all possible values supported by the device. These APIs will have the same names as [Negotiated Media Support APIs](#41-negotiated-media-support) but end w/ `Possible` instead of `Supported` to denote that all device supported values are evaluated, not just the currently negotiated values.

These APIs require the same capability permissions as their [Negotiated Media Support APIs](#41-negotiated-media-support) counterparts.

These values never change without a restart.

The APIs are as follows:

 - `audioFormatPossible`
 - `videoFormatPossible`

## 6. Media Info

The Firebolt `MediaInfo` module consists of APIs to get information
about any media actively being decoded by the Media Pipeline or an active HDMI input.

### 6.1. MediaInfo for current app

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

The `pipeline` parameter is required for the JSON-RPC request, however, the Firebolt SDK **SHOULD** provide a default value of `1` if it is not provided by the calling app.

For example:

```javascript
MediaInfo.videoCodec()
```

Would query the video codec for the app's pipeline `1` in JavaScript, which supports default values for parameters.

#### 6.1.1. Video Format

The `MediaInfo` module **MUST** have a `videoFormat` API that returns an `object` with the
video codec, e.g., H.265, VP9, etc., features, and resolution of the media currently in the
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

The `videoFormat` result **MUST** have a `features` array property with zero or more of the following values:

| Enumeration                   | Notes |
| ----------------------------- | ----- |
| `HDR`                         | Aggregation of any features that starts with `HDR` |
| `HDR_DOLBYVISION`             | Only true for the VIDEO_DOLBYVISION format  |
| `HDR_HDR10`                   | Any format that supports HDR10 metadata    |
| `HDR_HDR10PLUS`               | Any format that supports HDR10+ metadata   |
| `HDR_ST2084`                  | Any format that supports ST2084 color transfer |
| `HDR_HLG`                     | Any format that supports HLG color transfer |

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

#### 6.1.2. Audio Format

The `MediaInfo` module **MUST** have a `audioFormat` API that returns an `object` with the
video codec, e.g., H.265, VP9, etc., features, and resolution of the media currently in the
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

The `audioFormat` result **MUST** have a `features` array property with zero or more of the following values:

| Enumeration                   | Notes |
| ----------------------------- | ----- |
| `CHANNELS_MONO`               | |
| `CHANNELS_STEREO`             | |
| `CHANNELS_SURROUND`           | Aggregation of any SURROUND features |
| `CHANNELS_SURROUND_5_1`       | |
| `CHANNELS_SURROUND_7_1`       | |

The `audioFormat` result **MUST** have a `resolution` string property with one of the following values:

- TBD

The `audioFormat` API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioFormatChanged` notification.

Use of the `audioFormat` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:audio-format` capability.

### 6.2. Global MediaInfo

First party apps need a way to query which media formats are currently being output, without caring about which pipeline.

**TODO**: need to define output more specifically. Hardware decoder? Software Decoder, HDMI, Composite... SPDIff, Jeremy to check with XClass?

The following APIs **MUST** exist:

-   `activeVideoFormats`
-   `activeAudioFormats`
-   `onActiveVideoFormatsChanged`
-   `onActiveAudioFormatsChanged`

These APIs **MUST** all be Firebolt `property:readonly` APIs with the
corresponding notifications.

These APIs **MUST** take no parameters.

These APIs **MUST** return an array of Formats that are currently being sent to a decoder pipeline.

These APIs **MUST** have corresponding notifications for when a specific type becomes active or inactive, e.g. `onActiveVideoFormatsChanged`.

For example:

```typescript
const isDolbyVision:boolean = await MediaInfo.activeVideoFormats().find(f => f.type === Media.Formats.VIDEO_DOLBYVISION)

MediaInfo.activeVideoFormats((active) => {
  const dolbyVision = active.find(f => f.type === Media.Formats.VIDEO_DOLBYVISION)
  console.log('Dolby Vision is now ' + (dolbyVision ? 'active' : 'inactive') + '.')
})
```
**TODO**: Group Audio & Video from output 1, output 2, etc.
**TODO**: Add display dimensions to video formats in this array, so we know how big they are
**TODO**: How do i use this api for just the "main" screen and ignore the other.

These APIs **MUST** all be gated by `manage` role of the same
capabilities required by the corresponding methods above, i.e.:

| Capability               | Use                 | Manage                    |
|--------------------------|---------------------|---------------------------|
| media-info:video-format  | videoFormatSupported | activeVideoFormats       |
| media-info:audio-format  | audioFormatSupported | activeAudioFormats       |

*Capability names truncated for legibility

## 7. Device Media Settings

### 7.1. Audio Settings
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

**TODO**: the rest of these need to move to Rialto:

The audioSettings **MUST** include an `atmosOutputLock` boolean property.

The audioSettings **MUST** include an `audioLoundnessEquivalence` boolean property.

The audioSettings API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioSettingsChanged` notification.

Use of the `audioSettings` and `onAudioSettingsChanged` APIs require access
to the `use` role of the `xrn:firebolt:capability:device:audio-settings` capability.

TODO: Netflix needs to be able to *set* atmosOutputLock...

### 7.2. Video Settings
The `Device` module **MUST** have an `videoSettings` API that returns
the Device's current video settings.

The videoSettings **MUST** include a boolean `useSourceFrameRate` property.

If this is set to `true` then the hdmi output frame rate is set to follow video source frame rate.

### 7.3. Rialto

- Preferred resolution/framerate
- atmos lock
- loudness eq

## 8. Notes

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