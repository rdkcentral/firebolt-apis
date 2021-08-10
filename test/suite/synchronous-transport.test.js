// NOTE: this test SHOULD NOT include Setup, since it does it's own
// setup for Firebolt SDK/TL handshake
const win = globalThis || window
if (!win.__firebolt) {
    win.__firebolt = {}
}

// holds test transport layer state, e.g. callback
const state = {

}

// These all get set synchronously, so we'll update them as they happen
let getTransportLayerCalled = false
let sendCalled = false
let inactiveListened = false
let callbackWiredUp = false
let postReadyState = null

// Wire up our synchronous transport layer before the SDK loads
beforeAll( () => {
    win.__firebolt.getTransportLayer = function() {
        // we'll assert on this later...
        getTransportLayerCalled = true
        return {
            send: function(message) {
                // we'll assert on this later...
                sendCalled = true
                const json = JSON.parse(message)
                if (json.method.toLowerCase() === 'lifecycle.oninactive') {
                    // we'll assert on this later...
                    inactiveListened = true

                    if (state.callback) {
                        // we'll assert on this later...
                        callbackWiredUp = true
                        let response = {
                            jsonrpc: '2.0',
                            id: json.id,
                            result: {
                                state: 'inactive'
                            }
                        }
                        // catching errors, so all tests don't fail if this breaks
                        try {
                            // send back the onInactive event immediately, to test for race conditions
                            state.callback(JSON.stringify(response))
                        }
                        catch (err) {
                            // fail silenetly (the boolean-based tests below will figure it out...)
                        }
                    }
                }
            },
            receive: function(callback) {
                // store the callback
                state.callback = callback
            }
        }
    }

    // import Lifecycle (using require was the ony way i could get jest to load it AFTER this `beforeAll` code)
    const { Lifecycle } = require('../../dist/firebolt.js')    
    Lifecycle.ready()
})

test('Transport injected before SDK', () => {
    expect(getTransportLayerCalled).toBe(true)
});

test('Transport send method working', () => {
    expect(sendCalled).toBe(true)
});

test('Transport was sent `Lifecycle.onInactive` listener', () => {
    expect(inactiveListened).toBe(true)
});

test('Transport `receive` callback wired up', () => {
    expect(callbackWiredUp).toBe(true)
});
