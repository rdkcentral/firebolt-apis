const path = require('path')

/** @type {import('webpack').Configuration} */
module.exports = {
  mode: 'production',
  devtool: 'source-map',
  entry: './build/sdk/javascript/src/index.js',
  experiments: {
    outputModule: true,
  },
  optimization: {
    minimize: false
  },
  output: {
    library: {
      type: 'module'
    },
    filename: 'firebolt.mjs',
    globalObject: 'this',
    path: path.resolve(__dirname, 'dist')
  }
}
