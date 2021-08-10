/*******************************/
/* This file is auto-generated */
/* Do not edit!                */
/*******************************/
import Transport from '../Transport'
/* ${IMPORTS} */

/* ${INITIALIZATION} */

function version() {
  return new Promise( (resolve, reject) => {
      Transport.send('device', 'version').then( v => {
          v = v || {}
          v.sdk = v.sdk || {}
          v.sdk.major = parseInt('${major}')
          v.sdk.minor = parseInt('${minor}')
          v.sdk.patch = parseInt('${patch}')
          v.sdk.readable = '${readable}'
          resolve(v)    
      }).catch(error => {
          reject(error)
      })
  })
}

/* ${METHODS} */

export default {

  /* ${EVENTS} */
  /* ${ENUMS} */

  version,
  /* ${METHOD_LIST} */

}
