import Transport from "../Transport/index.mjs"
import Events from "../Events/index.mjs"

function prop(moduleName, key, params, callbackOrValue = null, immutable, readonly, contextParameterCount) {
  const numArgs = Object.values(params).length

  if (numArgs === contextParameterCount && callbackOrValue === null) {
    // getter
    return Transport.send(moduleName, key, params)
  } else if (numArgs === contextParameterCount && typeof callbackOrValue === 'function') {
    // subscribe
    if (immutable) {
      throw new Error('Cannot subscribe to an immutable property')
    }
    return Events.listen(moduleName, key + 'Changed', callbackOrValue)
  } else if (numArgs === (contextParameterCount) && callbackOrValue !== null) {
    // setter
    if (immutable) {
      throw new Error('Cannot set a value to an immutable property')
    }
    if (readonly) {
      throw new Error('Cannot set a value to a readonly property')
    }
    return Transport.send(moduleName, 'set' + key[0].toUpperCase() + key.substring(1), {
      value: callbackOrValue
    })
  }
  else if (numArgs < contextParameterCount) {
    throw new Error('Cannot get a value without all required context parameters.')
  }
  else {
    throw new Error('Property accessed with unexpected number of parameters.')
  }
}

export default {
  prop: prop
}