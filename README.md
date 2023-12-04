<p align="center">
<img src="./assets/logo.png" width="75" height="75" /> 
</p>

# Джеджалик

Швидкий компілятор Мавки для вебу.

```c++
#include "jejalyk.cpp"

std::string get_module_name(bool relative, std::string module, jejalyk::JejalykCompilationOptions options) {
    // ...
}

std::string get_module_path(bool relative, std::string module, jejalyk::CompilationOptions options) {
    // ...
}

std::string get_module_code(bool relative, std::string module, jejalyk::CompilationOptions options) {
    // ...
}

std::string get_butintin_module_code(std::string module, jejalyk::CompilationOptions options) {
    // ...
}

std::string get_remote_module_name(std::string module, jejalyk::CompilationOptions options) {
    // ...
}

std::string get_remote_module_pak_path(std::string module, jejalyk::CompilationOptions options) {
    // ...
}

std::string get_remote_module_path(std::string module, jejalyk::CompilationOptions options) {
    // ...
}

std::string get_remote_module_code(std::string module, jejalyk::CompilationOptions options) {
    // ...
}

int main() {
    const auto compilation_options = new jejalyk::CompilationOptions();
    compilation_options->get_module_name = &get_module_name;
    compilation_options->get_module_path = &get_module_path;
    compilation_options->get_module_code = &get_module_code;
    compilation_options->get_butintin_module_code = &get_butintin_module_code;
    compilation_options->get_remote_module_name = &get_remote_module_name;
    compilation_options->get_remote_module_pak_path = &get_remote_module_pak_path;
    compilation_options->get_remote_module_path = &get_remote_module_path;
    compilation_options->get_remote_module_code = &get_remote_module_code;

    const auto result = jejalyk::compile("друк(\"Привіт від Івана!\")", compilation_options);
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