# Play Intent

Document Status: Working Draft

See [Firebolt Requirements Governance](../../governance.md) for more info.

| Contributor     | Organization   |
| --------------- | -------------- |
| Jeremy LaCivita | Comcast        |

## 1. Overview
There are many use cases where a Firebolt device will need to inform an app of a user's intention to play something. This could originate from a voice remote, an editorial tile, a developer tool, or any number of places. Having a standard message to play something allows an app to integrate with this message once, while allowing the platform to change when and where the intent comes from w/out further work from the app.

Apps will need to be able to play specific entities from a back-office meta-data integration, entities from a federated meta-data integration, or non-specific entities based on a query.

The existing Firebolt `playback` intent does not meet these requirements. This document outlines a more flexible `play` intent to replace it.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Play Intent](#3-play-intent)
  - [3.1. Play Options](#31-play-options)
    - [3.1.1. Play Options for Entity](#311-play-options-for-entity)
    - [3.1.2. Play Options for Query](#312-play-options-for-query)
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

### 3.1. Play Options
The available options depend on what type of play intent they are attached to.

#### 3.1.1. Play Options for Entity
For `play` intents with an `entity`, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "entity": {
            "entityId": "xyz"
        }
    }
 }
 ```

The `options` property of the intent **MAY** contain a `playlistId` string property, to
identify a larger playlist to contine playing after the entity, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "entity": {
            "entityId": "xyz"
        }
    },
    "options": {
        "playlistId": "abc"
    }
 }
 ```

#### 3.1.2. Play Options for Query
For `play` intents with an `query`, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "query": "Ed Sheeran"
    }
 }
 ```

The `options` property of the intent **MAY** contain an `entityTypes` array of strings property, to
filter which entity typess, e.g. `[ "music", "program" ]` should be included, e.g.:

 ```json
 {
    "action": "play",
    "data": {
        "query": "Ed Sheeran"
    },
    "options": {
        "entityTypes": [
            "music"
        ]
    }
 }
 ```

 **TODO**: need to confirm with Merlin team that we're okay calling "music" an entity type.

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