# Intents

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info. 

| Contributor     | Organization |
| --------------- | ------------ |
| Jeremy LaCivita | Comcast      |

## 1. Overview
Offen times an end-user has a specific intention that needs to be communicated 
to an app by the platform. A common reason for this is that a platform may have 
a voice interface, and an end-user has given an instruction that needs to be 
carried out by a specific app, e.g. a deep link to content w/in that app. 

Other use cases include editorially placed calls to action in the main user 
experience, developer tools, and app-to-app communication brokered by Firebolt 
intents. 

All intents have an `action`, and `context` property, and many intents have an 
additional `data` property. 

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Intent Action](#3-intent-action)
- [4. Intent Context](#4-intent-context)
- [5. Intent Data](#5-intent-data)
- [Intent Types](#intent-types)

## 3. Intent Action
The intent `action` denotes what type of intent it is. 

All intents **MUST** have a `string` attribute denoting the type of intent. 

See the various [Intent Types](#intent-types) below for values. 

## 4. Intent Context
The intent `context` provides information on where the intent orginated from. 

All intents **MUST** have a `context` property, which is an object. 

The `context` object **MUST** have a `source` string property with one of the 
following values: 

 | Value       | Description                                                                         |
 |-------------|-------------------------------------------------------------------------------------|
 | `voice`     | This intent originated from a voice service                                         |
 | `editorial` | This intent originated from an editorial CMS                                        |
 | `api`       | This intent originated from some other API on the platform, e.g. `Discovery.launch` |

The `context` object **MAY** have a `campaign` string property, which can have 
any string value. This property denotes an editorial campaign. 

## 5. Intent Data
If an intent has any additional data, it **MUST** be in the `data` property. 

## Intent Types

- [Play](./play.md)
- [Tune](./tune.md)
- [Basic Navigation](./navigation.md)
  