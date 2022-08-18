/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

import { testHarness } from '../Setup'
import { Lifecycle } from '../../dist/lib/firebolt.mjs'
import { jest } from '@jest/globals';

let readyResolved = false
let readyCalled = false
let readyMetricCalled = false

testHarness.onSend = function(module, method, params, id) {
    if (module === 'lifecycle' && method === 'ready') {
        readyCalled = true
    }
    else if (module === 'metrics' && method === 'ready') {
        readyMetricCalled = true
    }
}

const callback = jest.fn()
const startupState = Lifecycle.state()

beforeAll(()=> {
    Lifecycle.listen((event, _) => {
        callback(event)
    })

    Lifecycle.once('foreground', () => {
        Lifecycle.close('userExit')
    })
    
    Lifecycle.once('unloading', () => {
        Lifecycle.finished()
    })
    
    let p = new Promise( (resolve, reject) => {
        Lifecycle.once('unloading', _ => {
            resolve()
        })
    })

    Lifecycle.ready().then(_ => {
        readyResolved = true
    })

    return p
})

test('Lifecycle.ready Promise resolved', () => {
    expect(readyCalled).toBe(true)
    expect(readyResolved).toBe(true)
})

test('Lifecycle.ready calls Metrics.ready', () => {
    expect(readyMetricCalled).toBe(true)
})


test('App starts up in the \'initializing\' state', () => {
    expect(startupState).toBe('initializing')
})

test('App moves to the \'inactive\' state next', () => {
    expect(callback).nthCalledWith(1, 'inactive')
})

test('App moves to the \'foreground\' state next', () => {
    expect(callback).nthCalledWith(2, 'foreground')
})

test('App moves to the \'inactive\' state next', () => {
    expect(callback).nthCalledWith(3, 'inactive')
})

test('App moves to the \'unloading\' state next', () => {
    expect(callback).nthCalledWith(4, 'unloading')
},)
