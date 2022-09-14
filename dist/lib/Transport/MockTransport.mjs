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

let listener
export const setMockListener = func => { listener = func }

let mock
const pending = []
const eventMap = {}

let callback
let testHarness

if (window.__firebolt && window.__firebolt.testHarness) {
  testHarness = window.__firebolt.testHarness
}

function send(message) {
  console.debug('Sending message to transport: ' + message)
  let json = JSON.parse(message)

  // handle bulk sends
  if (Array.isArray(json)) {
    json.forEach(j => send(JSON.stringify(j)))
    return
  }

  let [module, method] = json.method.split('.')

  if (testHarness && testHarness.onSend) {
    testHarness.onSend(module, method, json.params, json.id)
  }

  // store the ID of the first listen for each event
  if (method.match(/^on[A-Z]/)) {
    if (json.params.listen) {
      eventMap[json.id] = module.toLowerCase() + '.' + method[2].toLowerCase() + method.substr(3)
    } else {
      Object.keys(eventMap).forEach(key => {
        if (eventMap[key] === module.toLowerCase() + '.' + method[2].toLowerCase() + method.substr(3)) {
          delete eventMap[key]
        }
      })
    }
  }

  if (mock)
    handle(json)
  else
    pending.push(json)
}

function handle(json) {
  let result
  try {
    result = getResult(json.method, json.params)
  }
  catch (error) {
    setTimeout(() => callback(JSON.stringify({ 
      jsonrpc: '2.0',
      error: {
        code: -32602,
        message: "Invalid params (this is a mock error from the mock transport layer)"
      },
      id: json.id
    })))
  }

  setTimeout(() => callback(JSON.stringify({ 
    jsonrpc: '2.0',
    result: result,
    id: json.id
  })))
}

function receive(_callback) {
  callback = _callback

  if (testHarness && (typeof testHarness.initialize === 'function')) {
    testHarness.initialize({
      emit: event,
      listen: function(...args) { listener(...args) },
    })
  }
}

function event(module, event, value) {
 const listener = Object.entries(eventMap).find(([k, v]) => v.toLowerCase() === module.toLowerCase() + '.' + event.toLowerCase())
  if (listener) {
    let message = JSON.stringify({
      jsonrpc: '2.0',
      id: parseInt(listener[0]),
      result: value
    })
    callback(message)
  }
}

function dotGrab(obj = {}, key) {
  const keys = key.split('.')
  let ref = obj
  for (let i = 0; i < keys.length; i++) {
    ref = ref[keys[i]] || {}
  }
  return ref
}

function getResult(method, params) {
  let api = dotGrab(mock, method)

  if (method.match(/^[a-zA-Z]+\.on[A-Za-z]+$/)) {
    api = {
      event: method,
      listening: true
    }
  }

  if (typeof api === 'function') {
    return params == null ? api() : api(params)
  } else return api
}

export function setMockResponses(m) {
  mock = m

  pending.forEach(json => handle(json))
  pending.length = 0
}

export default {
  send: send,
  receive: receive,
  event: event
}

