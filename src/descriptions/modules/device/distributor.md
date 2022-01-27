Get the distributor ID for this device

| Device Information | Request              | Response                                                   | Value     | Return Type[^1] | Description                                           |
| ------------------ | -------------------- | :--------------------------------------------------------- | --------- | --------------- | ----------------------------------------------------- |
| Distributor        | `device.distributor` | `{   "jsonrpc": "2.0",   "id": 1,   "result": "Company" }` | "Company" | `Sting`         | The distributor of the device (Comcast, Charter, etc) |