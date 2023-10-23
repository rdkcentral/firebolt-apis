

































# App Presentation
need to write this up...  

Document Status: Working Draft  

See [Firebolt Requirements Governance](../../governance.md) for more info.  

| Contributor               | Organization |
| ------------------------- | ------------ |
| Andrew Bennet             | Sky          |
| Cody Bonney               | Charter      |
| Bart Catrysse             | Liberty      |
| Tim Dibben                | Sky          |
| Jeremy LaCivita           | Comcast      |
| Ramprasad Lakshminarayana | Sky          |
| Kevin Pearson             | Comcast      |
| Peter Yu                  | Comcast      |


## 1. Overview
TBD...  

- [1. Overview](#1-overview)
- [2. Focus](#2-focus)
- [3. Display](#3-display)
  - [3.1. Display vs Lifecycle](#31-display-vs-lifecycle)
- [4. Overlay](#4-overlay)
- [5. Background Audio](#5-background-audio)
- [6. Picture-in-Picture Video](#6-picture-in-picture-video)
- [7. Platform-provided Loading Screen](#7-platform-provided-loading-screen)
- [8. App-provided Loading Screen](#8-app-provided-loading-screen)


## 2. Focus
The `Presentation` module **MUST** have a `focus` boolean property that returns 
  whether or not the app has input, e.g. RCU, focus.  

As a property, this API also has an `onFocusChanged` notification.  

## 3. Display
The `Presentation` module **MUST** have a `display` string property that  
returns one of the following values:  

| Value        | Description                                                                                                             |
|--------------|-------------------------------------------------------------------------------------------------------------------------|
| `fullscreen` | The app is displayed such that the dimensions fill the entire screen                                                    |
| `offscreen`  | The app is has it's graphics surface attached, but not displayed on the screen at the moment, e.g. scrolled out of view |
| `scaled`     | The app is displayed at a size smaller than the entire screen but at least 25% of the width or height                   |
| `thumbnail`  | The app is displayed at a size smaller than 25% of the width or height of the entire screen                             |
| `loading`    | The platform is displaying a loading screen while the app prepares to be activated                                      | 
| `none`       | The app does not have it's graphics surface attached to the screen                                                      |

### 3.1. Display vs Lifecycle
Each Lifecycle state only supports certain display states:  

| Lifecycle      | Supported Displays                               |
|----------------|--------------------------------------------------|
| `initializing` | `none`, `loading`                                |
| `active`       | `fullscreen`, `scaled`, `thumbnail`, `offscreen` |
| `running`      | `none`, `loading`                                |
| `suspended`    | `none`, `loading`                                |
| `sleeping`     | `none`, `loading`                                |

See [Picture-in-picture](#6-picture-in-picture-video) and [Background  
Audio](#5-background-audio) for exceptions to this.  

## 4. Overlay
The `Presentation` module **MUST** have an `overlay` string property that  
returns one of the following values:  

| Value     | Description                                                                |
|-----------|----------------------------------------------------------------------------|
| `icon`    | There is an informative icon, e.g. volume, on top of the app.              |
| `band`    | There is a horizontal overlay at the top or bottom of the app.             |
| `sidebar` | There is a vertical sidebar covering less than 33% of the app on one side. |
| `blocked` | There is a significantly sized UX covering a majority of the app.          |

## 5. Background Audio
If an app has the `xrn:firebolt:capability:media:background-audio`, then it can 
  keep playing audio/video when the app is in the `none` display state and  
the audio will be played for the user.  

When an app has this capability, it **MAY** be put into the `none` display  
state while in the `active` Lifecycle state.  

## 6. Picture-in-Picture Video
If an app has the `xrn:firebolt:capability:media:picture-in-picture`, then it  
can keep playing audio/video when the app is in the `none` display state and  
the audio & video will be presented to the user in bounding box determined by 
  the platform. Note that this does not include the entire UX of the app,  
just the active media pipeline.  

When an app has this capability, it **MAY** be put into the `none` display  
state while in the `active` Lifecycle state.  

## 7. Platform-provided Loading Screen
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

The presentation state of the app **MUST** be `LOADING` for the entire time the 
  loading screen is displayed.  

See [Lifecycle](./index.md) for more info on launching.  

## 8. App-provided Loading Screen
If an app provides the `xrn:firebolt:capability:lifecycle:loading-screen`  
capability, then the platform **MAY** invoke this capability in some  
situations.  

In order for an app and use an app-provided loading screen, the app **MUST**  
provide the `xrn:firebolt:capability:lifecycle:activity` capability. If the  
app does not provide this capability, then app-provided loading screens  
**MUST NOT** but invoked for the app.  

Apps that provide the loading screen capability **MUST** be made visible at the 
  very beginning of the `Activity.activate()` transition, rather than at the  
end.  

The presentation state of the app **SHOULD NOT** be `none` at any time during  
the `activate()` transition.  

See [Lifecycle](./index.md) for more info on loading and activating apps.  
