# App Presentation
need to write this up...

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor    | Organization   |
| -------------- | -------------- |
| Andrew Bennet            | Sky            |
| Cody Bonney   | Charter |
| Bart Catrysse            | Liberty           |
| Tim Dibben            | Sky            |
| Jeremy LaCivita            | Comcast            |
| Ramprasad Lakshminarayana | Sky |
| Kevin Pearson            | Comcast            |
| Peter Yu            | Comcast           |


## 1. Overview
TBD...

- [1. Overview](#1-overview)
- [2. Display](#2-display)
  - [2.1. Display vs Lifecycle](#21-display-vs-lifecycle)
- [3. Overlay](#3-overlay)
- [4. Off-screen Video](#4-off-screen-video)
- [5. Platform-provided Loading Screen](#5-platform-provided-loading-screen)
- [6. App-provided Loading Screen](#6-app-provided-loading-screen)


## 2. Display
The `Presentation` module **MUST** have a `display` string property that returns one of the following values:

| Value | Description |
|-------|-------------|
| `FULLSCREEN` | The app is displayed such that the dimensions fill the entire screen |
| `OFFSCREEN`  | The app is not displayed on the screen at all |
| `SCALED`     | The app is displayed at a size smaller than the entire screen but at least 25% of the width or height |
| `THUMBNAIL` | The app is displayed at a size smaller than 25% of the width or height of the entire screen |
| `LOADING` | The platform is displaying a loading screen while  the app loads | 

### 2.1. Display vs Lifecycle
Each Lifecycle state only supports certain display states:

| Lifecycle | Supported Displays |
|-------|-------------|
| `FOREGROUND` | `FULLSCREEN`, `SCALED` |
| `BACKGROUND` | `FULLSCREEN`, `SCALED`, `THUMBNAIL` |
| `STARTED`    | `OFFSCREEN` |
| `SUSPENDED`  |             |

See [Off-screen Video](#2-offscreen-video) for an exception to this.

## 3. Overlay
The `Presentation` module **MUST** have an `overlay` string property that returns one of the following values:

| Value | Description |
|-------|-------------|
| `ICON` | There is an informative icon, e.g. volume, on top of the app. |
| `BAND`  | There is a horizontal overlay at the top or bottom of the app. |
| `SIDEBAR`     | There is a vertical sidebar covering less than 33% of the app on one side. |
| `BLOCKED` | There is a significantly sized UX covering a majority of the app. |

## 4. Off-screen Video
If an app has the `xrn:firebolt:capability:presentation:offscreen-audio` or `-video` capability, then it can keep playing video/audio when the app is off-screen.

When an app has this capability, it **MAY** be put into the `OFFSCREEN` display state while in the `BACKGROUND` Lifecycle state.

## 5. Platform-provided Loading Screen
Most apps will leverage a platform-provided loading screen.

If an app provides the `xrn:firebolt:capability:presentation:loading-screen`
capability, then the platform **MAY** use the app-provided loading screen, in
which case, the rest of the section does not apply.

The loading screen **SHOULD** include a loading image referenced in the app's
manifest and cached on the device.

The loading screen **MUST** be displayed when the user attempts to launch the
app.

The loading screen **MUST** stay displayed until the app becomes active, or
launching is cancelled.

The presentation state of the app **MUST** be `LOADING` for the entire time
the loading screen is displayed.

See [Lifecycle](./index.md) for more info on launching.

## 6. App-provided Loading Screen
If an app provides the `xrn:firebolt:capability:presentation:loading-screen`
capability, then the platform **MAY** invoke this capability in some situations.

In order for an app and use an app-provided loading screen, the app **MUST**
provide the `xrn:firebolt:capability:lifecycle:management` capability. If the app
does not provide this capability, then app-provided loading screens **MUST NOT**
but invoked for the app. 

Apps that provide the loading screen capability **MUST** be made visible at
the very beginning of the `LifecycleManagement.activate()` transition, rather
than at the end.

The presentation state of the app **MUST** be `FULLSCREEN` or `SCALED` during
the `activate()` transition.

See [Lifecycle](./index.md) for more info on loading and activating apps.
