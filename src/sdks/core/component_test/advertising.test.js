import "./utils/bootstrap.mjs";

import { test, expect, describe } from "@jest/globals";
import Advertising from "../dist/lib/Advertising/index.mjs";

describe("Advertising API", () => {
  test("advertisingId returns expected structure", async () => {
    const result = await Advertising.advertisingId();

    expect(result).toMatchObject({
      ifa: "bd87dd10-8d1d-4b93-b1a6-a8e5d410e400",
      ifa_type: "sspid",
      lmt: "0",
    });
  });
});

