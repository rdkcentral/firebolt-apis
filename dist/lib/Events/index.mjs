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
import { setMockListener } from '../Transport/MockTransport.mjs'

let listenerId = 0

// holds two maps of ${module}.${event} => listenerId, e.g. callback method id
// note that one callback can listen to multiple events, e.g. 'discovery.*'
// internal is only available via a private export that we use to ensure our modules know about
// events before the apps using the SDK (otherwise state errors can happen)
const listeners = {
  internal: {},
  external: {},

  // Several convenience functions below for checking both internal & external lists w/ one operation

  // gets a merge list of ids for a single event key
  get: (key) => {
    return Object.assign(Object.assign({}, listeners.internal[key]), listeners.external[key])
  },
  // adds a callback/id to a key on the external list only 
  set: (key, id, value) => {
    listeners.external[key] = listeners.external[key] || {}
    listeners.external[key][id] = value
  },
  // adds a callback/id to a key on the internal list only 
  setInternal: (key, id, value) => {
    listeners.internal[key] = listeners.internal[key] || {}
    listeners.internal[key][id] = value
  },
  // finds the key for an id in either list (it can only be in one)
  find: (id) => {
    let key
    [listeners.internal, listeners.external].find(group => {
      key = Object.keys(group).find(key => group[key][id])
      if (key) return true
    })
    return key
  },
  // removes an id from either list
  remove: (id) => {
    [listeners.internal, listeners.external].forEach(group => {
      Object.keys(group).forEach(key => {
        if (group[key] && group[key][id]) {
          delete group[key][id]
          if (Object.values(group[key]).length === 0) {
            delete group[key]
          }
        }
      })
    })
  },
  // removes a key from both lists if _internal is true, otherwise only the external list
  removeKey: (key, _internal=false) => {
    _internal && listeners.internal[key] && delete listeners.internal[key]
    listeners.external[key] && delete listeners.external[key]
  },
  // gives a list of all keys
  keys: () => {
    return Array.from(new Set(Object.keys(listeners.internal).concat(Object.keys(listeners.external))))
  },
  // counts how many listeners are in a key across both lists
  count: (key) => {
    return Object.values(listeners.get(key)).length
  }
}

// holds a map of RPC Ids => Context Key, e.g. the RPC id of an onEvent call mapped to the corresponding context parameters key for that RPC call
const keys = {}

// holds a map of ${module}.${event} => Transport.send calls (only called once per event)
// note that the keys here MUST NOT contain wild cards
const oncers = []
const validEvents = {}
const validContext = {}

let transportInitialized = false

export const emit = (id, value) => {
  callCallbacks(listeners.internal[keys[id]], [value])
  callCallbacks(listeners.external[keys[id]], [value])
}

export const registerEvents = (module, events) => {
  validEvents[module.toLowerCase()] = events.concat()
}

export const registerEventContext = (module, event, context) => {
  validContext[module.toLowerCase()] = validContext[module.toLowerCase()] || {}
  validContext[module.toLowerCase()][event] = context.concat()
}

const callCallbacks = (cbs, args) => {
  cbs &&
    Object.keys(cbs).forEach(listenerId => {
      let callback = cbs[listenerId]
      if (oncers.indexOf(parseInt(listenerId)) >= 0) {
        oncers.splice(oncers.indexOf(parseInt(listenerId)), 1)
        delete cbs[listenerId]
      }
      callback.apply(null, args)
    })
}

const doListen = function(module, event, callback, context, once, internal=false) {
  init()

  if (typeof callback !== 'function') {
    return Promise.reject('No valid callback function provided.')
  } else {
    if (module === '*') {
      return Promise.reject('No valid module name provided')
    }

    const wildcard = event === '*'
    const events = (wildcard ? validEvents[module] : [event]) // explodes wildcards into an array
    const promises = []
    const hasContext = Object.values(context).length > 0
    const contextKey = Object.keys(context).sort().map(key => key + '=' + JSON.stringify(context[key])).join('&')

    listenerId++

    if (once) {
      oncers.push(listenerId)
    }

    events.forEach(event => {
      const key = module + '.' + event + (hasContext ? `.${contextKey}`  : '')

      if (Object.values(listeners.get(key)).length === 0) {
        const { id, promise } = Transport.listen(module, 'on' + event[0].toUpperCase() + event.substring(1), { listen: true })
        keys[id] = key
        promises.push(promise)
      }

      const setter = internal ? listeners.setInternal : listeners.set

      if (wildcard) {
        setter(key, ''+listenerId, value => callback(event, value))
      }
      else {
        setter(key, ''+listenerId, callback)
      }
    })

    let resolve, reject
    let p = new Promise((res, rej) => {
      resolve = res
      reject = rej
    })

    if (promises.length) {
      Promise.all(promises).then(responses => {
        resolve(listenerId)
      }).catch(error => {
        // Promise.all rejects if at least one promise rejects... we don't want that behavior here
        // TODO: Do something better than fail silently
        if (event === '*') {
          resolve(listenerId)
        }
        else {
          reject(error)
        }
      })
    }
    else {
      resolve(listenerId)
    }

    return p
  }
}

const getListenArgs = function(...args) {
  const callback = args.pop()
  const module = (args.shift() || '*').toLowerCase()
  const event = args.shift() || '*'
  const context = {}
  
  for (let i = 0; i<args.length; i++) {
    context[validContext[module][event][i]] = args.shift()
  }

  return [module, event, callback, context]
}

const once = function(...args) {
  const [module, event, callback, context] = getListenArgs(...args)
  return doListen(module, event, callback, context, true)
}

const listen = function(...args) {
  const [module, event, callback, context] = getListenArgs(...args)
  return doListen(module, event, callback, context, false)
}

const clear = function(...args) {
  if (args && args.length && typeof args[0] === 'number') {
    return doClear(args[0])
  }
  else {
    const moduleOrId = args.shift()
    const event = args.shift() || undefined
    return doClear(moduleOrId, event) // todo: add context
  }
}

// calls doListen with a priority flag for internal listeners to get priority
export const prioritize = function(...args) {
  const [module, event, callback, context] = getListenArgs(...args)
  return doListen(module, event, callback, context, false, true)
}

const unsubscribe = (key) => {
  console.log(key)
  const [module, event] = key.split('.').slice(0, 2)
  Transport.send(module, 'on' + event[0].toUpperCase() + event.substr(1), { listen: false })
}


// TODO: clear needs to go through Transport Layer
const doClear = function (moduleOrId = false, event = false) {
  if (typeof moduleOrId === 'number') {
    const searchId = moduleOrId.toString()
    const key = listeners.find(searchId)

    listeners.remove(searchId)
    if (listeners.count(key) === 0) {
      unsubscribe(key)
    }
    return true
  } else {
    if (!moduleOrId && !event) {
      listeners.keys().forEach(key => {
        listeners.removeKey(key)
        unsubscribe(key)
      })
    } else if (!event) {
      listeners.keys().forEach(key => {
        if (key.indexOf(moduleOrId.toLowerCase()) === 0) {
          listeners.removeKey(key)
          unsubscribe(key)
        }
      })
    } else {
      listeners.removeKey(moduleOrId + '.' + event)
      unsubscribe(moduleOrId + '.' + event)
    }
  }
}

const init = () => {
  if (!transportInitialized) {
    Transport.addEventEmitter(emit)
    setMockListener(listen)
    transportInitialized = true
  }
}

export default {
  listen: listen,
  once: once,
  clear: clear,
  broadcast(event, value) {
    emit(Object.entries(keys).find( ([k, v]) => v === 'app.'+event)[0], value)
  },
}
