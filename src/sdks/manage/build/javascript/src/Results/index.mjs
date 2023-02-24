import Transport from "../Transport/index.mjs"

/*
methods = Map<string, {
    x-this-param: 'accessory',
    x-additional-params: ['timeout'],
    x-method: 'Accessory.pair'
}>
*/

function transform(result, transforms) {

    if (!transforms || !transforms.methods) {
        return result
    }

    const { methods } = transforms
    const transformed = JSON.parse(JSON.stringify(result))

    Object.keys(methods).forEach(key => {
        const method_info = methods[key]
        const rpc_method = method_info['x-method']
        const [module, method] = rpc_method.split('.')
        const params = {}
        params[method_info['x-this-param']] = transformed
        transformed[key] = (...args) => {
            // copy the args into the correct RPC param names
            for (var i=0; i<args.length; i++) {
                params[method_info['x-additional-params'][i]] = args[i]
            }
            return Transport.send(module.toLowerCase(), method, params)
        }
    })
    return transformed
}

export default {
    transform
}