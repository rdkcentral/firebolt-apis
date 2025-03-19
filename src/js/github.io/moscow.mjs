import nopt from 'nopt'
import path from 'path'
import { readJson, readDir, readFiles, readText, writeFiles, writeText, writeJson } from '../../../node_modules/@firebolt-js/openrpc/src/shared/filesystem.mjs'

const knownOpts = {
    'output': [String],
    'input': [String]
}

const defaultOpts = {
}

const shortHands = {
    'o': '--output',
    'i': '--input'
}
  
// Last 2 arguments are the defaults.
const parsedArgs = Object.assign(defaultOpts, nopt(knownOpts, shortHands, process.argv, 2))

const signOff = () => console.log('\nThis has been a presentation of \x1b[38;5;202mFirebolt\x1b[0m \u{1F525} \u{1F529}\n')

console.dir(parsedArgs)

const specification = await readJson(path.join(parsedArgs.input))
const openrpc = specification.apis["1"]

const capabilities = () => {
    const getOrCreateCapMethodList = (capabilities, c) => capabilities[c] = capabilities[c] || { uses: [], manages: [], provides: [] }
    const capabilities = {}
    openrpc.methods.forEach(method => {
        const caps = method.tags.find(t => t.name === "capabilities");
        (caps['x-uses'] || []).forEach(c => {
          getOrCreateCapMethodList(capabilities, c)
          capabilities[c].uses.push(method.name)
        });
        (caps['x-manages'] || []).forEach(c => {
          getOrCreateCapMethodList(capabilities, c)
          capabilities[c].manages.push(method.name)
        });
        if (caps['x-provides']) {
          const c = caps['x-provides']
          getOrCreateCapMethodList(capabilities, c)
          capabilities[caps['x-provides']].provides.push(method.name)
        }
    })

    Object.entries(specification.capabilities).forEach( ([c, v]) => {
        capabilities[c].level = v.level
    })

    let manifest = ''

    manifest += '\n## Methods\n| | Module | Method | Firebolt Global |\n|-|--|--|--|\n'
    let n = 1
    let module = ''

    const stripOn = x => x.match(/^[a-zA-Z]+\.on[A-Z]/) ? x.split('.')[0] + '.' + x.split('.')[1].substring(2).toLowerCase() + x.split('.')[1].substring(3) : x

    openrpc.methods.sort( ({ name: a }, { name: b }) => { a = stripOn(a); b = stripOn(b); return a < b ? -1 : a > b ? 1 : 0 }).forEach(method => {
        let uses = Object.entries(capabilities).filter( ([c, v]) => v.uses.includes(method.name)).map(([c, v]) => c)
        let mans = Object.entries(capabilities).filter( ([c, v]) => v.manages.includes(method.name)).map(([c, v]) => c)
        let pros = Object.entries(capabilities).filter( ([c, v]) => v.provides.includes(method.name)).map(([c, v]) => c)
        let level = Array.from(new Set(uses.concat(mans).concat(pros).map(c => capabilities[c].level))).join(', ')

        uses = uses.map(c => c.split(':').slice(3, 5).join(':')).map(c => `\`${c}\``).join(', ')
        pros = pros.map(c => c.split(':').slice(3, 5).join(':')).map(c => `\`${c}\``).join(', ')
        mans = mans.map(c => c.split(':').slice(3, 5).join(':')).map(c => `\`${c}\``).join(', ')
        level = level.includes('must') ? 'must' : level.includes('should') ? 'should' : 'could'

        if (uses || pros) {
            console.dir(uses)
            let m = method.name.split('.')[0]
            if (m === module) {
                m = ''
            }
            else
            {
                module = m
            }

            if (method.tags.find(t => t.name === 'deprecated')) {
                level = 'deprecated'
            }

            manifest += `| ${n++} | ${m} | ${method.name.split('.')[1]} | ${level === 'must' ? 'Yes' : 'No'} |\n`
        }

    })

    return manifest
}

// This is the main README, and goes in a few places...
console.log(`Will copy ${path.join('.', 'README.md')} to ${path.join(parsedArgs.output)}`)
const index = frontmatter(await readText(path.join('README.md')), null, null) + capabilities()
writeText(path.join(parsedArgs.output), index)

function channel(version) {
    const parts = version.split("-")

    if (parts.length > 1) {
        parts.shift()
        const chnl = parts.join("-").split(".").shift()
        return chnl
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
