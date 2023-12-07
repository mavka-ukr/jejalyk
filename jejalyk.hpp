#pragma once

#include <string>
#include "parser.hpp"
#include "compiler.hpp"

namespace jejalyk {
    const std::string head = R"(
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

макет дія друк(...значення) ніщо
)";

    inline CompilationResult* compile(const std::string& code, CompilationOptions* options) {
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
        const auto root_scope = new CompilationScope();
        const auto structureObject = new CompilationType();
        root_scope->assign("Структура", {structureObject}, structureObject);
        const auto head_body_compilation_result = jejalyk::compile_body(
            head_parser_result->program_node->body,
            root_scope,
            options
        );
        if (head_body_compilation_result->error) {
            head_body_compilation_result->error->message =
                    "[ВАДА В ГОЛОВІ :(] " + head_body_compilation_result->error->message;
            head_compilation_result->error = head_body_compilation_result->error;
            return head_compilation_result;
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
                options
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
