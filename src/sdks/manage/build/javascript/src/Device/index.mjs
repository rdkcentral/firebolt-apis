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

registerEvents('Device', Object.values(["deviceNameChanged","nameChanged","developerModeChanged"]))


Transport.registerDeprecatedMethod('Device', 'onDeviceNameChanged', 'Use Device.name() instead.')

function name() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'name', {  }, callbackOrValue, false, false, 0)
}
// onDeviceNameChanged API is handled via listen('deviceNameChanged', (data) => void)

function provision(accountId, deviceId, distributorId) {

  const transforms = null

  return Transport.send('device', 'provision', { accountId, deviceId, distributorId }, transforms)
}
function developerMode() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'developerMode', {  }, callbackOrValue, false, false, 0)
}
// onNameChanged API is handled via listen('nameChanged', (data) => void)
// onDeveloperModeChanged API is handled via listen('developerModeChanged', (data) => void)

    function listen(...args) {
      return Events.listen('device', ...args)
    } 
    
    function once(...args) {
      return Events.once('device', ...args)
    }
    
    function clear(...args) {
      return Events.clear('device', ...args)
    }
    
export default {

  events: {
    deviceNameChanged:'deviceNameChanged',
    nameChanged:'nameChanged',
    developerModeChanged:'developerModeChanged'
  },
name,
  provision,
  developerMode,
  listen,
  once,
  clear
}