#pragma once

#include <map>
#include <string>
#include "tools.hpp"

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
    const std::string MAVKA_MODULE = "мМо"; // мМо(назва, функція)
    const std::string MAVKA_NEGATIVE = "мНг"; // мНг(значення)
    const std::string MAVKA_POSITIVE = "мПз"; // мПз(значення)
    const std::string MAVKA_POST_DECREMENT = "мПод"; // мПод(значення)
    const std::string MAVKA_POST_INCREMENT = "мПоі"; // мПоі(значення)
    const std::string MAVKA_PRE_DECREMENT = "мПрд"; // мПрд(значення)
    const std::string MAVKA_PRE_INCREMENT = "мПрі"; // мПрі(значення)
    const std::string MAVKA_GIVE = "мДт"; // мДт(модуль, назва, значення)
    const std::string MAVKA_STRUCTURE = "мСтр"; // мСтр(назва, параметри)
    const std::string MAVKA_IS = "мЄ"; // мЄ(а, б)
    const std::string MAVKA_CONTAINS = "мМє"; // мМє(а, б)
    const std::string MAVKA_FROM_TO = "мВід"; // мВід(від, до, символ, функція)
    const std::string MAVKA_FROM_TO_FN = "мВідФ"; // мВідФ(оператор, крок)

    inline std::string varname(const std::string& name) {
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
        size_t line{};
        size_t column{};
        std::string message;
    };

    class NodeCompilationResult {
    public:
        CompilationError* error = nullptr;
        CompilationType* type = nullptr;
        std::string result;
    };

    class CompilationResult : public NodeCompilationResult {
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

    NodeCompilationResult* compile_node(mavka::ast::ASTNode* node,
                                        CompilationScope* scope,
                                        CompilationOptions* options);

    NodeCompilationResult* compile_body(std::vector<mavka::ast::ASTNode *> body,
                                        CompilationScope* scope,
                                        CompilationOptions* options);

    NodeCompilationResult* compile_params(std::vector<mavka::ast::ParamNode *> params,
                                          CompilationScope* scope,
                                          CompilationOptions* options);

    NodeCompilationResult* compile_structure_params(std::vector<mavka::ast::StructureParamNode *> params,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

    NodeCompilationResult* compile_anon_diia_node(mavka::ast::AnonDiiaNode* node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options);

    NodeCompilationResult* compile_arithmetic_node(mavka::ast::ArithmeticNode* node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_array_node(mavka::ast::ArrayNode* node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);

    NodeCompilationResult* compile_as_node(mavka::ast::AsNode* node,
                                           CompilationScope* scope,
                                           CompilationOptions* options);

    NodeCompilationResult* compile_assign_complex_node(mavka::ast::AssignComplexNode* node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);

    NodeCompilationResult* compile_assign_simple_node(mavka::ast::AssignSimpleNode* node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);

    NodeCompilationResult* compile_bitwise_node(mavka::ast::BitwiseNode* node,
                                                CompilationScope* scope,
                                                CompilationOptions* options);

    NodeCompilationResult* compile_bitwise_not_node(mavka::ast::BitwiseNotNode* node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

    NodeCompilationResult* compile_call_node(mavka::ast::CallNode* node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_arg_node(mavka::ast::ArgNode* node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);

    NodeCompilationResult* compile_chain_node(mavka::ast::ChainNode* node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);

    NodeCompilationResult* compile_comparison_node(mavka::ast::ComparisonNode* node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_continue_node(mavka::ast::ContinueNode* node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_diia_node(mavka::ast::DiiaNode* node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_each_node(mavka::ast::EachNode* node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_eval_node(mavka::ast::EvalNode* node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_function_node(mavka::ast::FunctionNode* node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_from_to_simple_node(mavka::ast::FromToSimpleNode* from_to_simple_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);

    NodeCompilationResult* compile_from_to_complex_node(mavka::ast::FromToComplexNode* from_to_complex_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options);

    NodeCompilationResult* compile_get_element_node(mavka::ast::GetElementNode* node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

    NodeCompilationResult* compile_give_node(mavka::ast::GiveNode* node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_god_node(mavka::ast::GodNode* node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);

    NodeCompilationResult* compile_identifier_node(mavka::ast::IdentifierNode* node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_if_node(mavka::ast::IfNode* node,
                                           CompilationScope* scope,
                                           CompilationOptions* options);

    NodeCompilationResult* compile_module_node(mavka::ast::ModuleNode* node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);

    NodeCompilationResult* compile_negative_node(mavka::ast::NegativeNode* node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_not_node(mavka::ast::NotNode* node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);

    NodeCompilationResult* compile_number_node(mavka::ast::NumberNode* node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);

    NodeCompilationResult* compile_positive_node(mavka::ast::PositiveNode* node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_post_decrement_node(mavka::ast::PostDecrementNode* node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);

    NodeCompilationResult* compile_post_increment_node(mavka::ast::PostIncrementNode* node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);

    NodeCompilationResult* compile_pre_decrement_node(mavka::ast::PreDecrementNode* node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);

    NodeCompilationResult* compile_pre_increment_node(mavka::ast::PreInrementNode* node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);

    NodeCompilationResult* compile_dictionary_node(mavka::ast::DictionaryNode* node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_return_node(mavka::ast::ReturnNode* node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);

    NodeCompilationResult* compile_string_node(mavka::ast::StringNode* node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);

    NodeCompilationResult* compile_structure_node(mavka::ast::StructureNode* node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options);

    NodeCompilationResult* compile_take_module_node(mavka::ast::TakeModuleNode* node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

    NodeCompilationResult* compile_take_pak_node(mavka::ast::TakePakNode* node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_ternary_node(mavka::ast::TernaryNode* node,
                                                CompilationScope* scope,
                                                CompilationOptions* options);

    NodeCompilationResult* compile_test_node(mavka::ast::TestNode* node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_throw_node(mavka::ast::ThrowNode* node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);

    NodeCompilationResult* compile_try_node(mavka::ast::TryNode* node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);

    NodeCompilationResult* compile_type_value_node(mavka::ast::TypeValueNode* node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_type_value_single_node(mavka::ast::TypeValueSingleNode* node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options);

    NodeCompilationResult* compile_wait_node(mavka::ast::WaitNode* node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_while_node(mavka::ast::WhileNode* node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);

    inline NodeCompilationResult* compile_anon_diia_node(mavka::ast::AnonDiiaNode* anon_diia_node,
                                                         CompilationScope* scope,
                                                         CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();

        const auto params_compilation_result = compile_params(anon_diia_node->params, scope, options);
        if (params_compilation_result->error) {
            node_compilation_result->error = params_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_params = params_compilation_result->result;

        const auto body = compile_body(anon_diia_node->body, scope, options);

        node_compilation_result->result = MAVKA_DIIA + "(null," + compiled_params + ",function() {\n" + body->result
                                          + "\n})";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_arithmetic_node(mavka::ast::ArithmeticNode* arithmetic_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();

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
            node_compilation_result->error->line = arithmetic_node->start_line;
            node_compilation_result->error->column = arithmetic_node->start_column;
            node_compilation_result->error->message = "unsupported arithmetic operation: " + arithmetic_node->op;
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_array_node(mavka::ast::ArrayNode* array_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> compiled_elements;
        for (const auto& element: array_node->elements) {
            const auto element_compilation_result = compile_node(element, scope, options);
            if (element_compilation_result->error) {
                node_compilation_result->error = element_compilation_result->error;
                return node_compilation_result;
            }
            compiled_elements.push_back(element_compilation_result->result);
        }
        node_compilation_result->result = "[" + tools::implode(compiled_elements, ",") + "]";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_as_node(mavka::ast::AsNode* as_node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
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
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_assign_complex_node(mavka::ast::AssignComplexNode* node,
                                                              CompilationScope* scope,
                                                              CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_assign_simple_node(mavka::ast::AssignSimpleNode* assign_simple_node,
                                                             CompilationScope* scope,
                                                             CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = assign_simple_node->name;
        const auto value = compile_node(assign_simple_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = varname(name) + "=" + value->result;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_bitwise_node(mavka::ast::BitwiseNode* bitwise_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
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
            node_compilation_result->error->line = bitwise_node->start_line;
            node_compilation_result->error->column = bitwise_node->start_column;
            node_compilation_result->error->message = "unsupported bitwise operation: " + bitwise_node->op;
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_bitwise_not_node(mavka::ast::BitwiseNotNode* bitwise_not_node,
                                                           CompilationScope* scope,
                                                           CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto compiled_value = compile_node(bitwise_not_node->value, scope, options);
        if (compiled_value->error) {
            node_compilation_result->error = compiled_value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_BIT_NOT + "(" + compiled_value->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_call_node(mavka::ast::CallNode* call_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
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
        const auto args_string = tools::implode(*args, ",");
        node_compilation_result->result = MAVKA_CALL + "(" + value->result + ",{" + args_string + "})";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_arg_node(mavka::ast::ArgNode* arg_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
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

    inline NodeCompilationResult* compile_chain_node(mavka::ast::ChainNode* chain_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto left = compile_node(chain_node->left, scope, options);
        if (left->error) {
            node_compilation_result->error = left->error;
            return node_compilation_result;
        }
        if (jejalyk::tools::instanceof<mavka::ast::IdentifierNode>(chain_node->right)) {
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
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_comparison_node(mavka::ast::ComparisonNode* comparison_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
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
        } else if (comparison_node->op == "є") {
            node_compilation_result->result =
                    MAVKA_IS + "(" + compiled_left->result + "," + compiled_right->result + ")";
        } else if (comparison_node->op == "не є") {
            node_compilation_result->result =
                    "!" + MAVKA_IS + "(" + compiled_left->result + "," + compiled_right->result + ")";
        } else if (comparison_node->op == "містить") {
            node_compilation_result->result =
                    MAVKA_CONTAINS + "(" + compiled_left->result + "," + compiled_right->result + ")";
        } else if (comparison_node->op == "не містить") {
            node_compilation_result->result =
                    "!" + MAVKA_CONTAINS + "(" + compiled_left->result + "," + compiled_right->result + ")";
        } else {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->line = comparison_node->start_line;
            node_compilation_result->error->column = comparison_node->start_column;
            node_compilation_result->error->message = "unsupported comparison operation: " + comparison_node->op;
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_continue_node(mavka::ast::ContinueNode* node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        node_compilation_result->result = "continue";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_diia_node(mavka::ast::DiiaNode* diia_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();

        const auto params_compilation_result = compile_params(diia_node->params, scope, options);
        if (params_compilation_result->error) {
            node_compilation_result->error = params_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_params = params_compilation_result->result;

        const auto body = compile_body(diia_node->body, scope, options);

        node_compilation_result->result = varname(diia_node->name) + "=" + MAVKA_DIIA + "(" + "\"" + diia_node->name
                                          + "\"" + "," +
                                          compiled_params + ",function() {\n" + body->result + "\n})";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_each_node(mavka::ast::EachNode* each_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(each_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        if (each_node->keyName.empty()) {
            node_compilation_result->result =
                    "for (" + varname(each_node->name) + " of mavka_values(" + value->result
                    + ")) {}";
        } else {
            node_compilation_result->result =
                    "for ([" + varname(each_node->keyName) + "," + varname(each_node->keyName) +
                    "] of mavka_entries(" + value->result
                    + ")) {}";
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_eval_node(mavka::ast::EvalNode* node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_function_node(mavka::ast::FunctionNode* function_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();

        const auto params_compilation_result = compile_params(function_node->params, scope, options);
        if (params_compilation_result->error) {
            node_compilation_result->error = params_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_params = params_compilation_result->result;

        const auto body = compile_body(function_node->body, scope, options);

        node_compilation_result->result = MAVKA_DIIA + "(null," + compiled_params + ",function() {\n" + body->result
                                          + "\n})";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_from_to_simple_node(mavka::ast::FromToSimpleNode* from_to_simple_node,
                                                              CompilationScope* scope,
                                                              CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto from = compile_node(from_to_simple_node->from, scope, options);
        if (from->error) {
            node_compilation_result->error = from->error;
            return node_compilation_result;
        }
        const auto to = compile_node(from_to_simple_node->to, scope, options);
        if (to->error) {
            node_compilation_result->error = to->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_FROM_TO + "(" + from->result + "," + to->result + ",\"" +
                                          from_to_simple_node->toSymbol + "\"," + MAVKA_FROM_TO_FN + "(\"+\",1))";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_from_to_complex_node(mavka::ast::FromToComplexNode* from_to_complex_node,
                                                               CompilationScope* scope,
                                                               CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto from = compile_node(from_to_complex_node->from, scope, options);
        if (from->error) {
            node_compilation_result->error = from->error;
            return node_compilation_result;
        }
        const auto to = compile_node(from_to_complex_node->to, scope, options);
        if (to->error) {
            node_compilation_result->error = to->error;
            return node_compilation_result;
        }
        const auto step = compile_node(from_to_complex_node->step, scope, options);
        if (step->error) {
            node_compilation_result->error = step->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_FROM_TO + "(" + from->result + "," + to->result + ",\"" +
                                          from_to_complex_node->toSymbol + "\"," + MAVKA_FROM_TO_FN + "(\"" +
                                          from_to_complex_node->stepSymbol + "\"," + step->result + "))";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_get_element_node(mavka::ast::GetElementNode* get_element_node,
                                                           CompilationScope* scope,
                                                           CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(get_element_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        const auto index = compile_node(get_element_node->index, scope, options);
        if (index->error) {
            node_compilation_result->error = index->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_GET + "(" + value->result + "," + index->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_give_node(mavka::ast::GiveNode* give_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto elements = new std::vector<std::string>();
        for (const auto& element: give_node->elements) {
            if (!element->as.empty()) {
                elements->push_back(
                    MAVKA_GIVE + "(module,\"" + element->as + "\"," + varname(element->name) + ")");
            } else {
                elements->push_back(
                    MAVKA_GIVE + "(module,\"" + element->name + "\"," + varname(element->name) + ")");
            }
        }
        node_compilation_result->result = tools::implode(*elements, ";\n");
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_god_node(mavka::ast::GodNode* node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_identifier_node(mavka::ast::IdentifierNode* identifier_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        node_compilation_result->result = varname(identifier_node->name);
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_if_node(mavka::ast::IfNode* if_node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto condition = compile_node(if_node->condition, scope, options);
        if (condition->error) {
            node_compilation_result->error = condition->error;
            return node_compilation_result;
        }
        const auto body = compile_body(if_node->body, scope, options);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        if (!if_node->else_body.empty()) {
            const auto else_body = compile_body(if_node->else_body, scope, options);
            if (else_body->error) {
                node_compilation_result->error = else_body->error;
                return node_compilation_result;
            }
            node_compilation_result->result = "if(" + condition->result + "){\n" + body->result + "\n}else{\n"
                                              + else_body->result + "\n}";
        } else {
            node_compilation_result->result = "if(" + condition->result + "){\n" + body->result + "\n}";
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_module_node(mavka::ast::ModuleNode* module_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto body = compile_body(module_node->body, scope, options);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = varname(module_node->name) + "=" + MAVKA_MODULE + "(" + "\"" + module_node
                                          ->name + "\"" +
                                          ",function(module){\n"
                                          + body->result + "\n})";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_negative_node(mavka::ast::NegativeNode* negative_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(negative_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_NEGATIVE + "(" + value->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_not_node(mavka::ast::NotNode* not_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(not_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_NOT + "(" + value->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_number_node(mavka::ast::NumberNode* number_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        node_compilation_result->result = number_node->value;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_positive_node(mavka::ast::PositiveNode* positive_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(positive_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_POSITIVE + "(" + value->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_post_decrement_node(mavka::ast::PostDecrementNode* post_decrement_node,
                                                              CompilationScope* scope,
                                                              CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(post_decrement_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_POST_DECREMENT + "(" + value->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_post_increment_node(mavka::ast::PostIncrementNode* post_increment_node,
                                                              CompilationScope* scope,
                                                              CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(post_increment_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_POST_INCREMENT + "(" + value->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_pre_decrement_node(mavka::ast::PreDecrementNode* pre_decrement_node,
                                                             CompilationScope* scope,
                                                             CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(pre_decrement_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_PRE_DECREMENT + "(" + value->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_pre_increment_node(mavka::ast::PreInrementNode* pre_increment_node,
                                                             CompilationScope* scope,
                                                             CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(pre_increment_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_PRE_INCREMENT + "(" + value->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_dictionary_node(mavka::ast::DictionaryNode* dictionary_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> compiled_elements;
        for (const auto& element: dictionary_node->elements) {
            const auto value = compile_node(element.second, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            compiled_elements.push_back("[\"" + element.first + "\"," + value->result + "]");
        }
        node_compilation_result->result = "new Map([" + tools::implode(compiled_elements, ",") + "])";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_return_node(mavka::ast::ReturnNode* return_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(return_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "return " + value->result;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_string_node(mavka::ast::StringNode* string_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        node_compilation_result->result = "\"" + string_node->value + "\"";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_structure_node(mavka::ast::StructureNode* structure_node,
                                                         CompilationScope* scope,
                                                         CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto compiled_params = compile_structure_params(structure_node->params, scope, options);
        if (compiled_params->error) {
            node_compilation_result->error = compiled_params->error;
            return node_compilation_result;
        }
        node_compilation_result->result = varname(structure_node->name) + "=" + MAVKA_STRUCTURE + "(" + "\""
                                          + structure_node->name + "\"" + "," +
                                          compiled_params->result + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_take_module_node(mavka::ast::TakeModuleNode* node,
                                                           CompilationScope* scope,
                                                           CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_take_pak_node(mavka::ast::TakePakNode* node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_ternary_node(mavka::ast::TernaryNode* ternary_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto condition = compile_node(ternary_node->condition, scope, options);
        if (condition->error) {
            node_compilation_result->error = condition->error;
            return node_compilation_result;
        }
        const auto true_value = compile_body(ternary_node->body, scope, options);
        if (true_value->error) {
            node_compilation_result->error = true_value->error;
            return node_compilation_result;
        }
        const auto else_body = compile_body(ternary_node->else_body, scope, options);
        if (else_body->error) {
            node_compilation_result->error = else_body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "(" + condition->result + ")?" + true_value->result + ":" + else_body
                                          ->result;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_test_node(mavka::ast::TestNode* test_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto left = compile_node(test_node->left, scope, options);
        if (left->error) {
            node_compilation_result->error = left->error;
            return node_compilation_result;
        }
        const auto right = compile_node(test_node->right, scope, options);
        if (right->error) {
            node_compilation_result->error = right->error;
            return node_compilation_result;
        }
        // todo: complete
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_throw_node(mavka::ast::ThrowNode* throw_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(throw_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "throw " + value->result;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_try_node(mavka::ast::TryNode* try_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto body = compile_body(try_node->body, scope, options);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        const auto catch_body = compile_body(try_node->catch_body, scope, options);
        if (catch_body->error) {
            node_compilation_result->error = catch_body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "try{\n" + body->result + "\n}catch(" + varname(try_node->name) + "){\n" +
                                          catch_body->result
                                          + "\n}";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_type_value_node(mavka::ast::TypeValueNode* type_value_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        // todo: complete
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_type_value_single_node(
        mavka::ast::TypeValueSingleNode* type_value_single_node,
        CompilationScope* scope,
        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(type_value_single_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = value->result;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_wait_node(mavka::ast::WaitNode* wait_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(wait_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "await " + value->result;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_while_node(mavka::ast::WhileNode* while_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto condition = compile_node(while_node->condition, scope, options);
        if (condition->error) {
            node_compilation_result->error = condition->error;
            return node_compilation_result;
        }
        const auto body = compile_body(while_node->body, scope, options);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "while(" + condition->result + "){\n" + body->result + "\n}";
        return node_compilation_result;
    }


    inline NodeCompilationResult* compile_node(mavka::ast::ASTNode* node,
                                               CompilationScope* scope,
                                               CompilationOptions* options) {
        if (jejalyk::tools::instanceof<mavka::ast::AnonDiiaNode>(node)) {
            return compile_anon_diia_node(dynamic_cast<mavka::ast::AnonDiiaNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ArithmeticNode>(node)) {
            return compile_arithmetic_node(dynamic_cast<mavka::ast::ArithmeticNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ArrayNode>(node)) {
            return compile_array_node(dynamic_cast<mavka::ast::ArrayNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::AsNode>(node)) {
            return compile_as_node(dynamic_cast<mavka::ast::AsNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::AssignComplexNode>(node)) {
            return compile_assign_complex_node(dynamic_cast<mavka::ast::AssignComplexNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::AssignSimpleNode>(node)) {
            return compile_assign_simple_node(dynamic_cast<mavka::ast::AssignSimpleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::BitwiseNode>(node)) {
            return compile_bitwise_node(dynamic_cast<mavka::ast::BitwiseNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::BitwiseNotNode>(node)) {
            return compile_bitwise_not_node(dynamic_cast<mavka::ast::BitwiseNotNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::CallNode>(node)) {
            return compile_call_node(dynamic_cast<mavka::ast::CallNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ArgNode>(node)) {
            return compile_arg_node(dynamic_cast<mavka::ast::ArgNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ChainNode>(node)) {
            return compile_chain_node(dynamic_cast<mavka::ast::ChainNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ComparisonNode>(node)) {
            return compile_comparison_node(dynamic_cast<mavka::ast::ComparisonNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ContinueNode>(node)) {
            return compile_continue_node(dynamic_cast<mavka::ast::ContinueNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::DiiaNode>(node)) {
            return compile_diia_node(dynamic_cast<mavka::ast::DiiaNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::EachNode>(node)) {
            return compile_each_node(dynamic_cast<mavka::ast::EachNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::EvalNode>(node)) {
            return compile_eval_node(dynamic_cast<mavka::ast::EvalNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::FunctionNode>(node)) {
            return compile_function_node(dynamic_cast<mavka::ast::FunctionNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::FromToSimpleNode>(node)) {
            return compile_from_to_simple_node(dynamic_cast<mavka::ast::FromToSimpleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::FromToComplexNode>(node)) {
            return compile_from_to_complex_node(dynamic_cast<mavka::ast::FromToComplexNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::GetElementNode>(node)) {
            return compile_get_element_node(dynamic_cast<mavka::ast::GetElementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::GiveNode>(node)) {
            return compile_give_node(dynamic_cast<mavka::ast::GiveNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::GodNode>(node)) {
            return compile_god_node(dynamic_cast<mavka::ast::GodNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::IdentifierNode>(node)) {
            return compile_identifier_node(dynamic_cast<mavka::ast::IdentifierNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::IfNode>(node)) {
            return compile_if_node(dynamic_cast<mavka::ast::IfNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ModuleNode>(node)) {
            return compile_module_node(dynamic_cast<mavka::ast::ModuleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::NegativeNode>(node)) {
            return compile_negative_node(dynamic_cast<mavka::ast::NegativeNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::NotNode>(node)) {
            return compile_not_node(dynamic_cast<mavka::ast::NotNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::NumberNode>(node)) {
            return compile_number_node(dynamic_cast<mavka::ast::NumberNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PositiveNode>(node)) {
            return compile_positive_node(dynamic_cast<mavka::ast::PositiveNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PostDecrementNode>(node)) {
            return compile_post_decrement_node(dynamic_cast<mavka::ast::PostDecrementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PostIncrementNode>(node)) {
            return compile_post_increment_node(dynamic_cast<mavka::ast::PostIncrementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PreDecrementNode>(node)) {
            return compile_pre_decrement_node(dynamic_cast<mavka::ast::PreDecrementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::PreInrementNode>(node)) {
            return compile_pre_increment_node(dynamic_cast<mavka::ast::PreInrementNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::DictionaryNode>(node)) {
            return compile_dictionary_node(dynamic_cast<mavka::ast::DictionaryNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ReturnNode>(node)) {
            return compile_return_node(dynamic_cast<mavka::ast::ReturnNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::StringNode>(node)) {
            return compile_string_node(dynamic_cast<mavka::ast::StringNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::StructureNode>(node)) {
            return compile_structure_node(dynamic_cast<mavka::ast::StructureNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TakeModuleNode>(node)) {
            return compile_take_module_node(dynamic_cast<mavka::ast::TakeModuleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TakePakNode>(node)) {
            return compile_take_pak_node(dynamic_cast<mavka::ast::TakePakNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TernaryNode>(node)) {
            return compile_ternary_node(dynamic_cast<mavka::ast::TernaryNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TestNode>(node)) {
            return compile_test_node(dynamic_cast<mavka::ast::TestNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::ThrowNode>(node)) {
            return compile_throw_node(dynamic_cast<mavka::ast::ThrowNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TryNode>(node)) {
            return compile_try_node(dynamic_cast<mavka::ast::TryNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TypeValueNode>(node)) {
            return compile_type_value_node(dynamic_cast<mavka::ast::TypeValueNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::TypeValueSingleNode>(node)) {
            return compile_type_value_single_node(dynamic_cast<mavka::ast::TypeValueSingleNode *>(node), scope,
                                                  options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::WaitNode>(node)) {
            return compile_wait_node(dynamic_cast<mavka::ast::WaitNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::WhileNode>(node)) {
            return compile_while_node(dynamic_cast<mavka::ast::WhileNode *>(node), scope, options);
        }

        if (node == nullptr) {
            const auto node_compilation_result = new NodeCompilationResult();
            node_compilation_result->result = "";
            return node_compilation_result;
        }

        throw std::runtime_error("Unknown node type");
    }

    inline NodeCompilationResult* compile_body(std::vector<mavka::ast::ASTNode *> body,
                                               CompilationScope* scope,
                                               CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> compiled_body;
        for (const auto node: body) {
            const auto item_node_compilation_result = compile_node(node, scope, options);
            if (item_node_compilation_result->error) {
                item_node_compilation_result->error = item_node_compilation_result->error;
                return item_node_compilation_result;
            }
            if (item_node_compilation_result->result.empty()) {
                continue;
            }
            compiled_body.push_back(item_node_compilation_result->result);
        }
        node_compilation_result->result = tools::implode(compiled_body, ";\n");
        return node_compilation_result;
    }


    inline NodeCompilationResult* compile_params(std::vector<mavka::ast::ParamNode *> params,
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
        node_compilation_result->result = "[" + tools::implode(compiled_params, ",") + "]";
        return node_compilation_result;
    }


    inline NodeCompilationResult* compile_structure_params(std::vector<mavka::ast::StructureParamNode *> params,
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
        node_compilation_result->result = "[" + tools::implode(compiled_params, ",") + "]";
        return node_compilation_result;
    }
}
