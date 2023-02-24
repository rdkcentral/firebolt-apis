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
import ProvideManager from '../ProvideManager/index.mjs'
import { registerProviderInterface } from '../ProvideManager/index.mjs'


registerProviderInterface('xrn:firebolt:capability:lifecycle:launch', 'Lifecycle', [{"name":"launch","focus":false,"response":true,"parameters":true}])
registerProviderInterface('xrn:firebolt:capability:lifecycle:state', 'Lifecycle', [{"name":"ready","focus":false,"response":true,"parameters":true},{"name":"close","focus":false,"response":true,"parameters":true},{"name":"finished","focus":false,"response":true,"parameters":true}])



function setState(appId, state) {

  const transforms = null

  return Transport.send('lifecycle', 'setState', { appId, state }, transforms)
}

function session(session) {

  const transforms = null

  return Transport.send('lifecycle', 'session', { session }, transforms)
}
  
  function provide(capability, provider) {
    return ProvideManager.provide(capability, provider)
  }
  
    function listen(...args) {
      return Events.listen('lifecycle', ...args)
    } 
    
    function once(...args) {
      return Events.once('lifecycle', ...args)
    }
    
    function clear(...args) {
      return Events.clear('lifecycle', ...args)
    }
    
export default {


  ProgramType: {
    MOVIE: 'movie',
    EPISODE: 'episode',
    SEASON: 'season',
    SERIES: 'series',
    OTHER: 'other',
    PREVIEW: 'preview',
    EXTRA: 'extra',
    CONCERT: 'concert',
    SPORTING_EVENT: 'sportingEvent',
    ADVERTISEMENT: 'advertisement',
    MUSIC_VIDEO: 'musicVideo',
    MINISODE: 'minisode'
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

setState,
  session,
  provide
}