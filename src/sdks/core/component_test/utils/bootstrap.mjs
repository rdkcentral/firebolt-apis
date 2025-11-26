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