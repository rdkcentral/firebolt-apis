import nopt from 'nopt'
import path from 'path'
import { readJson, readDir, readFiles, readText, writeFiles, writeText, writeJson } from '../../../node_modules/@firebolt-js/openrpc/src/shared/filesystem.mjs'

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
const version = channel(packageJson.version)
const requirements = await readFiles(await readDir(path.join('.', 'requirements'), { recursive: true }), path.join('.', 'requirements'))

const processFiles = (docs, base, dir, subdir, category, setType) => {
    Object.keys(docs).forEach(ref => {
        let data = docs[ref]
        const source = ref
        delete docs[ref]
        let type = ''

        if (setType && category === 'requirements') {
            const parts = ref.split(path.sep)
            if (parts.length >= 3) {
                type = ref.split(path.sep)[1].replace(/.$/,'');
            }
        }

        if (ref.endsWith('.md')) {
            const filename = ref.split(path.sep).pop()
            if (filename !== 'index.md') {
                const dirname = filename.split('.').shift()
                const parts = ['index.md']
                // if the dirname is the same as parent dir, don't insert it
                if (dirname != ref.split(path.sep).slice(-2, -1)[0]) {
                    parts.unshift(dirname)
                    data = data.replace(/\]\(\.\.\//g, '](../../')
                    data = data.replace(/\]\(\.\//g, '](../')
                }
                data = data.replace(/\]\((.*?)\.md([\)#])/g, ']($1$2')
                data = data.replace(/\]\((.*?)\/(.*?)\/\2([\)#])/g, ']($1/$2$3')
            ref = ref.split(path.sep).slice(0, -1).concat(parts).join(path.sep)
            }

            docs[path.join(parsedArgs.output, dir, version, subdir, ref)] = frontmatter(data, version, subdir, category, type)
        }
        else {
            docs[path.join(parsedArgs.output, dir, version, subdir, ref)] = data
        }
    
        console.log(`Will copy ${path.join(base, source)} to ${path.join(parsedArgs.output, dir, version, subdir, ref)}`)
    
        if (version === 'latest') {
            if (ref.endsWith('.md')) {
                docs[path.join(parsedArgs.output, dir, packageJson.version, subdir, ref)] = frontmatter(data, packageJson.version, subdir, category, type)
            }
            else {
                docs[path.join(parsedArgs.output, dir, packageJson.version, subdir, ref)] = data
            }
            console.log(`Will copy ${path.join(base, source)} to ${path.join(parsedArgs.output, dir, packageJson.version, subdir, ref)}`)
        }    
    })
}

processFiles(requirements, path.join('.', 'requirements'), 'requirements', '', 'requirements', true)
writeFiles(requirements)

packageJson.workspaces.forEach(async workspace => {
    const docs = await readFiles(await readDir(path.join(workspace, 'build', 'docs', 'markdown'), { recursive: true }), path.join(workspace, 'build', 'docs', 'markdown'))

    docs['index.md'] = (await readText(path.join(workspace, 'README.md')))
    docs['changelog.md'] = '---\ntitle: Change Log\n---\n' + (await readText(path.join(workspace, 'CHANGELOG.md')))

    // point to new output location
    processFiles(docs, path.join(workspace, 'build', 'docs', 'markdown'), 'apis', workspace.split(path.sep).pop())

    writeFiles(docs)
})

// This is the main README, and goes in a few places...
console.log(`Will copy ${path.join('.', 'README.md')} to ${path.join(parsedArgs.output, 'apis', 'index.md')}`)
const index = frontmatter(await readText(path.join('README.md')), null, null)
writeText(path.join(parsedArgs.output, 'apis', 'index.md'), index)
if (version === 'latest') {
    console.log(`Will copy ${path.join('.', 'README.md')} to ${path.join(parsedArgs.output, packageJson.version, 'index.md')}`)
    writeText(path.join(parsedArgs.output, 'apis', packageJson.version, 'index.md'), index)
}

// this is the firebolt spec JSON
const specification = await readJson(path.join('dist', 'firebolt-specification.json'))
writeJson(path.join(parsedArgs.output, 'requirements', version, 'specifications', 'firebolt-specification.json'), specification)
if (version === 'latest') {
    writeJson(path.join(parsedArgs.output, 'requirements', packageJson.version, 'specifications', 'firebolt-specification.json'), specification)
}

// this is the firebolt OpenRPC spec JSON
const openrpc = await readJson(path.join('dist', 'firebolt-open-rpc.json'))
writeJson(path.join(parsedArgs.output, 'requirements', version, 'specifications', 'firebolt-open-rpc.json'), openrpc)
if (version === 'latest') {
    writeJson(path.join(parsedArgs.output, 'requirements', packageJson.version, 'specifications', 'firebolt-open-rpc.json'), openrpc)
}

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

function frontmatter(data, version, sdk, category, type) {
    let matter = ''
    if (data.startsWith('---')) {
        matter = data = data.substring(4)
        matter = data.substring(0, data.indexOf('---'))
        data = data.substring(data.indexOf('---')+4)
    }

    matter = '---\n' + matter + '\n'

    if (version && matter.indexOf('Version:') === -1) {
        matter += `version: ${version}\n`
    }

    if (matter.indexOf('layout:') === -1) {
        matter += `layout: default\n`
    }

    if (matter.toLowerCase().indexOf('title:') === -1) {
        matter += `title: ${data.match(/\# (.*?)\n/)[1]}\n`
    }

    if (sdk && matter.indexOf('sdk:') === -1) {
        matter += `sdk: ${sdk}\n`
    }

    if (category && matter.indexOf('category:') === -1) {
        matter += `category: ${category}\n`
    }

    if (type && matter.indexOf('type:') === -1) {
        matter += `type: ${type}\n`
    }

    matter += '---\n'

    return matter + data.replace(/\<details(.*?)\>/g, '<details markdown="1" $1>')
}

signOff()
