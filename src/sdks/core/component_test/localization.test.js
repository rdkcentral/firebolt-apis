import "./utils/bootstrap.mjs";

import { test, expect, describe } from "@jest/globals";
import Localization from "../dist/lib/Localization/index.mjs";

describe("Localization API", () => {
  test("country returns 'US'", async () => {
    await expect(Localization.country()).resolves.toBe("US");
  });

  test("preferredAudioLanguages returns expected array", async () => {
    await expect(Localization.preferredAudioLanguages()).resolves.toEqual([
      "spa",
      "eng",
    ]);
  });

  test("presentationLanguage returns 'en-US'", async () => {
    await expect(Localization.presentationLanguage()).resolves.toBe("en-US");
  });
});
