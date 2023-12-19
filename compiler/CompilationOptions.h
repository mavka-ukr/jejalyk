#pragma once

#ifndef COMPILATION_OPTIONS_H
#define COMPILATION_OPTIONS_H

#include <string>

namespace jejalyk {
    class GetModuleResult {
    public:
        std::string error;
        std::string result;
        bool builtin = false;
    };

    class CompilationOptions {
    public:
        CompilationOptions* parent = nullptr;
        std::string root_module_path;
        std::string current_module_path;
        std::string std_code;
        std::string args;
        int body_depth = 0;
        bool allow_js = false;

        GetModuleResult* (*get_module_name)(bool, std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_module_path)(bool, std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_module_code)(bool, std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_remote_module_name)(std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_remote_module_path)(std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_remote_module_code)(std::string, CompilationOptions*) = nullptr;

        CompilationOptions* clone();
    };
}
#endif //COMPILATION_OPTIONS_H