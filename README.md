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

jejalyk::GetModuleResult* get_module_name(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

jejalyk::GetModuleResult* get_module_path(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

jejalyk::GetModuleResult* get_module_code(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    // ...
}

jejalyk::GetModuleResult* get_pak(std::string name, std::string version, std::string as, jejalyk::CompilationOptions* options) {
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
    options->get_pak = &get_pak;

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
  main_module_path: "",
  root_module_path: "",
  current_module_path: "",
  get_module_name: async (relative, module, options) => {
    return { error: "", result: "" };
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
    main_module_path: "",
    root_module_path: "",
    current_module_path: "",
    get_module_name: async (relative, module, options) => {
      return { error: "", result: "" };
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

```shell
./build.sh node # node wasm
```

```shell
./build.sh web # web wasm
```

```shell
./build.sh all # node wasm and web wasm
```

```shell
./build.sh Onode # optimized node wasm
```

```shell
./build.sh Oweb # optimized web wasm
```

```shell
./build.sh Oall # optimized node wasm and optimized web wasm
```

```shell
./dist.sh # release (node and web)
```

### Використання

Після побудови випускової версії через dist.sh ви можете потестувати пакет виконавши цю команду в теці з проектом:

```shell
npm i -g .
```

У вас встановиться локальний пакет джеджалика, який ви можете використовувати як звичайний, встановлений з npm. Майте наувазі, що випускову версію через dist.sh ви будуєте в себе для тестування. А от для PR вам треба залишити теку dist незмінною. Будь ласка, перед відправкою PR впевніться, що тека dist не змінилась.
