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

registerEvents('Advertising', Object.values(["policyChanged"]))




function config(options) {

  const transforms = null

  return Transport.send('advertising', 'config', { options }, transforms)
}
function policy() {
  const callbackOrValue = arguments[0]
  return Prop.prop('advertising',  'policy', {  }, callbackOrValue, false, true, 0)
}

function advertisingId() {

  const transforms = null

  return Transport.send('advertising', 'advertisingId', {  }, transforms)
}

function deviceAttributes() {

  const transforms = null

  return Transport.send('advertising', 'deviceAttributes', {  }, transforms)
}

function appBundleId() {

  const transforms = null

  return Transport.send('advertising', 'appBundleId', {  }, transforms)
}
// onPolicyChanged API is handled via listen('policyChanged', (data) => void)

    function listen(...args) {
      return Events.listen('advertising', ...args)
    } 
    
    function once(...args) {
      return Events.once('advertising', ...args)
    }
    
    function clear(...args) {
      return Events.clear('advertising', ...args)
    }
    
export default {

  events: {
    policyChanged:'policyChanged'
  },

  SkipRestriction: {
    NONE: 'none',
    ADS_UNWATCHED: 'adsUnwatched',
    ADS_ALL: 'adsAll',
    ALL: 'all'
  },

config,
  policy,
  advertisingId,
  deviceAttributes,
  appBundleId,
  listen,
  once,
  clear
}