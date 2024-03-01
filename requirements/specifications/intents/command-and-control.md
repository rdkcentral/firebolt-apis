# Command and Control Intents

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor      | Organization |
| ---------------- | ------------ |
| Saras Arveti     | Comcast      |
| Eileen Bengston  | Comcast      |
| Michael Driscoll | Comcast      |
| Simon Grist      | Sky          |
| Jeremy LaCivita  | Comcast      |

## 1. Overview

This document outlines several basic Intents for controlling a Firebolt
compliant device.

### 1.1. Message.type

Message.type should be a useful grouping to bucket related intents
together for easier forwarding to appropriate components.

## 2. Table of Contents
- [1. Overview](#1-overview)
  - [1.1. Message.type](#11-messagetype)
- [2. Table of Contents](#2-table-of-contents)
- [3. Control Intents](#3-control-intents)
  - [3.1. Power Intent](#31-power-intent)
  - [3.2. Volume Intents](#32-volume-intents)
    - [3.2.1. Volume Intent](#321-volume-intent)
    - [3.2.2. Mute Intent](#322-mute-intent)
  - [3.3. Channel Intent](#33-channel-intent)
  - [3.4. Media Control Intents](#34-media-control-intents)
    - [3.4.1. Pause, Resume, Replay, and Stop Intents](#341-pause-resume-replay-and-stop-intents)
    - [3.4.2. Seek Intent](#342-seek-intent)
    - [3.4.3. Trick Play Intent](#343-trick-play-intent)
  - [3.5. Accessibility Intents](#35-accessibility-intents)
    - [3.5.1. Closed Captions Intent](#351-closed-captions-intent)
    - [3.5.2. Voice Guidance Intent](#352-voice-guidance-intent)
    - [3.5.3. Audio Descritions Intent](#353-audio-descritions-intent)
    - [3.5.4. Text Magnification Intent](#354-text-magnification-intent)
  - [3.6. Interaction Intents](#36-interaction-intents)
    - [3.6.1. Focus Intent](#361-focus-intent)
    - [3.6.2. Select Intent](#362-select-intent)
    - [3.6.3. Scroll Intent](#363-scroll-intent)
    - [3.6.4. Back Intent](#364-back-intent)
    - [3.6.5. Exit Intent](#365-exit-intent)
- [4. Section Intents](#4-section-intents)
  - [4.1. Content Discovery Section Intents](#41-content-discovery-section-intents)
  - [4.2. Device Settings Launch Intent](#42-device-settings-launch-intent)
- [5. Volume Notes](#5-volume-notes)
  - [5.1. Jump Notes](#51-jump-notes)
  - [5.2. Core SDK APIs](#52-core-sdk-apis)

## 3. Control Intents

Control intents are for user intentions that will be needed regardless
of whether there are any apps installed.

For example, these intents are all useful even if only using your TV
with a single HDMI input, and not for apps.

### 3.1. Power Intent

This intent allows a user to turn the device on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:power",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "power",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Additionally, this intent allows a user to set a timer for turning off
the power, aka a "sleep timer."

This is handled by the optional field delay, which is measured in whole
seconds:

```json
{
    "type": "xrn:firebolt:intent:platform:power",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "power",
        "data": {
            "value": true | false,
            "delay": 3600
        },
        "context": {
            "source": "voice"
        }
    }
}

```

While it may not be implemented by all platforms, this could also be
used to turn on the TV with a timer.

### 3.2. Volume Intents

Volume Intents control the audio level of the device.

#### 3.2.1. Volume Intent

This intent allows setting the volume to an absolute or relative value.

```json
{
    "type": "xrn:firebolt:intent:platform:volume",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "volume",
        "data": {
            "value": 70
        },
        "context": {
            "source": "VOICE"
        }
    }
}

```

The value is an integer value from 0 to 100.

This intent also supports relative volume changes, by providing the
optional relative field:

```json
{
    "type": "xrn:firebolt:intent:platform:volume",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "volume",
        "data": {
            "value": -10,
            "relative": true
        },
        "context": {
            "source": "VOICE"
        }
    }
}

```

The value is a positive or negative integer that is relative to a scale
of 0-100.

Firebolt will not support complicated relative changes, e.g. "Set the
volume to 50% *of what it currently is\...*"

**Note**: Both Google & Alexa support either 0-10 or 0% to 100%.

Firebolt uses a size of 0-100 for this intent. It\'s up to each voice
integration if it wants to convert "5" to "50%" before generating
the intent, but convenience transformations like this are recommended.

#### 3.2.2. Mute Intent

This intent allows the user to mute or unmute the device.

```json
{
    "type": "xrn:firebolt:intent:platform:volume",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "mute",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "VOICE"
        }
    }
}
```

### 3.3. Channel Intent

For tuning to a specific channel, either OTA or in-app, see [Tune
Intents](./tune.md).

The intents in this section are for relative next/previous channel user
intentions and are a separate type of Intent. This allows each app to
decide what "channel" means. For example, an App might simply take you
to the next section/genre if it doesn\'t have linear streams in it\'s
catalog.

The goal of the action property to is tell the client how to parse the
Intent, so overloading the tune intent with a different structure is not
desirable.

Also,
"tune" inherently means to zero in on a specific part of a
scale, e.g. tuning a harp.

For relative "channel surfing" we\'ll use the more content-centric
action "channel" which will also align with non-linear apps that want
to leverage the channel up/down intent.

The Channel Intent allows a user to scan "channels" in an app (or
actual OTA channels if not in an app).

Users can scan to the next or previous channel. For scanning to the most
recent, i.e. "Last" channel, see [Interaction
Intent
](#interaction-intents).

```json
{
    "type": "xrn:firebolt:intent:platform:channel",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "channel",
        "data": {
            "value": "next" | "previous"
        },
        "context": {
            "source": "voice"
        }
    }
}

```

The value property MUST always be "next" or "previous". These are
chosen over up/down since not all use cases will be numeric.

Since this intent is always relative to the current app, there is no
need for an appId.

If this Intent needs to be passed to the current app, it can be passed
as-is, via the Discovery. onNavigateTo API, or a simulated RCU press of
one of the channel up/down buttons.

### 3.4. Media Control Intents

#### 3.4.1. Pause, Resume, Replay, and Stop Intents

These intents allow the user to pause and resume playback of the current
Media: 

```json
{
    "type": "xrn:firebolt:intent:platform:media-control",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "pause" | "resume" | "replay" | "stop",
        "context": {
            "source": "voice"
        }
    }
}
```

**TODO**: this is different than what we officially published. We need
to track down if anyone implemented the old Pause Intent.

If the action is pause, then the currently playing media should be
paused, with the frames on-screen and the video decoder ready to resume.

If the action is resume, then the currently paused media should resume.

If the action is replay, then the currently paused media should restart
from the beginning. This should work even if the decoder has finished,
and its resources have been released.

If the action is stop, then the currently playing media should be
stopped, frames removed from the screen, and any decoder resources
should be released.

#### 3.4.2. Seek Intent

The seek intent allows users to jump to a relative or absolute position
in the currently playing media.

```json
{
    "type": "xrn:firebolt:intent:platform:media-control",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "seek",
        "data": {
            "seconds": 3600
        },
        "context": {
            "source": "voice"
        }
    }
}

```

The seconds value is a positive integer representing where to seek.

This intent also supports relative seeking, by providing the optional
relative field:

```json
{
    "type": "xrn:firebolt:intent:platform:media-control",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "seek",
        "data": {
            "seconds": -30,
            "relative": true
        },
        "context": {
            "source": "voice"
        }
    }
}

```

For relative seeking, the seconds value may be a positive or negative
value.

#### 3.4.3. Trick Play Intent

The Trick Play Intent allows users to fast-forward or rewind:

```json
{
    "type": "xrn:firebolt:intent:platform:media-control",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "trickplay",
        "data": {
            "speed": 2.5
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Speed is a float in the range of -10 to 10, with negative values
denoting backwards/rewind and values between -1 and 1 denoting slow
motion.

It is a device-level decision how to implement different speeds, however
actual fast playback (with audio) should be used where possible and
reasonable, e.g. a speed of 1.5 should actually be playing the video w/
sync\'d audio, while a speed of 10 will likely be using iframes and not
have audio. For speeds less than zero it is not important, and likely
undesirable, to provide audio.

### 3.5. Accessibility Intents

These intents manipulate accessibility features on the device.

#### 3.5.1. Closed Captions Intent

This intent allows a user to turn closed captions on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "closedCaptions",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "closedCaptions",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.5.2. Voice Guidance Intent

This intent allows a user to turn voice guidance on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "voiceGuidance",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "voiceGuidance",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.5.3. Audio Descritions Intent

This intent allows a user to turn voice guidance on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "audioDescription",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "audioDescription",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.5.4. Text Magnification Intent

This intent allows a user to turn text magnification on or off.

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "textMagnification",
        "data": {
            "value": true | false
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Additionally, this intent may specify a toggle:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "textMagnification",
        "data": {
            "toggle": true
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Finally, this intent may specify a magnification scale as a number:

```json
{
    "type": "xrn:firebolt:intent:platform:accessibility",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "textMagnification",
        "data": {
            "scale": 2.5
        },
        "context": {
            "source": "voice"
        }
    }
}
```

Setting the scale to `1` turns off magnification. Setting the scale to a value greater than 1 turns on magnification.

Even if a Firebolt platform does not support specifying the numeric scale, it **MUST** turn magnifacation on and off based on them.

The magnification intent **MUST** have only one property, `scale`, `toggle`, `value` and **MUST NOT** comebine them in a single intent.

### 3.6. Interaction Intents

Interaction Intents allow for voice (or other upstream intent service)
to control an on-screen UI without need for a keyboard or remote.

#### 3.6.1. Focus Intent

The Focus Intent allows users to move the focus / cursor
up/down/left/right:

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "focus",
        "data": {
            "direction": "up" | "down" | "left" | "right"
        },
        "context": {
            "source": "voice"
        }
    }
}

```

Note that this does not give focus to a particular app, which is handled
by the "launch" action.

These Intents will generate appropriate HTML browser keyCode events to
facilitate up/down/left/right key presses.

#### 3.6.2. Select Intent

The select intent allows users to tell an app select, e.g.,
"click" on
whatever is focused. This is a platform-level intent that effectively
sends the "Ok" or "Select" key to the current app.

**NOTE**: i don\'t like using "click" here, but i can\'t think of a
good word that isn\'t super vague. "Select" means highlighting, not
actually hitting okay, so we can\'t use that. I considered "activate"
but that seems odd\... Open to discussing this.

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "select",
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.6.3. Scroll Intent

The Scroll Intent allows users to move the current view port
up/down/left/right:

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "scroll",
        "data": {
            "direction": "up" | "down" | "left" | "right",
            "unit": "page" | "line" | "percent",
            "distance": 2.5
        },
        "context": {
            "source": "voice"
        }
    }
}

```

The distance is a float that represents how many of units to scroll. All
three data properties are required.

These Intents will generate appropriate browser / DOM scrolling
operations that don\'t require custom APIs.

#### 3.6.4. Back Intent

The back intent allows users to tell an app go to "back" like a
browser. This is a platform-level intent and will initiate a browser
back flow for web apps. For native apps, this will be converted to an
app Navigation Intent by the client and surfaced through the navigateTo
API.

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "back",
        "context": {
            "source": "voice"
        }
    }
}
```

#### 3.6.5. Exit Intent

The exit intent allows users to tell an app close. This is a
platform-level intent and will simply move the current app into the
inactive state.

```json
{
    "type": "xrn:firebolt:intent:platform:interaction",
    "target": "client",
    "metadata": {
        "assistant": "XFINITY",
        "lang": "eng-USA",
        "micType": "NEAR_FIELD"
    },
    "intent": {
        "action": "exit",
        "context": {
            "source": "voice"
        }
    }
}
```

## 4. Section Intents

The section intent is already defined as part of Firebolt.

### 4.1. Content Discovery Section Intents

The following section IDs will be used, with the Firebolt application
type:

xrn:firebolt:application-type:main

| Section    | Description                                                         |
| ---------- | ------------------------------------------------------------------- |
| guide      | Launches a program guide, typically linear, in the main experience. |
| menu       | Launches a top-level menu, or home page, of the main experience.    |
| recordings | Launches a list of user recordings in the main experience.          |
| favorites  | Launches a list of user favorites in the main experience.           |
| purchases  | Launches a list of user purchased content in the main experience.   |
| playlist   | Launches a list of content the user has saved for future playback.  |
| recent     | Launches a list of recently watched content.                        |

Note that not every Firebolt Distributor will have all of these
features. For unsupported features, these intents should simply launch
the main aggregated experience UI.

### 4.2. Device Settings Launch Intent

To launch the settings UI, a Launch Intent will be used, with the
Firebolt application type:

xrn:firebolt:application-type:settings

Currently there are no standardized sections for the settings App.

## 5. Volume Notes

Whether or not a TV uses logarithmic or linear scale is irrelevant to
the Intent schema.

### 5.1. Jump Notes

For the feature of instantly moving forward/backwards by \<N\> seconds I
prefer *not* to call this "skip" because in the AVOD world,
"skip"
means to completely bypass an add or chapter (like next track of a CD
player). I\'ve used "jump" in the past, but I\'m open to other names.
We could go with seek, and have a relative and absolute version?

### 5.2. Core SDK APIs

We need SDK APIs for some of these, since they\'re potentially surfaced
to apps, e.g. channel scanning.

Need App-facing SDK APIs for:

-   Seek (otherwise how to pass the value) - New API, maybe
    MediaControl.onSeek

-   TrickPlay (how to pass the speed) - New API, maybe
    MediaControl.onTrickPlay

-   Channel (how to pass direction) - Discovery.onNavigateTo

Everything else is handled by the OS, i think.
