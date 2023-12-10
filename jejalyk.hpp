#pragma once

#include <string>
#include "parser.hpp"
#include "compiler.hpp"
#include "head.h"

namespace jejalyk {
    inline CompilationResult* compile(const std::string& code, CompilationOptions* options) {
        const auto root_scope = new CompilationScope();
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
        compilation_result->result = head_body_compilation_result->result;
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
            compilation_result->result = compilation_result->result + "\n" + std_body_compilation_result->result;
            for (const auto& [name, value]: std_scope->subjects) {
                root_scope->subjects[name] = value;
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
                compilation_result->result = "(async function(){\n" + compilation_result->result + "\n" + body_compilation_result->result + "\n})()";
            }
        }
        return compilation_result;
    }
}
