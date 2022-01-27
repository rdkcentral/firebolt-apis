| Device Information | Request                  | Response                                                     | Value                | Return Type[^1]    | Description                  |
| ------------------ | ------------------------ | ------------------------------------------------------------ | -------------------- | ------------------ | ---------------------------- |
| Video Resolution   | `device.videoResolution` | `{   "jsonrpc": "2.0",   "id": 1,   "result": [     1920,     1080   ] }` | `[   1920,   1080 ]` | `[bigint, bigint]` | The current video resolution |

With videoResolution you can have a return of the . Similarly you can have a single return value for NetworkState of either `connected` or `dicconnected`.

The return values are also reusable objects. 

##### Resolution

```typescript
type Resolution = [bigint, bigint]
```
