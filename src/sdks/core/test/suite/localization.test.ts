/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 Sky UK
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
 */


import { test, expect } from "@jest/globals";
import { Localization } from '@firebolt-js/sdk';

test("country", async () => {
  return Localization.country().then((res: string) => {
    expect(res).toBe("US");
  });
});
test("preferredAudioLanguages", async () => {
  const res = await Localization.preferredAudioLanguages();
  expect(res).toEqual(["spa", "eng"]);
});
test("presentationLanguage", async () => {
  const res = await Localization.presentationLanguage();
  expect(res).toBe("en-US");
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