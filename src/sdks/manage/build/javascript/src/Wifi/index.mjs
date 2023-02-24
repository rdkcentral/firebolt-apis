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





function scan(timeout) {

  const transforms = null

  return Transport.send('wifi', 'scan', { timeout }, transforms)
}

function connect(ssid, passphrase, security) {

  const transforms = null

  return Transport.send('wifi', 'connect', { ssid, passphrase, security }, transforms)
}

function disconnect() {

  const transforms = null

  return Transport.send('wifi', 'disconnect', {  }, transforms)
}

function wps(security) {

  const transforms = null

  return Transport.send('wifi', 'wps', { security }, transforms)
}

export default {


  WifiSecurityMode: {
    NONE: 'none',
    WEP_64: 'wep64',
    WEP_128: 'wep128',
    WPA_PSK_TKIP: 'wpaPskTkip',
    WPA_PSK_AES: 'wpaPskAes',
    WPA_2PSK_TKIP: 'wpa2PskTkip',
    WPA_2PSK_AES: 'wpa2PskAes',
    WPA_ENTERPRISE_TKIP: 'wpaEnterpriseTkip',
    WPA_ENTERPRISE_AES: 'wpaEnterpriseAes',
    WPA_2ENTERPRISE_TKIP: 'wpa2EnterpriseTkip',
    WPA_2ENTERPRISE_AES: 'wpa2EnterpriseAes',
    WPA_2PSK: 'wpa2Psk',
    WPA_2ENTERPRISE: 'wpa2Enterprise',
    WPA_3PSK_AES: 'wpa3PskAes',
    WPA_3SAE: 'wpa3Sae'
  },


  WPSSecurityPin: {
    PUSH_BUTTON: 'pushButton',
    PIN: 'pin',
    MANUFACTURER_PIN: 'manufacturerPin'
  },

scan,
  connect,
  disconnect,
  wps
}