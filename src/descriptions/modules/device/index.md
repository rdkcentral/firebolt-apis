#### Device 

Firebolt allows you to quickly determine useful information about the device your app is running on. This is useful for ensuring that if your app has device feature-dependent functionality it can run properly on a device. 

All the requests are written as 

```json
{
  "jsonrpc": "2.0",
  "id": 1,
  "method": "device.platform", // i.e. device.XXXXX, device.distributor, device.type, etc
  "params": {}
}
```

[^1]: The returns are a promise of the return type. 



| Device Information | Request                   | Response                                                     | Value                                                        | Return Type[^1]    | Description                                           |
| ------------------ | ------------------------- | :----------------------------------------------------------- | ------------------------------------------------------------ | ------------------ | ----------------------------------------------------- |
| Distributor        | `device.distributor`      | `{   "jsonrpc": "2.0",   "id": 1,   "result": "Company" }`   | "Company"                                                    | `Sting`            | The distributor of the device (Comcast, Charter, etc) |
| Platform           | `device.platform`         | `{   "jsonrpc": "2.0",   "id": 1,   "result": "WPE" }`       | "WPE"                                                        | `Sting`            | The platform ID                                       |
| Type               | `deivce.type`             | `{   "jsonrpc": "2.0",   "id": 1,   "result": "STB" }`       | "STB"                                                        | `Sting`            | The device type                                       |
| SKU                | `device.sku`              | `{   "jsonrpc": "2.0",   "id": 1,   "result": "AX061AEI" }`  | "AX061AEI"                                                   | `Sting`            | The device SKU                                        |
| Make               | `device.make`             | `{   "jsonrpc": "2.0",   "id": 1,   "result": "Arris" }`     | "Arris"                                                      | `Sting`            | The device make                                       |
| Model              | `device.model`            | `{   "jsonrpc": "2.0",   "id": 1,   "result": "xi6" }`       | 'xi6'                                                        | `String`           | The device model                                      |
| Version            | `device.version`          | `{   "jsonrpc": "2.0",   "id": 1,   "result": {     "sdk": {       "major": 0,       "minor": 5,       "patch": 0,       "readable": "Firebolt JS SDK v0.5.0"     },     "os": {       "major": 0,       "minor": 1,       "patch": 0,       "readable": "Firebolt OS v0.1.0"     },     "debug": ""   } }` | `{   "sdk": {     "major": 0,     "minor": 5,     "patch": 0,     "readable": "Firebolt JS SDK v0.5.0"   },   "os": {     "major": 0,     "minor": 1,     "patch": 0,     "readable": "Firebolt OS v0.1.0"   },   "debug": "" }` | `Object`           | The SDK, OS and other version info of the device      |
| HDCP               | `device.hdcp`             | `{   "jsonrpc": "2.0",   "id": 1,   "result": {     "hdr10": true,     "hdr10Plus": true,     "dolbyVision": true,     "hlg": true   } }` | {     "hdr10": true,     "hdr10Plus": true,     "dolbyVision": true,     "hlg": true   } ` | `BooleanMap` |                    | The supported HDCP profiles                           |
| HDR                | `device.hdr`              | `{   "jsonrpc": "2.0",   "id": 1,   "result": {     "hdr10": true,     "hdr10Plus": true,     "dolbyVision": true,     "hlg": true   } }` | `{   "hdr10": true,   "hdr10Plus": true,   "dolbyVision": true,   "hlg": true }` | `BooleanMap`       | The supported HDR profiles                            |
| Audio              | `device.audio`            | `{   "jsonrpc": "2.0",   "id": 1,   "result": {     "stereo": true,     "dolbyDigital5.1": true,     "dolbyDigital5.1+": true,     "dolbyAtmos": true   } }` | `{   "stereo": true,   "dolbyDigital5.1": true,   "dolbyDigital5.1+": true,   "dolbyAtmos": true }` | `AudioProfiles`    | The supported audio profiles                          |
| Screen Resolution  | `device.screenResolution` | `{   "jsonrpc": "2.0",   "id": 1,   "result": [     1920,     1080   ] }` | `[   1920,   1080 ]`                                         | `[bigint, bigint]` | The screen resolution of the device                   |
| Video Resolution   | `device.videoResolution`  | `{   "jsonrpc": "2.0",   "id": 1,   "result": [     1920,     1080   ] }` | `[   1920,   1080 ]`                                         | `[bigint, bigint]` | The current video resolution                          |
| Name               | `device.name`             | `{   "jsonrpc": "2.0",   "id": 1,   "result": "Living Room" }` | `"Living Room"`                                              | `String`           | The human readable name of the device                 |
| Network            | `device.network`          | `{   "jsonrpc": "2.0",   "id": 1,   "result": {     "state": "connected",     "type": "wifi"   } }` | `{ "state": "connected",   "type": "wifi" }`                 | `Object`           | The current network status and type                   |

**Related Schemas**

##### Resolution

```typescript
type Resolution = [bigint, bigint]
```

##### **Network**

```javascript
type NetworkType = 'wifi' | 'ethernet' | 'hybrid'
```

```javascript
type NetworkState = 'connected' | 'disconnected'
```

##### **Audio Profiles**

```javascript
type AudioProfiles = {}
```

