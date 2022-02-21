### A. Personalised ads turned OFF

| Platform           | Result                                         |
| ------------------ | ---------------------------------------------- |
| CAD Result         | {"limitAdTracking":true}                       |
| Hisense TV  Result | {"limitAdTracking":true}                       |
| XRE Result         | {"limitedAdTracking":false,"usPrivacy":"1-Y-"} |
| Thor XRE  Result   | {"limitedAdTracking":false,"usPrivacy":"1-Y-"} |

**Remarks:**

1. For XCLASS - When Personalised ads turned on/off limitAdTracking value changes -  For a state(ON/OFF) of Personalised ads , the above values are constant for multiple time invocation.
2. For XRE devices and ThorXRE devices - When Personalised ads turned on/off usPrivacy value changes, but limitedAdTracking is always false. 

### B. Personalised ads turned ON

| Platform           | Result                                         |
| ------------------ | ---------------------------------------------- |
| CAD Result         | {"limitAdTracking":false}                      |
| Hisense TV  Result | {"limitAdTracking":false}                      |
| XRE Result         | {"limitedAdTracking":false,"usPrivacy":"1-N-"} |
| Thor XRE  Result   | {"limitedAdTracking":false,"usPrivacy":"1-N-"} |

