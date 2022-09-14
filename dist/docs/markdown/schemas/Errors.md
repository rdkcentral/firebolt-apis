---
title: Errors
---
# Errors Schema
---
Version 0.8.0


## JSON-Schema
This document was generated from a JSON-Schema, and is intended to provide a human readable overview and examples of the methods contained in the module.

For the full schema, see the link below.

| Schema |
|--------|
| [errors.json](https://github.com/rdkcentral/firebolt-openrpc/blob/feature/badger-parity/src/schemas/errors.json) |

## Table of Contents
 
 - Schemas
    - [FireboltError](#firebolterror)
    - [UserNotAuthenticatedError](#usernotauthenticatederror)


## Schemas

### FireboltError

```typescript
type FireboltError = {
  code: number
  message: string
  data?: {
  }
}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "code": -32601,
  "message": "Method not found"
}
```

</details>


#### Details

An error resulting from calling a Firebolt method.


---

### UserNotAuthenticatedError

```typescript
type UserNotAuthenticatedError = {"code":401,"message":"User is not authenticated."}
```




<details>
  <summary><b>Examples</b></summary>

```json
{
  "code": 401,
  "message": "User is not authenticated."
}
```

</details>




---


