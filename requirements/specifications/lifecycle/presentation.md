# App Presentation

need to write this up... 

Document Status: Working Draft 

See [Firebolt Requirements Governance](../../governance.md) for more info. 
| Contributor               | Organization |
| ------------------------- | ------------ |
| Andrew Bennett            | Sky          |
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
  - [4.1. 4.1 Overlay vs Focus](#41-41-overlay-vs-focus)
- [5. Background Audio](#5-background-audio)
- [6. Picture-in-Picture Video](#6-picture-in-picture-video)
- [7. Navigation](#7-navigation)
- [8. Platform-provided Loading Screen](#8-platform-provided-loading-screen)
- [9. App-provided Loading Screen](#9-app-provided-loading-screen)
- [10. When to use a loading screen](#10-when-to-use-a-loading-screen)


## 2. Focus

The `Presentation` module **MUST** have a `focus` boolean property that returns 
whether or not the app has input, e.g. RCU, focus. 

**TODO**: let's clearly define focus. RCU, soft-keyboard, soft-remote, 

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


**TODO**: an app could be offscreen & scaled. If a scaled or thumbnailed app 
goes offscreen, it's now offscreen. 
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
| Value      | Description                                                                |
|------------|----------------------------------------------------------------------------|
| `partial`  | There is a vertical sidebar covering less than 33% of the app on one side. |
| `blocking` | There is a significantly sized UX covering a majority of the app.          |
| `none`     | There is nothing covering the app.                                         |

### 4.1. 4.1 Overlay vs Focus

| Focus | Overlay                 |
| ----- | ----------------------- |
| true  | none                    |
| false | partial, blocking, none |

## 5. Background Audio

When an app has this capability, it **MAY** be put into the `none` display 
state while in the `active` Lifecycle state. 

If an app has the `xrn:firebolt:capability:media:background-audio`, then it can 
keep playing audio/video when the app is in the `none` display state and the 
audio will be played for the user. 

TODO: do we want background apps to have a gfx surface? that means they'd be in 
'offscreen' display and using more memory TODO: we probably want to support 
both modes here. 
## 6. Picture-in-Picture Video

When an app has the `xrn:firebolt:capability:media:picture-in-picture` 
capability, it **MAY** be put into the `none` display state while in the 
`active` Lifecycle state. 

If an app has the `xrn:firebolt:capability:media:picture-in-picture`, then it 
can keep playing audio/video when the app is in the `none` display state and 
the audio & video will be presented to the user in bounding box determined by 
the platform. Note that this does not include the entire UX of the app, just 
the active media pipeline. 

## 7. Navigation
Typically navigation is handled either when the app is activated, via the 
`intent` parameter of the [`activate` 
method](./index.md#42-activating-an-app), or by internal input within the 
app. 

There are other times when the platform needs to inform an app of a user's 
intent to navigate when the app is already `ACTIVE`, e.g. when a voice 
command is executed or an RCU sends a reserved key to the platform that would 
result in the app taking some action, e.g. going to its home screen. 

If the app provides the `xrn:firebolt:capability:presentation:navigation` 
capability then the platform **MUST** call the `Navigation.navigateTo` method 
of the app's provider and pass an `intent` to an app that is in the `ACTIVE` 
state. 

An app **MAY** receive a navigate call while it is already executing a navigate 
call. 

An app **MUST** acknowledge receipt of each navigate call. 

Platforms **MAY** decide to remove focus from or deactivate apps that do not 
acknowledge the `navigateTo` call. 

An app **MAY** decide how to prioritize multiple navigate calls, but likely 
**SHOULD** prioritize the most recent one. 

To fullfil a prioritized `navigateTo()` call, the app **MUST** inspect the 
`intent` parameter and prepare to fulfill a specific [Navigation 
Intent](../intents/navigation.md) which may include: 

 - Loading any metadata needed to display the user's intended content.
 - Performing any entitlement checks to decide whether to display a player or a purchase flow
 - Any other steps necesary to present content to the user quickly

The app **MAY** display a loading indicator. 

To invoke an app's `navigateTo` provider API the platform **MUST**: 

> The platform **MUST** dispatch the `Presentation.onRequestNavigateTo` 
> notification to the app, and wait for `appNavigateToTimeout` milliseconds for 
> either a `Presentation.navigateToResult` or `Presentation.navigateToError` 
> call in response. 
> 
> Once the platform receives the `navigateToResult` call, then the platform may 
> proceed with the expectation that the app in fact will handle the `intent` 
> 
> If the app times out or makes an `navigateToError` call, then the app **MAY** 
> have focus removed or be deactivated, so that the platform can handle the 
> `intent` in some other way 


## 8. Platform-provided Loading Screen

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
## 9. App-provided Loading Screen

If an app provides the `xrn:firebolt:capability:presentation:loading-screen` 
capability, then the platform **MAY** invoke this capability in some 
situations. 

If the app is being created w/ preload: false then: 

Apps that provide the loading screen capability **MUST** be made visible at the 
end of the `Application.create()` transition, rather than at the end of the 
activate transition. 

**TODO**: if an app is in the running state already, show it at the beginning 
of `activate()` 

The presentation state of the app **SHOULD NOT** be `none` at any time during 
the `activate()` transition. 

See [Lifecycle](./index.md) for more info on loading and activating apps. 

## 10. When to use a loading screen

- cold launch
- wake from sleep
