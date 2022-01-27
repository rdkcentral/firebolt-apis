| Device Information | Request        | Response                                                     | Value                                                        | Return Type[^1] | Description                  |
| ------------------ | -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | --------------- | ---------------------------- |
| Audio              | `device.audio` | `{   "jsonrpc": "2.0",   "id": 1,   "result": {     "stereo": true,     "dolbyDigital5.1": true,     "dolbyDigital5.1+": true,     "dolbyAtmos": true   } }` | `{   "stereo": true,   "dolbyDigital5.1": true,   "dolbyDigital5.1+": true,   "dolbyAtmos": true }` | `AudioProfiles` | The supported audio profiles |

