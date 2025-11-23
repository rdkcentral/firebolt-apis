import { transport } from '../../../../../test/TransportHarness.js'
import MockTransport from '../../build/javascript/src/Transport/MockTransport.mjs'

import { test, expect } from "@jest/globals"
import { Lifecycle, Device, Discovery } from "../../build/javascript/src/firebolt";

let listenerId: number

test('Able to get TypeScript listenerId', () => {
    return Lifecycle.listen('onInactive', () => { }).then((id: number) => {
        listenerId = id
        expect(listenerId > 0).toBe(true)
    })
})

test('Able to get resolution', () => {
    return Device.screenResolution().then((res: [number, number]) => {
        expect(res[0] > 0).toBe(true)
        expect(res[1] > 0).toBe(true)
    })
})