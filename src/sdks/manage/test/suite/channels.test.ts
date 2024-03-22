import { Channels } from "../../build/javascript/src/firebolt-manage";
import { test, expect } from "@jest/globals";


//TODO: rename ScanProgress -> ScanStatus
//TODO: rename percent -> progress

//TODO: add onStop() subscriber 
//TODO: Maybe?? rename stop -> cancel in both temporal-set and progressive-update methods
//TODO, probably want error or event for onStopped()
// add stop scan

Channels.scan()
Channels.status()
Channels.stopScan()

Channels.listen('start', 'complete', 'stop', 'error', 'progress')

Channels.listen('progressUpdate', ()=>{
    // show updates
})

const worker = new Promise( (resolve, reject) => {
    const process:Channels.ScanProcess = Channels.scan()

    let percent = -1
    let updates = 0
    let increasing = true
    let error

    process.onStop( (status:Channels.ScanStatus) => {
        status.progress
        status.data.count
    })

    process.onProgress((status:Channels.ScanStatus) => {
        console.dir(status)
        // assert progress is going up
        increasing = increasing && (status.progress > percent)
        console.log(`${status.progress} > ${percent}: ${increasing}`)
        percent = status.progress
        updates++
    })

    process.onComplete((data:Channels.ScanResult) => {
        console.dir(data)
        resolve({process, percent, updates, increasing, data, error} )
    })

    process.onError((_error:Channels.ScanError) => {
        error = _error
        console.dir(error)
    })

})

test("Channels.scan()", () => {
    return worker.then((result:any) => {
        expect(typeof result.process.onProgress).toBe("function")
        expect(typeof result.process.onComplete).toBe("function")
        expect(typeof result.process.onError).toBe("function")
        expect(typeof result.process.stop).toBe("function")
    
        expect(typeof result.data).toBe("object")
        expect(result.increasing).toBe(true)
        expect(result.updates).toBeGreaterThan(1)
        expect(typeof result.error.code).toBe('number')
    })
  });

test("Channels.onScanProgress()", () => {
    return worker.then((result:any) => {
        expect(result.increasing).toBe(true)
        expect(result.updates).toBeGreaterThan(1)
    })
});

test("Channels.onScanComplete()", () => {
    return worker.then((result:any) => {
        expect(typeof result.data).toBe("object")
    })
});

test("Channels.onScanError()", () => {
    return worker.then((result:any) => {
        expect(typeof result.error.code).toBe('number')
    })
});

test("Channels.stopScan()", () => {
    return worker.then(_ => new Promise((resolve, reject) => {
        const process: Channels.ScanProcess = Channels.scan()
        process.stop()

        let updates = 0
        let complete = false


        setTimeout( _ => {
            expect(updates).toBe(0)
            expect(complete).toBe(false)
            resolve(null)
        }, 1000)

        process.onProgress((status: Channels.ScanStatus) => {
            console.dir(status)
            // assert progress is going up
            updates++
        })

        process.onComplete((data: any) => {
            console.dir(data)
            complete = true
        })

  
    }))
})