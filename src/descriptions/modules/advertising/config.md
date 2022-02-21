### Personalised ads turned OFF

#### A. No Coppa Value

| Platform           | Result: No coppa value                                       |
| ------------------ | ------------------------------------------------------------ |
| CAD Result         | {"id":10,"result":{"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"5571cc8a-6921-49aa-b05c-953b391bffa2","ifa":"eyJ2YWx1ZSI6IjU1NzFjYzhhLTY5MjEtNDlhYS1iMDVjLTk1M2IzOTFiZmZhMiIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"0","authenticationEntity":""},"jsonrpc":"2.0"} |
| Hisense TV  Result | {"id":16,"result":{"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"35c2737b-e610-4680-a3ab-a7584c01939e","ifa":"eyJ2YWx1ZSI6IjM1YzI3MzdiLWU2MTAtNDY4MC1hM2FiLWE3NTg0YzAxOTM5ZSIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"0","authenticationEntity":""},"jsonrpc":"2.0"} |
| XRE Result         | {"code":401,"message":"config Method requires  use of at least one Object-embedded param with boolean 'coppa' key."} |
| Thor XRE  Result   | {"code":401,"message":"config Method requires  use of at least one Object-embedded param with boolean 'coppa' key."} |

**Remarks:** 

1. For XCLASS - When Personalised ads turned on/off - adOptOut , privacyData, ifaValue, ifa changes. 
2. For a state(ON/OFF) of Personalised ads , the above values are constant for multiple time invocation.
3. For XRE devices and ThorXRE devices - Error message

#### B. Coppa Value False

| Platform           | Result: coppa value false                                    |
| ------------------ | ------------------------------------------------------------ |
| CAD Result         | {"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"5571cc8a-6921-49aa-b05c-953b391bffa2","ifa":"eyJ2YWx1ZSI6IjU1NzFjYzhhLTY5MjEtNDlhYS1iMDVjLTk1M2IzOTFiZmZhMiIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"0","authenticationEntity":""} |
| Hisense TV  Result | {"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"35c2737b-e610-4680-a3ab-a7584c01939e","ifa":"eyJ2YWx1ZSI6IjM1YzI3MzdiLWU2MTAtNDY4MC1hM2FiLWE3NTg0YzAxOTM5ZSIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"0","authenticationEntity":""} |
| XRE Result         | {"adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"9948eaf8-8fa7-4f97-8b91-c668ce71b609","ifa":"eyJ2YWx1ZSI6Ijk5NDhlYWY4LThmYTctNGY5Ny04YjkxLWM2NjhjZTcxYjYwOSIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"Comcast_FireboltRefApp","appBundleID":"Comcast_FireboltRefApp.Comcast","distributorAppID":"1000","coppa":"0"} |
| Thor XRE  Result   | {"adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"7f155904-442f-4d57-9934-959ce93db783","ifa":"eyJ2YWx1ZSI6IjdmMTU1OTA0LTQ0MmYtNGQ1Ny05OTM0LTk1OWNlOTNkYjc4MyIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"Comcast_FireboltRefApp","appBundleID":"Comcast_FireboltRefApp.Comcast","distributorAppID":"1001","coppa":"0"} |

| Platform           | Result:  -coppa value true                                   |
| ------------------ | ------------------------------------------------------------ |
| CAD Result         | {"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"5571cc8a-6921-49aa-b05c-953b391bffa2","ifa":"eyJ2YWx1ZSI6IjU1NzFjYzhhLTY5MjEtNDlhYS1iMDVjLTk1M2IzOTFiZmZhMiIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"1","authenticationEntity":""} |
| Hisense TV  Result | {"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"35c2737b-e610-4680-a3ab-a7584c01939e","ifa":"eyJ2YWx1ZSI6IjM1YzI3MzdiLWU2MTAtNDY4MC1hM2FiLWE3NTg0YzAxOTM5ZSIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"1","authenticationEntity":""} |
| XRE Result         | {"adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"9948eaf8-8fa7-4f97-8b91-c668ce71b609","ifa":"eyJ2YWx1ZSI6Ijk5NDhlYWY4LThmYTctNGY5Ny04YjkxLWM2NjhjZTcxYjYwOSIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"Comcast_FireboltRefApp","appBundleID":"Comcast_FireboltRefApp.Comcast","distributorAppID":"1000","coppa":"1"} |
| Thor XRE  Result   | {"adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"7f155904-442f-4d57-9934-959ce93db783","ifa":"eyJ2YWx1ZSI6IjdmMTU1OTA0LTQ0MmYtNGQ1Ny05OTM0LTk1OWNlOTNkYjc4MyIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"Comcast_FireboltRefApp","appBundleID":"Comcast_FireboltRefApp.Comcast","distributorAppID":"1001","coppa":"1"} |

