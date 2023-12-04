#include <emscripten/bind.h>

#include <string>
#include "nlohmann/json.hpp""
#include "jejalyk.cpp"

std::string compile_wasm(std::string code) {
    return compile(code);
}

std::string fetch_call() {
    emscripten::val fetch = emscripten::val::global("fetch");
    emscripten::val response = fetch(std::string("https://мавка.укр/тачки")).await();
    emscripten::val text = response.call<emscripten::val>("text").await();
    auto answer = text.as<std::string>();
    return answer;
}

EMSCRIPTEN_BINDINGS (jejalyk_wasm) {
    emscripten::function("compile", &compile_wasm);
}
