const jejalyk = require("./build/jejalyk.js")

jejalyk.onRuntimeInitialized = () => {
    const compile = jejalyk.cwrap('compile', 'string', ['string'])
    console.log(compile("привіт"));
}