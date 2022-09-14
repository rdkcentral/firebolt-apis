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

registerEvents('Accessibility', Object.values(["closedCaptionsSettingsChanged","voiceGuidanceSettingsChanged"]))


Transport.registerDeprecatedMethod('Accessibility', 'closedCaptions', 'Use Accessibility.closedCaptionsSettings() instead.')
Transport.registerDeprecatedMethod('Accessibility', 'voiceGuidance', 'Use Accessibility.voiceGuidanceSettings() instead.')


function closedCaptions() {

  const transforms = null

  return Transport.send('accessibility', 'closedCaptions', {  }, transforms)
}
function closedCaptionsSettings() {
  const callbackOrValue = arguments[0]
  return Prop.prop('accessibility',  'closedCaptionsSettings', {  }, callbackOrValue, false, true, 0)
}

function voiceGuidance() {

  const transforms = null

  return Transport.send('accessibility', 'voiceGuidance', {  }, transforms)
}
function voiceGuidanceSettings() {
  const callbackOrValue = arguments[0]
  return Prop.prop('accessibility',  'voiceGuidanceSettings', {  }, callbackOrValue, false, true, 0)
}
// onClosedCaptionsSettingsChanged API is handled via listen('closedCaptionsSettingsChanged', (data) => void)
// onVoiceGuidanceSettingsChanged API is handled via listen('voiceGuidanceSettingsChanged', (data) => void)

    function listen(...args) {
      return Events.listen('accessibility', ...args)
    } 
    
    function once(...args) {
      return Events.once('accessibility', ...args)
    }
    
    function clear(...args) {
      return Events.clear('accessibility', ...args)
    }
    
export default {

  events: {
    closedCaptionsSettingsChanged:'closedCaptionsSettingsChanged',
    voiceGuidanceSettingsChanged:'voiceGuidanceSettingsChanged'
  },
closedCaptions,
  closedCaptionsSettings,
  voiceGuidance,
  voiceGuidanceSettings,
  listen,
  once,
  clear
}