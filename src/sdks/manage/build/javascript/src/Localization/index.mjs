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

registerEvents('Localization', Object.values(["localityChanged","postalCodeChanged","countryCodeChanged","languageChanged","localeChanged"]))



function locality() {
  const callbackOrValue = arguments[0]
  return Prop.prop('localization',  'locality', {  }, callbackOrValue, false, false, 0)
}
function postalCode() {
  const callbackOrValue = arguments[0]
  return Prop.prop('localization',  'postalCode', {  }, callbackOrValue, false, false, 0)
}
function countryCode() {
  const callbackOrValue = arguments[0]
  return Prop.prop('localization',  'countryCode', {  }, callbackOrValue, false, false, 0)
}
function language() {
  const callbackOrValue = arguments[0]
  return Prop.prop('localization',  'language', {  }, callbackOrValue, false, false, 0)
}
function locale() {
  const callbackOrValue = arguments[0]
  return Prop.prop('localization',  'locale', {  }, callbackOrValue, false, false, 0)
}

function additionalInfo() {

  const transforms = null

  return Transport.send('localization', 'additionalInfo', {  }, transforms)
}
// onLocalityChanged API is handled via listen('localityChanged', (data) => void)
// onPostalCodeChanged API is handled via listen('postalCodeChanged', (data) => void)
// onCountryCodeChanged API is handled via listen('countryCodeChanged', (data) => void)
// onLanguageChanged API is handled via listen('languageChanged', (data) => void)
// onLocaleChanged API is handled via listen('localeChanged', (data) => void)

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
    localityChanged:'localityChanged',
    postalCodeChanged:'postalCodeChanged',
    countryCodeChanged:'countryCodeChanged',
    languageChanged:'languageChanged',
    localeChanged:'localeChanged'
  },
locality,
  postalCode,
  countryCode,
  language,
  locale,
  additionalInfo,
  listen,
  once,
  clear
}