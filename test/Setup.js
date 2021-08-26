/**
 * This module sets up the mock transport layer immediately, instead of letting the SDK wait 500ms
 */

const win = globalThis || window

if (!win.__firebolt) {
    win.__firebolt = {}
}

// wires up the mock transport w/out waiting
win.__firebolt.mockTransportLayer = true

// sets a flag that mock defaults impls can use to speed things up, e.g. Lifecycle/defaults.js
win.__firebolt.automation = true

export const testHarness = {
    initialize: function(config) {
        this.emit = config.emit
    }
}

win.__firebolt.testHarness = testHarness