import nopt from 'nopt'
import path from 'path'
import { readJson, readDir, readFiles, readText, writeFiles, writeText, writeJson } from '../../../node_modules/@firebolt-js/openrpc/src/shared/filesystem.mjs'

const knownOpts = {
    'file': [String]
}

const defaultOpts = {
}

const shortHands = {
    'f': '--file'
}
  
// Last 2 arguments are the defaults.
const parsedArgs = Object.assign(defaultOpts, nopt(knownOpts, shortHands, process.argv, 2))

const signOff = () => console.log('\nThis has been a presentation of \x1b[38;5;202mFirebolt\x1b[0m \u{1F525} \u{1F529}\n')

//const packageJson = await readJson(process.env.npm_package_json)
//const version = channel(packageJson.version)
const requirements = await readFiles(await readDir(path.join('.', 'requirements'), { recursive: true }), path.join('.'))

const processFiles = (docs) => {
    Object.keys(docs).forEach(ref => {

        if (ref.endsWith('.md')) {
            let data = docs[ref]

//            console.log(data)
            // find all headers
            const headers = data.match(/#+[ \t]+(([0-9]+\.)+)[ /t]+(.*?)\n/g)
    
            // turn to slugs
            const slugs = headers.map(h => h.replace(/#/g, ''))
                            .map(h => h.replace(/\t/g, ''))
                            .map(h => h.replace(/\./g, ''))
                            .map(h => h.replace(/^ /g, ''))
                            .map(h => h.replace(/\n$/g, ''))
                            .map(h => h.replace(/ /g, '-'))
                            .map(h => h.toLowerCase())
                            .map(h => '#' + h)

            const links = data.match(/\]\(.*?\#.*?\)/g)

            links.map(l => l.slice(2, -1)).forEach(link => {
                if (!slugs.find(s => s === link)) {
                    const best = slugs.find(s => s.match(new RegExp(link.replace(/^\#[0-9]+/, '#[0-9]+')))) || slugs.find(s => s.startsWith(link.split('-')[0] + '-'))
                    console.log('Fixing broken link: (' + link + ') -> (' + best + ')')
                    data = data.replace('](' + link + ')', '](' + best + ')')
                }
            })    
            docs[ref] = data
        }
    })
}

processFiles(requirements)
writeFiles(requirements)

signOff()
