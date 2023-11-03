const jejalyk = require("./build/jejalyk.js")

jejalyk.onRuntimeInitialized = () => {
    const compile = jejalyk.cwrap("compile", "string", ["string"]);
    const code = "test";
    const result = JSON.parse(compile(code));
    console.log(result);
}