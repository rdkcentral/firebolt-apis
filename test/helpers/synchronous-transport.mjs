if (!window.__firebolt) {
    window.__firebolt = {}
}

let sendCallback
let receiveCallback
let first = false
let _history = []

window.__firebolt.transport = {
    send: function(message) {
        const json = JSON.parse(message)
        _history.push(json)
        sendCallback && sendCallback(json)
    },
    response: function(json) {
        receiveCallback(JSON.stringify(json))
    },
    receive: function(callback) {
        // store the callback
        receiveCallback = callback
    },
    onSend: function(callback) {
        sendCallback = callback
    },
    history() {
        return _history.concat()
    },
    instantiatedBeforeSdk() {
        return first
    }
}

export default transport