| Platform   | Result                                                   |
| ---------- | -------------------------------------------------------- |
| CAD        | `{{"state":"connected","type":"WIFI"},"success":true  }` |
| Hicense TV | `{"state":"connected","type":"ETHERNET"}`                |
| XRE        | `{"state":"connected","type":"hybrid"}`                  |
| Thor XRE   | `{"state":"connected","type":"wifi"}`                    |

**Remarks: Differs for devices according to  the network.**

#### Notes

Network allows you to see if your app is running on a connected device and how it's connected to the internet. 

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