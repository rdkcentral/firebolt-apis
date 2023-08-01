# Play Intent

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Jeremy LaCivita | Comcast        |
| Liz Sheffield   | Comcast        |
| Seth Kelly      | Comcast        |

## 1. Overview
There are many use cases where a Firebolt device will need to inform an app of a user's intention to play something. This could originate from a voice remote, an editorial tile, a developer tool, or any number of places. Having a standard message to play something allows an app to integrate with this message once, while allowing the platform to change when and where the intent comes from w/out further work from the app.

Apps will need to be able to play specific entities from a back-office meta-data integration, entities from a federated meta-data integration, or non-specific entities based on a query.

The existing Firebolt `playback` intent does not meet these requirements. This document outlines a more flexible `play` intent to replace it.

TODO: 

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Play Intent](#3-play-intent)
  - [3.1. Play First Option for a Playlist Entity](#31-play-first-option-for-a-playlist-entity)
  - [3.2. Play Options for Query](#32-play-options-for-query)
- [4. Core APIs](#4-core-apis)

## 3. Play Intent
The Firebolt `navigateTo` notification **MUST** support a `play` intent, which tells an app to initiate playback of either a specific entity or to find content that matches a query and play that content.

The `play` intent **MUST** have an `action` property, whose value is `'play'`.

The `play` intent **MUST** have `data` property, which is an object conforming to the following:

> The `data` object **MUST** have either an `entity` object property or a `query` string property and **MUST NOT** have both.
>
> The `entity` object, if present, **MUST** be an [Entity](../entities/index.md).
> 
> The `data` object **MAY** have an `options` object property that conforms to [Play Options](#31-play-options).

The `play` intent **MUST** have a `context` object property that conforms to the [Intent Context](./context.md).

An example play intent:

```json 
{
    "action": "play",
    "data": {
        "query": "Ed Sheeran"
    },
    "context": {
        "source": "voice"
    }
}
```

Which would instruct an app to search for content matching the query "Ed Sheeran" and then play the results.

### 3.1. Play First Option for a Playlist Entity
For `play` intents with an `entity` whose `entityType` is `"playlist"`, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "entity": {
            "entityType": "playlist",
            "entityId": "playlist/xyz"
        }
    }
 }
 ```

The `options` property of the intent **MAY** contain a `playFirstId` string property, to
identify an entity to play *before* starting the playlist, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "entity": {
            "entityType": "playlist",
            "entityId": "playlist/xyz"
        }
    },
    "options": {
        "playFirstId": "song/xyz"
    }
 }
 ```

 If `playFirstId` is provided, the the targeted app **MUST** attempt to play the entity denoted by `playFirstId` first, regardless of whether it is part of the identified playlist or not.
 
 If the `playFirstId` was successfully played, then the app **SHOULD** remove the `playFirstId` entity from any later position in the playlist, if appropriate.

The `options` property of the intent **MAY** contain a `playFirstTrack` integer property, to
identify an entity from the playlist to play *before* the rest of the playlist, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "entity": {
            "entityType": "playlist",
            "entityId": "playlist/xyz"
        }
    },
    "options": {
        "playFirstTrack": 3
    }
 }
 ```

If `playFirstTrack` is provided and the playlist has at least that many items, then the item denoted by `playFirstTrack` **MUST** be moved from it's original position to the front of the playlist for.

The options object **MUST NOT** have both a `playFirstId` and a `playFirstTrack` property.

### 3.2. Play Options for Query
For `play` intents with a `query`, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "query": "Ed Sheeran"
    }
 }
 ```

The `options` property of the intent **MAY** contain a `programTypes` array-of-strings property, to
filter which program entity typess, e.g. `[ "movie", "episode" ]` should be included, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "query": "Ed Sheeran"
    },
    "options": {
        "programTypes": [
            "movie"
        ]
    }
 }
 ```

The `options` property of the intent **MAY** contain a `musicTypes` array-of-strings property, to
filter which music entity typess, e.g. `[ "song", "album" ]` should be included, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "query": "Ed Sheeran"
    },
    "options": {
        "programTypes": [
            "movie"
        ],
        "musicTypes": [
            "song"
        ]
    }
 }
 ```
 
## 4. Core APIs
The Firebolt Core SDK will support listening to `play` intents via the `Discovery.navigateTo` notification.

```javascript
import { Discovery } from '@firebolt-js/sdk'

Discovery.listen('navigateTo', (intent) => {
    if (intent.action === 'play') {
        // do stuff with play intent!
    }
})
```