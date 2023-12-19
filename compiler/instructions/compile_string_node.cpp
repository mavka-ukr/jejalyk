#include "compile_string_node.h"

#include "compile_node.h"
#include "../compile.h"
#include "../../tools.h"
#include "../../parser.h"

namespace jejalyk {
NodeCompilationResult* compile_string_node(const mavka::ast::StringNode* string_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<mavka::ast::ASTNode *> parts;
        std::string current_part;
        bool interpolation = false;
        for (int i = 0; i < string_node->value.length(); ++i) {
            if (!interpolation && tools::is_digit(tools::safe_substr(string_node->value, i, 1)) &&
                tools::safe_substr(string_node->value, i - 1, 1) == "\\" &&
                tools::safe_substr(string_node->value, i - 2, 1) != "\\") {
                node_compilation_result->error = new CompilationError();
                node_compilation_result->error->path = options->current_module_path;
                node_compilation_result->error->line = string_node->start_line;
                node_compilation_result->error->column = string_node->start_column + i;
                node_compilation_result->error->message = "Числа не підтримуються в рядках.";
                return node_compilation_result;
            }

            if (!interpolation && tools::safe_substr(string_node->value, i, 1) == "%" &&
                tools::safe_substr(string_node->value, i + 1, 1) == "(" && tools::safe_substr(
                    string_node->value, i - 1, 1) != "\\") {
                interpolation = true;
                const auto part_string = new mavka::ast::StringNode();
                part_string->value = current_part;
                parts.push_back(part_string);
                current_part = "";
                i += 1;
                continue;
            }

            if (interpolation && tools::safe_substr(string_node->value, i, 1) == ")" && tools::safe_substr(
                    string_node->value, i - 1, 1) !=
                "\\") {
                interpolation = false;
                const auto parser_result = mavka::parser::parse(current_part);
                if (parser_result->error) {
                    node_compilation_result->error = new CompilationError();
                    node_compilation_result->error->path = options->current_module_path;
                    node_compilation_result->error->line = parser_result->error->line;
                    node_compilation_result->error->column = parser_result->error->column;
                    node_compilation_result->error->message = parser_result->error->message;
                    return node_compilation_result;
                }
                parts.push_back(parser_result->program_node->body[0]);
                current_part = "";
                continue;
            }

            current_part += string_node->value[i];
        }
        const auto part_string = new mavka::ast::StringNode();
        part_string->value = current_part;
        parts.push_back(part_string);
        std::vector<std::string> string_parts;
        for (const auto part: parts) {
            if (tools::instanceof<mavka::ast::StringNode>(part)) {
                const auto string_part = dynamic_cast<mavka::ast::StringNode *>(part);
                auto string_value = string_part->value;
                tools::replace_all(string_value, "\n", "\\n");
                tools::replace_all(string_value, "\r", "\\r");
                tools::replace_all(string_value, "\t", "\\t");
                tools::replace_all(string_value, "\"", "\\\"");
                string_parts.push_back("\"" + string_value + "\"");
            } else {
                const auto part_compilation_result = compile_node(part, scope, options);
                if (part_compilation_result->error) {
                    node_compilation_result->error = part_compilation_result->error;
                    return node_compilation_result;
                }
                const auto diName = scope->
                        put_debug(options->current_module_path, part->start_line, part->start_column);
                string_parts.push_back(
                    "мВикл(м_текст.чародія_викликати, [" + part_compilation_result->result + "]," + diName + ")");
            }
        }
        node_compilation_result->result = tools::implode(string_parts, "+");
        return node_compilation_result;
    }
}
