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

import { testSubscribeWithOneArgument, testListenWithOneArgument } from './utils/subscribeHelper.js';

import Localization from "../dist/lib/Localization/index.mjs";

test('Localization.country subscription', async () => {
  return testSubscribeWithOneArgument( Localization, 'country','US', 
    '{"jsonrpc":"2.0","method":"Localization.onCountryChanged","params":{"Default Result":"US"}}');
});

test('Localization.once: onCountryChanged', async () => {
  return testListenWithOneArgument( Localization, 'once','onCountryChanged','US', 
    '{"jsonrpc":"2.0","method":"Localization.onCountryChanged","params":{"Default Result":"US"}}');
});

test('Localization.listen: onCountryChanged', async () => {
  return testListenWithOneArgument( Localization, 'listen','onCountryChanged','US', 
    '{"jsonrpc":"2.0","method":"Localization.onCountryChanged","params":{"Default Result":"US"}}');
});

test('Localization.preferredAudioLanguages subscription', async () => {
  return testSubscribeWithOneArgument( Localization, 'preferredAudioLanguages',['spa', 'eng'], 
    '{"jsonrpc":"2.0","method":"Localization.onPreferredAudioLanguagesChanged","params":[["spa","eng"]]}');
});

test('Localization.once: onPreferredAudioLanguagesChanged', async () => {
  return testListenWithOneArgument( Localization, 'once','onPreferredAudioLanguagesChanged',['spa', 'eng'], 
    '{"jsonrpc":"2.0","method":"Localization.onPreferredAudioLanguagesChanged","params":[["spa","eng"]]}');
});

test('Localization.listen: onPreferredAudioLanguagesChanged', async () => {
  return testListenWithOneArgument( Localization, 'listen','onPreferredAudioLanguagesChanged',['spa', 'eng'], 
    '{"jsonrpc":"2.0","method":"Localization.onPreferredAudioLanguagesChanged","params":{"Default Result":["spa","eng"]}}');
});

test('Localization.presentationLanguage subscription', async () => {
  return testSubscribeWithOneArgument( Localization, 'presentationLanguage','en-US',
    '{"jsonrpc":"2.0","method":"Localization.onPresentationLanguageChanged","params":{"Default Result":"en-US"}}');
});

test('Localization.once: onPresentationLanguageChanged', async () => {
  return testListenWithOneArgument( Localization, 'once','onPresentationLanguageChanged','en-US',
    '{"jsonrpc":"2.0","method":"Localization.onPresentationLanguageChanged","params":{"Default Result":"en-US"}}');
});

test('Localization.listen: onPresentationLanguageChanged', async () => {
  return testListenWithOneArgument( Localization, 'listen','onPresentationLanguageChanged','en-US',
    '{"jsonrpc":"2.0","method":"Localization.onPresentationLanguageChanged","params":{"Default Result":"en-US"}}');
});

