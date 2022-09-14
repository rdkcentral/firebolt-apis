import Transport from '../Transport/index.mjs'

window.__firebolt = window.__firebolt || {}
const initializers = {}
const apis = {}
const queue = {}
const initialized = []
const frozen = false

window.__firebolt.registerExtensionSDK = (id, initializer) => {
    initializers[id] = initializer

    if (queue[id]) {
        initialize(id, queue[id])
        delete queue[id]
    }
}

// Method for handing off platform tokens to extension SDKs
registerAPI('authorize', (...args) => Transport.send('capabilities', 'authorize', {...args} ))

function initialize(id, config) {
    if (!frozen) {
        Object.freeze(apis)
    }
    Object.freeze(config)
    if (initializers[id]) {
        initializers[id](config, apis)
        delete initializers[id]
        initialized.push(id)
    }
    else {
        queue[id] = config
    }
}

function active() {
    return Object.freeze(initialized.contact())
}

export function registerAPI(name, method) {
    apis[name] = method
}

export default {
    initialize,
    active
}