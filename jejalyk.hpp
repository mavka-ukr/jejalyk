#pragma once

#include <string>
#include "parser.hpp"
#include "compiler.hpp"

namespace jejalyk {
    const std::string head = R"(
макет структура пусто
кінець

макет структура число
кінець

макет структура текст
кінець

макет структура логічне
кінець

макет структура Дія
кінець

макет структура Модуль
кінець

макет субʼєкт так логічне
макет субʼєкт ні логічне
)";

    inline CompilationResult* compile(const std::string& code, CompilationOptions* options) {
        const auto root_scope = new CompilationScope();

        const auto head_parser_result = mavka::parser::parse(head);
        if (head_parser_result->error) {
            const auto compilation_result = new CompilationResult();
            compilation_result->error = new CompilationError();
            compilation_result->error->line = head_parser_result->error->line;
            compilation_result->error->column = head_parser_result->error->column;
            compilation_result->error->message = "[ВАДА В ГОЛОВІ :(] " + head_parser_result->error->message;
            return compilation_result;
        }
        const auto head_compilation_result = new CompilationResult();
        const auto head_body_compilation_result = jejalyk::compile_body(
            head_parser_result->program_node->body,
            root_scope,
            options,
            false
        );
        if (head_body_compilation_result->error) {
            head_body_compilation_result->error->message =
                    "[ВАДА В ГОЛОВІ :(] " + head_body_compilation_result->error->message;
            head_compilation_result->error = head_body_compilation_result->error;
            return head_compilation_result;
        }

        if (!options->std_code.empty()) {
            const auto std_parser_result = mavka::parser::parse(options->std_code);
            if (std_parser_result->error) {
                const auto compilation_result = new CompilationResult();
                compilation_result->error = new CompilationError();
                compilation_result->error->line = std_parser_result->error->line;
                compilation_result->error->column = std_parser_result->error->column;
                compilation_result->error->message = "[ВАДА В STD] " + std_parser_result->error->message;
                return compilation_result;
            }
            const auto std_compilation_result = new CompilationResult();
            const auto std_body_compilation_result = jejalyk::compile_body(
                std_parser_result->program_node->body,
                root_scope,
                options,
                false
            );
            if (std_body_compilation_result->error) {
                std_body_compilation_result->error->message =
                        "[ВАДА В STD] " + std_body_compilation_result->error->message;
                std_compilation_result->error = std_body_compilation_result->error;
                return std_compilation_result;
            }
        }

        const auto parser_result = mavka::parser::parse(code);
        const auto compilation_result = new CompilationResult();
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
                compilation_result->result = body_compilation_result->result;
            }
        }
        return compilation_result;
    }
}
