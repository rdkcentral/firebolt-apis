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

    allowResumePoints: function () { return MockProps.mock('privacy', 'allowResumePoints', arguments, true) },

    allowUnentitledResumePoints: function () { return MockProps.mock('privacy', 'allowUnentitledResumePoints', arguments, true) },

    allowWatchHistory: function () { return MockProps.mock('privacy', 'allowWatchHistory', arguments, true) },

    allowProductAnalytics: function () { return MockProps.mock('privacy', 'allowProductAnalytics', arguments, true) },

    allowPersonalization: function () { return MockProps.mock('privacy', 'allowPersonalization', arguments, true) },

    allowUnentitledPersonalization: function () { return MockProps.mock('privacy', 'allowUnentitledPersonalization', arguments, true) },

    allowRemoteDiagnostics: function () { return MockProps.mock('privacy', 'allowRemoteDiagnostics', arguments, true) },

    allowPrimaryContentAdTargeting: function () { return MockProps.mock('privacy', 'allowPrimaryContentAdTargeting', arguments, true) },

    allowPrimaryBrowseAdTargeting: function () { return MockProps.mock('privacy', 'allowPrimaryBrowseAdTargeting', arguments, true) },

    allowAppContentAdTargeting: function () { return MockProps.mock('privacy', 'allowAppContentAdTargeting', arguments, true) },

    allowACRCollection: function () { return MockProps.mock('privacy', 'allowACRCollection', arguments, true) },

    allowCameraAnalytics: function () { return MockProps.mock('privacy', 'allowCameraAnalytics', arguments, true) },

    settings: {
  "allowACRCollection": true,
  "allowResumePoints": false,
  "allowAppContentAdTargeting": false,
  "allowCameraAnalytics": true,
  "allowPersonalization": true,
  "allowPrimaryBrowseAdTargeting": false,
  "allowPrimaryContentAdTargeting": false,
  "allowProductAnalytics": true,
  "allowRemoteDiagnostics": true,
  "allowUnentitledPersonalization": true,
  "allowUnentitledResumePoints": false,
  "allowWatchHistory": true
},

    setAllowResumePoints: null,

    setAllowUnentitledResumePoints: null,

    setAllowWatchHistory: null,

    setAllowProductAnalytics: null,

    setAllowPersonalization: null,

    setAllowUnentitledPersonalization: null,

    setAllowRemoteDiagnostics: null,

    setAllowPrimaryContentAdTargeting: null,

    setAllowPrimaryBrowseAdTargeting: null,

    setAllowAppContentAdTargeting: null,

    setAllowACRCollection: null,

    setAllowCameraAnalytics: null
}