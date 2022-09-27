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

// NOTE: this test SHOULD NOT include Setup, since it does it's own
// setup for Firebolt SDK/TL handshake

import { Lifecycle, Discovery } from '../../dist/lib/firebolt.mjs'

// holds test transport layer state, e.g. callback
const state = {

}

let pullEntityInfoListenCount = 0
let entityInfoPulled = false
let entityInfoReceived = false
let entityInfoPushed = false
let callbackWiredUp = false
let sendCalled = false
let correlationId
let secondRegistrationFailed = false

beforeAll(() => {
    return new Promise( (resolve, reject) => {
        const transport = {
            send: function(message) {
                sendCalled = true
                const json = JSON.parse(message)
                if (json.method.toLowerCase() === 'discovery.onpullentityinfo') {
                    // we'll assert on this later...
                    pullEntityInfoListenCount++
                    if (state.callback) {
                        // we'll assert on this later...
                        callbackWiredUp = true
                        let response = {
                            jsonrpc: '2.0',
                            id: json.id,
                            result: {
                                listening: true,
                                event: 'discovery.onPullEntityInfo'
                            }
                        }
                        // catching errors, so all tests don't fail if this breaks
                        try {
                            state.callback(JSON.stringify(response))
                        }
                        catch (err) {
                            throw err
                            // fail silenetly (the boolean-based tests below will figure it out...)
                        }
        
                        setTimeout( _ => {
                            correlationId = '' + parseInt(Math.random() * 1000)
                            try {
                                response = {
                                    jsonrpc: '2.0',
                                    id: json.id,
                                    result: {
                                        correlationId: correlationId,
                                        parameters: {
                                            entityId: "345"
                                        }
                                    }
                                }
        
                                state.callback(JSON.stringify(response))
        
                                state.callback(JSON.stringify({
                                    jsonrpc: '2.0',
                                    id: json.id,
                                    result: {
                                        correlationId: 'this-will-fail',
                                        parameters: {
                                            entityId: "this-will-fail"
                                        }
                                    }
                                }))
                            }
                            catch (err) {
                                throw err
                            }

                            // resolve the beforeAll promise
                            setTimeout(_ => { resolve() }, 500)
                        })
                    }
                }
                else if (json.method.toLowerCase() === 'discovery.entityinfo') {
                    if (correlationId && (json.params.correlationId === correlationId)) {
                        entityInfoReceived = true
                    }
                    else if (correlationId && (json.params.correlationId === 'this-will-fail')) {
                    }
                    else if (!json.params.correlationId && json.params.result.entity.identifiers.entityId === "PUSH:345") {
                        entityInfoPushed = true
                    }
                    state.callback(JSON.stringify({
                        jsonrpc: '2.0',
                        id: json.id,
                        result: true
                    }))
                }
            },
            receive: function(callback) {
                // store the callback
                state.callback = callback
            }
        }
        
        window.__firebolt.setTransportLayer(transport)

        // Setup a callback that returns the correct payload
        Discovery.entityInfo((parameters) => {

            if (parameters.entityId === 'this-will-fail') {
                throw "Intentional Test failure"
            }

            entityInfoPulled = true
            return Promise.resolve({
                "expires": "2025-01-01T00:00:00.000Z",
                "entity": {
                    "identifiers": {
                    "entityId": "PULL:345"
                    },
                    "entityType": "program",
                    "programType": "movie",
                    "title": "Cool Runnings",
                    "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
                    "releaseDate": "1993-01-01T00:00:00.000Z",
                    "contentRatings": [
                    {
                        "scheme": "US-Movie",
                        "rating": "PG"
                    },
                    {
                        "scheme": "CA-Movie",
                        "rating": "G"
                    }
                    ],
                    "waysToWatch": [
                        {
                            "identifiers": {
                            "assetId": "123"
                            },
                            "expires": "2025-01-01T00:00:00.000Z",
                            "entitled": true,
                            "entitledExpires": "2025-01-01T00:00:00.000Z",
                            "offeringType": "buy",
                            "price": 2.99,
                            "videoQuality": "UHD",
                            "audioProfile": "dolbyAtmos",
                            "audioLanguages": [
                            "en"
                            ],
                            "closedCaptions": [
                            "en"
                            ],
                            "subtitles": [
                            "es"
                            ],
                            "audioDescriptions": [
                            "en"
                            ]
                        }
                    ]
                }
            })
        })

        Discovery.entityInfo({
            "expires": "2025-01-01T00:00:00.000Z",
            "entity": {
                "identifiers": {
                "entityId": "PUSH:345"
                },
                "entityType": "program",
                "programType": "movie",
                "title": "Cool Runnings",
                "synopsis": "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Pulvinar sapien et ligula ullamcorper malesuada proin libero nunc.",
                "releaseDate": "1993-01-01T00:00:00.000Z",
                "contentRatings": [
                {
                    "scheme": "US-Movie",
                    "rating": "PG"
                },
                {
                    "scheme": "CA-Movie",
                    "rating": "G"
                }
                ],
                "waysToWatch": [
                    {
                        "identifiers": {
                        "assetId": "123"
                        },
                        "expires": "2025-01-01T00:00:00.000Z",
                        "entitled": true,
                        "entitledExpires": "2025-01-01T00:00:00.000Z",
                        "offeringType": "buy",
                        "price": 2.99,
                        "videoQuality": "UHD",
                        "audioProfile": "dolbyAtmos",
                        "audioLanguages": [
                        "en"
                        ],
                        "closedCaptions": [
                        "en"
                        ],
                        "subtitles": [
                        "es"
                        ],
                        "audioDescriptions": [
                        "en"
                        ]
                    }
                ]
            }
        })

        Discovery.entityInfo(() => {}).catch(error => {
            secondRegistrationFailed = true
        })

        Lifecycle.ready()
        })
})

test('Transport was sent listeners', () => {
    expect(pullEntityInfoListenCount).toBeGreaterThan(0)
});

test('Transport was sent each listener only once', () => {
    expect(pullEntityInfoListenCount).toBe(1)
});

test('Entity Info was pulled from the app', ()=> {
    expect(entityInfoPulled).toBe(true)
    expect(entityInfoReceived).toBe(true)
});

test('Entity Info was pushed from the app', ()=> {
    expect(entityInfoPushed).toBe(true)
});

test('Entity Info pull handler cannot be registered more than once', ()=> {
    expect(secondRegistrationFailed).toBe(true)
});