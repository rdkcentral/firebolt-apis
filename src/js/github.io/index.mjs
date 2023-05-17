import nopt from 'nopt'
import path from 'path'
import { readJson, readDir, readFiles, readText, writeFiles, writeText } from '../../../node_modules/@firebolt-js/openrpc/src/shared/filesystem.mjs'

const knownOpts = {
    'output': [String]
}

const defaultOpts = {
}

const shortHands = {
    'o': '--output'
}
  
// Last 2 arguments are the defaults.
const parsedArgs = Object.assign(defaultOpts, nopt(knownOpts, shortHands, process.argv, 2))

const signOff = () => console.log('\nThis has been a presentation of \x1b[38;5;202mFirebolt\x1b[0m \u{1F525} \u{1F529}\n')

const packageJson = await readJson(process.env.npm_package_json)

packageJson.workspaces.forEach(async workspace => {
    const docs = await readFiles(await readDir(path.join(workspace, 'build', 'docs', 'markdown'), { recursive: true }), path.join(workspace, 'build', 'docs', 'markdown'))
    Object.entries(docs).forEach( ([path, data]) => {
        data = frontmatter(path, data, packageJson) + '\n' + data
    })

    docs['index.md'] = (await readText(path.join(workspace, 'README.md')))
    docs['changelog.md'] = '---\ntitle: Change Log\n---' + (await readText(path.join(workspace, 'CHANGELOG.md')))

    // point to new output location
    Object.keys(docs).forEach(ref => {
        const version = channel(packageJson.version)
        const data = docs[ref]
        const sdk = workspace.split(path.sep).pop()
        delete docs[ref]
        docs[path.join(parsedArgs.output, version, sdk, ref)] = frontmatter(data, version, sdk)

        if (version === 'latest') {
            docs[path.join(parsedArgs.output, packageJson.version, sdk, ref)] = frontmatter(data, packageJson.version, sdk)
        }
    })

    writeFiles(docs)
})

const index = frontmatter(await readText(path.join('README.md')), null, null)
writeText(path.join(parsedArgs.output, 'index.md'), index)

function channel(version) {
    const parts = version.split("-")

    if (parts.length > 1) {
        parts.shift()
        const chnl = parts.join("-").split(".").shift()

        if (['next', 'next-major', 'test'].includes(chnl)) {
            return chnl
        }
        else {
            return 'test'
        }
    }
    else {
        return 'latest'
    }
}

function frontmatter(data, version, sdk) {
    let matter = ''
    if (data.startsWith('---')) {
        matter = data = data.substring(4)
        matter = data.substring(0, data.indexOf('---'))
        data = data.substring(data.indexOf('---')+4)
    }

    matter = '---\n' + matter + '\n'

    if (matter.indexOf('title:') === -1) {
        matter += `title: Title\n`
    }

    if (version && matter.indexOf('Version:') === -1) {
        matter += `version: ${version}\n`
    }

    if (matter.indexOf('layout:') === -1) {
        matter += `layout: default\n`
    }

    if (sdk && matter.indexOf('sdk:') === -1) {
        matter += `sdk: ${sdk}\n`
    }

    matter += '---\n'

    return matter + data
}

signOff()
