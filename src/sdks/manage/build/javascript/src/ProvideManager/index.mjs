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
import { registerEventContext } from '../Events/index.mjs'

/* ${INITIALIZATION} */

  /* ${METHODS} */

const providerInterfaces = {}

export const registerProviderInterface = (capability, module, methods) => {
  if (providerInterfaces[capability]) {
    throw `Capability ${capability} has multiple provider interfaces registered.`
  }

  methods.forEach(m => m.name = `${module}.${m.name}`)
  providerInterfaces[capability] = methods.concat()
}

const provide = function(capability, provider) {
  const methods = []
  const iface = providerInterfaces[capability]

  if (provider.constructor.name !== 'Object') {
    methods.push(...Object.getOwnPropertyNames(Object.getPrototypeOf(provider)).filter(item => typeof provider[item] === 'function' && item !== 'constructor'))
  }
  else {
    methods.push(...Object.getOwnPropertyNames(provider).filter(item => typeof provider[item] === 'function'))
  }

  if (!iface) {
    throw "Ignoring unknown provider capability."
  }

  // make sure every interfaced method exists in the providers methods list
  const valid = iface.every(method => methods.find(m => m === method.name.split('.').pop()))

  if (!valid) {
    throw `Provider that does not fully implement ${capability}:\n\t${iface.map(m=>m.name.split('.').pop()).join('\n\t')}`
  }

  iface.forEach(imethod => {
    const parts = imethod.name.split('.')
    const method = parts.pop();
    const module = parts.pop().toLowerCase();
    const defined = !!methods.find(m => m === method) 

    if (!defined) {
      return // returns from this cycle of iface.forEach
    }

    Events.listen(module, `request${method.charAt(0).toUpperCase() + method.substr(1)}`, function (request) {
      const providerCallArgs = []
      
      // only pass in parameters object if schema exists
      if (imethod.parameters) {
        providerCallArgs.push(request.parameters)
      }
      else {
        providerCallArgs.push(null)
      }

      const session = {
        correlationId: () => {
          return request.correlationId
        }
      }
      
      // only pass in the focus handshake if needed
      if (imethod.focus) {
        session.focus = () => {
          Transport.send(module, `${method}Focus`, {
            correlationId: request.correlationId
          })
        }
      }

      providerCallArgs.push(session)

      const response = {
        correlationId: request.correlationId
      }

      try {
        const result = provider[method].apply(provider, providerCallArgs)

        if (!(result instanceof Promise)) {
          throw `Provider method ${method} did not return a Promise.`
        }
      
        result.then(result => {
          if (imethod.response) {
            response.result = result
          }

          Transport.send(module, `${method}Response`, response)
        })
      }
      catch(error) {
        response.error = {
          code: error.code || 1000, // todo: should be some reserved code for "Unknown"
          message: error.message || `An error occured while calling provided ${method} method.`
        }

        if (error.data) {
          response.error.data = JSON.parse(JSON.stringify(error.data))
        }

        Transport.send(module, `${method}Error`, response)
      }
    })
  })
}

export default {
  provide,
  /* ${EVENTS} */
  /* ${ENUMS} */
  /* ${METHOD_LIST} */
}
