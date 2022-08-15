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

import { setMockResponses } from './Transport/MockTransport.mjs'
import { registerAPI } from './Extensions/index.mjs'

/* ${MOCK_IMPORTS} */

setMockResponses({
  /* ${MOCK_OBJECTS} */
})

registerAPI('authorize', (grants) => {
  return new Promise( (resolve, reject) => {
      // this will fail until we support capabilities
      // once it works, this will trigger user grant UIs, and update the FAT
      Transport.send('capabilities', 'request', { grants })
      .then(granted => {
          if (granted && granted.length) {
              resolve(granted)
          }
          else {
              reject()
          }
      })
      // This is temporary. Will be handled by a user grant policy in future
      .catch(_ => {
          // assume all commerce capabilities require a pin prompt
          if (grants.find(g => g.capability.startsWith('xrn:firebolt:capabilities:commerce:'))) {
              Transport.send('profile', 'approvePurchase', {})
                  .then(result => {
                      if (result) {
                          resolve(grants)
                      }
                      else {
                          reject()
                      }
                  })
                  .catch(error => {
                      reject(error)
                  })
          }
      })
  })
})

/* ${EXPORTS} */
export { default as Log } from './Log/index.mjs'
export { default as Events } from './Events/index.mjs'
export { default as Settings } from './Settings/index.mjs'
export { default as Extensions } from './Extensions/index.mjs'
