import { test, expect } from "@jest/globals";
import { Localization } from '@firebolt-js/sdk';

test("country", async() => {
  return Localization.country().then((res: string) => {
    expect(res).toBe("US");
  });
});
test("preferredAudioLanguages", async() => {
  const res = await Localization.preferredAudioLanguages();
  expect(res).toEqual(["spa","eng"]);
});
test("presentationLanguage", async() => {
  const res = await Localization.presentationLanguage();
  expect(res).toBe("en-US");
});

test('listen', async () => {
  await Localization.listen((event: string, data: object) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('once', async () => {
  await Localization.once((event: string, data: object) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('listen onCountryChanged', async () => {
  return Localization.listen((event: 'onCountryChanged', listener: { data: string }) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('once onCountryChanged', async () => {
  return Localization.once((event: 'onCountryChanged', listener: { data: string }) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('listen onPreferredAudioLanguagesChanged', async () => {
  return Localization.listen((event: 'onPreferredAudioLanguagesChanged', listener: { data: string[] }) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('once onPreferredAudioLanguagesChanged', async () => {
  return Localization.once((event: 'onPreferredAudioLanguagesChanged', listener: { data: string[] }) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('listen onPresentationLanguageChanged', async () => {
  return Localization.listen((event: 'onPresentationLanguageChanged', listener: { data: string }) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('once onPresentationLanguageChanged', async () => {
  return Localization.once((event: 'onPresentationLanguageChanged', listener: { data: string }) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});