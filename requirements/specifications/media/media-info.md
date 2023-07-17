# Requirements Style Guide

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Anthony Borzota            | Comcast            |
| Jeremy LaCivita | Comcast |

## 1. Overview

In some cases, an app will need to be aware of what media formats and
codecs are playing, even for media files were cultivated outside of the
app provider's purview, e.g. playing MP3 files in a generic media player
app (see [Media Access
Requirements](https://comcastcorp.sharepoint.com/:w:/r/sites/hqppa/Shared%20Documents/Global%20App%20Platform/Firebolt/Requirements/Core/Media/Media%20Access%20Requirements.docx?d=w4185f84db06746b2b4564068e57937cb&csf=1&web=1&e=5vUs9I)
for more info).

In cases like this, the app may have a requirement to display the type
of media being displayed, e.g., "Dolby Audio."

As a W3C-based platform, there is no standard API for detecting media
formats or codecs that works in all cases, short of inspecting the bytes
of the media in the app itself.

To solve this, Firebolt APIs will be created to detect the formats and
codecs currently being decoded by the [Media
Pipeline](./media-pipeline.md).

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Media Info](#3-media-info)
  - [3.1. MediaInfo for current app](#31-mediainfo-for-current-app)
    - [3.1.1. Dynamic Range](#311-dynamic-range)
    - [3.1.2. Video Codec](#312-video-codec)
    - [3.1.3. Immersive Audio](#313-immersive-audio)
    - [3.1.4. Audio Codec](#314-audio-codec)
    - [3.1.5. Frame Rate](#315-frame-rate)
    - [3.1.6. Resolution](#316-resolution)
  - [3.2. MediaInfo any Media Pipeline or HDMI input](#32-mediainfo-any-media-pipeline-or-hdmi-input)
- [4. Device Media Capabilities](#4-device-media-capabilities)
  - [4.1. Dynamic Range](#41-dynamic-range)
  - [4.2. Video Codec](#42-video-codec)
  - [4.3. Immersive Audio](#43-immersive-audio)
  - [4.4. Audio Codec](#44-audio-codec)
  - [4.5. Resolution](#45-resolution)
- [5. APIs](#5-apis)
  - [5.1. Core SDK APIs](#51-core-sdk-apis)
  - [5.2. Manage SDK APIs](#52-manage-sdk-apis)

## 3. Media Info

The Firebolt `MediaInfo` module consists of APIs to get information
about any media actively being decoded by the Media Pipeline.

### 3.1. MediaInfo for current app

Apps need a way to query the media info for media currently being played  
by the app.

#### 3.1.1. Dynamic Range

The `MediaInfo` module **MUST** have a `dynamicRangeProfile` API that
returns the dynamic range profile, e.g., HDR, HDR10, etc., of the
media currently playing. This API **MUST** return one of the following
values:

-   `"none"`
-   `"hdr10"`
-   `"hdr10plus"`
-   `"dolbyVision"`
-   `"slHdr1"`
-   `"hlg" `
-   `"unknown"`

The dynamicRangeProfile API **MUST** be a Firebolt `property:readonly`
API, and have a corresponding `onDynamicRangeProfileChanged`
notification.

The `MediaInfo` module **MUST** have an `isHDR` API that returns true if
the value of `dynamicRangeProfile` is currently any of the values
excluding `none` and `unknown`.

The `isHDR` API **MUST** be a Firebolt `property:readonly` API, and have
a corresponding `onIsHDRChanged` notification.

Use of the `dynamicRangeProfile` and `isHDR` APIs requires access to the
`use` role of the `xrn:firebolt:capability:media-info:hdr`
capability.

#### 3.1.2. Video Codec

The `MediaInfo` module **MUST** have a `videoCodec` API that returns the
video codec, e.g., H.265, VP9, etc., of the media currently in the
media pipeline (either playing or paused). This API **MUST** return
one of the following values:

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

The videoCodec API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onVideoCodecChanged` notification.

Use of the `videoCodec` APIs requires access to the `use` role of the
`xrn:firebolt:capability:media-info:video-codec` capability.

#### 3.1.3. Immersive Audio

The `MediaInfo` module **MUST** have an `audioProfile` API that returns
the immersive (or not) audio profile, e.g., Dolby Atmos, etc., of the
media currently playing. This API **MUST** return one of the following
values:

-   `"auro3d"`
-   `"dolbyAtmos"`
-   `"dtsx"`
-   `"mpegh"`
-   `"unknown"`
-   `"none"`

The audioProfile API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioProfileChanged` notification.

The `MediaInfo` module **MUST** have an `isImmersiveAudio` API that
returns true if the value of `audioProfile` is currently any of the
values excluding `none`.

The `isImmersiveAudio` API **MUST** be a Firebolt `property:readonly`
API, and have a corresponding `onIsImmersiveAudioChanged`
notification.

Use of the `audioProfile` and `isImmersiveAudio` APIs requires access
to the `use` role of the
`xrn:firebolt:capability:media-info:audio-profile` capability.

#### 3.1.4. Audio Codec

The `MediaInfo` module **MUST** have an `audioCodec` API that returns
the audio codec, e.g., ac3, ac4, ogg, etc., of the media currently
playing. This API **MUST** return one of the following values:

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
  
The audioCodec API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioCodecChanged` notification.

Use of the `audioCodec` APIs requires access to the `use` role of the
`xrn:firebolt:capability:media-info:audio-codec` capability.

#### 3.1.5. Frame Rate

The `MediaInfo` module **MUST** have a `frameRate` API that returns
the frame rate, e.g., 24, of the media currently
playing. This API **MUST** return an number greater than or equal to `0`.

If no video is playing, then this API **MUST** return `0`.
  
The audioCodec API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onFrameRateChanged` notification.

Use of the `frameRate` APIs requires access to the `use` role of the
`xrn:firebolt:capability:media-info:frame-rate` capability.

#### 3.1.6. Resolution

The `MediaInfo` module **MUST** have a `resolution` API that returns
the encoded dimensions, e.g., `{ "width": 4096, "height": 2160 }`, of the media currently
playing. Note that this has nothing to do with the dimensions rasterized on the screen (see the Device [Resolution](#312-resolution) API for that).
This API **MUST** return an object with two integers greater than or equal to `0`.
  
The resolution API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onResolutionChanged` notification.

Use of the `resolution` APIs requires access to the `use` role of the
`xrn:firebolt:capability:media-info:resolution` capability.

### 3.2. MediaInfo any Media Pipeline or HDMI input

First party apps need a way to query the media info for media currently
being played by *any* app or input.

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

These APIs take a `pipeline` parameter identifying for which Media Pipeline the info is being requested.

**TODO**: look at Rialto's Manage APIs to check on semantics of pipeline/app IDs.

These APIs **MUST** all be gated by `manage` role of the same
capabilities required by the corresponding methods above, i.e.:

| Capability               | Use                 | Manage                    |
|--------------------------|---------------------|---------------------------|
| media-info:hdr           | dynamicRangeProfile | dynamicRangeProfileForPipeline |
| media-info:video-codec   | videoCodec          | videoCodecForPipeline          |
| media-info:hdr           | isHdr               | isHdrForPipeline               |
| media-info:audio-profile | audioProfile        | audioProfileForPipeline        |
| media-info:audio-codec   | audioCodec          | audioCodecForPipeline          |
| media-info:audio-profile | isImmersiveAudio    | isImmersiveAudioForPipeline    |
| media-info:frame-rate    | frameRate           | frameRateForPipeline           |

*Capability names truncated for legibility

If the `pipeline` parameter starts with `xrn:firebolt:media:hdmi:` and ends with an integer, then the API is requesting info for that HDMI input.

## 4. Device Media Capabilities

In addition to surfacing info about the currently playing media, an app
may also want to know what types of media capabilities the *device* is
capable of.

To facilitate this, the `Device` module will have similar methods that
return all possible values supported on the device.

### 4.1. Dynamic Range

The `Device` module **MUST** have a `dynamicRangeProfile` API that
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

The dynamicRangeProfile API **MUST** be a Firebolt `property:readonly`
API, and have a corresponding `onDynamicRangeProfileChanged`
notification.

The `Device` module **MUST** have an `supportsHDR` API that returns true if
the value of `dynamicRangeProfile` contains currently any of the values
beyond `none` and `unknown`.

The `supportsHDR` API **MUST** be a Firebolt `property:readonly` API, and have
a corresponding `onSupportsHDRChanged` notification.

Use of the `dynamicRangeProfile` and `supportsHDR` APIs requires access to the
`use` role of the `xrn:firebolt:capability:device:info`
capability.

### 4.2. Video Codec

The `Device` module **MUST** have a `videoCodec` API that returns the
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

The videoCodec API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onVideoCodecChanged` notification.

Use of the `videoCodec` APIs requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

### 4.3. Immersive Audio

The `Device` module **MUST** have an `audioProfile` API that returns
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
have a corresponding `onAudioProfileChanged` notification.

The `Device` module **MUST** have an `supportsImmersiveAudio` API that
returns true if the value of `audioProfile` is currently any of the
values excluding `none`.

The `supportsImmersiveAudio` API **MUST** be a Firebolt `property:readonly`
API, and have a corresponding `onSupportsImmersiveAudio`
notification.

Use of the `audioProfile` and `isImmersiveAudio` APIs requires access
to the `use` role of the `xrn:firebolt:capability:device:info` capability.

### 4.4. Audio Codec

The `Device` module **MUST** have an `audioCodec` API that returns
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
  
The audioCodec API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onAudioCodecChanged` notification.

Use of the `audioCodec` APIs requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

### 4.5. Resolution

The `Device` module **MUST** have a `resolution` API that returns
the native dimensions, e.g., `{ "width": 4096, "height": 2160 }`, the
device is currently rasterizing (if the device has a screen) or outputting
(if the device does not).

This API **MUST** return an object with two integers greater than or equal to `0`.
  
The resolution API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onResolutionChanged` notification.

Use of the `resolution` APIs requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

## 5. APIs

### 5.1. Core SDK APIs

Example:

```javascript
import { MediaInfo } from '@firebolt-js/sdk'

const mediaInfo = MediaInfo.getSession('1')

console.log(mediaInfo.dynamicRangeProfile())
```

### 5.2. Manage SDK APIs
Example:

```javascript
import { MediaInfo } from '@firebolt-js/manage-sdk'

const hdmiInfo = MediaInfo.getSession('xrn:firebolt:media:hdmi:1')

console.log(hdmiInfo.dynamicRangeProfile())

const appInfo = MediaInfo.getSession('hulu:1')

console.log(appInfo.audioProfile())
```