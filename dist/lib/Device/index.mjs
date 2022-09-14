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

registerEvents('Device', Object.values(["deviceNameChanged","hdcpChanged","hdrChanged","audioChanged","screenResolutionChanged","videoResolutionChanged","nameChanged","networkChanged"]))


Transport.registerDeprecatedMethod('Device', 'onDeviceNameChanged', 'Use Device.name() instead.')

function version() {
  return new Promise( (resolve, reject) => {
      Transport.send('device', 'version').then( v => {
          v = v || {}
          v.sdk = v.sdk || {}
          v.sdk.major = parseInt('0')
          v.sdk.minor = parseInt('8')
          v.sdk.patch = parseInt('0')
          v.sdk.readable = 'The Firebolt JS SDK'
          resolve(v)    
      }).catch(error => {
          reject(error)
      })
  })
}

function id() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'id', {  }, callbackOrValue, true, true, 0)
}
function distributor() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'distributor', {  }, callbackOrValue, true, true, 0)
}
function platform() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'platform', {  }, callbackOrValue, true, true, 0)
}
function uid() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'uid', {  }, callbackOrValue, true, true, 0)
}
function type() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'type', {  }, callbackOrValue, true, true, 0)
}
function model() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'model', {  }, callbackOrValue, true, true, 0)
}
function sku() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'sku', {  }, callbackOrValue, true, true, 0)
}
function make() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'make', {  }, callbackOrValue, true, true, 0)
}
function hdcp() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'hdcp', {  }, callbackOrValue, false, true, 0)
}
function hdr() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'hdr', {  }, callbackOrValue, false, true, 0)
}
function audio() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'audio', {  }, callbackOrValue, false, true, 0)
}
function screenResolution() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'screenResolution', {  }, callbackOrValue, false, true, 0)
}
function videoResolution() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'videoResolution', {  }, callbackOrValue, false, true, 0)
}
function name() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'name', {  }, callbackOrValue, false, true, 0)
}
// onDeviceNameChanged API is handled via listen('deviceNameChanged', (data) => void)
function network() {
  const callbackOrValue = arguments[0]
  return Prop.prop('device',  'network', {  }, callbackOrValue, false, true, 0)
}
// onHdcpChanged API is handled via listen('hdcpChanged', (data) => void)
// onHdrChanged API is handled via listen('hdrChanged', (data) => void)
// onAudioChanged API is handled via listen('audioChanged', (data) => void)
// onScreenResolutionChanged API is handled via listen('screenResolutionChanged', (data) => void)
// onVideoResolutionChanged API is handled via listen('videoResolutionChanged', (data) => void)
// onNameChanged API is handled via listen('nameChanged', (data) => void)
// onNetworkChanged API is handled via listen('networkChanged', (data) => void)

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
    hdcpChanged:'hdcpChanged',
    hdrChanged:'hdrChanged',
    audioChanged:'audioChanged',
    screenResolutionChanged:'screenResolutionChanged',
    videoResolutionChanged:'videoResolutionChanged',
    nameChanged:'nameChanged',
    networkChanged:'networkChanged'
  },

  NetworkType: {
    WIFI: 'wifi',
    ETHERNET: 'ethernet',
    HYBRID: 'hybrid'
  },


  NetworkState: {
    CONNECTED: 'connected',
    DISCONNECTED: 'disconnected'
  },


  AudioProfile: {
    STEREO: 'stereo',
    DOLBY_DIGITAL_5_1: 'dolbyDigital5.1',
    DOLBY_DIGITAL_7_1: 'dolbyDigital7.1',
    DOLBY_DIGITAL_5_1_PLUS: 'dolbyDigital5.1+',
    DOLBY_DIGITAL_7_1_PLUS: 'dolbyDigital7.1+',
    DOLBY_ATMOS: 'dolbyAtmos'
  },


  version,
id,
  distributor,
  platform,
  uid,
  type,
  model,
  sku,
  make,
  hdcp,
  hdr,
  audio,
  screenResolution,
  videoResolution,
  name,
  network,
  listen,
  once,
  clear
}
