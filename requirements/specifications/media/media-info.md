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

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. MimeTypes](#3-mimetypes)
- [4. Media Info](#4-media-info)
  - [4.1. MediaInfo for current app](#41-mediainfo-for-current-app)
    - [4.1.1. Video Codec](#411-video-codec)
    - [4.1.2. Audio Codec](#412-audio-codec)
    - [4.1.3. Dynamic Range](#413-dynamic-range)
    - [4.1.4. Immersive Audio](#414-immersive-audio)
    - [4.1.5. Frame Rate](#415-frame-rate)
    - [4.1.6. Resolution](#416-resolution)
    - [4.1.7. Resolution (Alternative)](#417-resolution-alternative)
  - [4.2. MediaInfo for Pipeline](#42-mediainfo-for-pipeline)
  - [4.3. Global MediaInfo](#43-global-mediainfo)
- [5. Device Media Support](#5-device-media-support)
  - [5.1. Negotiated Media Support](#51-negotiated-media-support)
    - [5.1.1. Video Codecs](#511-video-codecs)
    - [5.1.2. Audio Codecs](#512-audio-codecs)
    - [5.1.3. Dynamic Range](#513-dynamic-range)
    - [5.1.4. Immersive Audio](#514-immersive-audio)
    - [5.1.5. Resolutions](#515-resolutions)
    - [5.1.6. Resolutions (Alternative)](#516-resolutions-alternative)
  - [5.2. Implicit Media Support](#52-implicit-media-support)

## 3. MimeTypes
The Firebolt `MimeTypes` module consists of static enumeration of all codecs, formats, etc., and their mime-types.

| Name             | Value                  | Notes |
| ---------------- | ---------------------- |------ |
| `AUDIO_AAC`      | `audio/mp4a-latm`      |
| `AUDIO_AC3`      | `audio/ac3`            |
| `AUDIO_AC4`      | `audio/ac4`
| `AUDIO_DTS`      | `audio/vnd.dts`        |
| `AUDIO_EAC3`     | `audio/eac3`           | Note we call this AC3+ in RDK...
| `AUDIO_MPEG`     | `audio/mpeg`           | 
| `AUDIO_MPEG1`    | `audio/mpeg-L1`        | 
| `AUDIO_MPEG2`    | `audio/mpeg-L2`        | 
| `AUDIO_MPEG4`    | `audio/mp4`            | 
| `AUDIO_OPUS`     | `audio/opus`           |
| `AUDIO_OGG`      | `audio/ogg`            |
| `AUDIO_TRUEHD`   | `audio/true-hd`        |
| `AUDIO_WAV`      | `audio/wav`            |
| `HDR_HDR10`      | `video/hdr10`          |
| `HDR_HDR10PLUS`  | `video/hdr10-plus`     |
| `HDR_DOLBYVISION`| `video/dolbyVision`    |
| `HDR_SLHDR1`     | `video/slhdr1`         |
| `HDR_HLG`        | `video/hlg`            |
| `IA_AURO3D`      | `audio/auro-3d`        |
| `IA_DOLBYATMOS`  | `audio/dolby-atmos`    |
| `IA_DTS_X`       | `audio/vnd.dts.uhd;profile=p2` |
| `IA_MPEGH_MHA1`  | `audio/mha1`           |
| `IA_MPEGH_MHM1`  | `audio/mhm1`           |
| `VIDEO_AV1`      | `video/av01`           |
| `VIDEO_H263`     | `video/3gpp`           |
| `VIDEO_H264`     | `video/avc`            |
| `VIDEO_H265`     | `video/hevc`           |
| `VIDEO_MPEG`     | `video/mpeg`           |
| `VIDEO_VP8`      | `video/x-vnd.on2.vp8`  |
| `VIDEO_VP9`      | `video/x-vnd.on2.vp9`  |
| `VIDEO_VP10`     | `video/x-vnd.on2.vp10` |
| `VIDEO_VC1`      | `video/wvc1`           |
| `UNKNOWN`        | `unknown`              |
| `NONE`           | `none`                 |

## 4. Media Info

The Firebolt `MediaInfo` module consists of APIs to get information
about any media actively being decoded by the Media Pipeline or an active HDMI input.

### 4.1. MediaInfo for current app

Apps need a way to query the media info for media currently being played  
by the app. All of the following methods take a single `pipeline`
parameter, which identifies the Media Pipeline in the current app's scope
that is being queried, e.g.:

```javascript
import { MediaInfo } from '@firebolt-js/sdk'

MediaInfo.videoCodec(1) // return the video codec in the current app's media pipeline 1
MediaInfo.videoCodec(2) // return the video codec in the current app's media pipeline 2
```

The `pipeline` parameter is required for the JSON-RPC request, however, the Firebolt SDK **SHOULD** provide a default value of `1` if it is not provided by the calling app.

For example:

```javascript
MediaInfo.videoCodec()
```

Would query the video codec for the app's pipeline `1` in JavaScript, which supports default values for parameters.

#### 4.1.1. Video Codec

The `MediaInfo` module **MUST** have a `videoCodec` API that returns the
video codec, e.g., H.265, VP9, etc., of the media currently in the
media pipeline (either playing or paused). This API **MUST** return
one of the following values from the `MimeTypes` module:

- `VIDEO_AV1`
- `VIDEO_H263`
- `VIDEO_H264`
- `VIDEO_H265`
- `VIDEO_MPEG`
- `VIDEO_VP8`
- `VIDEO_VP9`
- `VIDEO_VP10`
- `VIDEO_VC1`
- `UNKNOWN`
- `NONE`

The videoCodec API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onVideoCodecChanged` notification.

Use of the `videoCodec` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:video-codec` capability.

#### 4.1.2. Audio Codec

The `MediaInfo` module **MUST** have an `audioCodec` API that returns
the audio codec, e.g., ac3, ac4, ogg, etc., of the media currently
playing. This API **MUST** return one of the following values from the `MimeTypes` module:

- `AUDIO_AAC`
- `AUDIO_AC3`
- `AUDIO_AC4`
- `AUDIO_DTS`
- `AUDIO_EAC3`
- `AUDIO_MPEG`
- `AUDIO_MPEG1`
- `AUDIO_MPEG2`
- `AUDIO_MPEG4`
- `AUDIO_OPUS`
- `AUDIO_OGG`
- `AUDIO_TRUEHD`
- `AUDIO_WAV`
- `UNKNOWN`
- `NONE`
  
The audioCodec API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioCodecChanged` notification.

Use of the `audioCodec` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:audio-codec` capability.

#### 4.1.3. Dynamic Range

The `MediaInfo` module **MUST** have a `dynamicRangeProfile` API that
returns the dynamic range profile, e.g., HDR, HDR10, etc., of the
media currently playing. This API **MUST** return one of the following
values from the `MimeTypes` module:

- `HDR_HDR10`
- `HDR_HDR10PLUS`
- `HDR_DOLBYVISION`
- `HDR_SLHDR1`
- `HDR_HLG`
- `NONE`
- `UNKNOWN`

The dynamicRangeProfile API **MUST** be a Firebolt `property:readonly`
API, and have a corresponding `onDynamicRangeProfileChanged`
notification.

The `MediaInfo` module **MUST** have an `isHDR` API that returns true if
the value of `dynamicRangeProfile` is currently any of the values
excluding `none` and `unknown`.

The `isHDR` API **MUST** be a Firebolt `property:readonly` API, and have
a corresponding `onIsHDRChanged` notification.

Use of the `dynamicRangeProfile` and `isHDR` APIs require access to the
`use` role of the `xrn:firebolt:capability:media-info:hdr`
capability.

#### 4.1.4. Immersive Audio

The `MediaInfo` module **MUST** have an `audioProfile` API that returns
the immersive (or not) audio profile, e.g., Dolby Atmos, etc., of the
media currently playing. This API **MUST** return one of the following
values from the `MimeTypes` module:

- `IA_AURO3D`
- `IA_DOLBYATMOS`
- `IA_DTS_X`
- `IA_MPEGH_MHA1`
- `IA_MPEGH_MHM1`
- `UNKNOWN`
- `NONE`

The audioProfile API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioProfileChanged` notification.

The `MediaInfo` module **MUST** have an `isImmersiveAudio` API that
returns true if the value of `audioProfile` is currently any of the
values excluding `none`.

The `isImmersiveAudio` API **MUST** be a Firebolt `property:readonly`
API, and have a corresponding `onIsImmersiveAudioChanged`
notification.

Use of the `audioProfile` and `isImmersiveAudio` APIs require access
to the `use` role of the
`xrn:firebolt:capability:media-info:audio-profile` capability.

#### 4.1.5. Frame Rate

The `MediaInfo` module **MUST** have a `frameRate` API that returns
the frame rate, e.g., 24, of the media currently
playing. This API **MUST** return a number greater than or equal to `0`.

If no video is playing, then this API **MUST** return `0`.
  
The audioCodec API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onFrameRateChanged` notification.

Use of the `frameRate` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:frame-rate` capability.

#### 4.1.6. Resolution

The `MediaInfo` module **MUST** have a `resolution` API that returns
the encoded dimensions, e.g., `{ "width": 4096, "height": 2160 }`, of the media currently
playing. Note that this has nothing to do with the dimensions rasterized on the screen (see the Device [Resolution](#312-resolution) API for that).
This API **MUST** return an object with two integers greater than or equal to `0`.
  
The resolution API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onResolutionChanged` notification.

Use of the `resolution` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:resolution` capability.

#### 4.1.7. Resolution (Alternative)

**TODO**: pick one

The `MediaInfo` module **MUST** have a `resolution` API that returns
the encoded dimensions as a string enumeration, e.g., `"1020p"`, of the media currently
playing. Note that this has nothing to do with the dimensions rasterized on the screen (see the Device [Resolution](#312-resolution) API for that).

This API **MUST** return a string with one of the following values:

- `"720p"`
- `"1080p"`
- `"1440p"`
- `"1800p"`
- `"2160p"`

 **Note**: do we want interlaced versions?
  
The resolution API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onResolutionChanged` notification.

Use of the `resolution` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:resolution` capability.

### 4.2. MediaInfo for Pipeline
First party apps need a way to query the media info for media currently
being played by *any* pipeline, regardless of which app owns the pipeline.

The following APIs **MUST** exist:

-   `dynamicRangeProfileForPipeline`
-   `videoCodecForPipeline`
-   `isHdrForPipeline`
-   `audioProfileForPipeline`
-   `audioCodecForPipeline`
-   `isImmersiveAudioForPipeline`
-   `frameRateForPipeline`
-   `resolutionForPipeline`

These APIs **MUST** all be Firebolt `property:readonly` APIs with the
corresponding notifications.

These APIs take an opaque `pipeline` string parameter identifying for which Media Pipeline the info is being requested, e.g.:

```javascript
MediaInfo.videoCodecForPipeline('xyz')
```

These pipelines are actual Media Pipeline IDs, rather than the natural counting integer app-scoped ids.

These APIs **MUST** all be gated by `manage` role of the same
capabilities required by the corresponding methods above, i.e.:

| Capability               | Use                 | Manage                    |
|--------------------------|---------------------|---------------------------|
| media-info:video-codec   | videoCodec          | videoCodecForPipeline          |
| media-info:audio-codec   | audioCodec          | audioCodecForPipeline          |
| media-info:hdr           | dynamicRangeProfile | dynamicRangeProfileForPipeline |
| media-info:hdr           | isHdr               | isHdrForPipeline               |
| media-info:audio-profile | audioProfile        | audioProfileForPipeline        |
| media-info:audio-profile | isImmersiveAudio    | isImmersiveAudioForPipeline    |
| media-info:frame-rate    | frameRate           | frameRateForPipeline           |

*Capability names truncated for legibility

### 4.3. Global MediaInfo

First party apps need a way to query if a given media info type is currently active, without caring about which pipeline.

The following APIs **MUST** exist:

-   `dynamicRangeProfileActive`
-   `videoCodecActive`
-   `isHdrActive`
-   `audioProfileActive`
-   `audioCodecActive`
-   `isImmersiveAudioActive`
-   `frameRateActive`
-   `resolutionActive`

These APIs **MUST** all be Firebolt `property:readonly` APIs with the
corresponding notifications.

These APIs **MUST** take a single string parameter `type` which **MUST** be one of the [MimeTypes](#3-mimetypes) supported as results for the corresponding `*ForPipeline` API.

These APIs **MUST** return a boolean, denoting whether *any* pipeline on he system is has the `type` active.

These APIs **MUST** have corresponding notifications for when a specific type becomes active or inactive, e.g. `onDynamicRangeProfileActiveChanged`.

For example:

```typescript
const isDolbyVision:boolean = await MediaInfo.dynamicRangeProfileActive(MimeType.HDR_DOLBYVISION)

MediaInfo.dynamicRangeProfileActive(MimeType.HDR_DOLBYVISION, (active) => {
  console.log('Dolby Vision is now ' + (active ? 'active' : 'inactive') + '.')
})
```

These APIs **MUST** all be gated by `manage` role of the same
capabilities required by the corresponding methods above, i.e.:

| Capability               | Use                 | Manage                    |
|--------------------------|---------------------|---------------------------|
| media-info:video-codec   | videoCodec          | videoCodecActive          |
| media-info:audio-codec   | audioCodec          | audioCodecActive          |
| media-info:hdr           | dynamicRangeProfile | dynamicRangeProfileActive |
| media-info:hdr           | isHdr               | isHdrActive               |
| media-info:audio-profile | audioProfile        | audioProfileActive        |
| media-info:audio-profile | isImmersiveAudio    | isImmersiveAudioActive    |
| media-info:frame-rate    | frameRate           | frameRateActive           |

*Capability names truncated for legibility

## 5. Device Media Support
Apps need to know what types of media the device supports.

There are two sets of supported media in question:

- What the device has negotiated as supported with other connected devices, e.g. an HDMI Soundbar
- What the device is implicitly supports

For example, a Firebolt device capable of Dolby Atmos connected to a soundbar that is only capable of Dolby Audio might want to display a notification to the user, e.g.:

```javascript
const device = await Device.allAudioProfiles().includes(MimeType.IA_DOLBYATMOS)
const negotiated = await Device.audioProfiles().includes(MimeType.IA_DOLBYATMOS)

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

Note that many, but not all, of these methods are pluralized to illustrate that they
return all possible values, rather than a single active value, e.g.:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.videoCodecs() // return the supported video codecs
```

#### 5.1.1. Video Codecs

The `Device` module **MUST** have a `videoCodecs` API that returns the
video codecs, e.g., H.265, VP9, etc., that are supported by the current
device configuration. This API **MUST** return an Array with one or more
of the following values:

-   `"av1"`
-   `"h263"`
-   `"h264"`
-   `"h265"`
-   `"mpeg"`
-   `"vp8"`
-   `"vp9"`
-   `"vp10"`
-   `"vc1"`
-   `"unknown"`
-   `"none"`

The videoCodecs API **MUST** be a Firebolt `property:immutable` API.

**TODO**: Can plugging in a new TV to a STB change videoCodecs support?

Use of the `videoCodecs` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

#### 5.1.2. Audio Codecs

The `Device` module **MUST** have an `audioCodecs` API that returns
the audio codecs, e.g., ac3, ac4, ogg, etc., that are supported by the current
device configuration. This API **MUST** return an Array with one or more of the
following values:

-   `"aac"`
-   `"ac3"`
-   `"ac3plus"`
-   `"eac3"`
-   `"ac4"`
-   `"dts"`
-   `"mpeg1"`
-   `"mpeg2"`
-   `"mpeg3"`
-   `"mpeg4"`
-   `"opus"`
-   `"ogg"`
-   `"trueHd"`
-   `"wav"`
-   `"unknown"`
-   `"none"`
  
The audioCodecs API **MUST** be a Firebolt `property:immutable` API.

**TODO**: Can plugging in a new soundbar change audioCodecs support?

Use of the `audioCodecs` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

#### 5.1.3. Dynamic Range

The `Device` module **MUST** have a `dynamicRangeProfiles` API that
returns the dynamic range profiles, e.g., HDR, HDR10, etc., that are
supported by the current device configuration. This API **MUST** return
an Array with one or more of the following values:

-   `"none"`
-   `"hdr10"`
-   `"hdr10plus"`
-   `"dolbyVision"`
-   `"slHdr1"`
-   `"hlg" `
-   `"unknown"`

The dynamicRangeProfiles API **MUST** be a Firebolt `property:readonly`
API, and have a corresponding `onDynamicRangeProfilesChanged`
notification.

The `MediaInfo` module **MUST** have an `supportsHDR` API that returns true if
the value of `dynamicRangeProfiles` contains any of the values beyond `none`
and `unknown`.

The `supportsHDR` API **MUST** be a Firebolt `property:readonly` API, and have
a corresponding `onSupportsHDRChanged` notification.

Use of the `dynamicRangeProfiles` and `supportsHDR` APIs require access to the
`use` role of the `xrn:firebolt:capability:device:info`
capability.

#### 5.1.4. Immersive Audio

The `Device` module **MUST** have an `audioProfiles` API that returns
the immersive (or not) audio profiles, e.g., Dolby Atmos, etc., that are
supported by the current device configuration. This API **MUST** return an
Array with one ore more of the following values:

-   `"auro3d"`
-   `"dolbyAtmos"`
-   `"dtsx"`
-   `"mpegh"`
-   `"unknown"`
-   `"none"`

The audioProfile API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioProfilesChanged` notification.

The `Device` module **MUST** have an `supportsImmersiveAudio` API that
returns true if the value of `audioProfiles` contains any of the
values beyond `none`.

The `supportsImmersiveAudio` API **MUST** be a Firebolt `property:readonly`
API, and have a corresponding `onSupportsImmersiveAudioChanged`
notification.

Use of the `audioProfiles` and `supportsImmersiveAudio` APIs require access
to the `use` role of the `xrn:firebolt:capability:device:info` capability.

#### 5.1.5. Resolutions

The `Device` module **MUST** have a `resolutions` API that returns an array
of the native dimensions the device is capable of rasterizing (if the device
has a screen) or outputting (if the device does not).

This API **MUST** return an Array of objects with two integers greater than or equal to `0`, e.g.:

```json
[
  { "width": 4096, "height": 2160 },
  { "width": 2048, "height": 1080 },
  { "width": 1024, "height": 540 }
]
```

The resolution API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onResolutionChanged` notification.

Use of the `resolution` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

Note that this API is not part of the `MediaInfo` module, but is documented here for completeness.

#### 5.1.6. Resolutions (Alternative)

**TODO**: pick one

The `Device` module **MUST** have a `resolutions` API that returns
an array
of the native dimensions the device is capable of rasterizing (if the device
has a screen) or outputting (if the device does not).

This API **MUST** return an Array of strings with one or more of the following values:

- `"720p"`
- `"1080p"`
- `"1440p"`
- `"1800p"`
- `"2160p"`

 **Note**: do we want interlaced versions?
  
The resolution API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onResolutionChanged` notification.

Use of the `resolution` APIs require access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

### 5.2. Implicit Media Support
Apps may also need to know what types of media support the device implicitly has,
regardless of other connected devices.

To facilitate this, the `Device` module will have a set of methods that
return all possible values supported by the device. These APIs will have the same names as [Negotiated Media Support APIs](#41-negotiated-media-support) prefixed with the word `all` to denote that all device supported values are returned, not just the currently negotiated values.

These APIs require the same capability permissions as their [Negotiated Media Support APIs](#41-negotiated-media-support) counterparts.

These values never change without a restart, and **MUST** all be `property:immutable` APIs with no `on<Property>Changed` notification API.

Note that many, but not all, of these methods are pluralized to illustrate that they
return all possible values, rather than a single active value, e.g.:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.allVideoCodecs() // return the supported video codecs
```

The APIs are as follows:

 - `allVideoCodecs`
 - `allAudioCodecs`
 - `allDynamicRanges`
 - `allImmersiveAudioProfiles`
 - `allResolutions`
