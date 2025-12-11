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

import "./utils/bootstrap.mjs";

import { test } from '@jest/globals';

import {
  testSubscribeWithOneArgument,
  testSubscribeWithTwoArguments,
  testListenWithOneArgument,
  testListenWithTwoArguments,
  testSubscribeWithThreeArguments,
  testListenWithThreeArguments
} from './utils/subscribeHelper.js';

import Accessibility from '../dist/lib/Accessibility/index.mjs';

test('Accessibility.audioDescription subscription', async () => {
  return testSubscribeWithOneArgument(Accessibility, 'audioDescription', true, 
    '{"jsonrpc":"2.0","method":"Accessibility.onAudioDescriptionChanged","params":{"value":true}}');
});

test('Accessibility.once: onAudioDescriptionChanged', async () => {
  return testListenWithOneArgument(Accessibility, 'once', 'onAudioDescriptionChanged', true, 
    '{"jsonrpc":"2.0","method":"Accessibility.onAudioDescriptionChanged","params":{"value":true}}');
});

test('Accessibility.listen: onAudioDescriptionChanged', async () => {
  return testListenWithOneArgument(Accessibility, 'listen', 'onAudioDescriptionChanged', true, 
    '{"jsonrpc":"2.0","method":"Accessibility.onAudioDescriptionChanged","params":{"value":true}}');
});

test('Accessibility.closedCaptionsSettings subscription', async () => {
  return testSubscribeWithTwoArguments(Accessibility, 'closedCaptionsSettings', true, ['eng', 'spa'], 
    '{"jsonrpc":"2.0","method":"Accessibility.onClosedCaptionsSettingsChanged","params":{"enabled":true,"languages":["eng","spa"]}}');
});

test('Accessibility.once: onClosedCaptionsSettingsChanged', async () => {
  return testListenWithTwoArguments(Accessibility, 'once', 'onClosedCaptionsSettingsChanged', true, ['eng', 'spa'], 
    '{"jsonrpc":"2.0","method":"Accessibility.onClosedCaptionsSettingsChanged","params":{"enabled":true,"languages":["eng","spa"]}}');
});

test('Accessibility.listen: onClosedCaptionsSettingsChanged', async () => {
  return testListenWithTwoArguments(Accessibility, 'listen', 'onClosedCaptionsSettingsChanged', true, ['eng', 'spa'], 
    '{"jsonrpc":"2.0","method":"Accessibility.onClosedCaptionsSettingsChanged","params":{"enabled":true,"languages":["eng","spa"]}}');
});

test('Accessibility.highContrastUI subscription', async () => {
  return testSubscribeWithOneArgument(Accessibility, 'highContrastUI', true, 
    '{"jsonrpc":"2.0","method":"Accessibility.onHighContrastUIChanged","params":{"value":true}}');
});

test('Accessibility.once: onHighContrastUIChanged', async () => {
  return testListenWithOneArgument(Accessibility, 'once', 'onHighContrastUIChanged', true, 
    '{"jsonrpc":"2.0","method":"Accessibility.onHighContrastUIChanged","params":{"value":true}}');
});

test('Accessibility.listen: onHighContrastUIChanged', async () => {
  return testListenWithOneArgument(Accessibility, 'listen', 'onHighContrastUIChanged', true, 
    '{"jsonrpc":"2.0","method":"Accessibility.onHighContrastUIChanged","params":{"value":true}}');
});


test('Accessibility.voiceGuidanceSettings subscription', async () => {
  return testSubscribeWithThreeArguments(Accessibility, 'voiceGuidanceSettings', true, 0.8, true, 
    '{"jsonrpc":"2.0","method":"Accessibility.onVoiceGuidanceSettingsChanged","params":{"enabled":true,"level":0.8,"spokenFeedback":true}}');
});

test('Accessibility.once: onVoiceGuidanceSettingsChanged', async () => {
  return testListenWithThreeArguments(Accessibility, 'once', 'onVoiceGuidanceSettingsChanged', true, 0.8, true, 
    '{"jsonrpc":"2.0","method":"Accessibility.onVoiceGuidanceSettingsChanged","params":{"enabled":true,"level":0.8,"spokenFeedback":true}}');
});

test('Accessibility.listen: onVoiceGuidanceSettingsChanged', async () => {
  return testListenWithThreeArguments(Accessibility, 'listen', 'onVoiceGuidanceSettingsChanged', true, 0.8, true, 
    '{"jsonrpc":"2.0","method":"Accessibility.onVoiceGuidanceSettingsChanged","params":{"enabled":true,"level":0.8,"spokenFeedback":true}}');
});