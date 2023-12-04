import Module from "./build/jejalyk_wasm.js";

Module().then(async (jejalyk) => {
    console.log(await jejalyk.compile(`
модуль а
кінець
`));
});
