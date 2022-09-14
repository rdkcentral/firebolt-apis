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

import { setMockResponses } from './Transport/MockTransport.mjs'
import { registerAPI } from './Extensions/index.mjs'
import Authentication from './Authentication/index.mjs'
import Transport from './Transport/index.mjs'

import { default as accessibility } from './Accessibility/defaults.mjs'
import { default as account } from './Account/defaults.mjs'
import { default as advertising } from './Advertising/defaults.mjs'
import { default as authentication } from './Authentication/defaults.mjs'
import { default as device } from './Device/defaults.mjs'
import { default as discovery } from './Discovery/defaults.mjs'
import { default as keyboard } from './Keyboard/defaults.mjs'
import { default as lifecycle } from './Lifecycle/defaults.mjs'
import { default as localization } from './Localization/defaults.mjs'
import { default as metrics } from './Metrics/defaults.mjs'
import { default as parameters } from './Parameters/defaults.mjs'
import { default as profile } from './Profile/defaults.mjs'
import { default as secondscreen } from './SecondScreen/defaults.mjs'
import { default as platform } from './Platform/defaults.mjs'

setMockResponses({
  accessibility: accessibility,
  account: account,
  advertising: advertising,
  authentication: authentication,
  device: device,
  discovery: discovery,
  keyboard: keyboard,
  lifecycle: lifecycle,
  localization: localization,
  metrics: metrics,
  parameters: parameters,
  profile: profile,
  secondscreen: secondscreen,
  platform: platform,
})

registerAPI('authorize', (required, optional) => {
  return new Promise( (resolve, reject) => {
    // this will fail until we support capabilities
    // once it works, this will trigger user grant UIs, and update the FAT
    Transport.send("capabilities", "authorize", {required, optional}).then(token => {
      resolve(token)
    })
    // This is temporary. Will be handled by a user grant policy in future
    .catch(error => {
      // TODO: Need to finalize this error schema.
      // currently assuming that any error from `capabilities.authorize` that has `data.capabilities`
      // means that the method exists, and this is a list of capability info objects
      if (error.data && error.data.capabilities) {
        // reject, because something went wrong
        reject(error)
      }
      // otherwise, this is a method not found error, and we should fallback to 0.x behavior
      else {
        // assume all commerce capabilities require a pin prompt
        if (required.find(p => p.capability.startsWith('xrn:firebolt:capabilities:commerce:'))) {
          Transport.send('profile', 'approvePurchase', {})
            .then(result => {
              if (result) {
                Authentication.token('platform').then(token => {
                  resolve(token.value)
                })
              }
              else {
                reject(new Error('User did not grant access to purchase.'))
              }
            })
            .catch(error => {
              reject(error)
            })
        }
      }
    })
  })
})

export { default as Accessibility } from './Accessibility/index.mjs'
export { default as Account } from './Account/index.mjs'
export { default as Advertising } from './Advertising/index.mjs'
export { default as Authentication } from './Authentication/index.mjs'
export { default as Device } from './Device/index.mjs'
export { default as Discovery } from './Discovery/index.mjs'
export { default as Keyboard } from './Keyboard/index.mjs'
export { default as Lifecycle } from './Lifecycle/index.mjs'
export { default as Localization } from './Localization/index.mjs'
export { default as Metrics } from './Metrics/index.mjs'
export { default as Parameters } from './Parameters/index.mjs'
export { default as Profile } from './Profile/index.mjs'
export { default as SecondScreen } from './SecondScreen/index.mjs'
export { default as Platform } from './Platform/index.mjs'
export { default as Log } from './Log/index.mjs'
export { default as Events } from './Events/index.mjs'
export { default as Settings } from './Settings/index.mjs'
export { default as Extensions } from './Extensions/index.mjs'
