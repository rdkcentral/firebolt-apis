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


registerProviderInterface('xrn:firebolt:capability:usergrant:acknowledgechallenge', 'AcknowledgeChallenge', [{"name":"challenge","focus":true,"response":true,"parameters":true}])


  
  function provide(capability, provider) {
    return ProvideManager.provide(capability, provider)
  }
  
    function listen(...args) {
      return Events.listen('acknowledgechallenge', ...args)
    } 
    
    function once(...args) {
      return Events.once('acknowledgechallenge', ...args)
    }
    
    function clear(...args) {
      return Events.clear('acknowledgechallenge', ...args)
    }
    
export default {

provide
}