**Remarks**: 

1. For XCLASS and ThorXRE devices - When Personalised ads turned on/off - adOptOut , privacyData, ifaValue, ifa changes. For a state(ON/OFF) of Personalised ads , the above values are constant for multiple time invocation.
2. For XRE devices - No changes in  adOptOut , privacyData, ifaValue, ifa even when Personalised ads is turned on/off. The above values are constant for multiple time invocation. 
3. For XCLASS devices, the response contains 15 key-value pairs but XRE devices response contains 8 key-value pairs only"



### Personalised ads turned ON

#### A. No Coppa Value

| Platform           | Result: No Coppa Value                                       |
| ------------------ | ------------------------------------------------------------ |
| CAD Result         | {"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":false,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1OLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjAifQ==","ifaValue":"a0ba15b9-729f-430d-b783-d979d58e051e","ifa":"eyJ2YWx1ZSI6ImEwYmExNWI5LTcyOWYtNDMwZC1iNzgzLWQ5NzlkNThlMDUxZSIsImlmYV90eXBlIjoic3NwaWQiLCJsbXQiOiIwIn0=","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"0","authenticationEntity":""} |
| Hisense TV  Result | {"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":false,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1OLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjAifQ==","ifaValue":"4abd952a-39d7-441d-8f13-b1fe36e8736f","ifa":"eyJ2YWx1ZSI6IjRhYmQ5NTJhLTM5ZDctNDQxZC04ZjEzLWIxZmUzNmU4NzM2ZiIsImlmYV90eXBlIjoic3NwaWQiLCJsbXQiOiIwIn0=","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"0","authenticationEntity":""} |
| XRE Result         | {"code":401,"message":"config  Method requires use of at least one Object-embedded param with boolean  'coppa' key."} |
| Thor XRE  Result   | {"code":401,"message":"config  Method requires use of at least one Object-embedded param with boolean  'coppa' key."} |

#### B. Coppa Value False

| Platform           | Result: Coppa Value False                                    |
| ------------------ | ------------------------------------------------------------ |
| CAD Result         | {"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":false,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1OLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjAifQ==","ifaValue":"a0ba15b9-729f-430d-b783-d979d58e051e","ifa":"eyJ2YWx1ZSI6ImEwYmExNWI5LTcyOWYtNDMwZC1iNzgzLWQ5NzlkNThlMDUxZSIsImlmYV90eXBlIjoic3NwaWQiLCJsbXQiOiIwIn0=","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"0","authenticationEntity":""} |
| Hisense TV  Result | {"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":false,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1OLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjAifQ==","ifaValue":"4abd952a-39d7-441d-8f13-b1fe36e8736f","ifa":"eyJ2YWx1ZSI6IjRhYmQ5NTJhLTM5ZDctNDQxZC04ZjEzLWIxZmUzNmU4NzM2ZiIsImlmYV90eXBlIjoic3NwaWQiLCJsbXQiOiIwIn0=","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"0","authenticationEntity":""} |
| XRE Result         | {"adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"9948eaf8-8fa7-4f97-8b91-c668ce71b609","ifa":"eyJ2YWx1ZSI6Ijk5NDhlYWY4LThmYTctNGY5Ny04YjkxLWM2NjhjZTcxYjYwOSIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"Comcast_FireboltRefApp","appBundleID":"Comcast_FireboltRefApp.Comcast","distributorAppID":"1000","coppa":"0"} |
| Thor XRE  Result   | {"privacyData":"eyJ1c19wcml2YWN5IjoiMS1OLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjAifQ==","ifaValue":"f38e69c0-e953-4ac4-853c-3910162ba2ac","ifa":"eyJ2YWx1ZSI6ImYzOGU2OWMwLWU5NTMtNGFjNC04NTNjLTM5MTAxNjJiYTJhYyIsImlmYV90eXBlIjoic3NwaWQiLCJsbXQiOiIwIn0=","appName":"Comcast_FireboltRefApp","appBundleID":"Comcast_FireboltRefApp.Comcast","distributorAppID":"1001","coppa":"0"} |

