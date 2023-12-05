#include <string>
#include "parser.hpp"

namespace jejalyk {
    class CompilationType {
    public:
        std::map<std::string, CompilationType*> properties;
    };

    class CompilationScope {
    public:
        CompilationScope* parent = nullptr;
        std::map<std::string, CompilationType*> subjects;
    };

    class CompilationError {
    public:
        mavka::parser::MavkaParserError* parser_error = nullptr;
        std::string result;
    };

    class NodeCompilationResult {
    public:
        CompilationError* error = nullptr;
        CompilationType* type = nullptr;
        std::string result;
    };

    class CompilationResult : public NodeCompilationResult {
    public:
        mavka::parser::MavkaParserError* parser_error = nullptr;
    };

    class CompilationOptions {
    public:
        CompilationOptions* parent = nullptr;
        std::string root_module_path;
        std::string current_module_path;

        std::string (*get_module_name)(bool, std::string, CompilationOptions*) = nullptr;

        std::string (*get_module_path)(bool, std::string, CompilationOptions*) = nullptr;

        std::string (*get_module_code)(bool, std::string, CompilationOptions*) = nullptr;

        std::string (*get_butintin_module_code)(std::string, CompilationOptions*) = nullptr;

        std::string (*get_remote_module_name)(std::string, CompilationOptions*) = nullptr;

        std::string (*get_remote_module_pak_path)(std::string, CompilationOptions*) = nullptr;

        std::string (*get_remote_module_path)(std::string, CompilationOptions*) = nullptr;

        std::string (*get_remote_module_code)(std::string, CompilationOptions*) = nullptr;
    };

    std::string implode(const std::vector<std::string>& lst, const std::string& delim) {
        std::string ret;
        for (const auto& s: lst) {
            if (!ret.empty()) {
                ret += delim;
            }
            ret += s;
        }
        return ret;
    }

    NodeCompilationResult* compile_node(mavka::ast::ASTNode* node,
                                        CompilationScope* scope,
                                        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();

        if (mavka::ast::instanceof<mavka::ast::NumberNode>(node)) {
            const auto number_node = dynamic_cast<mavka::ast::NumberNode *>(node);
            node_compilation_result->type = scope->subjects["число"];
            node_compilation_result->result = number_node->value;
        }

        return node_compilation_result;
    }

    CompilationResult* compile(std::string code, CompilationOptions* options) {
        const auto parser_result = mavka::parser::parse(code);
        const auto compilation_result = new CompilationResult();

        if (parser_result->error) {
            compilation_result->parser_error = parser_result->error;
        } else {
            const auto scope = new CompilationScope();
            scope->subjects["число"] = new CompilationType();
            std::vector<std::string> lines;

            for (const auto& node: parser_result->program_node->body) {
                const auto node_compilation_result = compile_node(node, scope, options);
                if (node_compilation_result->error) {
                    compilation_result->error = node_compilation_result->error;
                    return compilation_result;
                } else {
                    lines.push_back(node_compilation_result->result);
                }
            }

            compilation_result->result = implode(lines, "\n");
        }
        return compilation_result;
    }
}
