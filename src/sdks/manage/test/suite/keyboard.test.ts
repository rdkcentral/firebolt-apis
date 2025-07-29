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
import { transport } from '../../../../../test/TransportHarness.js'
import MockTransport from '../../build/javascript/src/Transport/MockTransport.mjs'
import { test, expect, beforeAll } from "@jest/globals";
import { Keyboard, Settings } from "../../build/javascript/src/firebolt-manage";


const standardKeyboardResponse = 'stadard keyboard response';
const passwordKeyboardResponse = 'password keyboard response';
const emailKeyboardResponse = 'email keyboard response';

const standardKeyboardMessage = "Enter your text";
const passwordKeyboardMessage = "Enter your password";
const emailKeyboardMessage = "Enter your email";

var standardKeyboardResponceReceived = false;
var passwordKeyboardResponceReceived = false;
var emailKeyboardResponceReceived = false;

class KBProvider {
  async standard(
    message: string
  ): Promise<string> {
    expect(message).toBe(standardKeyboardMessage);
    return Promise.resolve(standardKeyboardResponse);
  }
  async password(
    message?: string
  ): Promise<string> {
    expect(message).toBe(passwordKeyboardMessage);
    return Promise.resolve(passwordKeyboardResponse);
  }
  async email(
    type: Keyboard.EmailUsage,
    message?: string
  ): Promise<string> {
    expect(type).toBe('signIn');
    expect(message).toBe(emailKeyboardMessage);
    return Promise.resolve(emailKeyboardResponse);
  }
}

class KBProviderWithError implements Keyboard.Keyboard {
  async standard(
    message: string
  ): Promise<string> {
    throw new Error('failed')
  }
  async password(
    message?: string
  ): Promise<string> {
    throw new Error('failed')
  }
  async email(
    type: Keyboard.EmailUsage,
    message?: string
  ): Promise<string> {
    throw new Error('failed')
  }
}

async function testResponseReceived(allResponsesReceived) {

  MockTransport.receiveMessage(
    JSON.stringify({
      jsonrpc: '2.0',
      method: 'Keyboard.standard',
      params: { message: standardKeyboardMessage },
      id: 1,
    })
  );
  MockTransport.receiveMessage(
    JSON.stringify({
      jsonrpc: '2.0',
      method: 'Keyboard.password',
      params: { message: passwordKeyboardMessage },
      id: 2,
    })
  );
  MockTransport.receiveMessage(
    JSON.stringify({
      jsonrpc: '2.0',
      method: 'Keyboard.email',
      params: { type: 'signIn', message: emailKeyboardMessage },
      id: 3,
    })
  );

  // Asynchronously wait for all responses to be received
  await allResponsesReceived;

  expect(standardKeyboardResponceReceived).toBe(true);
  expect(passwordKeyboardResponceReceived).toBe(true);
  expect(emailKeyboardResponceReceived).toBe(true);

};

test('Keyboard.provide() declarations', async () => {

  standardKeyboardResponceReceived = false;
  passwordKeyboardResponceReceived = false;
  emailKeyboardResponceReceived = false;

  Keyboard.provide(new KBProvider());

  // Variables to manage the promise resolution
  let resolveAllResponsesReceived;
  let allResponsesReceived = new Promise((resolve) => {
    resolveAllResponsesReceived = resolve;
  });

  transport.onSend((json) => {
    if (json.method) {
      let [module, method] = json.method.split('.');
      expect(module).toBe('Keyboard');
    }
    //catch the response
    if (json.method == null) {
      if (json.result == standardKeyboardResponse) {
        standardKeyboardResponceReceived = true;
      }
      if (json.result == passwordKeyboardResponse) {
        passwordKeyboardResponceReceived = true;
      }
      if (json.result == emailKeyboardResponse) {
        emailKeyboardResponceReceived = true;
      }

      // Resolve the promise if all expected responses have been received
      if (
        standardKeyboardResponceReceived &&
        passwordKeyboardResponceReceived &&
        emailKeyboardResponceReceived
      ) {
        resolveAllResponsesReceived();
      }
    }
  });

  await testResponseReceived(allResponsesReceived);
});

test("Keyboard.provide() with error response", async () => {

  standardKeyboardResponceReceived = false;
  passwordKeyboardResponceReceived = false;
  emailKeyboardResponceReceived = false;

  Keyboard.provide(new KBProviderWithError());
  // Variables to manage the promise resolution
  let resolveAllResponsesReceived;

  let allResponsesReceived = new Promise((resolve) => {
    resolveAllResponsesReceived = resolve;
  });
  transport.onSend((json) => {
    if (json.method) {
      let [module, method] = json.method.split('.');
      expect(module).toBe('Keyboard');
    }
    //catch the response
    if (json.method == null) {
      // confirm that the error is received
      if (json.error) {
        if (json.id === 1) {
          standardKeyboardResponceReceived = true;
        }
        if (json.id === 2) {
          passwordKeyboardResponceReceived = true;
        }
        if (json.id === 3) {
          emailKeyboardResponceReceived = true;
        }
      }
      // Resolve the promise if all expected responses have been received
      if (
        standardKeyboardResponceReceived &&
        passwordKeyboardResponceReceived &&
        emailKeyboardResponceReceived
      ) {
        resolveAllResponsesReceived();
      }
    }
  });

  await testResponseReceived(allResponsesReceived);
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
