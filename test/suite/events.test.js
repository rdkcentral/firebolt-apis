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

import Setup from '../Setup'
import { Events } from '../../dist/lib/firebolt.mjs'
import { jest } from '@jest/globals';

jest.setTimeout(10000)

let count = 0

const listenThenClearCallback = jest.fn()
const listenCallback = jest.fn()
const onceCallback = jest.fn()

test(`Events.listen received 4 events`, () => {
    return Events.listen('App', 'testEvent', v => listenThenClearCallback(v)).then(listenerId => {
        Events.listen('App', 'testEvent', v => listenCallback(v))
        Events.once('App', 'testEvent', v => onceCallback(v))
    
        // Everyone gets this
        Events.broadcast('testEvent', { id: count++ })
    
        // Everyone but the 'once' listener get's this
        Events.broadcast('testEvent', { id: count++ })
    
        Events.clear(listenerId)
    
        // The main listener gets these two
        Events.broadcast('testEvent', { id: count++ })
        Events.broadcast('testEvent', { id: count++ })
    
        Events.clear('App')
    
        // Nobody gets these
        Events.broadcast('testEvent', { id: count++ })
        Events.broadcast('testEvent', { id: count++ })    

        expect(listenCallback).toBeCalledTimes(4)
    })
})

test(`Events.listen w/ clear received 2 events`, () => {
    expect(listenThenClearCallback).toBeCalledTimes(2)
})

test(`Events.once received 1 event`, () => {
    expect(onceCallback).toBeCalledTimes(1)
})
