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
import { ready as logReady } from '../Metrics/index.mjs'
import { prioritize } from '../Events/index.mjs'

registerEvents('Lifecycle', Object.values(["inactive","foreground","background","suspended","unloading"]))



export const store = {
  _current: 'initializing',
  get current() {
    return this._current
  }
}

async function ready() {
  let readyRes;
  await prioritize('Lifecycle', (event, value) => {
    store._current = event
  })
  readyRes =await Transport.send('lifecycle', 'ready', {})
  setTimeout(_ => {
    logReady()
  })
  return readyRes
}


function close(reason) {

  const transforms = null

  return Transport.send('lifecycle', 'close', { reason }, transforms)
}
// onInactive API is handled via listen('inactive', (data) => void)
// onForeground API is handled via listen('foreground', (data) => void)
// onBackground API is handled via listen('background', (data) => void)
// onSuspended API is handled via listen('suspended', (data) => void)
// onUnloading API is handled via listen('unloading', (data) => void)

    function listen(...args) {
      return Events.listen('lifecycle', ...args)
    } 
    
    function once(...args) {
      return Events.once('lifecycle', ...args)
    }
    
    function clear(...args) {
      return Events.clear('lifecycle', ...args)
    }
    
function state() {
  return store.current
}

function finished() {
  if (store.current === 'unloading') {
    return Transport.send('lifecycle', 'finished')
  } else {
    throw 'Cannot call finished() except when in the unloading transition'
  }
}

// public API
export default {

  events: {
    inactive:'inactive',
    foreground:'foreground',
    background:'background',
    suspended:'suspended',
    unloading:'unloading'
  },


  CloseReason: {
    REMOTE_BUTTON: 'remoteButton',
    USER_EXIT: 'userExit',
    DONE: 'done',
    ERROR: 'error'
  },


  LifecycleState: {
    INITIALIZING: 'initializing',
    INACTIVE: 'inactive',
    FOREGROUND: 'foreground',
    BACKGROUND: 'background',
    UNLOADING: 'unloading',
    SUSPENDED: 'suspended'
  },


  ready,
  state,
  finished,

close,
  listen,
  once,
  clear
}
