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
import { Device } from "../../dist/lib/firebolt";

test("Device.version()", () => {
  const expectedOutput: object = {
    debug: "",
    os: { major: 0, minor: 1, patch: 0, readable: "Firebolt OS v0.1.0" },
    sdk: { major: 0, minor: 7, patch: 0, readable: "The Firebolt JS SDK" },
  };
  return Device.version().then((v: object) => {
    expect(v).toEqual(expectedOutput);
  });
});

test("Device.id()", () => {
  return Device.id().then((res: string) => {
    expect(res).toBe("123");
  });
});

test("Device.distributor()", () => {
  return Device.distributor().then((res: string) => {
    expect(res).toBe("Company");
  });
});

test("Device.platform()", () => {
  return Device.platform().then((res: string) => {
    expect(res).toBe("WPE");
  });
});

test("Device.uid()", () => {
  return Device.uid().then((res: string) => {
    expect(res).toBe("ee6723b8-7ab3-462c-8d93-dbf61227998e");
  });
});

test("Device.type()", () => {
  return Device.type().then((res: string) => {
    expect(res).toBe("STB");
  });
});

test("Device.model()", () => {
  return Device.model().then((res: string) => {
    expect(res).toBe("xi6");
  });
});

test("Device.sku()", () => {
  return Device.sku().then((res: string) => {
    expect(res).toBe("AX061AEI");
  });
});

test("Device.make()", () => {
  return Device.make().then((res: string) => {
    expect(res).toBe("Arris");
  });
});

test("Device.hdcp()", () => {
  const expectedOutput: Device.BooleanMap = {
    "hdcp1.4": true,
    "hdcp2.2": true,
  };
  return Device.hdcp().then((res: Device.BooleanMap) => {
    expect(res).toEqual(expectedOutput);
  });
});

test("Device.hdcp(subscriber)", () => {
  return Device.hdcp((supportedHdrProfiles: Device.BooleanMap) => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("Device.audio()", () => {
  return Device.audio().then((res: Device.AudioProfiles) => {
    expect(res).toEqual({
      dolbyAtmos: true,
      "dolbyDigital5.1": true,
      "dolbyDigital5.1+": true,
      stereo: true,
    });
  });
});

test("Device.audio(subscriber)", () => {
  return Device.audio(
    (supportedAudioProfiles: Device.AudioProfiles) => {}
  ).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("Device.screenResolution()", () => {
  return Device.screenResolution().then((res: [number, number]) => {
    expect(res).toEqual(expect.arrayContaining([1920, 1080]));
  });
});

test("Device.screenResolution(subscriber)", () => {
  return Device.screenResolution(
    (screenResolution: [number, number]) => {}
  ).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("Device.videoResolution()", () => {
  return Device.videoResolution().then((res: [number, number]) => {
    expect(res).toEqual(expect.arrayContaining([1920, 1080]));
  });
});

test("Device.videoResolution(subscriber)", () => {
  return Device.videoResolution((videoResolution: [number, number]) => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("Device.name()", () => {
  return Device.name().then((res: string) => {
    expect(res).toBe("Living Room");
  });
});

test("Device.name(subscriber)", () => {
  return Device.name((value: string) => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test("Device.network()", () => {
  return Device.network().then((res: object) => {
    expect(res).toEqual({ state: "connected", type: "wifi" });
  });
});

test("Device.network(subscriber)", () => {
  return Device.network((networkInfo: object) => {}).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});
