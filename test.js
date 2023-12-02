import Module from "./build/jejalyk_node.js";

Module().then(async (jejalyk) => {
    console.log(await jejalyk.compile('друк("привіт!")'));
});
