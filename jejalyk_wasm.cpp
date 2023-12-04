#include <emscripten/bind.h>

#include <string>
#include "nlohmann/json.hpp"
#include "jejalyk.hpp"

std::string get_module_name(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    return "lol";
}

std::string compile(std::string code) {
    const auto options = new jejalyk::CompilationOptions();
    options->get_module_name = &get_module_name;
    const auto result = jejalyk::compile(code, options);
    return result->result;
}

std::string fetch_call() {
    emscripten::val fetch = emscripten::val::global("fetch");
    emscripten::val response = fetch(std::string("https://мавка.укр/тачки")).await();
    emscripten::val text = response.call<emscripten::val>("text").await();
    auto answer = text.as<std::string>();
    return answer;
}

EMSCRIPTEN_BINDINGS (jejalyk_wasm) {
    emscripten::function("compile", &compile);
}
