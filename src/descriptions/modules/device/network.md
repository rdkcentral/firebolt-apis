Network allows you to see if your app is running on a connected device and how it's connected to the internet. 

| Device Information | Request          | Response                                                     | Value                                        | Return Type[^1] | Description                         |
| ------------------ | ---------------- | ------------------------------------------------------------ | -------------------------------------------- | --------------- | ----------------------------------- |
| Network            | `device.network` | `{   "jsonrpc": "2.0",   "id": 1,   "result": {     "state": "connected",     "type": "wifi"   } }` | `{ "state": "connected",   "type": "wifi" }` | `Object`        | The current network status and type |

For Network type you can have a single return value of `wifi`, `ethernet`, or `hybrid`. Similarly you can have a single return value for NetworkState of either `connected` or `dicconnected`.

The return values are also reusable objects. 

##### [**Network**](/#networkstate)

```javascript
type NetworkType = 'wifi' | 'ethernet' | 'hybrid'
```

```javascript
type NetworkState = 'connected' | 'disconnected'
```

#####  