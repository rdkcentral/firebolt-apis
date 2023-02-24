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
import { test, expect } from "@jest/globals";
import { Lifecycle } from "../../build/javascript/src/firebolt-manage";
test("Lifecycle.setState()", () => {
    return Lifecycle.setState("Test_APP_ID", Lifecycle.LifecycleState.INITIALIZING).then((res) => {
        expect(res).toEqual({});
    });
});
test("Lifecycle.provide() with blank object", () => {
    expect(() => {
        Lifecycle.provide("xrn:firebolt:capability:lifecycle:state", {});
    }).toThrow();
});
test("Lifecycle.session()", () => {
    const dummyData = {
        app: {
            id: "123",
            url: "test_url",
            title: "test_title",
            catalog: "test_catalog",
        },
        runtime: {
            id: "123",
        },
    };
    return Lifecycle.session(dummyData).then((res) => {
        expect(res).not.toBeNull();
    });
});
