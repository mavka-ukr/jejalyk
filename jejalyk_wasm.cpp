#include <emscripten/bind.h>

#include <string>
#include "nlohmann/json.hpp"
#include "jejalyk.hpp"

using namespace emscripten;

val compilation_options_to_val(jejalyk::CompilationOptions* options) {
    const auto options_val = val::object();
    options_val.set(std::string("root_module_path"), std::string(options->root_module_path));
    options_val.set(std::string("current_module_path"), std::string(options->current_module_path));
    return options_val;
}

std::string get_module_name(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_module_name"];
    const auto answer = mco_module_name(relative, module, compilation_options_to_val(options)).await();
    return answer.as<std::string>();
}

std::string get_module_path(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_module_path"];
    const auto answer = mco_module_name(relative, module, compilation_options_to_val(options)).await();
    return answer.as<std::string>();
}

std::string get_module_code(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_module_code"];
    const auto answer = mco_module_name(relative, module, compilation_options_to_val(options)).await();
    return answer.as<std::string>();
}

std::string get_butintin_module_code(std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_butintin_module_code"];
    const auto answer = mco_module_name(module, compilation_options_to_val(options)).await();
    return answer.as<std::string>();
}

std::string get_remote_module_name(std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_remote_module_name"];
    const auto answer = mco_module_name(module, compilation_options_to_val(options)).await();
    return answer.as<std::string>();
}

std::string get_remote_module_pak_path(std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_remote_module_pak_path"];
    const auto answer = mco_module_name(module, compilation_options_to_val(options)).await();
    return answer.as<std::string>();
}

std::string get_remote_module_path(std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_remote_module_path"];
    const auto answer = mco_module_name(module, compilation_options_to_val(options)).await();
    return answer.as<std::string>();
}

std::string get_remote_module_code(std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_remote_module_code"];
    const auto answer = mco_module_name(module, compilation_options_to_val(options)).await();
    return answer.as<std::string>();
}

std::string compile(std::string code) {
    const auto mco = val::global("mavka_compilation_options");
    const auto options = new jejalyk::CompilationOptions();
    options->root_module_path = mco["root_module_path"].as<std::string>();
    options->current_module_path = mco["current_module_path"].as<std::string>();
    options->get_module_name = &get_module_name;
    options->get_module_path = &get_module_path;
    options->get_module_code = &get_module_code;
    options->get_butintin_module_code = &get_butintin_module_code;
    options->get_remote_module_name = &get_remote_module_name;
    options->get_remote_module_pak_path = &get_remote_module_pak_path;
    options->get_remote_module_path = &get_remote_module_path;
    options->get_remote_module_code = &get_remote_module_code;
    nlohmann::json result;
    const auto compilation_result = jejalyk::compile(code, options);
    if (compilation_result->parser_error) {
        result["error"] = compilation_result->parser_error->message;
    } else {
        result["result"] = compilation_result->result;
    }
    return result.dump();
}

EMSCRIPTEN_BINDINGS (jejalyk_wasm) {
    function("compile", &compile);
}
