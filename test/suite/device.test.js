import Setup from '../Setup'
import { Device } from '../../dist/firebolt.js'

const version = require('../../version.json')
const foo = require('../../package.json')

test(`Device.version() to be ${version.major}.${version.minor}.${version.patch}`, () => {
    return Device.version().then( v => {
        expect(v.sdk.major).toBe(version.major)
        expect(v.sdk.minor).toBe(version.minor)
        expect(v.sdk.patch).toBe(version.patch)
    })
});

test(`package.json version to be ${version.major}.${version.minor}.${version.patch}`, () => {
    expect(parseInt(foo.version.split('.')[0])).toBe(version.major)
    expect(parseInt(foo.version.split('.')[1])).toBe(version.minor)
    expect(parseInt(foo.version.split('.')[2])).toBe(version.patch)
});