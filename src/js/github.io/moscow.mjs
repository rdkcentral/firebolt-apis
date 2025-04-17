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
const openrpc = await readJson(path.join(path.dirname(parsedArgs.input), 'firebolt-core-open-rpc.json')) //specification.apis["1"]

const capabilities = () => {
    const getOrCreateCapMethodList = (capabilities, c) => capabilities[c] = capabilities[c] || { uses: [], manages: [], provides: [] }
    const capabilities = {}
    openrpc.methods.sort((a, b) => {
        const nameA = a.name.toUpperCase();
        const nameB = b.name.toUpperCase();
        if (nameA < nameB) {
          return -1;
        }
        if (nameA > nameB) {
          return 1;
        }
        return 0;
      }).forEach(method => {
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
        capabilities[c] = capabilities[c] || { uses: [], manages: [], provides: []}
        capabilities[c].level = v.level
    })

    let manifest = ',Module,Method,Required\n'
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

            manifest += `${n++},${m},${method.name.split('.')[1]},${level === 'must' ? 'Yes' : 'No'}\n`
        }

    })

    return manifest
}

const index = capabilities()

writeText(path.join(parsedArgs.output), index)

signOff()
