# Requirements Style Guide

Document Status: Working Draft

See [Firebolt Requirements Governance](./governance.md) for more info.

**NOTE**: Update this link based on your directory depth ^^

| Contributor    | Organization   |
| -------------- | -------------- |
| TBD            | TBD            |

## 1. Overview
This document is both a style guide *and* a template for Firebolt Requirements Specifications.

The Overview section is a non-normative or informative introduction to the contents and subject matter of the document. This is included to introduce the reader to the overall problem, solution, and scope. No formal requirements will be included here, as it will often be skipped by readers that are already familiar with the document.

Overviews can be as long or short as appropriate for the subject matter, and should have a target audience ranging from technical product managers to engineering teams that may be testing, implementing, or integrating with the functionality described in the document.

The overview must contain the following towards the end:

Requirements documents are written using the [IETF Best Common Practice 14](https://www.rfc-editor.org/rfc/rfc2119.txt) and should include the following summary in the Overview section:

The key words "**MUST**", "**MUST NOT**", "**REQUIRED**", "**SHALL**", "**SHALL NOT**", "**SHOULD**", "**SHOULD NOT**", "**RECOMMENDED**", "**NOT RECOMMENDED**", "**MAY**", and "**OPTIONAL**" in this document are to be interpreted as described in [BCP 14](https://www.rfc-editor.org/rfc/rfc2119.txt) [RFC2119] [RFC8174] when, and only when, they appear in all capitals, as shown here.

## 2. Table of Contents
- [1. Overview](#1-overview)
- [2. Table of Contents](#2-table-of-contents)
- [3. Channel Scanning](#3-channel-scanning)
  - [3.1. Example Feature](#31-example-feature)
  - [3.2. APIs](#32-apis)

**NOTE**: This is a simple table of contents. It should include links to all headers in the document, except for the top-level header (i.e. `# Title`). It is recommended to use a Markdown plugin to generate this based on headers ranging from level two to level six. Delete this note from your actual spec :)

## 3. Channel Scanning
A section describes group of closely related features. Many specifications have only one section, however, more complicated specifications may have many. The first paragraph of a section is typically a non-normative introduction to that section, and therefor does not contain any formal requirements.

As a first party app, I want to initiate a channel scan to discover which channels have a strong enough signal to be tuned via an antennae or dish.

As a first party app, I want to periodically scan for changes to the available channels to add newly tunable channels, and remove channels that are no longer tunable.

As a first party app, I want to know if a scan failed for any reason.

As a first party app, I want to know the approximate progress, as a percentage, of the active scan.

As a first party app, I want to know the number of channels found, in real time, of the active scan.



### 3.1. Example Feature
Each feature under a section will have it's own heading. Non-normative introductions to features are not typically needed, as the reader is ready to get into requirements at this point. It is recommended that all Feature headings under each Section contain only sentences or short paragraphs with formal requirements, e.g. MUST, SHOULD, MAY, MUST NOT, SHOULD NOT, etc. These sentences should be separated by blank lines for readability, e.g.:

This requirement **MUST** be satisifed.

This requirement **SHOULD** be satisfied.

This requirement **MUST** be satisfied. The requirement **MUST** be satisifed in this particular way.


### 3.2. APIs

Given an OpenRPC method tagged with `progressive-update`, e.g. `scan`, Firebolt OpenRPC will generate the following additional RPC methods:

`onScanError` - an event listener that can return any of the schemas in the `scan` methdod's `x-errors` tag extension.
`onScanProgress` - an event listener that periodically sends progress updates. Every `progress` event has an attribute called `percentage` that MUST approximate the percent complete the process is. If the `scan` methods result is not null, then the `progress` event will also have a proeprty called `data` with the current values of the result, e.g. what the result we be if we were done now.
`onScanComplete` - an event listener that fires when the scan is completely done. the payload is the final result of the `scan` method, which uses the same schema as the `result` of the `scan` method

The formal OpenRPC result of any `progressive-update` method should re

```c
#include Channels.h

Channels_scan()

```

```typescript

interface ScanProcess {
    function stop(): void;
    function onProgress(callback: (progress: ScanProgress) => void): void;
    function onComplete(callback: (data: ScanStatus) => void): void;
    function onStop()callback: (data: ScanStatus)=> void): void;
    function onError(callback: (error) => void): void;
}

interface Channels {
    function scan(): ScanProcess;
    function status(): ScanStatus;
    function getScan(): ScanProcess;
    function get(...): Channel[] // need some queries here...
}

// initiate a new scan and return the process
const scan = Channels.scan();

// get the current ScanResult (error if none active)
const status = await Channels.status() // 

{
    state; //'uninitiated' | 'scanning' | 'stopped' | 'complete'
    count;
}

// example

let scan: ScanProcess, data: ScanResult

if (status.state === 'uninitiated') {
    scan = Channels.scan();
}
else if (status.state === 'scanning') {
    scan = Channels.getScan() // throws error if no active scan
}
else if (status.state === 'complete') {
    doSomethingWithScanData(status)
}

if (scan) {

    // display progress UI

    scan.onProgress(progress => {
        console.log(progress.percent)
        console.log(progress.data.count)
    });

    scan.onError(error => {
        console.error(error)    
    })

    scan.onComplete(data => {
        doSomethingWithScanData(data)
        console.log(data.count)
    })
}
else {
    doSomethingWithScanData(status)
}

```