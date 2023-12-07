#pragma once

#include <string>
#include "parser.hpp"
#include "compiler.hpp"

namespace jejalyk {
    inline CompilationResult* compile(const std::string& code, CompilationOptions* options) {
        const auto parser_result = mavka::parser::parse(code);
        const auto compilation_result = new CompilationResult();

        if (parser_result->error) {
            compilation_result->error = new CompilationError();
            compilation_result->error->line = parser_result->error->line;
            compilation_result->error->column = parser_result->error->column;
            compilation_result->error->message = parser_result->error->message;
        } else {
            const auto scope = new CompilationScope();
            scope->subjects["обʼєкт"] = new CompilationType();
            scope->subjects["число"] = new CompilationType();
            scope->subjects["текст"] = new CompilationType();
            scope->subjects["логічне"] = new CompilationType();
            scope->subjects["так"] = scope->subjects["логічне"];
            scope->subjects["ні"] = scope->subjects["логічне"];
            std::vector<std::string> lines;

            for (const auto& node: parser_result->program_node->body) {
                const auto node_compilation_result = jejalyk::compile_node(node, scope, options);
                if (node_compilation_result->error) {
                    compilation_result->error = node_compilation_result->error;
                    return compilation_result;
                }
                lines.push_back(node_compilation_result->result);
            }

            compilation_result->result = tools::implode(lines, ";\n");
        }
        return compilation_result;
    }
}
