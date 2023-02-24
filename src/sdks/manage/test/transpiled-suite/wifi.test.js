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
import { Wifi } from "../../build/javascript/src/firebolt-manage";
test("wifi.scan()", () => {
    return Wifi.scan().then((res) => {
        expect(res).toEqual({
            list: [
                {
                    frequency: 2.4,
                    security: "wpa2Psk",
                    signalStrength: -70,
                    ssid: "DND",
                },
                {
                    frequency: 5,
                    security: "WPA2_ENTERPRISE_AES",
                    signalStrength: -70,
                    ssid: "Fortnite",
                },
                {
                    frequency: 2.4,
                    security: "none",
                    signalStrength: -70,
                    ssid: "Guardian",
                },
            ],
        });
    });
});
test("Wifi.connect()", () => {
    return Wifi.connect().then((res) => {
        expect(res).toEqual({
            frequency: 2.4,
            security: "wpa2Psk",
            signalStrength: -70,
            ssid: "DND",
        });
    });
});
test("Wifi.disconnect()", () => {
    return Wifi.disconnect().then((res) => {
        expect(res).toEqual({});
    });
});
test("Wifi.wps()", () => {
    return Wifi.wps().then((res) => {
        expect(res).toEqual({
            frequency: 2.4,
            security: "wpa2Psk",
            signalStrength: -70,
            ssid: "DND",
        });
    });
});
