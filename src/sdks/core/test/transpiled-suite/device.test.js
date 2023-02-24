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
import { Device } from "../../build/javascript/src/firebolt";
test("Device.version()", () => {
    const debug = "Non-parsable build info for error logging only.";
    const os = {
        major: 0,
        minor: 1,
        patch: 0,
        readable: "Firebolt OS v0.1.0"
    };
    const sdk = {
        major: 0,
        minor: 8,
        patch: 0,
        readable: "The Firebolt JS SDK",
    };
    const firmware = {
        major: 1,
        minor: 2,
        patch: 3,
        readable: "Device Firmware v1.2.3"
    };
    const api = {
        major: 0,
        minor: 8,
        patch: 0,
        readable: "Firebolt API v0.8.0"
    };
    return Device.version().then((v) => {
        expect(v.debug).toBe(debug);
        expect(v.os).toEqual(os);
        expect(v.api).toEqual(api);
        expect(v.firmware).toEqual(firmware);
        expect(typeof v.sdk.major).toBe('number');
        expect(typeof v.sdk.minor).toBe('number');
        expect(typeof v.sdk.patch).toBe('number');
        expect(typeof v.sdk.readable).toBe('string');
    });
});
test("Device.id()", () => {
    return Device.id().then((res) => {
        expect(res).toBe("123");
    });
});
test("Device.distributor()", () => {
    return Device.distributor().then((res) => {
        expect(res).toBe("Company");
    });
});
test("Device.platform()", () => {
    return Device.platform().then((res) => {
        expect(res).toBe("WPE");
    });
});
test("Device.uid()", () => {
    return Device.uid().then((res) => {
        expect(res).toBe("ee6723b8-7ab3-462c-8d93-dbf61227998e");
    });
});
test("Device.type()", () => {
    return Device.type().then((res) => {
        expect(res).toBe("STB");
    });
});
test("Device.model()", () => {
    return Device.model().then((res) => {
        expect(res).toBe("xi6");
    });
});
test("Device.sku()", () => {
    return Device.sku().then((res) => {
        expect(res).toBe("AX061AEI");
    });
});
test("Device.make()", () => {
    return Device.make().then((res) => {
        expect(res).toBe("Arris");
    });
});
test("Device.hdcp()", () => {
    const expectedOutput = {
        "hdcp1.4": true,
        "hdcp2.2": true,
    };
    return Device.hdcp().then((res) => {
        expect(res).toEqual(expectedOutput);
    });
});
test("Device.hdcp(subscriber)", () => {
    return Device.hdcp((supportedHdrProfiles) => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("Device.audio()", () => {
    return Device.audio().then((res) => {
        expect(res).toEqual({
            dolbyAtmos: true,
            "dolbyDigital5.1": true,
            "dolbyDigital5.1+": true,
            stereo: true,
        });
    });
});
test("Device.audio(subscriber)", () => {
    return Device.audio((supportedAudioProfiles) => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("Device.screenResolution()", () => {
    return Device.screenResolution().then((res) => {
        expect(res).toEqual(expect.arrayContaining([1920, 1080]));
    });
});
test("Device.screenResolution(subscriber)", () => {
    return Device.screenResolution((screenResolution) => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("Device.videoResolution()", () => {
    return Device.videoResolution().then((res) => {
        expect(res).toEqual(expect.arrayContaining([1920, 1080]));
    });
});
test("Device.videoResolution(subscriber)", () => {
    return Device.videoResolution((videoResolution) => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("Device.name()", () => {
    return Device.name().then((res) => {
        expect(res).toBe("Living Room");
    });
});
test("Device.name(subscriber)", () => {
    return Device.name((value) => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("Device.network()", () => {
    return Device.network().then((res) => {
        expect(res).toEqual({ state: "connected", type: "wifi" });
    });
});
test("Device.network(subscriber)", () => {
    return Device.network((networkInfo) => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() audioChanged event.", () => {
    return Device.listen("audioChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() audioChanged event.", () => {
    return Device.once("audioChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() deviceNameChanged event.", () => {
    return Device.listen("deviceNameChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() deviceNameChanged event.", () => {
    return Device.once("deviceNameChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() hdcpChanged event.", () => {
    return Device.listen("hdcpChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() hdcpChanged event.", () => {
    return Device.once("hdcpChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() hdrChanged event.", () => {
    return Device.listen("hdrChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() hdrChanged event.", () => {
    return Device.once("hdrChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() nameChanged event.", () => {
    return Device.listen("nameChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() nameChanged event.", () => {
    return Device.once("nameChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() networkChanged event.", () => {
    return Device.listen("networkChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() networkChanged event.", () => {
    return Device.once("networkChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() screenResolutionChanged event.", () => {
    return Device.listen("screenResolutionChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() screenResolutionChanged event.", () => {
    return Device.once("screenResolutionChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("listen() videoResolutionChanged event.", () => {
    return Device.listen("videoResolutionChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("once() videoResolutionChanged event.", () => {
    return Device.once("videoResolutionChanged", () => { }).then((res) => {
        expect(res > 0).toBe(true);
    });
});
test("clear()", () => {
    const result = Device.clear(2);
    expect(result).toBeFalsy();
});
