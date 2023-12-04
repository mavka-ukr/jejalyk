<img src="./assets/logo.png" width="75" height="75" /> 

# Джеджалик

Швидкий компілятор Мавки для вебу.

## Вимоги

- C++20
- Emscripten
- CMake
- Make
- Node.js

## Будування

```shell
./build.sh antl4 # antlr4 grammar
```

```shell
./build.sh node # node wasm
```

```shell
./build.sh web # web wasm
```

```shell
./build.sh all # web and node wasm
```

```shell
./build.sh Onode # optimized node wasm
```

```shell
./build.sh Oweb # optimized web wasm
```

```shell
./build.sh Oall # optimized web and optimized node wasm
```

## Використання

### C++

```c++
#include <string>
#include "jejalyk.cpp"

std::string get_module_name(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_module_path(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_module_code(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_butintin_module_code(std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_remote_module_name(std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_remote_module_pak_path(std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_remote_module_path(std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_remote_module_code(std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

int main() {
    const auto options = new jejalyk::CompilationOptions();
    options->root_module_path = "";
    options->current_module_path = "";
    options->get_module_name = &get_module_name;
    options->get_module_path = &get_module_path;
    options->get_module_code = &get_module_code;
    options->get_butintin_module_code = &get_butintin_module_code;
    options->get_remote_module_name = &get_remote_module_name;
    options->get_remote_module_pak_path = &get_remote_module_pak_path;
    options->get_remote_module_path = &get_remote_module_path;
    options->get_remote_module_code = &get_remote_module_code;

    const auto result = jejalyk::compile("друк(\"Привіт від Івана!\")", options);
    if (result->parser_error) {
        std::cout << result->parser_error->message << std::endl;
    } else if (result->error) {
        std::cout << result->error->message << std::endl;
    } else {
        std::cout << result->result << std::endl;
    }

    return 0;
}
```

### JavaScript

```javascript
import Module from "./build/jejalyk_node.js";

global.mavka_compilation_options = {
    root_module_path: "./",
    current_module_path: "./",
    get_module_name: async (relative, module, options) => {
        return "";
    },
    // ...
};

Module().then(async (jejalyk) => {
    const resultJson = await jejalyk.compile(`друк("Привіт від Івана!")`);
    const result = JSON.parse(resultJson);
    console.log(result);
});
```