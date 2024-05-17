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

  - <b>Firebolt Interactions</b>
    - Ability to fetch request and responses coming to/from platform
    - Capability: <b>xrn:firebolt:capability:cert-extension:fireboltinteractions</b>
  - <b>Health check Statistics</b>
    - Statistics from Firebolt-Implementation such as load, memory usage, how many firebolt connections are currently active, what apps, total requests, success and failure
    - Capability: <b>xrn:firebolt:capability:cert-extension:healthcheck</b>
  - <b>App performance Snapshot</b>
    - Snapshot of the performance for app such as load, memory etc.
    - Capability: <b>xrn:firebolt:capability:cert-extension:appperformancedata</b>
  - <b>Firebolt compatible provider calls</b>
    - <b>Keypress</b>
      - To navigate on the screen
      - Capability: <b>xrn:firebolt:capability:cert-extension:keypress</b>
    - <b>Screenshot</b>
      - Fetch and upload the screenshot
      - Capability: <b>xrn:firebolt:capability:cert-extension:screencapture</b>

## 4. HLA

![Sequence Diagram for Certification Extension SDk](CertificationExtensionSDK.png)