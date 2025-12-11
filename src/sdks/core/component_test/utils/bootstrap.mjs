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

// bootstrap.mjs
// This file should be imported first in the main entry point.

if (typeof global !== 'undefined' && !global.window) {
  // Create a mock window object on the global scope
  global.window = {};
}

// Set properties on this mock window object
global.window.__firebolt = global.window.__firebolt || {};
global.window.__firebolt.endpoint = process.env.FIREBOLT_ENDPOINT || 'ws://localhost:9998';

console.info(`[bootstrap.mjs] Global window setup complete. Endpoint: ${global.window.__firebolt.endpoint}`);