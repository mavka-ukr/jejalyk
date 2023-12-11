<img src="./assets/logo.png" width="75" height="75" /> 

# Джеджалик

Швидкий компілятор Мавки в JavaScript.

## Використання

[//]: # (### Термінал)

[//]: # ()

[//]: # (```shell)

[//]: # (./build/джеджалик тест.м тест.js)

[//]: # (```)

### C++

```c++
#include <string>
#include "jejalyk.hpp"

std::string get_module_name(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_module_path(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_module_code(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

std::string get_remote_module_name(std::string module, jejalyk::CompilationOptions* options) {
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
    options->args = "";
    options->std_code = "";
    options->root_module_path = "";
    options->current_module_path = "";
    options->get_module_name = &get_module_name;
    options->get_module_path = &get_module_path;
    options->get_module_code = &get_module_code;
    options->get_remote_module_name = &get_remote_module_name;
    options->get_remote_module_path = &get_remote_module_path;
    options->get_remote_module_code = &get_remote_module_code;

    const auto result = jejalyk::compile("друк(\"Привіт від Івана!\")", options);
    if (result->error) {
        std::cout << result->error->message << std::endl;
    } else {
        std::cout << result->result << std::endl;
    }

    return 0;
}
```

### Node.js

```html
npm i jejalyk
```

```javascript
import Module from "jejalyk/node";

global.mavka_compilation_options = {
  args: "",
  std_code: "",
  root_module_path: "",
  current_module_path: "",
  get_module_name: async (relative, module, options) => {
    return "";
  },
  // ...
};

Module().then(async (jejalyk) => {
  const result = await jejalyk.compile(`друк("Привіт від Івана!")`);
  console.log(result);
});
```

### Web

```html

<script src="./dist/optimized_jejalyk_web.js"></script>
<script>
  window.mavka_compilation_options = {
    args: "",
    std_code: "",
    root_module_path: "",
    current_module_path: "",
    get_module_name: async (relative, module, options) => {
      return "";
    },
    // ...
  };

  Module.onRuntimeInitialized = async () => {
    const result = await Module.compile(`друк("Привіт від Івана!")`);
    console.log(result);
  };
</script>
```

## Розробка

### Вимоги

- C++20
- CMake
- Make
- Node.js
- Emscripten
- Java (для ANTLR4)

### Початок

```
git clone https://github.com/mavka-ukr/jejalyk
cd jejalyk
npm install
```

### Будування

```shell
./build.sh antlr4 # antlr4 grammar
```

[//]: # (```shell)

[//]: # (./build.sh bin # executable)

[//]: # (```)

```shell
./build.sh node # node wasm
```

```shell
./build.sh web # web wasm
```

```shell
./build.sh all # executable and node wasm and web wasm
```

[//]: # (```shell)

[//]: # (./build.sh Obin # optimized executable)

[//]: # (```)

```shell
./build.sh Onode # optimized node wasm
```

```shell
./build.sh Oweb # optimized web wasm
```

```shell
./build.sh Oall # optimized executable and optimized node wasm and optimized web wasm
```

```shell
./dist.sh # optimized dist (node and web)
```
