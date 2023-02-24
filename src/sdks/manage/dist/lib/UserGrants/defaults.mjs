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

    app: [
  {
    "app": {
      "id": "certapp",
      "title": "Firebolt Certification"
    },
    "state": "granted",
    "capability": "xrn:firebolt:capability:data:app-usage",
    "role": "use",
    "lifespan": "seconds",
    "expires": "2022-12-14T20:20:39+00:00"
  },
  {
    "app": {
      "id": "certapp",
      "title": "Firebolt Certification"
    },
    "state": "denied",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "role": "use",
    "lifespan": "appActive"
  }
],

    device: [
  {
    "state": "granted",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "role": "use",
    "lifespan": "powerActive"
  }
],

    capability: [
  {
    "state": "granted",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "role": "use",
    "lifespan": "powerActive"
  }
],

    grant: null,

    deny: null,

    clear: null,

    request: [
  {
    "app": {
      "id": "certapp",
      "title": "Certification App"
    },
    "state": "granted",
    "capability": "xrn:firebolt:capability:localization:postal-code",
    "role": "use",
    "lifespan": "powerActive"
  }
]
}