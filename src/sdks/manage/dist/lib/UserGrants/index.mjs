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





function app(appId) {

  const transforms = null

  return Transport.send('usergrants', 'app', { appId }, transforms)
}

function device() {

  const transforms = null

  return Transport.send('usergrants', 'device', {  }, transforms)
}

function capability(capability) {

  const transforms = null

  return Transport.send('usergrants', 'capability', { capability }, transforms)
}

function grant(role, capability, options) {

  const transforms = null

  return Transport.send('usergrants', 'grant', { role, capability, options }, transforms)
}

function deny(role, capability, options) {

  const transforms = null

  return Transport.send('usergrants', 'deny', { role, capability, options }, transforms)
}

function clear(role, capability, options) {

  const transforms = null

  return Transport.send('usergrants', 'clear', { role, capability, options }, transforms)
}

function request(appId, permissions) {

  const transforms = null

  return Transport.send('usergrants', 'request', { appId, permissions }, transforms)
}

export default {


  Role: {
    USE: 'use',
    MANAGE: 'manage',
    PROVIDE: 'provide'
  },

app,
  device,
  capability,
  grant,
  deny,
  clear,
  request
}