#include <emscripten.h>
#include <emscripten/bind.h>

#include <string>
#include "jejalyk.hpp"

using namespace emscripten;

val compilation_options_to_val(jejalyk::CompilationOptions* options) {
    const auto options_val = val::object();
    options_val.set(std::string("root_module_path"), std::string(options->root_module_path));
    options_val.set(std::string("current_module_path"), std::string(options->current_module_path));
    return options_val;
}

val compilation_error_to_val(jejalyk::CompilationError* error) {
    const auto error_val = val::object();
    error_val.set(std::string("line"), error->line);
    error_val.set(std::string("column"), error->column);
    error_val.set(std::string("message"), std::string(error->message));
    return error_val;
}

jejalyk::GetModuleResult* val_to_get_module_result(val result) {
    const auto get_module_result = new jejalyk::GetModuleResult();
    get_module_result->error = result["error"].as<std::string>();
    get_module_result->result = result["result"].as<std::string>();
    get_module_result->builtin = result["buitlin"].as<bool>();
    return get_module_result;
}

jejalyk::GetModuleResult* get_module_name(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_module_name"];
    const auto answer = mco_module_name(relative, module, compilation_options_to_val(options)).await();
    return val_to_get_module_result(answer);
}

jejalyk::GetModuleResult* get_module_path(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_module_path"];
    const auto answer = mco_module_name(relative, module, compilation_options_to_val(options)).await();
    return val_to_get_module_result(answer);
}

jejalyk::GetModuleResult* get_module_code(bool relative, std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_module_code"];
    const auto answer = mco_module_name(relative, module, compilation_options_to_val(options)).await();
    return val_to_get_module_result(answer);
}

jejalyk::GetModuleResult* get_remote_module_name(std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_remote_module_name"];
    const auto answer = mco_module_name(module, compilation_options_to_val(options)).await();
    return val_to_get_module_result(answer);
}

jejalyk::GetModuleResult* get_remote_module_path(std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_remote_module_path"];
    const auto answer = mco_module_name(module, compilation_options_to_val(options)).await();
    return val_to_get_module_result(answer);
}

jejalyk::GetModuleResult* get_remote_module_code(std::string module, jejalyk::CompilationOptions* options) {
    const auto mco = val::global("mavka_compilation_options");
    const auto mco_module_name = mco["get_remote_module_code"];
    const auto answer = mco_module_name(module, compilation_options_to_val(options)).await();
    return val_to_get_module_result(answer);
}

val compile(std::string code) {
    const auto mco = val::global("mavka_compilation_options");
    const auto options = new jejalyk::CompilationOptions();
    options->args = mco["args"].as<std::string>();
    options->std_code = mco["std_code"].as<std::string>();
    options->root_module_path = mco["root_module_path"].as<std::string>();
    options->current_module_path = mco["current_module_path"].as<std::string>();
    options->get_module_name = &get_module_name;
    options->get_module_path = &get_module_path;
    options->get_module_code = &get_module_code;
    options->get_remote_module_name = &get_remote_module_name;
    options->get_remote_module_path = &get_remote_module_path;
    options->get_remote_module_code = &get_remote_module_code;

    val result = val::object();
    const auto compilation_result = jejalyk::compile(code, options);
    if (compilation_result->error) {
        result.set(std::string("error"), compilation_error_to_val(compilation_result->error));
    } else {
        result.set(std::string("result"), std::string(compilation_result->result));
    }
    return result;
}

EMSCRIPTEN_BINDINGS (jejalyk_wasm) {
    function("compile", &compile, allow_raw_pointers());
}
