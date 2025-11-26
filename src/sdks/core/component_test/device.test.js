import "./utils/bootstrap.mjs";

import { test, expect, describe } from "@jest/globals";
import Device from "../dist/lib/Device/index.mjs";

describe("Device API", () => {
  test("uid returns expected value", async () => {
    await expect(Device.uid()).resolves.toBe(
      "ee6723b8-7ab3-462c-8d93-dbf61227998e"
    );
  });

  test("deviceClass returns expected value", async () => {
    await expect(Device.deviceClass()).resolves.toBe("ott");
  });
});
