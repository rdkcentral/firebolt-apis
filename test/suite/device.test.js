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
import { Device } from '../../dist/firebolt.mjs'

const version = require('../../package.json').version.split('-')[0].split('.')

test(`Device.version() to be ${version[0]}.${version[1]}.${version[2]}`, () => {
    return Device.version().then( v => {
        expect(v.sdk.major).toBe(parseInt(version[0]))
        expect(v.sdk.minor).toBe(parseInt(version[1]))
        expect(v.sdk.patch).toBe(parseInt(version[2]))
    })
});