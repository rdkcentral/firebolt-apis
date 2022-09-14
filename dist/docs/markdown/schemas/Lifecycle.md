---
title: Lifecycle
---
# Lifecycle Schema
---
Version 0.8.0


## JSON-Schema
This document was generated from a JSON-Schema, and is intended to provide a human readable overview and examples of the methods contained in the module.

For the full schema, see the link below.

| Schema |
|--------|
| [lifecycle.json](https://github.com/rdkcentral/firebolt-openrpc/blob/feature/badger-parity/src/schemas/lifecycle.json) |

## Table of Contents
 
 - Schemas
    - [LifecycleState](#lifecyclestate)
    - [CloseReason](#closereason)


## Schemas

### LifecycleState

```typescript
type LifecycleState = 'initializing' | 'inactive' | 'foreground' | 'background' | 'unloading' | 'suspended'
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

The application lifecycle state


---

### CloseReason

```typescript
type CloseReason = 'remoteButton' | 'userExit' | 'error'
```




<details>
  <summary><b>Examples</b></summary>

```json
```

</details>


#### Details

The application close reason


---


