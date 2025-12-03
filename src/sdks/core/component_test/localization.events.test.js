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

