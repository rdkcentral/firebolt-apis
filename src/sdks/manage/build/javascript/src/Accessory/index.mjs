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





function pair(type, protocol, timeout) {

  const transforms = null

  return Transport.send('accessory', 'pair', { type, protocol, timeout }, transforms)
}

function list(type, protocol) {

  const transforms = null

  return Transport.send('accessory', 'list', { type, protocol }, transforms)
}

export default {


  AccessoryType: {
    REMOTE: 'Remote',
    SPEAKER: 'Speaker',
    OTHER: 'Other'
  },


  AccessoryTypeListParam: {
    REMOTE: 'Remote',
    SPEAKER: 'Speaker',
    ALL: 'All'
  },


  AccessoryProtocol: {
    BLUETOOTH_LE: 'BluetoothLE',
    RF4CE: 'RF4CE'
  },


  AccessoryProtocolListParam: {
    BLUETOOTH_LE: 'BluetoothLE',
    RF4CE: 'RF4CE',
    ALL: 'All'
  },

pair,
  list
}