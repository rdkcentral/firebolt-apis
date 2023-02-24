import Transport from "../Transport/index.mjs"
import Events from "../Events/index.mjs"

const sessions = {}

let eventEmitterInitialized = false
const eventHandler = (module, event, value) => {
    const session = getSession(module, method)
    if (session) {
        if (event === session.addName && session.add) {
            session.add(value)
        }
        else if (event === session.removeName && session.remove) {
            session.remove(value)
        }
    }
}

function getSession(module, method) {
    return sessions[module.toLowerCase() + '.' + method]
}

function startSession(module, method) {
    sessions[module.toLowerCase() + '.' + method] = {}
    return sessions[module.toLowerCase() + '.' + method]
}

function stopSession(module, method) {
    delete sessions[module.toLowerCase() + '.' + method]
}

function start(module, method, addName, removeName, params, add, remove, transforms) {
    let session = getSession(module, method)

    if (!eventEmitterInitialized) {
        Transport.addEventEmitter(eventHandler)
        eventEmitterInitialized = true
    }

    if (session) {
        throw `Error: only one ${module}.${method} operation may be in progress at a time. Call stop${method.charAt(0).toUpperCase() + method.substr(1)} on previous ${method} first.`
    }
    else {
        session = startSession(module, method)
    }

    if (!add) {
        throw `Error: ${module}.${method} requires at least one callback because results may be asynchronous.`
    }

    const requests = [
        {
            module: module,
            method: method,
            params: params,
            transforms: transforms
        }
    ]

    requests.push({
        module: module,
        method: addName,
        params: {
            listen: true
        },
        transforms: transforms
    })

    if (remove) {
        requests.push({
            module: module,
            method: removeName,
            params: {
                listen: true
            },
            transforms: transforms
        })
    }
    
    const results = Transport.send(requests)

    session.id = results[0].id
    session.addRpcId = results[1].id
    session.add = add
    session.remove = remove
    session.addName = addName
    session.removeName = removeName

    results[0].promise.then( items => {
        items && items.forEach(item => add(item))
    })

    results[1].promise.then( id => {
        // clear it out if the session is already canceled
        if (!session.id) {
            Events.clear(id)
        }
        else {
            session.addListenerId = id
        }
    })

    if (remove) {
        session.removeRpcId = results[2].id
        results[2].promise.then( id => {
            // clear it out if the session is already canceled
            if (!session.id) {
                Events.clear(id)
            }
            else {
                session.removeListenerId = id
            }
        })
    }

    return {
        stop: () => {
            const requests = [
                {
                    module: module,
                    method: `stop${method.charAt(0).toUpperCase() + method.substr(1)}`,
                    params: {
                        correlationId: session.id
                    }
                },
                {
                    module: module,
                    method: addName,
                    params: {
                        listen: false
                    }
                }
            ]

            if (remove) {
                requests.push({
                    module: module,
                    method: removeName,
                    params: {
                        listen: false
                    }
                })
            }
            Transport.send(requests)
            stopSession(module, method)
        }
    }
}



export default {
  start: start
}