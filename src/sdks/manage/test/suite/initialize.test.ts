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

const win = globalThis || window;

import { testHarness } from "../../../../../test/Setup";
import { beforeAll, test, expect } from "@jest/globals";
import { Device } from "../../build/javascript/src/firebolt-manage";

let version: any
let initCalled:boolean = false

beforeAll( () => {
    return new Promise( (resolve, reject) => {
        testHarness.onSend = function (module: string, method: string, params: any) {
            if (!module && method === "initialize") {
                initCalled = true
                version = params.version
                resolve(version)
            }
        }
        Device.name()
    })
})

test("Sdk.initialize()", () => {
    const parts:number[] = process.env.npm_package_version.split("-")[0].split(".").map(x => Number.parseInt(x))
    expect(version.major).toBe(parts[0])
    expect(version.minor).toBe(parts[1])
    expect(version.patch).toBe(parts[2])

})