# Media Access

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Anthony Borzotta           | Comcast           |
| Jeremy LaCivita | Comcast |

## 1. Overview

Many apps will need to make use of audio, video, images, and other
assets that are cultivated by the user of the device rather than by an
app or content provider. For example, an app might want to allow a user
to upload a photo to be used as a profile picture or provide a slide
show of photos from a connected USB device.

Giving such apps full access to the filesystem to facilitate access to
the user's personally cultivated media is providing far too much
information for such a simple use case. On the other hand, providing a
platform file picker UI might not enable the richness of experience that
app developers need.

The apps that would use this feature are primarily interested in user
cultivated media files, and where they came from, e.g., USB or a cloud
photo storage provider, etc., is of secondary or no importance. This API
is intended to expose user cultivated media in a convenient, file-system
agnostic, storage-agnostic way.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Media Access](#3-media-access)
  - [3.1. Listing Media Files](#31-listing-media-files)
  - [3.2. Accessing Volumes](#32-accessing-volumes)
  - [3.3. Volume Availability](#33-volume-availability)
  - [3.4. Accessing Files](#34-accessing-files)
  - [3.5. Core APIs](#35-core-apis)
    - [3.5.1. Volumes](#351-volumes)
    - [3.5.2. Audio, Video, Images, Files](#352-audio-video-images-files)
  - [3.6. Schemas](#36-schemas)
    - [3.6.1. MediaFile](#361-mediafile)
    - [3.6.2. Volume](#362-volume)
    - [3.6.3. VolumeType](#363-volumetype)

## 3. Media Access

The Firebolt `MediaAccess` module consists of APIs to list and read
various types of `MediaFile`. It also contains APIs for detecting when
new `MediaFile` Volumes are available.

### 3.1. Listing Media Files

The following APIs are used to return a list of `MediaFile` objects:

-   `MediaAccess.audio()`

-   `MediaAccess.images()`

-   `MediaAccess.video()`

-   `MediaAccess.media()`

-   `MediaAccess.files()`

These APIs **MUST** support an optional `volume` parameter of type
`Volume`.

If `volume` is provided, then these APIs **MUST** return all *matching*
(see below) `MediaFile` objects on user-granted volumes that match the
`volume` parameter. The if the `volume` parameter has `undefined` or
`null` properties, then those properties are not used to filter out
volumes from the list. For example a value of `{ type: "usb" }`
would return all matching `MediaFile` objects on any USB volumes.

If `volume` is not provided, then these APIs **MUST** return all
*matching* `MediaFiles` on all user-granted volumes.

These APIs **MUST** support an optional `files` parameter of type
`MediaFile`.

If files is provided, then these APIs **MUST** return all matching (see
below) ) `MediaFile` objects on user-granted volumes that match the
`files` parameter. The if the `files` parameter has `undefined` or
`null` properties, then those properties are not used to filter out
files from the list. For example a value of
`{ type: "application/mp3" }` would return all matching
`MediaFile` objects that have the mp3 mime type.

Wildcards, e.g. `{ uri: "*.mp3" }` are **not** supported.

**NOTE**: if this is easy we can reconsider...

If both `volume` and `files` are provided, then these APIs **MUST**
return all `MediaFiles` that match the volume parameter **AND** the
files parameter.

Each `MediaFile` includes the full URI, so that Apps may present them in
a manner that matches the directory structure on the `Volume`.

In order to call the `MediaAccess.audio()` API an app **MUST** have
permission to use the `xrn:firebolt:capability:media-access:audio`
capability.

The `MediaAccess.audio()` API only matches media that have a mime-type
of `audio/*`.

In order to call the `MediaAccess.images()` API an app **MUST** have
permission to use the `xrn:firebolt:capability:media-access:images`
capability.

The `MediaAccess.images()` API only matches media that have a
mime-type of `image/*`.

In order to call the `MediaAccess.video()` API an app **MUST** have
permission to use the `xrn:firebolt:capability:media-access:video`
capability.

The `MediaAccess.video()` API only matches media that have a
mime-type of `video/*`.

In order to call the `MediaAccess.media()` API an app **MUST** have
permission to use at least one of the the
`xrn:firebolt:capability:media-access:` capabilities for `audio`,
`images`, or `video`.

The `MediaAccess.media()` API only matches `MediaFile` objects that
the app has permission to, i.e. files that would have been returned from
`audio()`, `images()`, and `video()`.

In order to call the `MediaAccess.files()` API an app **MUST** have
permission to use the `xrn:firebolt:capability:media-access:files`
capability.

The `MediaAccess.files()` API matches all files on user-granted
volumes on multiple media storage devices connected to the TV/STB such
as USB Drive1, USB Drive2 etc . It's left to the app on how to use the
content and present to users to play, e.g. all files in a file explorer
UI, or various Tiles grouped under different sections based on media
type: Videos, Audio, Images, Misc., etc.

### 3.2. Accessing Volumes

Having permission to use the various media access capabilities is not
enough. An app **MUST** also have access to each volume if the device is
configured to require a User Grant to access new volumes.

To configure this, Distributors **MAY** configure a `GrantPolicy` on the
`xrn:firebolt:capability:volume:read` capability. This capability is
public and non-negotiable, so that distributors do not need to keep
track of which public APIs use it.

The default Firebolt `GrantPolicy` **MUST** be:

```json
{
    scope: "app",
    lifespan: "forever",
    overridable: true,
    options: [
        {
            steps: [
                {
                    capability: "xrn:firebolt:capability:usergrant:acknowledge",
                }
            ]
        }
    ]
}
```

This grant policy allows distributors to configure the `GrantPolicy` in
whatever way they want, including automatically granting.

Finally, the `GrantPolicy` object itself will have a new Boolean
configuration value, `perResource` for determining if a particular
policy is per resource or just for the capability as a whole.

If `perResource` is true, then a `resource` name `string` **MUST** be
passed when checking the grant status, and the resources that have been
granted **MUST** be persisted in the grant status.

For the `MediaAccess` APIs, the `resource` string will be the `uri` of
the media file to be played on a specific **Volume**.

This results in the first time an app wants to access MediaFiles on a
volume, the platform will check if the app not only has access to the
API used, but also the device being queried.

### 3.3. Volume Availability

Apps that consume user cultivated media will likely want to know when
volumes become available or unavailable.

This is accomplished with a temporal-set API called `volumes()`.

The volumes API **MUST** support a context parameter of type for the
Volume Type, e.g. `usb`, `local`, or `all`.

See [Temporal Sets](../openrpc-extensions/temporal-set.md) for more info.

### 3.4. Accessing Files

In order to do something with the file, apps will need access to the
file contents.

Firebolt platforms **MUST** provide a local `https` server for apps to
request MediaFiles.

The server **MUST** be reachable via the IP address 127.0.0.1

The server **MUST** only be accessible via `https` and have a valid,
self-signed certificate trusted by the browser.

**NOTE: does using an IP address mean we can't use SSL? Do we need a
fake domain name? Do we even need SSL if the host is 127.0.0.1?**

Authorization **MUST** be obtained by the Firebolt SDK using an
`rpc-only` authorize method.

Authorization **MUST** be short lived, e.g. less than 5 seconds.

To facilitate Authorization, Firebolt **MUST** offer an API to fetch the
file contents. The name of this API should be determined by the target
language of the SDK.

In the JavaScript SDK, the `MediaFile` schema **MUST** include an
`x-method` property called `fetch` that calls the ECMAScript `fetch` API
with a short-lived authorization token and returns the ECMAScript
`Response` object. See [Response Methods](../openrpc-extensions/response-method.md)
for more info on x-method properties.

In the JavaScript SDK, the `fetch` method **MUST** be called from within
an ECMAScript `Worker`, to avoid slowing down the app.

SDKs for other languages **SHOULD** come up with similar optimizations
using appropriate API names.

![Diagram Description automatically
generated](../../images/specifications/media/access/media/image1.png)

NOTE: This is (currently in XumoTV) handled by the ECMAScript `fetch`
method by passing a `file://` URI containing the `MediaFile` path. We
need to fix this!!

### 3.5. Core APIs

The following APIs are added to the Core SDK.

#### 3.5.1. Volumes

The `volumes` method can be called in one of three ways.

The get the currently cached list of Volumes w/out scanning call the
method with just a `query` parameter:

function volumes(query: Volume): Promise\<Volume[]\>

This returns the Volumes that the device is aware or, that match the
query, without checking if there are any new volumes.

To find the first volume that matches a query, pass in a `query` and a
`timeout`, in milliseconds, representing how long the app is willing to
wait.

function volumes(query: Volume, timeout: number): Promise\<Volume\>

This returns a `Volume` object if a match is found before the `timeout`.

To initiate a live temporal set that updates continuously, call the
method with a `query`, an `add` callback and a `remove` callback:

function volumes(query: Volume, add: (item: Volume) =\> void, remove:
(item: Volume) =\> void): VolumeProcess

This will initiate an open-ended scan for volumes matching the query and
call the callbacks when a device becomes available or unavailable.

This method returns a `VolumeProcess` object, synchronously, that
contains a single `stop()` method for cancelling the temporal-set
session.

#### 3.5.2. Audio, Video, Images, Files

These APIs return all the files that match the associated capability,
and the Volume query parameter:

function audio(volumes?: Volume, files?: MediaFile):
Promise\<MediaFile[]\>

function video(volumes?: Volume, files?: MediaFile):
Promise\<MediaFile[]\>

function images(volumes?: Volume, files?: MediaFile):
Promise\<MediaFile[]\>

function media(volumes?: Volume, files?: MediaFile):
Promise\<MediaFile[]\>

function files(volumes?: Volume, files?: MediaFile):
Promise\<MediaFile[]\>

The `volumes` and `files` parameters can be sparsely populated, e.g.
passing in `{ type: "usb" }` to the `audio` method would return
all audio files on any USB drive.

### 3.6. Schemas

The following Schemas are used by this API.

#### 3.6.1. MediaFile

This is the primary object return by the various APIs.

| Property | Type   | Description                                  |
|----------|--------|----------------------------------------------|
| volume   | Volume | The Volume the file is stored on             |
| uri      | string | The full path, including volume, to the file |
| type     | string | The mime-type of the file                    |

#### 3.6.2. Volume

This provides information about a Volume, e.g. a Device, that stores
MediaFiles.

| Property | Type       | Description                                       |
|----------|------------|---------------------------------------------------|
| type     | VolumeType | The type of volume, e.g. USB                      |
| uri      | string     | The full path to the root of the volume's storage |
| name     | string     | The display name of the volume                    |

#### 3.6.3. VolumeType

An enumeration of strings representing possible Volume types:

-   `'usb'`

-   `'local'`
