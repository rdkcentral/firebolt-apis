/*
 * Copyright 2021 Comcast Cable Communications Management, LLC
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

import { test, expect, beforeAll } from "@jest/globals";
import { Keyboard, Settings } from "../../src/sdks/manage/build/javascript/src/firebolt-manage";

const state = {
  cb: null,
  eventId: null,
  pending: [],
  id: 0
}

class MockProviderBroker {

  constructor() {
  }

  send(parsed) {
    if (parsed.method === 'Keyboard.provide') {
      // do we do anything?
    }
    let pending = state.pending.find(p => p.id === parsed.id)
    if (pending) {
      state.pending = state.pending.filter(p => p.id === parsed.id)
      pending.callback(parsed)
    }
  }

  receive(callback) {
    state.cb = callback
  }

  async triggerProvider(msg, providerCallback) {
    state.id++
    let fullMsg = {
      jsonrpc: '2.0',
      id: state.id,
      method: "Keyboard.standard",
      params: msg
    }

    state.pending.push({
      id: state.id,
      callback: providerCallback
    })
    state.cb(fullMsg)
  }
}
const broker = new MockProviderBroker()
let provider = null

beforeAll(async () => {
  window['__firebolt'].transport = new MockProviderBroker()
  Settings.setLogLevel('DEBUG')
  provider = new DelegatingKBProvider(new KBProvider())
  Keyboard.provide(provider);
})

class DelegatingKBProvider implements Keyboard.Keyboard {
  delegate: Keyboard.Keyboard;
  
  constructor(delegate: Keyboard.Keyboard) {
    this.delegate = delegate;
  }

  standard(message: string): Promise<string> {
    return this.delegate.standard(message)
  }
  password(message: string): Promise<string> {
    return this.delegate.password(message)
  }
  email(type: Keyboard.EmailUsage, message: string): Promise<string> {
    return this.delegate.email(type, message)
  }
}

class KBProvider implements Keyboard.Keyboard {
  standard(message: string): Promise<string> {
    return Promise.resolve('foo');
  }
  password(message: string): Promise<string> {
    return Promise.resolve(null);
  }
  email(type: Keyboard.EmailUsage, message: string): Promise<string> {
    return Promise.resolve(null);
  }
}

class KBProviderWithError implements Keyboard.Keyboard {
  standard(message: string): Promise<string> {
    throw { message: 'failed', code: 1000} //new Error('failed')
  }
  password(message: string): Promise<string> {
    throw { message: 'failed', code: 1000} //new Error('failed')
  }
  email(type: Keyboard.EmailUsage, message: string): Promise<string> {
    throw { message: 'failed', code: 1000} //new Error('failed')
  }
}

test("Keyboard.provide() declarations", async () => {
  let callback = null;
  let promise: Promise<any> = new Promise((resolve, reject) => {
    callback = resolve
  })
  provider.delegate = new KBProvider()
  broker.triggerProvider({
    message: 'Enter name'
  }, callback)
  let result = await promise
  expect(result.result).toStrictEqual('foo')
});

test("Keyboard.provide() with error response", async () => {
  let callback = null;
  let promise: Promise<any> = new Promise((resolve, reject) => {
    callback = resolve
  })
  provider.delegate = new KBProviderWithError()
  broker.triggerProvider({
    message: 'Enter name'
  }, callback)
  let result = await promise
  expect(result.error.message).toStrictEqual('failed')
  expect(result.error.code).toStrictEqual(1000)
});

// Events Test cases

// test("Keyboard.listen() for requestEmail event", () => {
//   return Keyboard.listen("requestEmail", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.once() for requestEmail event", () => {
//   return Keyboard.once("requestEmail", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.listen() for requestPassword event", () => {
//   return Keyboard.listen("requestPassword", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.once() for requestPassword event", () => {
//   return Keyboard.once("requestPassword", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.listen() for requestStandard event", () => {
//   return Keyboard.listen("requestStandard", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.once() for requestStandard event", () => {
//   return Keyboard.once("requestStandard", () => {}).then((res: number) => {
//     expect(res > 0).toBe(true);
//   });
// });

// test("Keyboard.clear()", () => {
//   const result = Keyboard.clear(2);
//   expect(result).toBeFalsy();
// });
