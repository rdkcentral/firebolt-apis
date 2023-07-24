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
- [3. MimeTypes](#3-mimetypes)
- [4. Media Info](#4-media-info)
  - [4.1. MediaInfo for current app](#41-mediainfo-for-current-app)
    - [4.1.1. Video Codec](#411-video-codec)
    - [4.1.2. Audio Codec](#412-audio-codec)
    - [4.1.3. Dynamic Range](#413-dynamic-range)
    - [4.1.4. Immersive Audio](#414-immersive-audio)
    - [4.1.5. Frame Rate](#415-frame-rate)
    - [4.1.6. Resolution](#416-resolution)
  - [4.2. MediaInfo any Media Pipeline](#42-mediainfo-any-media-pipeline)
  - [4.3. MediaInfo an HDMI Input](#43-mediainfo-an-hdmi-input)
- [5. Device Media Capabilities](#5-device-media-capabilities)
  - [5.1. Dynamic Range](#51-dynamic-range)
  - [5.2. Video Codec](#52-video-codec)
  - [5.3. Immersive Audio](#53-immersive-audio)
  - [5.4. Audio Codec](#54-audio-codec)
  - [5.5. Resolution](#55-resolution)
- [6. APIs](#6-apis)
  - [6.1. Core SDK APIs](#61-core-sdk-apis)
  - [6.2. Manage SDK APIs](#62-manage-sdk-apis)
- [7. API PoC](#7-api-poc)
  - [7.1. App detecting it's own media info](#71-app-detecting-its-own-media-info)
  - [7.2. App w/ PiP detecting it's own media info](#72-app-w-pip-detecting-its-own-media-info)
  - [7.3. EPG detecting when Ogg codec is used](#73-epg-detecting-when-ogg-codec-is-used)

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
about any media actively being decoded by the Media Pipeline.

### 4.1. MediaInfo for current app

Apps need a way to query the media info for media currently being played  
by the app. All of the following methods take a single `pipeline`
parameter, which identifies the Media Pipeline in the current app's scope
that is being queried, e.g.:

```javascript
import { Media Info } from '@firebolt-js/sdk'

MediaInfo.videoCodec('1') // return the video codec in the current app's media pipeline 1
MediaInfo.videoCodec('2') // return the video codec in the current app's media pipeline 2
```

**TODO**: look at Rialto's Manage APIs to check on semantics of pipeline/app IDs.

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
playing. This API **MUST** return an number greater than or equal to `0`.

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

### 4.2. MediaInfo any Media Pipeline

First party apps need a way to query the media info for media currently
being played by *any* app.

The following APIs **MUST** exist:

-   `dynamicRangeProfileForApp`
-   `videoCodecForApp`
-   `isHdrForApp`
-   `audioProfileForApp`
-   `audioCodecForApp`
-   `isImmersiveAudioForApp`
-   `frameRateForApp`
-   `resolutionForApp`

These APIs **MUST** all be Firebolt `property:readonly` APIs with the
corresponding notifications.

These APIs take an `appId` parameter and a `pipeline` parameter identifying for which Media Pipeline the info is being requested.

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
| media-info:frame-rate    | frameRate           | frameRateForApp           |

*Capability names truncated for legibility

### 4.3. MediaInfo an HDMI Input

First party apps need a way to query the media info for media currently
being played via an HDMI input.

The following APIs **MUST** exist:

-   `dynamicRangeProfileForInput`
-   `videoCodecForInput`
-   `isHdrForInput`
-   `audioProfileForInput`
-   `audioCodecForInput`
-   `isImmersiveAudioForInput`
-   `frameRateForInput`
-   `resolutionForInput`

These APIs **MUST** all be Firebolt `property:readonly` APIs with the
corresponding notifications.

These APIs take an `inputId` parameter identifying for which Media Pipeline the info is being requested.

These APIs **MUST** all be gated by `manage` role of the same
capabilities required by the corresponding methods above, i.e.:

| Capability               | Use                 | Manage                    |
|--------------------------|---------------------|---------------------------|
| media-info:hdr           | dynamicRangeProfile | dynamicRangeProfileForInput |
| media-info:video-codec   | videoCodec          | videoCodecForInput          |
| media-info:hdr           | isHdr               | isHdrForInput               |
| media-info:audio-profile | audioProfile        | audioProfileForInput        |
| media-info:audio-codec   | audioCodec          | audioCodecForInput          |
| media-info:audio-profile | isImmersiveAudio    | isImmersiveAudioForInput    |
| media-info:frame-rate    | frameRate           | frameRateForInput           |

*Capability names truncated for legibility

## 5. Device Media Capabilities

In addition to surfacing info about the currently playing media, an app
may also want to know what types of media capabilities the *device* is
capable of.

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

### 5.1. Dynamic Range

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

### 5.2. Video Codec

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

### 5.3. Immersive Audio

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

### 5.4. Audio Codec

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

### 5.5. Resolution

The `Device` module **MUST** have a `resolution` API that returns
the native dimensions, e.g., `{ "width": 4096, "height": 2160 }`, the
device is currently rasterizing (if the device has a screen) or outputting
(if the device does not).

This API **MUST** return an object with two integers greater than or equal to `0`.
  
The resolution API **MUST** be a Firebolt `property:readonly` API, and
have a corresponding `onResolutionChanged` notification.

Use of the `resolution` API requires access to the `use` role of the
`xrn:firebolt:capability:device:info` capability.

## 6. APIs

### 6.1. Core SDK APIs

The JavaScript Core SDK will have a generated, client-side method, `getPipeline`. This method takes a single paramter, which represents a Media Pipeline session id for the current app.

It returns a wrapped up interface of all `xrn:firebolt:capability:media-info:*` use capabilities, and caches the session ID so there is no need to pass it to every method call.

Example:

```javascript
import { MediaInfo } from '@firebolt-js/sdk'

const mediaInfo = MediaInfo.getPipeline('1')

console.log(mediaInfo.dynamicRangeProfile())
```

### 6.2. Manage SDK APIs
The JavaScript manage SDK will have a generated, client-side method, `getHDMI`. This method takes a single paramter, which represents an HDMI input id.

It returns a wrapped up interface of all `xrn:firebolt:capability:media-info:*` use capabilities, and caches the session ID so there is no need to pass it to every method call.

**TODO**:

Write up a sample of each API style we are considering for Core, Manage, and Manage-HDMI, so we can compare.


Example:

```javascript
import { MediaInfo } from '@firebolt-js/manage-sdk'

const hdmiInfo = MediaInfo.getHdmi('hdmi1')

console.log(hdmiInfo.dynamicRangeProfile())

const appInfo = MediaInfo.getPipelineForApp('hulu', '1')

await MediaInfo.videoCodecs().forEach(pipeline => {
  console.log(pipeline.videoCodecs())
})

MediaInfo.dynamicRangeProfile((profile) => {
  if (profile === 'dolbyVision') {

  }
})

console.log(appInfo.audioProfile())
```

## 7. API PoC

### 7.1. App detecting it's own media info

```javascript
import { MediaInfo, Device, Codecs } from '@firebolt-js/sdk'

if (MediaInfo.videoCodec() === Codecs.VIDEO_OGG) {
  console.log('why do i use this codec?')
}
```

### 7.2. App w/ PiP detecting it's own media info

```javascript
import { MediaInfo, Device, Codecs } from '@firebolt-js/sdk'

if (MediaInfo.videoCodec('2') === Codecs.VIDEO_OGG) {
  console.log('why do i use this codec?')
}
```

### 7.3. EPG detecting when Ogg codec is used

```javascript
import { MediaInfo, Device, Codecs } from '@firebolt-js/manage-sdk'

MediaInfo.listen('videoCodecForPipelineChanged', (event) => {
  if (event.type === 'hdmi' {
    console.log('HDMI codec changed to: ' + event.codec)
    if (event.codec === Codecs.VIDEO_OGG) {
      console.log('why am i using this codec?')
    } 
  }
  else if (event.type === 'streaming') {
    console.log('App id ' + event.appId + ' codec changed to: ' + event.codec + ' on pipeline ' + event.pipeline)
    if (event.codec === Codecs.VIDEO_OGG) {
      console.log('why am i using this codec?')
    } 
  }
})
```

