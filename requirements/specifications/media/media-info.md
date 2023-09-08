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

**TODO**: needs a refresh based on all the changes we've made

In some cases, an app will need to be aware of what media formats and
codecs are playing, even for media files which were cultivated outside of the
app provider's purview, e.g. playing MP3 files in a generic media player
app (see [Media Access
Requirements](./media-access.md)
for more info).

In cases like this, the app may have a requirement to display the type
of media being displayed, e.g., "Dolby Audio."

As a W3C-based platform, there is no standard API for detecting media
formats or codecs that works in all cases, short of inspecting the bytes
of the media in the app itself.

To solve this, Firebolt APIs will be created to detect the formats and
codecs currently being decoded by the [Media
Pipeline](./media-pipeline.md) or an active HDMI input.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. MimeTypes](#3-mimetypes)
- [4. Media Capabilities](#4-media-capabilities)
  - [4.1. Video Codec](#41-video-codec)
  - [4.2. Audio Codec](#42-audio-codec)
  - [4.3. Dynamic Range](#43-dynamic-range)
  - [4.4. Immersive Audio](#44-immersive-audio)
  - [4.5. Resolution](#45-resolution)
- [5. Media Info](#5-media-info)
  - [5.1. MediaInfo for current app](#51-mediainfo-for-current-app)
    - [5.1.1. Video Codec](#511-video-codec)
    - [5.1.2. Audio Codec](#512-audio-codec)
    - [5.1.3. Dynamic Range](#513-dynamic-range)
    - [5.1.4. Immersive Audio](#514-immersive-audio)
    - [5.1.5. Frame Rate](#515-frame-rate)
    - [5.1.6. Resolution](#516-resolution)
  - [5.2. MediaInfo for Pipeline](#52-mediainfo-for-pipeline)
  - [5.3. Global MediaInfo](#53-global-mediainfo)
- [6. Device Media Capabilities](#6-device-media-capabilities)
  - [6.1. Video Codec](#61-video-codec)
  - [6.2. Audio Codec](#62-audio-codec)
  - [6.3. Dynamic Range](#63-dynamic-range)
  - [6.4. Immersive Audio](#64-immersive-audio)
  - [6.5. Resolutions](#65-resolutions)

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

## 4. Media Capabilities

Apps need to know what types of media capabilities the current *device configuration*,
e.g. a Firebolt STB connected to an HDMI television, is capable of.

To facilitate this, the `MediaInfo` module will have a set of methods that
return all possible values supported by the current device configuration.

These values change and different AV inputs are activated or conntected.

Note that many, but not all, of these methods are pluralized to illustrate that they
return all possible values, rather than a single active value, e.g.:

```javascript
import { Device } from '@firebolt-js/sdk'

MediaInfo.videoCodecs() // return the supported video codecs
```

### 4.1. Video Codec

The `MediaInfo` module **MUST** have a `videoCodecs` API that returns the
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

Use of the `videoCodecs` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

### 4.2. Audio Codec

The `MediaInfo` module **MUST** have an `audioCodecs` API that returns
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

Use of the `audioCodecs` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

### 4.3. Dynamic Range

The `MediaInfo` module **MUST** have a `dynamicRangeProfiles` API that
returns the dynamic range profiles, e.g., HDR, HDR10, etc., tthat are
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

### 4.4. Immersive Audio

The `MediaInfo` module **MUST** have an `audioProfiles` API that returns
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

The `MediaInfo` module **MUST** have an `supportsImmersiveAudio` API that
returns true if the value of `audioProfiles` contains any of the
values beyond `none`.

The `supportsImmersiveAudio` API **MUST** be a Firebolt `property:readonly`
API, and have a corresponding `onSupportsImmersiveAudioChanged`
notification.

Use of the `audioProfiles` and `supportsImmersiveAudio` APIs require access
to the `use` role of the `xrn:firebolt:capability:device:info` capability.

### 4.5. Resolution

The `MediaInfo` module **MUST** have a `resolution` API that returns
the native dimensions, e.g., `{ "width": 4096, "height": 2160 }`, the
device is currently rasterizing (if the device has a screen) or outputting
(if the device does not).

This API **MUST** return an object with two integers greater than or equal to `0`.
  
The resolution API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onResolutionChanged` notification.

Use of the `resolution` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

## 5. Media Info

The Firebolt `MediaInfo` module consists of APIs to get information
about any media actively being decoded by the Media Pipeline or an active HDMI input.

### 5.1. MediaInfo for current app

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

#### 5.1.1. Video Codec

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

#### 5.1.2. Audio Codec

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

#### 5.1.3. Dynamic Range

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

#### 5.1.4. Immersive Audio

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

#### 5.1.5. Frame Rate

The `MediaInfo` module **MUST** have a `frameRate` API that returns
the frame rate, e.g., 24, of the media currently
playing. This API **MUST** return an number greater than or equal to `0`.

If no video is playing, then this API **MUST** return `0`.
  
The audioCodec API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onFrameRateChanged` notification.

Use of the `frameRate` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:frame-rate` capability.

#### 5.1.6. Resolution

The `MediaInfo` module **MUST** have a `resolution` API that returns
the encoded dimensions, e.g., `{ "width": 4096, "height": 2160 }`, of the media currently
playing. Note that this has nothing to do with the dimensions rasterized on the screen (see the Device [Resolution](#312-resolution) API for that).
This API **MUST** return an object with two integers greater than or equal to `0`.
  
The resolution API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onResolutionChanged` notification.

Use of the `resolution` APIs require access to the `use` role of the
`xrn:firebolt:capability:media-info:resolution` capability.

**TODO**: should resolution be an enum, rather than unbounded integers?

### 5.2. MediaInfo for Pipeline

```typescript
MediaInfo.dynamicRangeProfileActive(DOLBY_ATMOS): Promise<boolean>
MediaInfo.dynamicRangeProfileActive(DOLBY_ATMOS): Promise<boolean>
MediaInfo.dynamicRangeProfile<TBD>(pipelineId: integer): Promise<string>
```

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

### 5.3. Global MediaInfo

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

## 6. Device Media Capabilities

In addition to surfacing capabilities about the currently device configuration,
an app may also want to know what types of media capabilities the *device* is
possibly capable of, regardless of what inputs and outputs may be connected.

To facilitate this, the `Device` module will have similar methods that
return all possible values supported on the device.

Note that many, but not all, of these methods are pluralized to illustrate that they
return all possible values, rather than a single active value.

The APIs in this section do not need any parameters to identify
pipeline, etc, e.g.:

```javascript
import { Device } from '@firebolt-js/sdk'

Device.videoCodecs() // return the supported video codecs
```

### 6.1. Video Codec

The `Device` module **MUST** have a `videoCodecs` API that returns the
video codecs, e.g., H.265, VP9, etc., that are currently supported by the
device. This API **MUST** return an Array with one or more of the following
values:

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

Use of the `videoCodecs` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

### 6.2. Audio Codec

The `Device` module **MUST** have an `audioCodecs` API that returns
the audio codecs, e.g., ac3, ac4, ogg, etc., currently supported by the
device. This API **MUST** return an Array with one or more of the
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

Use of the `audioCodecs` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

### 6.3. Dynamic Range

The `Device` module **MUST** have a `dynamicRangeProfiles` API that
returns the dynamic range profiles, e.g., HDR, HDR10, etc., that are
currently supported by the device. This API **MUST** return an Array
with one or more of the following values:

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

The `Device` module **MUST** have an `supportsHDR` API that returns true if
the value of `dynamicRangeProfiles` contains any of the values beyond `none`
and `unknown`.

The `supportsHDR` API **MUST** be a Firebolt `property:readonly` API, and have
a corresponding `onSupportsHDRChanged` notification.

Use of the `dynamicRangeProfiles` and `supportsHDR` APIs require access to the
`use` role of the `xrn:firebolt:capability:device:info`
capability.

### 6.4. Immersive Audio

The `Device` module **MUST** have an `audioProfiles` API that returns
the immersive (or not) audio profiles, e.g., Dolby Atmos, etc., that are
currently supported by the device. This API **MUST** return an Array with
one ore more of the following values:

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

### 6.5. Resolutions

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
