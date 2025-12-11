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


import { expect } from '@jest/globals';

import { triggerRaw } from './httpClientHelper.js';

const testSubscribeWithOneArgument = async (module, subscribeFn, expectedArgs, rawEventPayload) => {
  const result = await new Promise((resolve) => {
    let listenerId = null;

    const notifier = module[`${subscribeFn}`];
    notifier((data) => {
      console.log("Subscribe callback:", data);
      expect(data).toEqual(expectedArgs);
      module.clear(listenerId);
      resolve(data);
    }).then((id) => {
      listenerId = id;
      console.log("Subscribe ID:", listenerId);
      triggerRaw(rawEventPayload);
    });
  });
  expect(result).toEqual(expectedArgs);
  return result;
}

const testSubscribeWithTwoArguments = async (module, subscribeFn, expectedArgs1, expectedArgs2, rawEventPayload) => {
  const result = await new Promise((resolve) => {
    let listenerId = null;

    const notifier = module[`${subscribeFn}`];
    notifier((data1, data2) => {
      console.log("Subscribe callback:", data1, data2);
      expect(data1).toEqual(expectedArgs1);
      expect(data2).toEqual(expectedArgs2);
      module.clear(listenerId);
      resolve([data1, data2]);
    }).then((id) => {
      listenerId = id;
      console.log("Subscribe ID:", listenerId);
      triggerRaw(rawEventPayload);
    });
  });
  expect(result).toEqual([expectedArgs1, expectedArgs2]);
  return result;
}

const testListenWithOneArgument = async (module, subscribeFn, eventName, expectedArgs, rawEventPayload) => {
  const result = await new Promise((resolve) => {
    let listenerId = null;

    const notifier = module[`${subscribeFn}`];
    notifier(eventName, (data) => {
      console.log("Listener callback:", data);
      expect(data).toEqual(expectedArgs);
      module.clear(listenerId);
      resolve(data);
    }).then((id) => {
      listenerId = id;
      console.log("Listener ID:", listenerId);
      triggerRaw(rawEventPayload);
    });
  });
  expect(result).toEqual(expectedArgs);
  return result;
}

const testListenWithTwoArguments = async (module, subscribeFn, eventName, expectedArgs1, expectedArgs2, rawEventPayload) => {
  const result = await new Promise((resolve) => {
    let listenerId = null;

    const notifier = module[`${subscribeFn}`];
    notifier(eventName, (data1, data2) => {
      console.log("Listener callback:", data1, data2);
      expect(data1).toEqual(expectedArgs1);
      expect(data2).toEqual(expectedArgs2);
      module.clear(listenerId);
      resolve([data1, data2]);
    }).then((id) => {
      listenerId = id;
      console.log("Listener ID:", listenerId);
      triggerRaw(rawEventPayload);
    });
  });
  expect(result).toEqual([expectedArgs1, expectedArgs2]);
  return result;
}

const testSubscribeWithThreeArguments = async (module, subscribeFn, expectedArgs1, expectedArgs2, expectedArgs3, rawEventPayload) => {
  const result = await new Promise((resolve) => {
    let listenerId = null;

    const notifier = module[`${subscribeFn}`];
    notifier((data1, data2, data3) => {
      console.log("Subscribe callback:", data1, data2, data3);
      expect(data1).toEqual(expectedArgs1);
      expect(data2).toEqual(expectedArgs2);
      expect(data3).toEqual(expectedArgs3);
      module.clear(listenerId);
      resolve([data1, data2, data3]);
    }).then((id) => {
      listenerId = id;
      console.log("Subscribe ID:", listenerId);
      triggerRaw(rawEventPayload);
    });
  });
  expect(result).toEqual([expectedArgs1, expectedArgs2, expectedArgs3]);
  return result;
}

const testListenWithThreeArguments = async (module, subscribeFn, eventName, expectedArgs1, expectedArgs2, expectedArgs3, rawEventPayload) => {
  const result = await new Promise((resolve) => {
    let listenerId = null;

    const notifier = module[`${subscribeFn}`];
    notifier(eventName, (data1, data2, data3) => {
      console.log("Listener callback:", data1, data2, data3);
      expect(data1).toEqual(expectedArgs1);
      expect(data2).toEqual(expectedArgs2);
      expect(data3).toEqual(expectedArgs3);
      module.clear(listenerId);
      resolve([data1, data2, data3]);
    }).then((id) => {
      listenerId = id;
      console.log("Listener ID:", listenerId);
      triggerRaw(rawEventPayload);
    });
  });
  expect(result).toEqual([expectedArgs1, expectedArgs2, expectedArgs3]);
  return result;
}

export {
  testSubscribeWithOneArgument,
  testSubscribeWithTwoArguments,
  testListenWithOneArgument,
  testListenWithTwoArguments,
  testSubscribeWithThreeArguments,
  testListenWithThreeArguments
};