#### C. Coppa Value True

| Platform           | Result: Coppa Value True                                     |
| ------------------ | ------------------------------------------------------------ |
| CAD Result         | {"id":14,"result":{"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":false,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1OLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjAifQ==","ifaValue":"a0ba15b9-729f-430d-b783-d979d58e051e","ifa":"eyJ2YWx1ZSI6ImEwYmExNWI5LTcyOWYtNDMwZC1iNzgzLWQ5NzlkNThlMDUxZSIsImlmYV90eXBlIjoic3NwaWQiLCJsbXQiOiIwIn0=","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"1","authenticationEntity":""},"jsonrpc":"2.0"} |
| Hisense TV  Result | {"id":16,"result":{"adServerUrl":"","adServerUrlTemplate":"","adNetworkID":"","adProfileID":"","adSiteSectionID":"","adOptOut":false,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1OLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjAifQ==","ifaValue":"4abd952a-39d7-441d-8f13-b1fe36e8736f","ifa":"eyJ2YWx1ZSI6IjRhYmQ5NTJhLTM5ZDctNDQxZC04ZjEzLWIxZmUzNmU4NzM2ZiIsImlmYV90eXBlIjoic3NwaWQiLCJsbXQiOiIwIn0=","appName":"comcast_firebolt_reference","appBundleID":"comcast_firebolt_reference.Comcast","distributorAppID":"1001","deviceAdAttributes":"eyJib0F0dHJpYnV0ZXNGb3JSZXZTaGFyZUlkIjoiMTExMiJ9","coppa":"1","authenticationEntity":""},"jsonrpc":"2.0"} |
| XRE Result         | {"result":{"adOptOut":true,"privacyData":"eyJ1c19wcml2YWN5IjoiMS1ZLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjEifQ==","ifaValue":"9948eaf8-8fa7-4f97-8b91-c668ce71b609","ifa":"eyJ2YWx1ZSI6Ijk5NDhlYWY4LThmYTctNGY5Ny04YjkxLWM2NjhjZTcxYjYwOSIsImlmYV90eXBlIjoic2Vzc2lvbklkIiwibG10IjoiMSJ9","appName":"Comcast_FireboltRefApp","appBundleID":"Comcast_FireboltRefApp.Comcast","distributorAppID":"1000","coppa":"1"} |
| Thor XRE  Result   | {"result":{"privacyData":"eyJ1c19wcml2YWN5IjoiMS1OLSIsInBkdCI6ImdkcDp2MSIsImxtdCI6IjAifQ==","ifaValue":"f38e69c0-e953-4ac4-853c-3910162ba2ac","ifa":"eyJ2YWx1ZSI6ImYzOGU2OWMwLWU5NTMtNGFjNC04NTNjLTM5MTAxNjJiYTJhYyIsImlmYV90eXBlIjoic3NwaWQiLCJsbXQiOiIwIn0=","appName":"Comcast_FireboltRefApp","appBundleID":"Comcast_FireboltRefApp.Comcast","distributorAppID":"1001","coppa":"1"} |

**Remarks:**

1. For  thorXRE when the personalized data is ON "adOptOut" is missing in  the response