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

registerEvents('SecondScreen', Object.values(["launchRequest","closeRequest","friendlyNameChanged"]))




function protocols() {

  const transforms = null

  return Transport.send('secondscreen', 'protocols', {  }, transforms)
}

function device(type) {

  const transforms = null

  return Transport.send('secondscreen', 'device', { type }, transforms)
}
function friendlyName() {
  const callbackOrValue = arguments[0]
  return Prop.prop('secondscreen',  'friendlyName', {  }, callbackOrValue, false, true, 0)
}
// onLaunchRequest API is handled via listen('launchRequest', (data) => void)
// onCloseRequest API is handled via listen('closeRequest', (data) => void)
// onFriendlyNameChanged API is handled via listen('friendlyNameChanged', (data) => void)

    function listen(...args) {
      return Events.listen('secondscreen', ...args)
    } 
    
    function once(...args) {
      return Events.once('secondscreen', ...args)
    }
    
    function clear(...args) {
      return Events.clear('secondscreen', ...args)
    }
    
export default {

  events: {
    launchRequest:'launchRequest',
    closeRequest:'closeRequest',
    friendlyNameChanged:'friendlyNameChanged'
  },
protocols,
  device,
  friendlyName,
  listen,
  once,
  clear
}