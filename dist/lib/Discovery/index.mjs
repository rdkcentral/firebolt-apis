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
import Prop from '../Prop/index.mjs'

registerEvents('Discovery', Object.values(["navigateTo","policyChanged"]))



function policy() {
  const callbackOrValue = arguments[0]
  return Prop.prop('discovery',  'policy', {  }, callbackOrValue, false, true, 0)
}

let entityInfoHasCallback = false

function entityInfo (data) {
  if (arguments.length === 1 && typeof arguments[0] === 'function') {
    if (entityInfoHasCallback) {
      return Promise.reject('Cannot register more than one entityInfo handler.')
    }

    const callback = arguments[0]
    entityInfoHasCallback = true
    return Events.listen('discovery', 'pullEntityInfo', (request) => {
      if (typeof request === 'boolean') return

      try {
        const result = callback(request.parameters).then(result => {
          const params = {
            correlationId: request.correlationId,
            result: result
          }
          Transport.send('discovery', 'entityInfo', params).catch(error => {
            const msg = typeof error === 'string' ? error : error.message || 'Unknown Error'
            console.error(`Failed to send entityInfo pull response through Transport Layer: ${msg}`)
          })
        }).catch(error => {
          const msg = typeof error === 'string' ? error : error.message || 'Unknown Error'
          console.error(`App 'entityInfo' callback failed: ${msg}`)
        })
      }
      catch (error) {
        const msg = typeof error === 'string' ? error : error.message || 'Unknown Error'
        console.error(`App 'entityInfo' callback failed: ${msg}`)
    }
    })
  }
  else {
    return Transport.send('discovery', 'entityInfo', { correlationId: null, result: data })
  }
}

let purchasedContentHasCallback = false

function purchasedContent (data) {
  if (arguments.length === 1 && typeof arguments[0] === 'function') {
    if (purchasedContentHasCallback) {
      return Promise.reject('Cannot register more than one purchasedContent handler.')
    }

    const callback = arguments[0]
    purchasedContentHasCallback = true
    return Events.listen('discovery', 'pullPurchasedContent', (request) => {
      if (typeof request === 'boolean') return

      try {
        const result = callback(request.parameters).then(result => {
          const params = {
            correlationId: request.correlationId,
            result: result
          }
          Transport.send('discovery', 'purchasedContent', params).catch(error => {
            const msg = typeof error === 'string' ? error : error.message || 'Unknown Error'
            console.error(`Failed to send purchasedContent pull response through Transport Layer: ${msg}`)
          })
        }).catch(error => {
          const msg = typeof error === 'string' ? error : error.message || 'Unknown Error'
          console.error(`App 'purchasedContent' callback failed: ${msg}`)
        })
      }
      catch (error) {
        const msg = typeof error === 'string' ? error : error.message || 'Unknown Error'
        console.error(`App 'purchasedContent' callback failed: ${msg}`)
    }
    })
  }
  else {
    return Transport.send('discovery', 'purchasedContent', { correlationId: null, result: data })
  }
}

function watched(entityId, progress, completed, watchedOn) {
  const transforms = null

  if (arguments.length === 1 && Array.isArray(arguments[0])) {
    return Transport.send('discovery', 'watched', arguments[0], transforms)
  }
  else {
    return Transport.send('discovery', 'watched', { entityId, progress, completed, watchedOn }, transforms)
  }
}

function watchNext(title, identifiers, expires, images) {

  const transforms = null

  return Transport.send('discovery', 'watchNext', { title, identifiers, expires, images }, transforms)
}

function entitlements(entitlements) {

  const transforms = null

  return Transport.send('discovery', 'entitlements', { entitlements }, transforms)
}

function launch(appId, intent) {

  const transforms = null

  return Transport.send('discovery', 'launch', { appId, intent }, transforms)
}
// onNavigateTo API is handled via listen('navigateTo', (data) => void)

import { signIn as logSignIn } from '../Metrics/index.mjs'

function signIn(entitlements) {
    const transforms = null

    const p = Transport.send('discovery', 'signIn', { entitlements }, transforms)
    
    p.then(_ => {
        setTimeout(_ => {
            logSignIn(entitlements)
        })    
    })

    return p
}

import { signOut as logSignOut } from '../Metrics/index.mjs'

function signOut() {
    const transforms = null

    const p = Transport.send('discovery', 'signOut', {  }, transforms)
    
    p.then(_ => {
        setTimeout(_ => {
            logSignOut()
        })    
    })

    return p
}
// onPolicyChanged API is handled via listen('policyChanged', (data) => void)

    function listen(...args) {
      return Events.listen('discovery', ...args)
    } 
    
    function once(...args) {
      return Events.once('discovery', ...args)
    }
    
    function clear(...args) {
      return Events.clear('discovery', ...args)
    }
    
export default {

  events: {
    navigateTo:'navigateTo',
    policyChanged:'policyChanged'
  },

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


  OfferingType: {
    FREE: 'free',
    SUBSCRIBE: 'subscribe',
    BUY: 'buy',
    RENT: 'rent'
  },


  AudioProfile: {
    STEREO: 'stereo',
    DOLBY_DIGITAL_5_1: 'dolbyDigital5.1',
    DOLBY_DIGITAL_7_1: 'dolbyDigital7.1',
    DOLBY_DIGITAL_5_1_PLUS: 'dolbyDigital5.1+',
    DOLBY_DIGITAL_7_1_PLUS: 'dolbyDigital7.1+',
    DOLBY_ATMOS: 'dolbyAtmos'
  },

policy,
  entityInfo,
  purchasedContent,
  watched,
  watchNext,
  entitlements,
  launch,
  signIn,
  signOut,
  listen,
  once,
  clear
}