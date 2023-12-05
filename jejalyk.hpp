#include <string>
#include "parser.hpp"

namespace jejalyk {
    const std::string MAVKA_CALL = "мВ"; // мВ(значення, аргументи)
    const std::string MAVKA_GET = "мО"; // мО(значення, властивість)

    std::string varname(std::string name) {
        return "м_" + name;
    }

    class CompilationType {
    public:
        std::map<std::string, CompilationType *> properties;
    };

    class CompilationScope {
    public:
        CompilationScope* parent = nullptr;
        std::map<std::string, CompilationType *> subjects;
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

        if (mavka::ast::instanceof<mavka::ast::AnonDiiaNode>(node)) {
            const auto anon_diia_node = dynamic_cast<mavka::ast::AnonDiiaNode *>(node);
        }

        if (mavka::ast::instanceof<mavka::ast::ArithmeticNode>(node)) {
            const auto arithmetic_node = dynamic_cast<mavka::ast::ArithmeticNode *>(node);
        }

        if (mavka::ast::instanceof<mavka::ast::ArrayNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::AsNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::AssignComplexNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::AssignSimpleNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::BitwiseNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::BitwiseNotNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::CallNode>(node)) {
            const auto call_node = dynamic_cast<mavka::ast::CallNode *>(node);
            const auto value = compile_node(call_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            const auto args = new std::vector<std::string>();
            for (const auto& arg: call_node->args) {
                const auto arg_compilation_result = compile_node(arg, scope, options);
                if (arg_compilation_result->error) {
                    node_compilation_result->error = arg_compilation_result->error;
                    return node_compilation_result;
                }
                args->push_back(arg_compilation_result->result);
            }
            const auto args_string = implode(*args, ",");
            node_compilation_result->result = MAVKA_CALL + "(" + value->result + ",{" + args_string + "})";
        }

        if (mavka::ast::instanceof<mavka::ast::ArgNode>(node)) {
            const auto arg_node = dynamic_cast<mavka::ast::ArgNode *>(node);
            const auto value = compile_node(arg_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            if (arg_node->name.empty()) {
                const auto index = std::to_string(arg_node->index);
                node_compilation_result->result = index + ":" + value->result;
            } else {
                const auto name = arg_node->name;
                node_compilation_result->result = name + ":" + value->result;
            }
            return node_compilation_result;
        }

        if (mavka::ast::instanceof<mavka::ast::ChainNode>(node)) {
            const auto chain_node = dynamic_cast<mavka::ast::ChainNode *>(node);
            const auto left = compile_node(chain_node->left, scope, options);
            if (left->error) {
                node_compilation_result->error = left->error;
                return node_compilation_result;
            }
            if (mavka::ast::instanceof<mavka::ast::IdentifierNode>(chain_node->right)) {
                const auto right = dynamic_cast<mavka::ast::IdentifierNode *>(chain_node->right)->name;
                node_compilation_result->result = MAVKA_GET + "(" + left->result + ",\"" + right + "\")";
            } else {
                const auto right = compile_node(chain_node->right, scope, options);
                if (right->error) {
                    node_compilation_result->error = right->error;
                    return node_compilation_result;
                }
                node_compilation_result->result = MAVKA_GET + "(" + left->result + "," + right->result + ")";
            }
        }

        if (mavka::ast::instanceof<mavka::ast::ComparisonNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::ContinueNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::DiiaNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::EachNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::EvalNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::FunctionNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::GetElementNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::GiveNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::GodNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::IdentifierNode>(node)) {
            const auto identifier_node = dynamic_cast<mavka::ast::IdentifierNode *>(node);
            node_compilation_result->result = varname(identifier_node->name);
        }

        if (mavka::ast::instanceof<mavka::ast::IfNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::ModuleNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::NegativeNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::NotNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::NumberNode>(node)) {
            const auto number_node = dynamic_cast<mavka::ast::NumberNode *>(node);
            node_compilation_result->result = number_node->value;
        }

        if (mavka::ast::instanceof<mavka::ast::PositiveNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::PostDecrementNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::PostIncrementNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::PreDecrementNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::PreInrementNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::DictionaryNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::ReturnNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::StringNode>(node)) {
            const auto string_node = dynamic_cast<mavka::ast::StringNode *>(node);
            node_compilation_result->result = "\"" + string_node->value + "\"";
        }

        if (mavka::ast::instanceof<mavka::ast::StructureNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::TakeModuleNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::TakePakNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::TernaryNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::TestNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::ThrowNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::TryNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::TypeValueNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::TypeValueSingleNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::WaitNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::WhileNode>(node)) {
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
                }
                lines.push_back(node_compilation_result->result);
            }

            compilation_result->result = implode(lines, ";\n");
        }
        return compilation_result;
    }
}
