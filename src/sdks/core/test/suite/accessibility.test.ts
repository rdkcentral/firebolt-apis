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

import { test, expect } from '@jest/globals';
import { Accessibility } from '@firebolt-js/sdk';


test("Accessibility.uid()", async () => {
  const res = await Accessibility.audioDescription();
  expect(res).toBe(true);
});

test("Accessibility.deviceClass()", async () => {
  const res = await Accessibility.closedCaptionsSettings();
  expect(res).toMatchObject({
    enabled: true,
    preferredLanguages: ["eng", "spa"],
  });
});

test("Accessibility.highContrastUI()", async () => {
  const res = await Accessibility.highContrastUI();
  expect(res).toBe(true);
});

test("Accessibility.voiceGuidanceSettings()", async () => {
  const res = await Accessibility.voiceGuidanceSettings();
  expect(res).toMatchObject({
    enabled: true,
    navigationHints: true,
    rate: 0.8,
  });
});

test('listen audioDescription', async () => {
  return Accessibility.listen('onAudioDescriptionChanged', (data: boolean) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('once audioDescription', async () => {
  return Accessibility.once('onAudioDescriptionChanged', (data: boolean) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('listen ClosedCaptionsSettings', async () => {
  return Accessibility.listen('onClosedCaptionsSettingsChanged', (data) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('once ClosedCaptionsSettings', async () => {
  return Accessibility.once('onClosedCaptionsSettingsChanged', (data) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('listen highContrastUI', async () => {
  return Accessibility.listen('onHighContrastUIChanged', (data: boolean) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('once highContrastUI', async () => {
  return Accessibility.once('onHighContrastUIChanged', (data: boolean) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('listen VoiceGuidanceSettings', async () => {
  return Accessibility.listen('onVoiceGuidanceSettingsChanged', (data) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('once VoiceGuidanceSettings', async () => {
  return Accessibility.once('onVoiceGuidanceSettingsChanged', (data) => { }).then((res: number) => {
    expect(res > 0).toBe(true);
  });
});

test('clear()', () => {
  const result: boolean = Accessibility.clear(-1000);
  expect(result).toBeFalsy();
});




