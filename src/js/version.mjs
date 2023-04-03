#!/usr/bin/env node

import { readFile, writeFile } from 'fs/promises'
import path from 'path'

process.argv.shift()
process.argv.shift()

const task = process.argv.shift()

if (task === 'sync') {
    const packageMain = await readFile(path.join('.', 'package.json'))
        .then(bytes => bytes.toString())
        .then(JSON.parse)
    
    console.log()
    
    await Promise.all(packageMain.workspaces.map(async workspace => {
        console.log(`Updating ${workspace}/package.json to version ${packageMain.version}.`)
        const packageWorkspace = await readFile(path.join('.', workspace, 'package.json'))
            .then(bytes => bytes.toString())
            .then(JSON.parse)
        packageWorkspace.version = packageMain.version
        return writeFile(path.join('.', workspace, 'package.json'), JSON.stringify(packageWorkspace, null, '\t'))
    }))

    console.log()
}
else if (task === 'channel') {
    const branch = process.argv.shift()
    const releaserc = await readFile(path.join('.', '.releaserc'))
                            .then(bytes => bytes.toString())
                            .then(JSON.parse)

    const config = releaserc.branches.find(b => b.name === branch) || { channel: 'test' }

    console.log(config.channel)
}
