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

registerEvents('Localization', Object.values(["languageChanged"]))




function locality() {

  const transforms = null

  return Transport.send('localization', 'locality', {  }, transforms)
}

function postalCode() {

  const transforms = null

  return Transport.send('localization', 'postalCode', {  }, transforms)
}

function countryCode() {

  const transforms = null

  return Transport.send('localization', 'countryCode', {  }, transforms)
}
function language() {
  const callbackOrValue = arguments[0]
  return Prop.prop('localization',  'language', {  }, callbackOrValue, false, true, 0)
}

function locale() {

  const transforms = null

  return Transport.send('localization', 'locale', {  }, transforms)
}

function latlon() {

  const transforms = null

  return Transport.send('localization', 'latlon', {  }, transforms)
}

function additionalInfo() {

  const transforms = null

  return Transport.send('localization', 'additionalInfo', {  }, transforms)
}
// onLanguageChanged API is handled via listen('languageChanged', (data) => void)

    function listen(...args) {
      return Events.listen('localization', ...args)
    } 
    
    function once(...args) {
      return Events.once('localization', ...args)
    }
    
    function clear(...args) {
      return Events.clear('localization', ...args)
    }
    
export default {

  events: {
    languageChanged:'languageChanged'
  },
locality,
  postalCode,
  countryCode,
  language,
  locale,
  latlon,
  additionalInfo,
  listen,
  once,
  clear
}