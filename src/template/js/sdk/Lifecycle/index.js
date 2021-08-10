/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 Comcast
 *
 * COMCAST HIGHLY CONFIDENTIAL AND PROPRIETARY
 * 
 * This file and its contents are the intellectual property of Comcast and may
 * not be used, copied, distributed or otherwise disclosed in whole or in part
 * without the express written permission of Comcast.
 */

import Transport from '../Transport/index.js'
import Events from '../Events'
import { registerEvents } from '../Events'
import { ready as metricsReady } from '../Metrics'

const Metrics = {
  ready: metricsReady
}

/* ${INITIALIZATION} */

export const store = {
  _current: 'initializing',
  get current() {
    return this._current
  }
}

Events.listen('Lifecycle', (event, value) => {
  store._current = event
})

function state() {
  return store.current
}

function ready() {
  Metrics.ready()
  return Transport.send('lifecycle', 'ready')
}

function close(reason) {
  return Transport.send('lifecycle', 'close', { reason: reason })
}

function finished() {
  if (store.current === 'unloading') {
    // Metrics.app.close()
    return Transport.send('lifecycle', 'finished')
  } else {
    throw 'Cannot call finished() except when in the unloading transition'
  }
}

/* ${EVENT_METHODS} */

// public API
export default {

  /* ${EVENTS} */

  /* ${ENUMS} */

  /* ${METHOD_LIST} */
}
