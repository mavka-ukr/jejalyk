#include <string>
#include "parser.hpp"

namespace jejalyk {
    const std::string MAVKA_CALL = "мВк"; // мВк(значення, аргументи)
    const std::string MAVKA_GET = "мОт"; // мО(значення, властивість)
    const std::string MAVKA_DIIA = "мДі"; // мД(назва, параметри, функція)
    const std::string MAVKA_PARAM = "мПр"; // мП(назва, тип, значення)
    const std::string MAVKA_ADD = "мДо"; // мДо(а, б)
    const std::string MAVKA_SUB = "мВі"; // мВі(а, б)
    const std::string MAVKA_MUL = "мМн"; // мМн(а, б)
    const std::string MAVKA_DIV = "мДл"; // мДл(а, б)
    const std::string MAVKA_MOD = "мОс"; // мОс(а, б)
    const std::string MAVKA_POW = "мСт"; // мСт(а, б)
    const std::string MAVKA_AND = "мІ"; // мІ(а, б)
    const std::string MAVKA_OR = "мАб"; // мАб(а, б)
    const std::string MAVKA_XOR = "мХр"; // мХр(а, б)
    const std::string MAVKA_NOT = "мНі"; // мНі(а)
    const std::string MAVKA_BIT_AND = "мДІ"; // мДІ(а, б)
    const std::string MAVKA_BIT_OR = "мДА"; // мДА(а, б)
    const std::string MAVKA_BIT_XOR = "мДХ"; // мДХ(а, б)
    const std::string MAVKA_BIT_NOT = "мДН"; // мДН(а)
    const std::string MAVKA_BIT_LSHIFT = "мЗС"; // мЗС(а, б)
    const std::string MAVKA_BIT_RSHIFT = "мЗП"; // мЗП(а, б)
    const std::string MAVKA_AS = "мЯк"; // мЯк(а, б)
    const std::string MAVKA_EQ = "мРі"; // мРі(а, б)
    const std::string MAVKA_LT = "мМе"; // мМе(а, б)
    const std::string MAVKA_LE = "мМр"; // мМр(а, б)
    const std::string MAVKA_GT = "мБі"; // мБі(а, б)
    const std::string MAVKA_GE = "мБр"; // мБр(а, б)

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
                                        CompilationOptions* options);

    NodeCompilationResult* compile_params(std::vector<mavka::ast::ParamNode *> params,
                                          CompilationScope* scope,
                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> compiled_params;
        for (int i = 0; i < params.size(); ++i) {
            const auto param = params[i];
            const auto param_name = param->name;
            std::string compiled_param_type = "undefined";
            std::string compiled_param_value = "undefined";
            if (param->type) {
                const auto param_type_compilation_result = compile_node(param->type, scope, options);
                if (param_type_compilation_result->error) {
                    node_compilation_result->error = param_type_compilation_result->error;
                    return node_compilation_result;
                }
                const auto param_type_result = param_type_compilation_result->result;
            }
            std::string param_string = MAVKA_PARAM + "(" + "\"" + param_name + "\"";
            if (compiled_param_type != "undefined") {
                param_string += "," + compiled_param_type;
            }
            if (compiled_param_value != "undefined") {
                param_string += "," + compiled_param_value;
            }
            compiled_params.push_back(param_string + ")");
        }
        node_compilation_result->result = "[" + implode(compiled_params, ",") + "]";
        return node_compilation_result;
    }

    NodeCompilationResult* compile_node(mavka::ast::ASTNode* node,
                                        CompilationScope* scope,
                                        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();

        if (mavka::ast::instanceof<mavka::ast::AnonDiiaNode>(node)) {
            const auto anon_diia_node = dynamic_cast<mavka::ast::AnonDiiaNode *>(node);

            const auto params_compilation_result = compile_params(anon_diia_node->params, scope, options);
            if (params_compilation_result->error) {
                node_compilation_result->error = params_compilation_result->error;
                return node_compilation_result;
            }
            const auto compiled_params = params_compilation_result->result;

            node_compilation_result->result = MAVKA_DIIA + "(null," + compiled_params + ")";
            return node_compilation_result;
        }

        if (mavka::ast::instanceof<mavka::ast::ArithmeticNode>(node)) {
            const auto arithmetic_node = dynamic_cast<mavka::ast::ArithmeticNode *>(node);
            const auto compiled_left = compile_node(arithmetic_node->left, scope, options);
            if (compiled_left->error) {
                node_compilation_result->error = compiled_left->error;
                return node_compilation_result;
            }
            const auto compiled_right = compile_node(arithmetic_node->right, scope, options);
            if (compiled_right->error) {
                node_compilation_result->error = compiled_right->error;
                return node_compilation_result;
            }
            if (arithmetic_node->op == "+") {
                node_compilation_result->result =
                        MAVKA_ADD + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (arithmetic_node->op == "-") {
                node_compilation_result->result =
                        MAVKA_SUB + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (arithmetic_node->op == "*") {
                node_compilation_result->result =
                        MAVKA_MUL + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (arithmetic_node->op == "/") {
                node_compilation_result->result =
                        MAVKA_DIV + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else {
                node_compilation_result->error = new CompilationError();
                node_compilation_result->error->result = "unsupported arithmetic operation: " + arithmetic_node->op;
            }
            return node_compilation_result;
        }

        if (mavka::ast::instanceof<mavka::ast::ArrayNode>(node)) {
            const auto array_node = dynamic_cast<mavka::ast::ArrayNode *>(node);
            std::vector<std::string> compiled_elements;
            for (const auto& element: array_node->elements) {
                const auto element_compilation_result = compile_node(element, scope, options);
                if (element_compilation_result->error) {
                    node_compilation_result->error = element_compilation_result->error;
                    return node_compilation_result;
                }
                compiled_elements.push_back(element_compilation_result->result);
            }
            node_compilation_result->result = "[" + implode(compiled_elements, ",") + "]";
            return node_compilation_result;
        }

        if (mavka::ast::instanceof<mavka::ast::AsNode>(node)) {
            const auto as_node = dynamic_cast<mavka::ast::AsNode *>(node);
            const auto left = compile_node(as_node->left, scope, options);
            if (left->error) {
                node_compilation_result->error = left->error;
                return node_compilation_result;
            }
            const auto right = compile_node(as_node->right, scope, options);
            if (right->error) {
                node_compilation_result->error = right->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_AS + "(" + left->result + "," + right->result + ")";
        }

        if (mavka::ast::instanceof<mavka::ast::AssignComplexNode>(node)) {
        }

        if (mavka::ast::instanceof<mavka::ast::AssignSimpleNode>(node)) {
            const auto assign_simple_node = dynamic_cast<mavka::ast::AssignSimpleNode *>(node);
            const auto name = assign_simple_node->name;
            const auto value = compile_node(assign_simple_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = varname(name) + "=" + value->result;
        }

        if (mavka::ast::instanceof<mavka::ast::BitwiseNode>(node)) {
            const auto bitwise_node = dynamic_cast<mavka::ast::BitwiseNode *>(node);
            const auto compiled_left = compile_node(bitwise_node->left, scope, options);
            if (compiled_left->error) {
                node_compilation_result->error = compiled_left->error;
                return node_compilation_result;
            }
            const auto compiled_right = compile_node(bitwise_node->right, scope, options);
            if (compiled_right->error) {
                node_compilation_result->error = compiled_right->error;
                return node_compilation_result;
            }
            if (bitwise_node->op == "&") {
                node_compilation_result->result =
                        MAVKA_BIT_AND + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (bitwise_node->op == "|") {
                node_compilation_result->result =
                        MAVKA_BIT_OR + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (bitwise_node->op == "^") {
                node_compilation_result->result =
                        MAVKA_BIT_XOR + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (bitwise_node->op == "<<") {
                node_compilation_result->result =
                        MAVKA_BIT_LSHIFT + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (bitwise_node->op == ">>") {
                node_compilation_result->result =
                        MAVKA_BIT_RSHIFT + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else {
                node_compilation_result->error = new CompilationError();
                node_compilation_result->error->result = "unsupported bitwise operation: " + bitwise_node->op;
            }
        }

        if (mavka::ast::instanceof<mavka::ast::BitwiseNotNode>(node)) {
            const auto bitwise_not_node = dynamic_cast<mavka::ast::BitwiseNotNode *>(node);
            const auto compiled_value = compile_node(bitwise_not_node->value, scope, options);
            if (compiled_value->error) {
                node_compilation_result->error = compiled_value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_BIT_NOT + "(" + compiled_value->result + ")";
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
            const auto comparison_node = dynamic_cast<mavka::ast::ComparisonNode *>(node);
            const auto compiled_left = compile_node(comparison_node->left, scope, options);
            if (compiled_left->error) {
                node_compilation_result->error = compiled_left->error;
                return node_compilation_result;
            }
            const auto compiled_right = compile_node(comparison_node->right, scope, options);
            if (compiled_right->error) {
                node_compilation_result->error = compiled_right->error;
                return node_compilation_result;
            }
            if (comparison_node->op == "==") {
                node_compilation_result->result =
                        MAVKA_EQ + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (comparison_node->op == "!=") {
                node_compilation_result->result =
                        "!" + MAVKA_EQ + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (comparison_node->op == "<") {
                node_compilation_result->result =
                        MAVKA_LT + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (comparison_node->op == "<=") {
                node_compilation_result->result =
                        MAVKA_LE + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (comparison_node->op == ">") {
                node_compilation_result->result =
                        MAVKA_GT + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else if (comparison_node->op == ">=") {
                node_compilation_result->result =
                        MAVKA_GE + "(" + compiled_left->result + "," + compiled_right->result + ")";
            } else {
                node_compilation_result->error = new CompilationError();
                node_compilation_result->error->result = "unsupported comparison operation: " + comparison_node->op;
            }
        }

        if (mavka::ast::instanceof<mavka::ast::ContinueNode>(node)) {
            node_compilation_result->result = "continue";
        }

        if (mavka::ast::instanceof<mavka::ast::DiiaNode>(node)) {
            const auto diia_node = dynamic_cast<mavka::ast::DiiaNode *>(node);

            const auto params_compilation_result = compile_params(diia_node->params, scope, options);
            if (params_compilation_result->error) {
                node_compilation_result->error = params_compilation_result->error;
                return node_compilation_result;
            }
            const auto compiled_params = params_compilation_result->result;

            node_compilation_result->result = varname(diia_node->name) + "=" + MAVKA_DIIA + "(" + "\"" + diia_node->name
                                              + "\"" + "," +
                                              compiled_params + ")";
            return node_compilation_result;
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
