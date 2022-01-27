| Device Information | Request                   | Response                                                     | Value                | Return Type[^1]    | Description                         |
| ------------------ | ------------------------- | ------------------------------------------------------------ | -------------------- | ------------------ | ----------------------------------- |
| Screen Resolution  | `device.screenResolution` | `{   "jsonrpc": "2.0",   "id": 1,   "result": [     1920,     1080   ] }` | `[   1920,   1080 ]` | `[bigint, bigint]` | The screen resolution of the device |

