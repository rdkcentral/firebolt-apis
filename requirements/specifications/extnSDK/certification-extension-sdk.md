# Firebolt Extension for Certification

Document Status: Proposed Specification 

See [Firebolt Requirements Governance](../../governance.md) for more info.

## 1. Overview
Document contains the  details around Firebolt Extension for Certification (will be called as FEC in rest of the document) and HLA for the same.


## 2. Table of Contents
- [Requirements](#requirements)
- [HLA](#hla)

## 3. Requirements
FEC would required below use cases to adhere.

  - <b>Firebolt Interactions</b>
    - Ability to fetch request and state of the response coming to/from platform
    - Capability: <b>xrn:firebolt:capability:certification:fireboltinteractions</b>
  - <b>Health check Statistics</b>
    - Statistics from Firebolt-Implementation such as load, memory usage, how many firebolt connections are currently active, what apps, total requests, success and failure
    - Capability: <b>xrn:firebolt:capability:certification:healthcheck</b>
  - <b>App performance Snapshot</b>
    - Snapshot of the performance for app such as load, memory etc.
    - Capability: <b>xrn:firebolt:capability:certification:appperformancedata</b>
  - <b>Firebolt compatible provider calls</b>
    - <b>Command and Control</b>
      - To control the firebolt compatible device e.g. interaction on screen, media control
      - Capability: <b>xrn:firebolt:capability:certification:commandandcontrol</b>
    - <b>Screenshot</b>
      - Fetch and upload the screenshot
      - Capability: <b>xrn:firebolt:capability:certification:screencapture</b>

## 4. HLA

![Sequence Diagram for Certification Extension SDk](CertificationExtensionSDK.png)