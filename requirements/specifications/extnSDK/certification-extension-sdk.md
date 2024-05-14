# Certification Extension SDK

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info.

## 1. Overview
Document contains the  details around Certification Extension SDK (will be called as CE-SDK in rest of the document) and HLA for the same.


## 2. Table of Contents
- [Requirements](#requirements)
- [HLA](#hla)

## 3. Requirements
CE-SDK would required below use cases to adhere.

  - Firebolt Interactions
    - Ability to fetch request and responses coming to/from platform
  - Performance Metrics
    - Ability to get performance metrics such as load, memory of the device via tools eg., CollectD
    - Ability to fetch performance metrics such as load, memory for particular process eg., Ripple
    - Ability to fetch app performance snapshot
  - Health check Statistics
    - Statistics such as how many firebolt connections are currently active, what apps, total requests, success and failure 
  - Thunder calls
    - Keypress
      - To navigate on the screen
    - Screenshot
      - Fetch, upload and compare
    - State of the application
      - Lifecycle state of the application
    - Device Info
    - Set & Get system settings
    - TBD - more would be added as and when new requirement comes in

## 4. HLA


