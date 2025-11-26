import "./utils/bootstrap.mjs";

import { test, expect, describe } from "@jest/globals";
import Accessibility from "../dist/lib/Accessibility/index.mjs";

describe("Accessibility API", () => {
  test("audioDescription returns boolean true", async () => {
    await expect(Accessibility.audioDescription()).resolves.toBe(true);
  });

  test("closedCaptionsSettings returns expected structure", async () => {
    const result = await Accessibility.closedCaptionsSettings();

    expect(result).toHaveProperty("enabled", true);
    expect(result).toHaveProperty("preferredLanguages");
    expect(result.preferredLanguages).toEqual(["eng", "spa"]);
  });

  test("highContrastUI returns boolean true", async () => {
    await expect(Accessibility.highContrastUI()).resolves.toBe(true);
  });

  test("voiceGuidanceSettings returns expected structure", async () => {
    const result = await Accessibility.voiceGuidanceSettings();

    expect(result).toMatchObject({
      enabled: true,
      navigationHints: true,
      rate: 0.8,
    });
  });
});
