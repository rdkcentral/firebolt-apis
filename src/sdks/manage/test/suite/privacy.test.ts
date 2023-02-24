import { test, expect } from "@jest/globals";
import { Privacy } from "../../build/javascript/src/firebolt-manage";

let listenerId: number;

test("privacy.allowResumePoints()", () => {
  return Privacy.allowResumePoints().then((res: boolean) => {
    // TODO: fix
    expect(true).toBe(true);
  });
});

test("privacy.listen() for allowPersonalizationChanged event", () => {
  Privacy.once;
  return Privacy.listen("allowPersonalizationChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.once() for allowPersonalizationChanged event", () => {
  Privacy.once;
  return Privacy.once("allowPersonalizationChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.listen() for allowWatchHistoryChanged event", () => {
  Privacy.once;
  return Privacy.listen("allowWatchHistoryChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.once() for allowWatchHistoryChanged event", () => {
  Privacy.once;
  return Privacy.once("allowWatchHistoryChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.listen() for allowAppContentAdTargetingChanged event", () => {
  Privacy.once;
  return Privacy.listen("allowAppContentAdTargetingChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.once() for allowAppContentAdTargetingChanged event", () => {
  Privacy.once;
  return Privacy.once("allowAppContentAdTargetingChanged", () => {}).then(
    (res: number) => {
      expect(res > 0).toBe(true);
    }
  );
});

test("privacy.clear()", () => {
  const result = Privacy.clear(2);
  expect(result).toBeFalsy();
});
