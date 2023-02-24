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

import Transport from '../Transport/index.mjs'
import Events from '../Events/index.mjs'
import { registerEvents } from '../Events/index.mjs'
import Prop from '../Prop/index.mjs'

registerEvents('Privacy', Object.values(["allowResumePointsChanged","allowUnentitledResumePointsChanged","allowWatchHistoryChanged","allowProductAnalyticsChanged","allowPersonalizationChanged","allowUnentitledPersonalizationChanged","allowRemoteDiagnosticsChanged","allowPrimaryContentAdTargetingChanged","allowPrimaryBrowseAdTargetingChanged","allowAppContentAdTargetingChanged","allowACRCollectionChanged","allowCameraAnalyticsChanged"]))



function allowResumePoints() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowResumePoints', {  }, callbackOrValue, false, false, 0)
}
function allowUnentitledResumePoints() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowUnentitledResumePoints', {  }, callbackOrValue, false, false, 0)
}
function allowWatchHistory() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowWatchHistory', {  }, callbackOrValue, false, false, 0)
}
function allowProductAnalytics() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowProductAnalytics', {  }, callbackOrValue, false, false, 0)
}
function allowPersonalization() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowPersonalization', {  }, callbackOrValue, false, false, 0)
}
function allowUnentitledPersonalization() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowUnentitledPersonalization', {  }, callbackOrValue, false, false, 0)
}
function allowRemoteDiagnostics() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowRemoteDiagnostics', {  }, callbackOrValue, false, false, 0)
}
function allowPrimaryContentAdTargeting() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowPrimaryContentAdTargeting', {  }, callbackOrValue, false, false, 0)
}
function allowPrimaryBrowseAdTargeting() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowPrimaryBrowseAdTargeting', {  }, callbackOrValue, false, false, 0)
}
function allowAppContentAdTargeting() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowAppContentAdTargeting', {  }, callbackOrValue, false, false, 0)
}
function allowACRCollection() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowACRCollection', {  }, callbackOrValue, false, false, 0)
}
function allowCameraAnalytics() {
  const callbackOrValue = arguments[0]
  return Prop.prop('privacy',  'allowCameraAnalytics', {  }, callbackOrValue, false, false, 0)
}

function settings() {

  const transforms = null

  return Transport.send('privacy', 'settings', {  }, transforms)
}
// onAllowResumePointsChanged API is handled via listen('allowResumePointsChanged', (data) => void)
// onAllowUnentitledResumePointsChanged API is handled via listen('allowUnentitledResumePointsChanged', (data) => void)
// onAllowWatchHistoryChanged API is handled via listen('allowWatchHistoryChanged', (data) => void)
// onAllowProductAnalyticsChanged API is handled via listen('allowProductAnalyticsChanged', (data) => void)
// onAllowPersonalizationChanged API is handled via listen('allowPersonalizationChanged', (data) => void)
// onAllowUnentitledPersonalizationChanged API is handled via listen('allowUnentitledPersonalizationChanged', (data) => void)
// onAllowRemoteDiagnosticsChanged API is handled via listen('allowRemoteDiagnosticsChanged', (data) => void)
// onAllowPrimaryContentAdTargetingChanged API is handled via listen('allowPrimaryContentAdTargetingChanged', (data) => void)
// onAllowPrimaryBrowseAdTargetingChanged API is handled via listen('allowPrimaryBrowseAdTargetingChanged', (data) => void)
// onAllowAppContentAdTargetingChanged API is handled via listen('allowAppContentAdTargetingChanged', (data) => void)
// onAllowACRCollectionChanged API is handled via listen('allowACRCollectionChanged', (data) => void)
// onAllowCameraAnalyticsChanged API is handled via listen('allowCameraAnalyticsChanged', (data) => void)

    function listen(...args) {
      return Events.listen('privacy', ...args)
    } 
    
    function once(...args) {
      return Events.once('privacy', ...args)
    }
    
    function clear(...args) {
      return Events.clear('privacy', ...args)
    }
    
export default {

  events: {
    allowResumePointsChanged:'allowResumePointsChanged',
    allowUnentitledResumePointsChanged:'allowUnentitledResumePointsChanged',
    allowWatchHistoryChanged:'allowWatchHistoryChanged',
    allowProductAnalyticsChanged:'allowProductAnalyticsChanged',
    allowPersonalizationChanged:'allowPersonalizationChanged',
    allowUnentitledPersonalizationChanged:'allowUnentitledPersonalizationChanged',
    allowRemoteDiagnosticsChanged:'allowRemoteDiagnosticsChanged',
    allowPrimaryContentAdTargetingChanged:'allowPrimaryContentAdTargetingChanged',
    allowPrimaryBrowseAdTargetingChanged:'allowPrimaryBrowseAdTargetingChanged',
    allowAppContentAdTargetingChanged:'allowAppContentAdTargetingChanged',
    allowACRCollectionChanged:'allowACRCollectionChanged',
    allowCameraAnalyticsChanged:'allowCameraAnalyticsChanged'
  },
allowResumePoints,
  allowUnentitledResumePoints,
  allowWatchHistory,
  allowProductAnalytics,
  allowPersonalization,
  allowUnentitledPersonalization,
  allowRemoteDiagnostics,
  allowPrimaryContentAdTargeting,
  allowPrimaryBrowseAdTargeting,
  allowAppContentAdTargeting,
  allowACRCollection,
  allowCameraAnalytics,
  settings,
  listen,
  once,
  clear
}