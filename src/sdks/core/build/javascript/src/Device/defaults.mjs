/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
import MockProps from "../Prop/MockProps.mjs"

export default {

    id: function () { return MockProps.mock('device', 'id', arguments, "123") },

    distributor: function () { return MockProps.mock('device', 'distributor', arguments, "Company") },

    platform: function () { return MockProps.mock('device', 'platform', arguments, "WPE") },

    uid: function () { return MockProps.mock('device', 'uid', arguments, "ee6723b8-7ab3-462c-8d93-dbf61227998e") },

    type: function () { return MockProps.mock('device', 'type', arguments, "STB") },

    model: function () { return MockProps.mock('device', 'model', arguments, "xi6") },

    sku: function () { return MockProps.mock('device', 'sku', arguments, "AX061AEI") },

    make: function () { return MockProps.mock('device', 'make', arguments, "Arris") },

    version: function () { return MockProps.mock('device', 'version', arguments, {
  "sdk": {
    "major": 0,
    "minor": 8,
    "patch": 0,
    "readable": "Firebolt JS SDK v0.8.0"
  },
  "api": {
    "major": 0,
    "minor": 8,
    "patch": 0,
    "readable": "Firebolt API v0.8.0"
  },
  "firmware": {
    "major": 1,
    "minor": 2,
    "patch": 3,
    "readable": "Device Firmware v1.2.3"
  },
  "os": {
    "major": 0,
    "minor": 1,
    "patch": 0,
    "readable": "Firebolt OS v0.1.0"
  },
  "debug": "Non-parsable build info for error logging only."
}) },

    hdcp: function () { return MockProps.mock('device', 'hdcp', arguments, {
  "hdcp1.4": true,
  "hdcp2.2": true
}) },

    hdr: function () { return MockProps.mock('device', 'hdr', arguments, {
  "hdr10": true,
  "hdr10Plus": true,
  "dolbyVision": true,
  "hlg": true
}) },

    audio: function () { return MockProps.mock('device', 'audio', arguments, {
  "stereo": true,
  "dolbyDigital5.1": true,
  "dolbyDigital5.1+": true,
  "dolbyAtmos": true
}) },

    screenResolution: function () { return MockProps.mock('device', 'screenResolution', arguments, [
  1920,
  1080
]) },

    videoResolution: function () { return MockProps.mock('device', 'videoResolution', arguments, [
  1920,
  1080
]) },

    name: function () { return MockProps.mock('device', 'name', arguments, "Living Room") },

    network: function () { return MockProps.mock('device', 'network', arguments, {
  "state": "connected",
  "type": "wifi"
}) }
}