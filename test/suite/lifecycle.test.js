import { testHarness } from '../Setup'
import { Lifecycle } from '../../dist/firebolt.js'

let readyResolved = false
let readyCalled = false
let readyMetricCalled = false
let readyMetricCalledAfterResolve = false

testHarness.onSend = function(module, method, params, id) {
    if (module === 'lifecycle' && method === 'ready') {
        readyCalled = true
    }
    else if (module === 'metrics' && method === 'ready') {
        readyMetricCalled = true

        if (readyResolved) {
            readyMetricCalledAfterResolve = true
        }
    }
}

const callback = jest.fn()
const startupState = Lifecycle.state()

beforeAll(()=> {
    Lifecycle.listen((event, _) => {
        callback(event)
    })

    Lifecycle.once('foreground', () => {
        Lifecycle.close('userExit')
    })
    
    Lifecycle.once('unloading', () => {
        Lifecycle.finished()
    })
    
    let p = new Promise( (resolve, reject) => {
        Lifecycle.once('unloading', _ => {
            resolve()
        })
    })

    Lifecycle.ready().then(_ => {
        readyResolved = true
    })

    return p
})

test('Lifecycle.ready Promise resolved', () => {
    expect(readyCalled).toBe(true)
    expect(readyResolved).toBe(true)
})

test('Lifecycle.ready calls Metrics.ready', () => {
    expect(readyMetricCalled).toBe(true)
    expect(readyMetricCalledAfterResolve).toBe(true)
})


test('App starts up in the \'initializing\' state', () => {
    expect(startupState).toBe('initializing')
})

test('App moves to the \'inactive\' state next', () => {
    expect(callback).nthCalledWith(1, 'inactive')
})

test('App moves to the \'foreground\' state next', () => {
    expect(callback).nthCalledWith(2, 'foreground')
})

test('App moves to the \'inactive\' state next', () => {
    expect(callback).nthCalledWith(3, 'inactive')
})

test('App moves to the \'unloading\' state next', () => {
    expect(callback).nthCalledWith(4, 'unloading')
},)
