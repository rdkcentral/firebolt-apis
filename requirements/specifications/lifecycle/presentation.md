# App Presentation

Document Status: Working Draft 

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor               | Organization |
| ------------------------- | ------------ |
| Andrew Bennett            | Sky          |
| Cody Bonney               | Charter      |
| Bart Catrysse             | Liberty      |
| Tim Dibben                | Sky          |
| Piotr Kobzda              | Liberty      |
| Jeremy LaCivita           | Comcast      |
| Ramprasad Lakshminarayana | Sky          |
| Kevin Pearson             | Comcast      |
| Jan Pedersen              | Sky          |
| Peter Yu                  | Comcast      |

## 1. Overview

This document describes the requirements that Firebolt platforms and Firebolt 
applications must fulfill when managing App Presention. *App Presentation* 
refers to the display, focus, and navigational aspects of an App. 

The *display* of an app refers to it its visibility and size. 

Whether an app has an *overlay* refers to any other apps or UX being presented 
on top of the app. 

Apps that are presented to users by the platform may receive *navigation* 
intents, which are like deep links from the platform. 


## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Focus](#3-focus)
- [4. Display](#4-display)
  - [4.1. Display vs Lifecycle](#41-display-vs-lifecycle)
- [5. Loading Screen](#5-loading-screen)
  - [5.1. Platform-provided Loading Screen](#51-platform-provided-loading-screen)
  - [5.2. App-provided Loading Screen](#52-app-provided-loading-screen)
  - [5.3. When to use a loading screen](#53-when-to-use-a-loading-screen)
- [6. Overlay](#6-overlay)
  - [6.1. Overlay vs Focus](#61-overlay-vs-focus)
- [7. Navigation](#7-navigation)
- [8. Background Audio](#8-background-audio)
- [9. Picture-in-Picture Video](#9-picture-in-picture-video)


## 3. Focus

The `Presentation` module **MUST** have a `focus` boolean property that returns 
whether or not the app has input, e.g. RCU, focus. 

**TODO**: let's clearly define focus. RCU, soft-keyboard, soft-remote, 

As a property, this API also has an `onFocusChanged` notification. 

## 4. Display

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

### 4.1. Display vs Lifecycle

Each Lifecycle state only supports certain display states: 

| Lifecycle      | Supported Displays                               |
|----------------|--------------------------------------------------|
| `initializing` | `none`, `loading`                                |
| `active`       | `fullscreen`, `scaled`, `thumbnail`, `offscreen` |
| `running`      | `none`, `loading`                                |
| `suspended`    | `none`, `loading`                                |
| `sleeping`     | `none`, `loading`                                |

See [Picture-in-picture](#9-picture-in-picture-video) and [Background 
Audio](#8-background-audio) for exceptions to this. 

## 5. Loading Screen
In order to manage user expectations, Firebolt platforms **MAY** display 
loading screens to end users when an app is going to be activated. Loading 
Screens may be rendered either by the platform, the app, or both, depending on 
Capability configuration. 

Firebolt platforms **MAY** decide when an app activation warrents a loading 
screen, for example when an app will be initialized or woken from sleep before 
activation. 

Proposal: 

If an app has the `xrn:firebolt:capability:presentation:loading-screen` 
capability and the platform chooses to utilize the app's loading screen, the 
app **MAY** be made visible any time from the beginning of activate() 
transition and **MUST** be made visible no later than the end. 

If an app does not have the 
`xrn:firebolt:capability:presentation:loading-screen` capability or the 
platform decides not to use the app's loading screen, the app **MUST** be made 
visible at the end of the activate() transition. 

### 5.1. Platform-provided Loading Screen

If an app provides the `xrn:firebolt:capability:presentation:loading-screen` 
capability, then the platform **MAY** use the app-provided loading screen, in 
which case, the rest of the section does not apply. 

If the platform determines that a platform loading screen will be displayed, 
then: 

> The loading screen **SHOULD** include a loading image referenced in the app's 
> manifest and cached on the device. 
> 
> The loading screen **MUST** be displayed when the user attempts to launch the 
> app. 
> 
> The loading screen **MUST** stay displayed until the app becomes active, or 
> launching is cancelled. 
> 
> The presentation state of the app **MUST** be `LOADING` for the entire time 
> the loading screen is displayed. 
> 
> Each Firebolt platform **MAY** define what "load screen" means in these 
> requirements. 

See [Lifecycle](./index.md) for more info on launching. 

### 5.2. App-provided Loading Screen

If an app provides the `xrn:firebolt:capability:presentation:loading-screen` 
capability, then the platform **MAY** invoke this capability in some 
situations. 

If the platform determines that an app loading screen will be displayed, then: 

> The platform provided loading screen **MAY** be displayed first. 
> 
> If the platform provided loading screen is displayed then the app's 
> presentation state should be `loading`. 
> 
> The app **MAY** be made visible at the beginning of the activate transition. 
> 
> The app **MAY** be made visible at a later point during the activate 
> transition based on platform-specific requirements, e.g. detecting that the 
> app's graphics surface has been utilized. 
> 
> The app **MUST** be made visible no later than the end of the activate 
> transition. 

The presentation state of the app **SHOULD NOT** be `none` at any time during 
the `activate()` transition. 

See [Lifecycle](./index.md) for more info on loading and activating apps. 

### 5.3. When to use a loading screen

It is up to each platform to determine when a loading screen is useful. 

Platforms **SHOULD** consider displaying a loading screen for: 

- app cold launch
- app wake from sleep

TODO: define all the various happy path & edge cases for this. 

## 6. Overlay
The `Presentation` module **MUST** have an `overlay` string property that 
informs the app when a focus-consuming overlay is present. 

| Value      | Description                                                                                   |
|------------|-----------------------------------------------------------------------------------------------|
| `partial`  | There is a overlay partially covering the app such that the content is still mostly viewable. |
| `blocking` | There is a blocking overlay covering a majority of the app.                                   |
| `none`     | There is nothing covering the app.                                                            |

### 6.1. Overlay vs Focus

| Focus | Overlay                 |
| ----- | ----------------------- |
| true  | none                    |
| false | partial, blocking, none |

## 7. Navigation
Typically navigation is handled either when the app is activated, via the 
`intent` parameter of the [`activate()` 
method](./index.md#52-activating-an-app), or by internal input within the app. 

There are other times when the platform needs to inform an app of a user's 
intent to navigate when the app is already `ACTIVE`, e.g. when a voice command 
is executed or an RCU sends a reserved key to the platform that would result in 
the app taking some action, e.g. going to its home screen. 

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


## 8. Background Audio
If an app has the `xrn:firebolt:capability:media:background-audio`, then it can 
keep playing audio/video when the app is in the `none` display state and the 
audio will be played for the user. 

When an app has this capability, it **MAY** be put into the `none` display 
state while in the `active` Lifecycle state. 

TODO: do we want background apps to have a gfx surface? that means they'd be in 
'offscreen' display and using more memory TODO: we probably want to support 
both modes here. 

## 9. Picture-in-Picture Video
If an app has the `xrn:firebolt:capability:media:picture-in-picture`, then it 
can keep playing audio/video when the app is in the `none` display state and 
the audio & video will be presented to the user in bounding box determined by 
the platform. Note that this does not include the entire UX of the app, just 
the active media pipeline. 

When an app has this capability, it **MAY** be put into the `none` display 
state while in the `active` Lifecycle state. 
