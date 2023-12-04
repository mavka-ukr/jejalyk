import Module from "./build/jejalyk_node.js";

global.mavka_compilation_options = {
    root_module_path: "./",
    current_module_path: "./",
    get_module_name: async (relative, module, options) => {
        console.log(relative, module, options);
        return "test";
    },
};

Module().then(async (jejalyk) => {
    const resultJson = await jejalyk.compile(`друк("Привіт!")`);
    const result = JSON.parse(resultJson);
    console.log(result);
});
