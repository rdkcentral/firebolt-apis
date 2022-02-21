### A. Personalised ads turned OFF

| Platform           | Result                                                       |
| ------------------ | ------------------------------------------------------------ |
| CAD Result         | {"id":20,"result":{"ifa":"5571cc8a-6921-49aa-b05c-953b391bffa2","ifa_type":"sessionId","lmt":"1"},"jsonrpc":"2.0"} |
| Hisense TV  Result | {"id":19,"result":{"ifa":"35c2737b-e610-4680-a3ab-a7584c01939e","ifa_type":"sessionId","lmt":"1"},"jsonrpc":"2.0"} |
| XRE Result         | {"result":{"lmt":"1","ifa":"9948eaf8-8fa7-4f97-8b91-c668ce71b609","ifaType":"sessionId"} |
| Thor XRE  Result   | {"result":{"lmt":"1","ifa":"7f155904-442f-4d57-9934-959ce93db783","ifaType":"sessionId"} |

**Remarks:**

1. For XCLASS and ThorXRE devices - When Personalised ads turned on/off ifa,ifa_type,lmt value changes -  For a state(ON/OFF) of Personalised ads , the above values are constant for multiple time invocation.
2. For XRE devices - When Personalised ads turned on/off no changes

### B. Personalised ads turned ON

| Platform           | Result                                                       |
| ------------------ | ------------------------------------------------------------ |
| CAD Result         | {"ifa":"a0ba15b9-729f-430d-b783-d979d58e051e","ifa_type":"sspid","lmt":"0"} |
| Hisense TV  Result | {"ifa":"4abd952a-39d7-441d-8f13-b1fe36e8736f","ifa_type":"sspid","lmt":"0"} |
| XRE Result         | {"lmt":"1","ifa":"9948eaf8-8fa7-4f97-8b91-c668ce71b609","ifaType":"sessionId"} |
| Thor XRE  Result   | {"lmt":"0","ifa":"f38e69c0-e953-4ac4-853c-3910162ba2ac","ifaType":"sspid"} |