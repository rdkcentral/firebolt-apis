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

import { default as accessibility } from './Accessibility/defaults.mjs'
import { default as accessory } from './Accessory/defaults.mjs'
import { default as account } from './Account/defaults.mjs'
import { default as acknowledgechallenge } from './AcknowledgeChallenge/defaults.mjs'
import { default as advertising } from './Advertising/defaults.mjs'
import { default as closedcaptions } from './ClosedCaptions/defaults.mjs'
import { default as developertools } from './DeveloperTools/defaults.mjs'
import { default as device } from './Device/defaults.mjs'
import { default as keyboard } from './Keyboard/defaults.mjs'
import { default as lifecycle } from './Lifecycle/defaults.mjs'
import { default as localization } from './Localization/defaults.mjs'
import { default as pinchallenge } from './PinChallenge/defaults.mjs'
import { default as privacy } from './Privacy/defaults.mjs'
import { default as usergrants } from './UserGrants/defaults.mjs'
import { default as voiceguidance } from './VoiceGuidance/defaults.mjs'
import { default as wifi } from './Wifi/defaults.mjs'

setMockResponses({
  accessibility: accessibility,
  accessory: accessory,
  account: account,
  acknowledgechallenge: acknowledgechallenge,
  advertising: advertising,
  closedcaptions: closedcaptions,
  developertools: developertools,
  device: device,
  keyboard: keyboard,
  lifecycle: lifecycle,
  localization: localization,
  pinchallenge: pinchallenge,
  privacy: privacy,
  usergrants: usergrants,
  voiceguidance: voiceguidance,
  wifi: wifi,
})

export { default as Accessibility } from './Accessibility/index.mjs'
export { default as Accessory } from './Accessory/index.mjs'
export { default as Account } from './Account/index.mjs'
export { default as AcknowledgeChallenge } from './AcknowledgeChallenge/index.mjs'
export { default as Advertising } from './Advertising/index.mjs'
export { default as ClosedCaptions } from './ClosedCaptions/index.mjs'
export { default as DeveloperTools } from './DeveloperTools/index.mjs'
export { default as Device } from './Device/index.mjs'
export { default as Keyboard } from './Keyboard/index.mjs'
export { default as Lifecycle } from './Lifecycle/index.mjs'
export { default as Localization } from './Localization/index.mjs'
export { default as PinChallenge } from './PinChallenge/index.mjs'
export { default as Privacy } from './Privacy/index.mjs'
export { default as UserGrants } from './UserGrants/index.mjs'
export { default as VoiceGuidance } from './VoiceGuidance/index.mjs'
export { default as Wifi } from './Wifi/index.mjs'
export { default as Log } from './Log/index.mjs'
export { default as Events } from './Events/index.mjs'
export { default as Settings } from './Settings/index.mjs'
