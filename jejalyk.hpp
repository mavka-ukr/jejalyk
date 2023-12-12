#pragma once

#include <string>
#include "parser.hpp"
#include "compiler.hpp"
#include "head.h"

namespace jejalyk {
    inline std::string wrap_run(std::string head, std::string code) {
        return R"(
)" + head + R"(
try{
)" + code + R"(
}catch(e) {
  if(e) {
    if(e instanceof MavkaError){
      if(e.di) {
        console.log(e.di+": "+e.message);
      }else{
        console.log(e.message);
      }
    }else{
      throw e;
    }
  }else{
    throw e;
  }
}
)";
    }

    inline CompilationResult* compile(const std::string& code, CompilationOptions* options) {
        const auto root_scope = new CompilationScope();
        root_scope->store_debug = false;
        root_scope->allow_js = true;
        std::vector<std::string> args = tools::split(options->args, " ");
        for (const auto& arg: args) {
            const auto arg_parts = tools::split(arg, "=");

            if (arg_parts[0] == "--інфо-викликів") {
                root_scope->store_debug = arg_parts[1] == "1";
            }
        }
        const auto compilation_result = new CompilationResult();

        const auto head = "js \"\"\"" + MAVKA_HEAD_JS + "\"\"\"" + "\n" + MAVKA_HEAD_M;

        const auto head_parser_result = mavka::parser::parse(head);
        if (head_parser_result->error) {
            const auto head_compilation_result = new CompilationResult();
            head_compilation_result->error = new CompilationError();
            head_compilation_result->error->line = head_parser_result->error->line;
            head_compilation_result->error->column = head_parser_result->error->column;
            head_compilation_result->error->message = "[ВАДА В ГОЛОВІ :(] " + head_parser_result->error->message;
            return head_compilation_result;
        }
        const auto head_compilation_result = new CompilationResult();
        const auto head_scope = new CompilationScope();
        head_scope->parent = root_scope;
        const auto head_body_compilation_result = jejalyk::compile_body(
            head_parser_result->program_node->body,
            head_scope,
            options,
            false
        );
        if (head_body_compilation_result->error) {
            head_body_compilation_result->error->message =
                    "[ВАДА В ГОЛОВІ :(] " + head_body_compilation_result->error->message;
            head_compilation_result->error = head_body_compilation_result->error;
            return head_compilation_result;
        }
        for (const auto& [name, value]: head_scope->subjects) {
            root_scope->subjects[name] = value;
        }

        if (!options->std_code.empty()) {
            const auto std_parser_result = mavka::parser::parse(options->std_code);
            if (std_parser_result->error) {
                const auto std_compilation_result = new CompilationResult();
                std_compilation_result->error = new CompilationError();
                std_compilation_result->error->line = std_parser_result->error->line;
                std_compilation_result->error->column = std_parser_result->error->column;
                std_compilation_result->error->message = "[ВАДА В STD] " + std_parser_result->error->message;
                return std_compilation_result;
            }
            const auto std_compilation_result = new CompilationResult();
            const auto std_scope = new CompilationScope();
            std_scope->parent = root_scope;
            const auto std_body_compilation_result = jejalyk::compile_body(
                std_parser_result->program_node->body,
                std_scope,
                options,
                false
            );
            if (std_body_compilation_result->error) {
                std_body_compilation_result->error->message =
                        "[ВАДА В STD] " + std_body_compilation_result->error->message;
                std_compilation_result->error = std_body_compilation_result->error;
                return std_compilation_result;
            }
            compilation_result->result = std_body_compilation_result->result;
            for (const auto& [name, value]: std_scope->subjects) {
                root_scope->subjects[name] = value;
            }
        }

        root_scope->allow_js = false;
        for (const auto& arg: args) {
            const auto arg_parts = tools::split(arg, "=");

            if (arg_parts[0] == "--розширення") {
                root_scope->allow_js = arg_parts[1] == "1";
            }
        }

        const auto parser_result = mavka::parser::parse(code);
        if (parser_result->error) {
            compilation_result->error = new CompilationError();
            compilation_result->error->line = parser_result->error->line;
            compilation_result->error->column = parser_result->error->column;
            compilation_result->error->message = parser_result->error->message;
        } else {
            const auto scope = new CompilationScope();
            scope->parent = root_scope;

            const auto body_compilation_result = jejalyk::compile_body(
                parser_result->program_node->body,
                scope,
                options,
                false
            );
            if (body_compilation_result->error) {
                compilation_result->error = body_compilation_result->error;
            } else {
                std::string compiled_di;
                for (const auto di: scope->root()->debug) {
                    compiled_di += "var " + di.first + "=" + di.second + ";";
                }
                std::vector<std::string> compiled_modules;
                for (const auto module: root_scope->modules) {
                    compiled_modules.push_back(module.second);
                }
                const auto compiled_modules_string = tools::implode(compiled_modules, "\n");
                compilation_result->result = wrap_run(
                    compiled_di + "\n" + head_body_compilation_result->result,
                    compilation_result->result + "\n" + compiled_modules_string + "\n" + body_compilation_result->result
                );
            }
        }
        return compilation_result;
    }
}
