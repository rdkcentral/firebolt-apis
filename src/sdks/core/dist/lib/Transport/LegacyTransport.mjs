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

export default class LegacyTransport {
  constructor (bridge) {
    this.bridge = bridge
  }

  send (msg) {
    this.bridge.JSMessageChanged(msg, () => {})
  }

  receive (callback) {
    window.$badger = window.$badger || {}
    /** Hold on to real $badger callback and event methods so they can be called for non-jsonrpc messages */
    const badgerCallback = window.$badger.callback ? window.$badger.callback.bind(window.$badger) : null
    const badgerEvent = window.$badger.event ? window.$badger.event.bind(window.$badger) : null
    window.$badger.callback = (pid, success, json) => {
      if (json.jsonrpc) {
        callback(JSON.stringify(json))
      } else if (badgerCallback) {
        badgerCallback(pid, success, json)
      }
    }
    window.$badger.event = (handlerId, json) => {
      if (json.jsonrpc) {
        callback(JSON.stringify(json))
      } else if (badgerEvent) {
        badgerEvent(handlerId, json)
      }
    }
  }

  static isLegacy (transport) {
    return LegacyTransport.isXREProxy(transport) || ((transport.send === undefined) && (transport.JSMessageChanged))
  }

  static isXREProxy (transport) {
    /** Set top boxes running XRE has a "Proxy" transport
     * native object that intercepts ALL method calls, so we
     * cannot test for transport.send existence because it will return true
     * even though it actually is not supported. Check if some obscure method
     * name like "proxyObjectTest" is defined. If it is then we know we are using a
     * Proxy object and thus is legacy transport.
     */
    return transport.proxyObjectTest !== undefined
  }
}
