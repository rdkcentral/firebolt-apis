# Accessibility Requirements

Document Status: Proposed Specification

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization |
| --------------- | ------------ |
| Andrew Bennett  | Sky          |
| Bart Catrysse   | LGI          |
| Jeremy LaCivita | Comcast      |
| Joe Martin      | Comcast      |

## 1. Overview

As the number of assistive technologies grow and become more feature-rich, Firebolt platforms and the services upon which they are built are expected to provide reasonable accommodations to users with visual or audible impairments.  These accomodations exist to allow these users to more easily understand and interact with content via these assistive technologies.

Accessibility is and will continue to be a core foundational principal of the Firebolt project, and as such, Firebolt shall expose any functionality required to configure and drive these assitive technologies, allowing Firebolt clients to build rich experiences that are curated to each user's specific needs.

### 1.1. User Stories

As an app, I want to...

- Get the user's audio description preferences
- Get the user's closed captioning preferences
- Get the user's high contrast UI preference
- Get the user's preferred closed captioning style
- Get the user's voice guidance preferences

## 2. Table of Contents

- [1. Overview](#1-overview)
  - [1.1. User Stories](#11-user-stories)
- [2. Table of Contents](#2-table-of-contents)
- [3. Constants, Types, and Schemas](#3-constants-types-and-schemas)
  - [3.1. Closed Captions Styles](#31-closed-captions-styles)
- [4. Accessibility](#4-accessibility)
  - [4.1. Audio Description Settings](#41-audio-description-settings)
  - [4.2. Closed Captions Settings](#42-closed-captions-settings)
  - [4.3. High Contrast UI](#43-high-contrast-ui)
  - [4.4. Voice Guidance Settings](#44-voice-guidance-settings)

## 3. Constants, Types, and Schemas

### 3.1. Closed Captions Styles

The Firebolt `Accessibility` module **MUST** have a `ClosedCaptionsStyles` object of the following schema:

| Name                | Type             | Required in Response | Notes                                                                                                                                      |
| ------------------- | ---------------- | -------------------- | ------------------------------------------------------------------------------------------------------------------------------------------ |
| `backgroundColor`   | `string`, `null` | No                   | Standard browser color name (e.g. `black`) or hexadecimal value (e.g. `#000000`)                                                           |
| `backgroundOpacity` | `string`, `null` | No                   | Minimum value: `0`, max: `100`                                                                                                             |
| `fontColor`         | `string`, `null` | No                   | Standard browser color name (e.g. `white`) or hexadecimal value (e.g. `#FFFFFF`)                                                           |
| `fontEdge`          | `string`, `null` | No                   | Allowed values: `depressed`, `drop_shadow_left`, `drop_shadow_right`, `none`, `raised`, `uniform`                                          |
| `fontEdgeColor`     | `string`, `null` | No                   | Standard browser color name (e.g. `grey`) or hexadecimal value (e.g. `#808080`)                                                            |
| `fontFamily`        | `string`, `null` | No                   | Allowed values: `casual`, `cursive`, `monospaced_sanserif`, `monospaced_serif`, `proportional_sanserif`, `proportional_serif`, `smallcaps` |
| `fontOpacity`       | `string`, `null` | No                   | Minimum value: `0`, max: `100`                                                                                                             |
| `fontSize`          | `number`, `null` | No                   | Minimum value: `0`                                                                                                                         |
| `textAlign`         | `string`, `null` | No                   | Allowed values: `left`, `center`, `right`                                                                                                  |
| `textAlignVertical` | `string`, `null` | No                   | Allowed values: `top`, `middle`, `bottom`                                                                                                  |
| `windowColor`       | `string`, `null` | No                   | Standard browser color name (e.g. `white`) or hexadecimal value (e.g. `#FFFFFF`)                                                           |
| `windowOpacity`     | `string`, `null` | No                   | Minimum value: `0`, max: `100`                                                                                                             |

## 4. Accessibility

Apps need to know what the user's preferences are for the various assistive technologies that may be available on the platform.

To facilitate this, the `Accessibility` module will provide convenience methods that encapsulate various accessibility preferences of the user, such as their closed captioning or voice guidance preferences.

### 4.1. Audio Description Settings

The `Accessibility` module **MUST** include an `audioDescriptionSettings` method that returns an object describing the user's audio description preferences.

This method's response **MUST** support the following properties:

| Property  | Type      | Description                                                    |
| --------- | --------- | -------------------------------------------------------------- |
| `enabled` | `boolean` | Whether or not audio descriptions should be enabled by default |

This method **MUST** have a corresponding `onAudioDescriptionSettingsChanged` event to notify listeners after a change to any properties have been made and that change has taken effect.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:accessibility:audiodescriptions` capability.

```javascript
Accessibility.audioDescriptionSettings()
//> {
//>   "enabled": true
//> }
```

### 4.2. Closed Captions Settings

The `Accessibility` module **MUST** include an `closedCaptionsSettings` method that returns an object describing the user's closed captions preferences.

This method's response **MUST** support the following properties:

| Property             | Type                   | Required in Response | Description                                                       |
| -------------------- | ---------------------- | -------------------- | ----------------------------------------------------------------- |
| `enabled`            | `boolean`              | Yes                  | Whether or not audio descriptions should be enabled by default    |
| `preferredLanguages` | `[]string`             | No                   | A list of preferred ISO 639-2 language codes for closed captions. |
| `styles`             | `ClosedCaptionsStyles` | No                   | The default style to use when displaying closed-captions          |

This method **MUST** have a corresponding `onClosedCaptionsSettingsChanged` event to notify listeners after a change to any properties have been made and that change has taken effect.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:accessibility:closedcaptions` capability.

```javascript
Accessibility.closedCaptionsSettings()
//> {
//>   "enabled": true,
//>   "preferredLanguages": [
//>     "eng",
//>     "spa"
//>   ],
//>   "styles": {
//>     "backgroundColor": "#000000",
//>     "backgroundOpacity": 100,
//>     "fontColor": "#ffffff",
//>     "fontEdge": "none",
//>     "fontEdgeColor": "#7F7F7F",
//>     "fontFamily": "monospaced_serif",
//>     "fontOpacity": 100,
//>     "fontSize": 1,
//>     "textAlign": "center",
//>     "textAlignVertical": "middle",
//>     "windowColor": "white",
//>     "windowOpacity": 50
//>   }
//> }
```

### 4.3. High Contrast UI

The `Accessibility` module **MUST** include a `highContrastUI` method that returns a boolean denoting whether the user prefers the UI to be presented in a high contrast mode.

This method **MUST** have a corresponding `onHighContrastUIChanged` event to notify listeners after a change to the property has been made.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:accessibility:highcontrastui` capability.

```javascript
Accessibility.highContrastUI()
//> true
```

### 4.4. Voice Guidance Settings

The `Accessibility` module **MUST** include a `voiceGuidanceSettings` method that returns an object describing the user's voice guidance preferences.

This method's response **MUST** support the following properties:

| Property          | Type      | Required in Response | Description                                                                                          |
| ----------------- | --------- | -------------------- | ---------------------------------------------------------------------------------------------------- |
| `enabled`         | `boolean` | Yes                  | Whether or not voice guidance is enabled by default                                                  |
| `navigationHints` | `boolean` | No                   | Whether or not voice guidance should include additional navigation hints                             |
| `speed`           | `number`  | No                   | The speed at which voice guidance speech will be read back to the user<br />Allowed range: 0.1 -> 10 |

This method **MUST** have a corresponding `onVoiceGuidanceSettingsChanged` event to notify listeners after a change to any properties have been made and that change has taken effect.

Access to these methods **MUST** require the `use` role of the `xrn:firebolt:capability:accessibility:voiceguidance` capability.

```javascript
Accessibility.voiceGuidanceSettings()
//> {
//>   "enabled": true,
//>   "navigationHints": false,
//>   "speed": 1.5
//> }
```
