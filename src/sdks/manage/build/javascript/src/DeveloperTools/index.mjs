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
import TemporalSet from '../TemporalSet/index.mjs'




function find(...args) {
    let add, remove
    if (typeof args[args.length-1] === 'function' && typeof args[args.length-2] === 'function') {
        remove = args.pop()
        add = args.pop()
    }
    else if (typeof args[args.length-1] === 'function') {
        add = args.pop()
    }

    const transforms = null
    
    return TemporalSet.start('developertools', 'find', 'onDeveloperToolAvailable', 'onDeveloperToolUnvailable', arguments, add, remove, transforms)
}

function pair(id) {

  const transforms = null

  return Transport.send('developertools', 'pair', { id }, transforms)
}

function unpair(id) {

  const transforms = null

  return Transport.send('developertools', 'unpair', { id }, transforms)
}

    function listen(...args) {
      return Events.listen('developertools', ...args)
    } 
    
    function once(...args) {
      return Events.once('developertools', ...args)
    }
    
    function clear(...args) {
      return Events.clear('developertools', ...args)
    }
    
export default {

find,
  pair,
  unpair
}