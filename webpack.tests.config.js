const path = require('path')
const glob = require('glob')

/** @type {import('webpack').Configuration} */
module.exports = {
  mode: 'production',
  entry: glob.sync("./test/suite/*.js"),
  module: {
    rules: [
      {
        test: /\.m?js$/,
        use: {
          loader: 'babel-loader',
          options: {
            presets: ['@babel/preset-env']
          }
        }
      }
    ],
  },
  output: {
    filename: 'firebolt.tests.js',
    path: path.resolve(__dirname, 'build'),
    globalObject: 'window',
    library: {
      name: 'Firebolt',
      type: 'window',
    }
  }
}
