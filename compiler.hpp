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

    inline NodeCompilationResult* compile_node(mavka::ast::ASTNode* node,
                                               CompilationScope* scope,
                                               CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();

        if (jejalyk::tools::instanceof<mavka::ast::AnonDiiaNode>(node)) {
            const auto anon_diia_node = dynamic_cast<mavka::ast::AnonDiiaNode *>(node);

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

        if (jejalyk::tools::instanceof<mavka::ast::ArithmeticNode>(node)) {
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
                node_compilation_result->error->line = arithmetic_node->start_line;
                node_compilation_result->error->column = arithmetic_node->start_column;
                node_compilation_result->error->message = "unsupported arithmetic operation: " + arithmetic_node->op;
            }
            return node_compilation_result;
        }

        if (jejalyk::tools::instanceof<mavka::ast::ArrayNode>(node)) {
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
            node_compilation_result->result = "[" + tools::implode(compiled_elements, ",") + "]";
            return node_compilation_result;
        }

        if (jejalyk::tools::instanceof<mavka::ast::AsNode>(node)) {
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

        if (jejalyk::tools::instanceof<mavka::ast::AssignComplexNode>(node)) {
        }

        if (jejalyk::tools::instanceof<mavka::ast::AssignSimpleNode>(node)) {
            const auto assign_simple_node = dynamic_cast<mavka::ast::AssignSimpleNode *>(node);
            const auto name = assign_simple_node->name;
            const auto value = compile_node(assign_simple_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = varname(name) + "=" + value->result;
        }

        if (jejalyk::tools::instanceof<mavka::ast::BitwiseNode>(node)) {
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
                node_compilation_result->error->line = bitwise_node->start_line;
                node_compilation_result->error->column = bitwise_node->start_column;
                node_compilation_result->error->message = "unsupported bitwise operation: " + bitwise_node->op;
            }
        }

        if (jejalyk::tools::instanceof<mavka::ast::BitwiseNotNode>(node)) {
            const auto bitwise_not_node = dynamic_cast<mavka::ast::BitwiseNotNode *>(node);
            const auto compiled_value = compile_node(bitwise_not_node->value, scope, options);
            if (compiled_value->error) {
                node_compilation_result->error = compiled_value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_BIT_NOT + "(" + compiled_value->result + ")";
        }

        if (jejalyk::tools::instanceof<mavka::ast::CallNode>(node)) {
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
            const auto args_string = tools::implode(*args, ",");
            node_compilation_result->result = MAVKA_CALL + "(" + value->result + ",{" + args_string + "})";
        }

        if (jejalyk::tools::instanceof<mavka::ast::ArgNode>(node)) {
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

        if (jejalyk::tools::instanceof<mavka::ast::ChainNode>(node)) {
            const auto chain_node = dynamic_cast<mavka::ast::ChainNode *>(node);
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::ComparisonNode>(node)) {
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::ContinueNode>(node)) {
            node_compilation_result->result = "continue";
        }

        if (jejalyk::tools::instanceof<mavka::ast::DiiaNode>(node)) {
            const auto diia_node = dynamic_cast<mavka::ast::DiiaNode *>(node);

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

        if (jejalyk::tools::instanceof<mavka::ast::EachNode>(node)) {
            const auto each_node = dynamic_cast<mavka::ast::EachNode *>(node);
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::EvalNode>(node)) {
        }

        if (jejalyk::tools::instanceof<mavka::ast::FunctionNode>(node)) {
            const auto function_node = dynamic_cast<mavka::ast::FunctionNode *>(node);

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

        if (jejalyk::tools::instanceof<mavka::ast::GetElementNode>(node)) {
            const auto get_element_node = dynamic_cast<mavka::ast::GetElementNode *>(node);
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::GiveNode>(node)) {
            const auto give_node = dynamic_cast<mavka::ast::GiveNode *>(node);
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::GodNode>(node)) {
        }

        if (jejalyk::tools::instanceof<mavka::ast::IdentifierNode>(node)) {
            const auto identifier_node = dynamic_cast<mavka::ast::IdentifierNode *>(node);
            node_compilation_result->result = varname(identifier_node->name);
        }

        if (jejalyk::tools::instanceof<mavka::ast::IfNode>(node)) {
            const auto if_node = dynamic_cast<mavka::ast::IfNode *>(node);
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::ModuleNode>(node)) {
            const auto module_node = dynamic_cast<mavka::ast::ModuleNode *>(node);
            const auto body = compile_body(module_node->body, scope, options);
            if (body->error) {
                node_compilation_result->error = body->error;
                return node_compilation_result;
            }
            node_compilation_result->result = varname(module_node->name) + "=" + MAVKA_MODULE + "(" + "\"" + module_node
                                              ->name + "\"" +
                                              ",function(module){\n"
                                              + body->result + "\n})";
        }

        if (jejalyk::tools::instanceof<mavka::ast::NegativeNode>(node)) {
            const auto negative_node = dynamic_cast<mavka::ast::NegativeNode *>(node);
            const auto value = compile_node(negative_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_NEGATIVE + "(" + value->result + ")";
        }

        if (jejalyk::tools::instanceof<mavka::ast::NotNode>(node)) {
            const auto not_node = dynamic_cast<mavka::ast::NotNode *>(node);
            const auto value = compile_node(not_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_NOT + "(" + value->result + ")";
        }

        if (jejalyk::tools::instanceof<mavka::ast::NumberNode>(node)) {
            const auto number_node = dynamic_cast<mavka::ast::NumberNode *>(node);
            node_compilation_result->result = number_node->value;
        }

        if (jejalyk::tools::instanceof<mavka::ast::PositiveNode>(node)) {
            const auto positive_node = dynamic_cast<mavka::ast::PositiveNode *>(node);
            const auto value = compile_node(positive_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_POSITIVE + "(" + value->result + ")";
        }

        if (jejalyk::tools::instanceof<mavka::ast::PostDecrementNode>(node)) {
            const auto post_decrement_node = dynamic_cast<mavka::ast::PostDecrementNode *>(node);
            const auto value = compile_node(post_decrement_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_POST_DECREMENT + "(" + value->result + ")";
        }

        if (jejalyk::tools::instanceof<mavka::ast::PostIncrementNode>(node)) {
            const auto post_increment_node = dynamic_cast<mavka::ast::PostIncrementNode *>(node);
            const auto value = compile_node(post_increment_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_POST_INCREMENT + "(" + value->result + ")";
        }

        if (jejalyk::tools::instanceof<mavka::ast::PreDecrementNode>(node)) {
            const auto pre_decrement_node = dynamic_cast<mavka::ast::PreDecrementNode *>(node);
            const auto value = compile_node(pre_decrement_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_PRE_DECREMENT + "(" + value->result + ")";
        }

        if (jejalyk::tools::instanceof<mavka::ast::PreInrementNode>(node)) {
            const auto pre_increment_node = dynamic_cast<mavka::ast::PreInrementNode *>(node);
            const auto value = compile_node(pre_increment_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_PRE_INCREMENT + "(" + value->result + ")";
        }

        if (jejalyk::tools::instanceof<mavka::ast::DictionaryNode>(node)) {
            const auto dictionary_node = dynamic_cast<mavka::ast::DictionaryNode *>(node);
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::ReturnNode>(node)) {
            const auto return_node = dynamic_cast<mavka::ast::ReturnNode *>(node);
            const auto value = compile_node(return_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = "return " + value->result;
        }

        if (jejalyk::tools::instanceof<mavka::ast::StringNode>(node)) {
            const auto string_node = dynamic_cast<mavka::ast::StringNode *>(node);
            node_compilation_result->result = "\"" + string_node->value + "\"";
        }

        if (jejalyk::tools::instanceof<mavka::ast::StructureNode>(node)) {
            const auto structure_node = dynamic_cast<mavka::ast::StructureNode *>(node);
            const auto compiled_params = compile_structure_params(structure_node->params, scope, options);
            if (compiled_params->error) {
                node_compilation_result->error = compiled_params->error;
                return node_compilation_result;
            }
            node_compilation_result->result = varname(structure_node->name) + "=" + MAVKA_STRUCTURE + "(" + "\""
                                              + structure_node->name + "\"" + "," +
                                              compiled_params->result + ")";
        }

        if (jejalyk::tools::instanceof<mavka::ast::TakeModuleNode>(node)) {
        }

        if (jejalyk::tools::instanceof<mavka::ast::TakePakNode>(node)) {
        }

        if (jejalyk::tools::instanceof<mavka::ast::TernaryNode>(node)) {
            const auto ternary_node = dynamic_cast<mavka::ast::TernaryNode *>(node);
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::TestNode>(node)) {
            const auto test_node = dynamic_cast<mavka::ast::TestNode *>(node);
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::ThrowNode>(node)) {
            const auto throw_node = dynamic_cast<mavka::ast::ThrowNode *>(node);
            const auto value = compile_node(throw_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = "throw " + value->result;
        }

        if (jejalyk::tools::instanceof<mavka::ast::TryNode>(node)) {
            const auto try_node = dynamic_cast<mavka::ast::TryNode *>(node);
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
        }

        if (jejalyk::tools::instanceof<mavka::ast::TypeValueNode>(node)) {
            const auto type_value_node = dynamic_cast<mavka::ast::TypeValueNode *>(node);
            // todo: complete
        }

        if (jejalyk::tools::instanceof<mavka::ast::TypeValueSingleNode>(node)) {
            const auto type_value_single_node = dynamic_cast<mavka::ast::TypeValueSingleNode *>(node);
            const auto value = compile_node(type_value_single_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = value->result;
        }

        if (jejalyk::tools::instanceof<mavka::ast::WaitNode>(node)) {
            const auto wait_node = dynamic_cast<mavka::ast::WaitNode *>(node);
            const auto value = compile_node(wait_node->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = "await " + value->result;
        }

        if (jejalyk::tools::instanceof<mavka::ast::WhileNode>(node)) {
            const auto while_node = dynamic_cast<mavka::ast::WhileNode *>(node);
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
        }

        return node_compilation_result;
    }

    NodeCompilationResult* compile_body(std::vector<mavka::ast::ASTNode *> body,
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
            compiled_body.push_back(item_node_compilation_result->result);
        }
        node_compilation_result->result = tools::implode(compiled_body, ";\n");
        return node_compilation_result;
    }


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
