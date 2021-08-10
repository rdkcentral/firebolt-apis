import Transport from '../Transport'
import { InternalMetrics } from '../Metrics'
/* ${IMPORTS} */

/* ${INITIALIZATION} */

function ready() {
  return Transport.send('metrics', 'ready', {})
}

function signIn() {
  return Transport.send('metrics', 'signIn', {})
}

function signOut() {
  return Transport.send('metrics', 'signOut', {})
}


/* ${METHODS} */

export default {

  /* ${EVENTS} */
  /* ${ENUMS} */
  /* ${METHOD_LIST} */

}

export {
  ready,
  signIn,
  signOut
}