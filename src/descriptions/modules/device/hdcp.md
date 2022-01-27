| Device Information | Request       | Response                                                     | Value                                                        | Return Type[^1] | Description                 |
| ------------------ | ------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | --------------- | --------------------------- |
| HDCP               | `device.hdcp` | `{   "jsonrpc": "2.0",   "id": 1,   "result": {     "hdr10": true,     "hdr10Plus": true,     "dolbyVision": true,     "hlg": true   } }` | {     "hdr10": true,     "hdr10Plus": true,     "dolbyVision": true,     "hlg": true   } ` | `BooleanMap` | `BooleanMap`    | The supported HDCP profiles |

