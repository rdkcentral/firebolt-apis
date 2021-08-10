import { Lifecycle } from '..'
import MockTransport from '../Transport/mock'
import { default as win } from '../Transport/global'

let inactive = 0 /* ${EXAMPLE:onInactive} */
let foreground = 0 /* ${EXAMPLE:onForeground} */
let background = 0 /* ${EXAMPLE:onBackground} */
let suspended = 0 /* ${EXAMPLE:onSuspended} */
let unloading = 0 /* ${EXAMPLE:onUnloading} */

const emit = (value) => {
  value.previous = Lifecycle.state()
  MockTransport.event('Lifecycle', value.state, value)
}

const automation = win && win.__firebolt ? !!win.__firebolt.automation : false

export default {
  ready: function() {
    inactive.previous = 'initializing'
    setTimeout(() => emit(inactive), automation ? 1 : 500)
    foreground.previous = 'inactive'
    setTimeout(() => emit(foreground), automation ? 2 : 1000)
  },

  close: function(params) {
    let reason = params.reason
    if (reason === Lifecycle.CloseReason.REMOTE_BUTTON) {
      setTimeout(() => emit(inactive), automation ? 1 : 500)
    }
    else if (Object.values(Lifecycle.CloseReason).includes(reason)) {
      setTimeout(() => emit(inactive), automation ? 1 : 500)
      setTimeout(() => emit(unloading), automation ? 2 : 1000)
      setTimeout(() => Lifecycle.finished(), automation ? 3: 3000)
    }
    else {
      throw "Invalid close reason"
    }
  },

  finished: function() {
    if (win.location)
      win.location.href = "about:blank"
  },
}
