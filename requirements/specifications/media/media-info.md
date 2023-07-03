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
  - [3.2. MediaInfo for other apps](#32-mediainfo-for-other-apps)
  - [3.3. Media Info and the Media Pipeline](#33-media-info-and-the-media-pipeline)
  - [3.4. Core SDK APIs](#34-core-sdk-apis)
  - [3.5. Manage SDK APIs](#35-manage-sdk-apis)
- [4. Media Capabilities](#4-media-capabilities)
  - [4.1. Dynamic Range](#41-dynamic-range)
  - [4.2. Immersive Audio](#42-immersive-audio)

## 3. Media Info

The Firebolt `MediaInfo` module consists of APIs to get information
about any media actively being decoded by the Media Pipeline.

### 3.1. MediaInfo for current app

Apps need a way to query the media info for media currently being played
by the app.

#### 3.1.1. Dynamic Range

The `MediaInfo` module **MUST** have a `dynamicRangeProfile` API that
returns the dynamic range profile, e.g., SDR, HDR, HDR10, etc., of the
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

### 3.2. MediaInfo for other apps

First party apps need a way to query the media info for media currently
being played by *any* app.

The following APIs **MUST** exist:

-   `dynamicRangeProfileForApp`
-   `videoCodecForApp`
-   `isHdrForApp`
-   `audioProfileForApp`
-   `audioCodecForApp`
-   `isImmersiveAudioForApp`

These APIs **MUST** all be Firebolt `property:readonly` APIs with the
corresponding notifications.

These APIs **MUST** all be gated by `manage` role of the same
capabilities required by the corresponding methods above, i.e.:

| Capability               | Use                 | Manage                    |
|--------------------------|---------------------|---------------------------|
| media-info:hdr           | dynamicRangeProfile | dynamicRangeProfileForApp |
| media-info:video-codec   | videoCodec          | videoCodecForApp          |
| media-info:hdr           | isHdr               | isHdrForApp               |
| media-info:audio-profile | audioProfile        | audioProfileForApp        |
| media-info:audio-codec   | audioCodec          | audioCodecForApp          |
| media-info:audio-profile | isImmersiveAudio    | isImmersiveAudioForApp    |

*Capability names truncated for legibility

### 3.3. Media Info and the Media Pipeline

All of the APIs in the `MediaInfo` module **SHOULD** treat the
`MediaPipeline` API as the source of truth, and get these values, on
demand, from the appropriate MediaPipeline APIs. See [Media Pipeline
Requirements](https://comcastcorp.sharepoint.com/:w:/r/sites/hqppa/Shared%20Documents/Global%20App%20Platform/Firebolt/Requirements/Core/Media/Media%20Pipeline%20Requirements.docx?d=wd7548d7c54fc443098a5dc6c0e63a4f9&csf=1&web=1&e=lRlFLq)
for more info.

**TODO**: evaluate any MediaPipeline gaps to fulfill the above
requirement.

### 3.4. Core SDK APIs

...

### 3.5. Manage SDK APIs

...

## 4. Media Capabilities

In addition to surfacing info about the currently playing media, an app
may also want to know what types of media capabilities the *device* is
capable of.

To facilitate this, the Device module will have similar methods that
return all possible values supported on the device.

### 4.1. Dynamic Range

The `Device` module **MUST** have a `dynamicRangeProfiles` API that
returns the dynamic range profiles, e.g., SDR, HDR, HDR10, etc., that
are supported on the device. This API **MUST** return an array with one
or more of the following values:

-   `"none"`
-   `"hdr10"`
-   `"hdr10plus"`
-   `"dolbyVision"`
-   `"slHdr1"`

The dynamicRangeProfiles API **MUST** be a Firebolt
`property:immutable` API.

Use of the `dynamicRangeProfiles` API requires access to the `use`
role of the `xrn:firebolt:capability:device:info` capability.

This method deprecates the `Device.hdr` API.

### 4.2. Immersive Audio

The `Device` module **MUST** have an `audioProfiles` API that returns
the immersive (or not) audio profiles, e.g., Dolby Atmos, etc., that are
supported on the device. This API **MUST** return an array with one or
more of the following values:

-   `"auro3d"`
-   `"dolbyAtmos"`
-   `"dtsx"`
-   `"mpegh"`
-   `"none"`

The audioProfiles API **MUST** be a Firebolt `property:immutable` API.

Use of the `audioProfiles` API requires access to the `use` role of
the `xrn:firebolt:capability:device:info` capability.

This method deprecates the `Device.audio` API.
