#pragma once

#include <string>
#include <utility>
#include "tools.hpp"

namespace jejalyk {
    const std::string MAVKA_CALL = "мВикл"; // мВикл(значення, аргументи)
    const std::string MAVKA_GET = "мОтрм"; // мОтрм(значення, властивість)
    const std::string MAVKA_SET = "мВстн"; // мВстн(значення, властивість, значення)
    const std::string MAVKA_SET_ELEMENT = "мПклс"; // мПклс(значення, елемент, значення)
    const std::string MAVKA_GET_ELEMENT = "мОтре"; // мОтрм(значення, елемент)
    const std::string MAVKA_DIIA = "мДія"; // мДія(назва, параметри, функція)
    const std::string MAVKA_METHOD = "мМетд"; // мМетд(назва, параметри, функція)
    const std::string MAVKA_SET_METHOD = "мВМтд"; // мВМтд(структура, метод)
    const std::string MAVKA_PARAM = "мПарм"; // мПарм(назва, тип, значення)
    const std::string MAVKA_VPARAM = "мВпрм"; // мВпрм(назва, тип, значення)
    const std::string MAVKA_ADD = "мДодт"; // мДодт(а, б)
    const std::string MAVKA_SUB = "мВідн"; // мВідн(а, б)
    const std::string MAVKA_MUL = "мМнож"; // мМнож(а, б)
    const std::string MAVKA_DIV = "мДілт"; // мДілт(а, б)
    const std::string MAVKA_MOD = "мОстч"; // мОстч(а, б)
    const std::string MAVKA_DIV_DIV = "мОст2"; // мОст2(а, б)
    const std::string MAVKA_POW = "мСтпн"; // мСтпн(а, б)
    const std::string MAVKA_NOT = "мНі"; // мНі(а)
    const std::string MAVKA_BIT_AND = "мДвІ"; // мДвІ(а, б)
    const std::string MAVKA_BIT_OR = "мДАбо"; // мДАбо(а, б)
    const std::string MAVKA_BIT_XOR = "мДваб"; // мДваб(а, б)
    const std::string MAVKA_BIT_NOT = "мДні"; // мДні(а)
    const std::string MAVKA_BIT_LSHIFT = "мЗвлв"; // мЗвлв(а, б)
    const std::string MAVKA_BIT_RSHIFT = "мЗвпр"; // мЗвпр(а, б)
    const std::string MAVKA_AS = "мЯк"; // мЯк(а, б)
    const std::string MAVKA_EQ = "мРівн"; // мРівн(а, б)
    const std::string MAVKA_LT = "мМенш"; // мМенш(а, б)
    const std::string MAVKA_LE = "мМері"; // мМері(а, б)
    const std::string MAVKA_GT = "мБілш"; // мБілш(а, б)
    const std::string MAVKA_GE = "мБірі"; // мБірі(а, б)
    const std::string MAVKA_MODULE = "мМодл"; // мМодл(назва, функція)
    const std::string MAVKA_NEGATIVE = "мНегт"; // мНегт(значення)
    const std::string MAVKA_POSITIVE = "мПозт"; // мПозт(значення)
    const std::string MAVKA_POST_DECREMENT = "мПдек"; // мПдек(значення)
    const std::string MAVKA_POST_INCREMENT = "мПінк"; // мПінк(значення)
    const std::string MAVKA_PRE_DECREMENT = "мПрдк"; // мПрдк(значення)
    const std::string MAVKA_PRE_INCREMENT = "мПрік"; // мПрік(значення)
    const std::string MAVKA_GIVE = "мДати"; // мДати(модуль, назва, значення)
    const std::string MAVKA_STRUCTURE = "мСтрк"; // мСтрк(назва, параметри, предок)
    const std::string MAVKA_IS = "мЄ"; // мЄ(а, б)
    const std::string MAVKA_CONTAINS = "мМає"; // мМає(а, б)
    const std::string MAVKA_FROM_TO = "мЦВід"; // мЦВід(від, до, символ, функція)
    const std::string MAVKA_FROM_TO_FN = "мЦВідФ"; // мЦВідФ(оператор, крок)
    const std::string MAVKA_VALUES_ITERATOR = "мІтер"; // мІтер(значення)
    const std::string MAVKA_ENTRIES_ITERATOR = "мІтерП"; // мІтерП(значення)
    const std::string MAVKA_PARENT = "мСпрд"; // мСпрд(я)

    inline std::string varname(const std::string& name) {
        return "м_" + name;
    }

    class CompilationError {
    public:
        std::string path;
        size_t line{};
        size_t column{};
        std::string message;
    };

    class CompilationSubject {
    public:
        virtual ~CompilationSubject() = default;
    };

    class CompilationScope {
    public:
        virtual ~CompilationScope() = default;

        CompilationScope* parent = nullptr;
        std::map<std::string, CompilationSubject *> subjects;
        std::map<std::string, std::string> modules;
        std::map<std::string, std::string> debug;
        bool store_debug = false;

        virtual bool has_module(const std::string& name) {
            return root()->modules.contains(name);
        }

        virtual std::string get_module(const std::string& name) {
            return root()->modules.find(name)->second;
        }

        virtual void set_module(const std::string& name, std::string code) {
            root()->modules.insert_or_assign(name, code);
        }

        virtual std::string put_debug(std::string path, size_t line, size_t column) {
            if (!root()->store_debug) {
                return "";
            }
            const auto debug_id = std::to_string(root()->debug.size());
            const auto debug_name = "DI" + debug_id;
            root()->debug[debug_name] = "\"" + path + ":" + std::to_string(line) + ":" + std::to_string(column) + "\"";
            return debug_name;
        }

        virtual CompilationError* assign(const std::string& name) {
            subjects.insert_or_assign(name, new CompilationSubject());
            return nullptr;
        }

        virtual CompilationSubject* get_local(const std::string& name) const {
            const auto subject_it = subjects.find(name);
            if (subject_it != subjects.end()) {
                return subject_it->second;
            }
            return nullptr;
        }

        virtual bool has_local(const std::string& name) const {
            const auto subject_it = subjects.find(name);
            if (subject_it != subjects.end()) {
                return true;
            }
            return false;
        }

        virtual CompilationSubject* get(const std::string& name) const {
            if (const auto subject = get_local(name)) {
                return subject;
            }
            if (parent) {
                return parent->get(name);
            }
            return nullptr;
        }

        virtual bool has(const std::string& name) const {
            if (has_local(name)) {
                return true;
            }
            if (parent) {
                return parent->has(name);
            }
            return false;
        }

        virtual CompilationScope* root() {
            if (parent) {
                return parent->root();
            }
            return this;
        }
    };

    class CompilationMicroScope final : public CompilationScope {
    public:
        CompilationError* assign(const std::string& name) override {
            return parent->assign(name);
        }

        CompilationSubject* get_local(const std::string& name) const override {
            return parent->get_local(name);
        }

        bool has_local(const std::string& name) const override {
            return parent->has_local(name);
        }

        CompilationSubject* get(const std::string& name) const override {
            return parent->get(name);
        }

        bool has(const std::string& name) const override {
            return parent->has(name);
        }

        CompilationScope* root() override {
            return parent->root();
        }
    };

    class NodeCompilationResult {
    public:
        CompilationError* error = nullptr;
        std::string result;
    };

    class CompilationResult : public NodeCompilationResult {
    };

    class GetModuleResult {
    public:
        std::string error;
        std::string result;
        bool builtin = false;
    };

    class CompilationOptions {
    public:
        CompilationOptions* parent = nullptr;
        std::string root_module_path;
        std::string current_module_path;
        std::string std_code;
        std::string args;
        int body_depth = 0;
        bool allow_js = false;

        GetModuleResult* (*get_module_name)(bool, std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_module_path)(bool, std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_module_code)(bool, std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_remote_module_name)(std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_remote_module_path)(std::string, CompilationOptions*) = nullptr;

        GetModuleResult* (*get_remote_module_code)(std::string, CompilationOptions*) = nullptr;

        CompilationOptions* clone() {
            const auto clone = new CompilationOptions();
            clone->parent = this;
            clone->root_module_path = root_module_path;
            clone->current_module_path = current_module_path;
            clone->std_code = std_code;
            clone->body_depth = body_depth;
            clone->allow_js = allow_js;
            clone->get_module_name = get_module_name;
            clone->get_module_path = get_module_path;
            clone->get_module_code = get_module_code;
            clone->get_remote_module_name = get_remote_module_name;
            clone->get_remote_module_path = get_remote_module_path;
            clone->get_remote_module_code = get_remote_module_code;
            return clone;
        }
    };

    NodeCompilationResult* compile_node(mavka::ast::ASTNode* node,
                                        CompilationScope* scope,
                                        CompilationOptions* options);

    NodeCompilationResult* compile_body(const std::vector<mavka::ast::ASTNode *>& body,
                                        CompilationScope* scope,
                                        CompilationOptions* options,
                                        const bool wrap = true,
                                        const std::string& before = "");

    NodeCompilationResult* compile_params(std::vector<mavka::ast::ParamNode *> params,
                                          CompilationScope* scope,
                                          CompilationOptions* options);

    NodeCompilationResult* compile_structure_params(std::vector<mavka::ast::StructureParamNode *> params,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

    // TypesCompilationResult* compile_types(std::vector<mavka::ast::ASTNode *> types,
    //                                       CompilationScope* scope,
    //                                       CompilationOptions* options);

    NodeCompilationResult* compile_anon_diia_node(const mavka::ast::AnonDiiaNode* anon_diia_node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options);

    NodeCompilationResult* compile_arithmetic_node(const mavka::ast::ArithmeticNode* arithmetic_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_array_node(const mavka::ast::ArrayNode* array_node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);

    NodeCompilationResult* compile_as_node(const mavka::ast::AsNode* as_node,
                                           CompilationScope* scope,
                                           CompilationOptions* options);

    NodeCompilationResult* compile_assign_by_identifier_node(
        const mavka::ast::AssignByIdentifierNode* assign_by_identifier_node,
        CompilationScope* scope,
        CompilationOptions* options);

    NodeCompilationResult* compile_assign_by_element_node(const mavka::ast::AssignByElementNode* assign_by_element_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options);

    NodeCompilationResult* compile_assign_simple_node(const mavka::ast::AssignSimpleNode* assign_simple_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);

    NodeCompilationResult* compile_bitwise_node(const mavka::ast::BitwiseNode* bitwise_node,
                                                CompilationScope* scope,
                                                CompilationOptions* options);

    NodeCompilationResult* compile_bitwise_not_node(const mavka::ast::BitwiseNotNode* bitwise_not_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

    NodeCompilationResult* compile_break_node(const mavka::ast::BreakNode* break_node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);

    NodeCompilationResult* compile_call_node(const mavka::ast::CallNode* call_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_arg_node(const mavka::ast::ArgNode* arg_node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);

    NodeCompilationResult* compile_chain_node(const mavka::ast::ChainNode* chain_node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);

    NodeCompilationResult* compile_comparison_node(const mavka::ast::ComparisonNode* comparison_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_continue_node(mavka::ast::ContinueNode* continue_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_diia_body(const std::vector<mavka::ast::ASTNode *>& body,
                                             const std::vector<mavka::ast::ParamNode *>& params,
                                             CompilationScope* scope,
                                             CompilationOptions* options,
                                             const bool wrap = true,
                                             const bool parent = false);

    NodeCompilationResult* compile_diia_node(const mavka::ast::DiiaNode* diia_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_each_node(const mavka::ast::EachNode* each_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_eval_node(mavka::ast::EvalNode* eval_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_function_node(const mavka::ast::FunctionNode* function_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_from_to_simple_node(const mavka::ast::FromToSimpleNode* from_to_simple_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);

    NodeCompilationResult* compile_from_to_complex_node(const mavka::ast::FromToComplexNode* from_to_complex_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options);

    NodeCompilationResult* compile_get_element_node(const mavka::ast::GetElementNode* get_element_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

    NodeCompilationResult* compile_give_node(const mavka::ast::GiveNode* give_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_god_node(mavka::ast::GodNode* node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);

    NodeCompilationResult* compile_identifier_node(const mavka::ast::IdentifierNode* identifier_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_if_node(const mavka::ast::IfNode* if_node,
                                           CompilationScope* scope,
                                           CompilationOptions* options);

    NodeCompilationResult* compile_module_node(const mavka::ast::ModuleNode* module_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);

    NodeCompilationResult* compile_mockup_diia_node(const mavka::ast::MockupDiiaNode* mockup_diia_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

    NodeCompilationResult* compile_mockup_module_node(const mavka::ast::MockupModuleNode* mockup_module_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);

    NodeCompilationResult* compile_mockup_object_node(const mavka::ast::MockupObjectNode* mockup_object_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);

    NodeCompilationResult* compile_mockup_structure_node(const mavka::ast::MockupStructureNode* mockup_structure,
                                                         CompilationScope* scope,
                                                         CompilationOptions* options);

    NodeCompilationResult* compile_mockup_subject_node(const mavka::ast::MockupSubjectNode* mockup_subject_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);

    NodeCompilationResult* compile_negative_node(const mavka::ast::NegativeNode* negative_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_not_node(const mavka::ast::NotNode* not_node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);

    NodeCompilationResult* compile_number_node(const mavka::ast::NumberNode* number_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);

    NodeCompilationResult* compile_positive_node(const mavka::ast::PositiveNode* positive_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_post_decrement_node(const mavka::ast::PostDecrementNode* post_decrement_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);

    NodeCompilationResult* compile_post_increment_node(const mavka::ast::PostIncrementNode* post_increment_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);

    NodeCompilationResult* compile_pre_decrement_node(const mavka::ast::PreDecrementNode* pre_decrement_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);

    NodeCompilationResult* compile_pre_increment_node(const mavka::ast::PreIncrementNode* pre_increment_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options);

    NodeCompilationResult* compile_dictionary_node(const mavka::ast::DictionaryNode* dictionary_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_return_node(const mavka::ast::ReturnNode* return_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);

    NodeCompilationResult* compile_string_node(const mavka::ast::StringNode* string_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);

    NodeCompilationResult* compile_structure_node(const mavka::ast::StructureNode* structure_node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options);

    NodeCompilationResult* compile_take_module_node(const mavka::ast::TakeModuleNode* take_module_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

    NodeCompilationResult* compile_take_pak_node(const mavka::ast::TakePakNode* take_pak_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);

    NodeCompilationResult* compile_ternary_node(const mavka::ast::TernaryNode* ternary_node,
                                                CompilationScope* scope,
                                                CompilationOptions* options);

    NodeCompilationResult* compile_test_node(const mavka::ast::TestNode* test_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_throw_node(const mavka::ast::ThrowNode* throw_node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);

    NodeCompilationResult* compile_try_node(const mavka::ast::TryNode* try_node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);

    NodeCompilationResult* compile_type_value_node(mavka::ast::TypeValueNode* type_value_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);

    NodeCompilationResult* compile_type_value_single_node(mavka::ast::TypeValueSingleNode* node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options);

    NodeCompilationResult* compile_wait_node(const mavka::ast::WaitNode* wait_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);

    NodeCompilationResult* compile_while_node(const mavka::ast::WhileNode* while_node,
                                              CompilationScope* scope,
                                              CompilationOptions* options);

    inline NodeCompilationResult* compile_anon_diia_node(const mavka::ast::AnonDiiaNode* anon_diia_node,
                                                         CompilationScope* scope,
                                                         CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, anon_diia_node->start_line,
                                             anon_diia_node->start_column);

        const auto node_compilation_result = new NodeCompilationResult();
        const auto anon_diia_scope = new CompilationScope();
        anon_diia_scope->parent = scope;
        const auto params_compilation_result = compile_params(anon_diia_node->params, anon_diia_scope, options);
        if (params_compilation_result->error) {
            node_compilation_result->error = params_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_params = params_compilation_result->result;

        const auto body = compile_diia_body(anon_diia_node->body, anon_diia_node->params, anon_diia_scope, options,
                                            true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_DIIA + "(null," +
                                          compiled_params + "," + (anon_diia_node->async ? "async " : "") +
                                          "function(args)" + body->result + "," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_arithmetic_node(const mavka::ast::ArithmeticNode* arithmetic_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, arithmetic_node->start_line,
                                             arithmetic_node->start_column);

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
                    MAVKA_ADD + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (arithmetic_node->op == "-") {
            node_compilation_result->result =
                    MAVKA_SUB + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (arithmetic_node->op == "*") {
            node_compilation_result->result =
                    MAVKA_MUL + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (arithmetic_node->op == "/") {
            node_compilation_result->result =
                    MAVKA_DIV + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (arithmetic_node->op == "%") {
            node_compilation_result->result = MAVKA_MOD + "(" + compiled_left->result + "," + compiled_right->result +
                                              "," + diName + ")";
        } else if (arithmetic_node->op == "//") {
            node_compilation_result->result = MAVKA_DIV_DIV + "(" + compiled_left->result + "," + compiled_right->result
                                              +
                                              "," + diName + ")";
        } else if (arithmetic_node->op == "**") {
            node_compilation_result->result = MAVKA_POW + "(" + compiled_left->result + "," + compiled_right->result
                                              +
                                              "," + diName + ")";
        } else {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = arithmetic_node->start_line;
            node_compilation_result->error->column = arithmetic_node->start_column;
            node_compilation_result->error->message = "unsupported arithmetic operation: " + arithmetic_node->op;
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_array_node(const mavka::ast::ArrayNode* array_node,
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

    inline NodeCompilationResult* compile_as_node(const mavka::ast::AsNode* as_node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options) {
        // const auto diName = scope->put_debug(options->current_module_path, as_node->start_line,
        //                                      as_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        node_compilation_result->error = new CompilationError();
        node_compilation_result->error->path = options->current_module_path;
        node_compilation_result->error->line = as_node->start_line;
        node_compilation_result->error->column = as_node->start_column;
        node_compilation_result->error->message = "Вказівка \"як\" тимчасово не працює.";
        return node_compilation_result;
        // const auto left = compile_node(as_node->left, scope, options);
        // if (left->error) {
        //     node_compilation_result->error = left->error;
        //     return node_compilation_result;
        // }
        // const auto right = compile_node(as_node->right, scope, options);
        // if (right->error) {
        //     node_compilation_result->error = right->error;
        //     return node_compilation_result;
        // }
        // node_compilation_result->result = MAVKA_AS + "(" + left->result + "," + right->result + "," + diName + ")";
        // return node_compilation_result;
    }

    inline NodeCompilationResult* compile_assign_by_identifier_node(
        const mavka::ast::AssignByIdentifierNode* assign_by_identifier_node,
        CompilationScope* scope,
        CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, assign_by_identifier_node->start_line,
                                             assign_by_identifier_node->start_column);
        if (assign_by_identifier_node->op == "=") {
            const auto node_compilation_result = new NodeCompilationResult();
            const auto assign_left = compile_node(assign_by_identifier_node->left, scope, options);
            if (assign_left->error) {
                node_compilation_result->error = assign_left->error;
                return node_compilation_result;
            }
            const auto assign_value = compile_node(assign_by_identifier_node->value, scope, options);
            if (assign_value->error) {
                node_compilation_result->error = assign_value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_SET + "(" + assign_left->result + ",\"" +
                                              assign_by_identifier_node->identifier + "\"," + assign_value->result +
                                              "," + diName + ")";
            return node_compilation_result;
        } else {
            auto operation = assign_by_identifier_node->op;
            if (operation == "+=") {
                operation = "+";
            }
            if (operation == "-=") {
                operation = "-";
            }
            if (operation == "*=") {
                operation = "*";
            }
            if (operation == "/=") {
                operation = "/";
            }
            if (operation == "%=") {
                operation = "%";
            }
            if (operation == "//=") {
                operation = "//";
            }
            if (operation == "**=") {
                operation = "**";
            }
            const auto new_assign_by_identifier_node = new mavka::ast::AssignByIdentifierNode();
            new_assign_by_identifier_node->left = assign_by_identifier_node->left;
            new_assign_by_identifier_node->identifier = assign_by_identifier_node->identifier;
            new_assign_by_identifier_node->op = "=";
            const auto arithmetic_node = new mavka::ast::ArithmeticNode();
            const auto chain_node = new mavka::ast::ChainNode();
            chain_node->left = assign_by_identifier_node->left;
            const auto identifier_node = new mavka::ast::IdentifierNode();
            identifier_node->name = assign_by_identifier_node->identifier;
            chain_node->right = identifier_node;
            arithmetic_node->left = chain_node;
            arithmetic_node->right = assign_by_identifier_node->value;
            arithmetic_node->op = operation;
            new_assign_by_identifier_node->value = arithmetic_node;
            return compile_assign_by_identifier_node(new_assign_by_identifier_node, scope, options);
        }
    }

    inline NodeCompilationResult* compile_assign_by_element_node(
        const mavka::ast::AssignByElementNode* assign_by_element_node,
        CompilationScope* scope,
        CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, assign_by_element_node->start_line,
                                             assign_by_element_node->start_column);
        if (assign_by_element_node->op == "=") {
            const auto node_compilation_result = new NodeCompilationResult();
            const auto assign_left = compile_node(assign_by_element_node->left, scope, options);
            if (assign_left->error) {
                node_compilation_result->error = assign_left->error;
                return node_compilation_result;
            }
            const auto assign_element = compile_node(assign_by_element_node->element, scope, options);
            if (assign_element->error) {
                node_compilation_result->error = assign_element->error;
                return node_compilation_result;
            }
            const auto assign_value = compile_node(assign_by_element_node->value, scope, options);
            if (assign_value->error) {
                node_compilation_result->error = assign_value->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_SET_ELEMENT + "(" + assign_left->result + "," +
                                              assign_element->result + "," + assign_value->result + "," + diName + ")";
            return node_compilation_result;
        } else {
            auto operation = assign_by_element_node->op;
            if (operation == "+=") {
                operation = "+";
            }
            if (operation == "-=") {
                operation = "-";
            }
            if (operation == "*=") {
                operation = "*";
            }
            if (operation == "/=") {
                operation = "/";
            }
            if (operation == "%=") {
                operation = "%";
            }
            if (operation == "//=") {
                operation = "//";
            }
            if (operation == "**=") {
                operation = "**";
            }
            const auto new_assign_by_element_node = new mavka::ast::AssignByElementNode();
            new_assign_by_element_node->left = assign_by_element_node->left;
            new_assign_by_element_node->element = assign_by_element_node->element;
            new_assign_by_element_node->op = "=";
            const auto arithmetic_node = new mavka::ast::ArithmeticNode();
            const auto get_element_node = new mavka::ast::GetElementNode();
            get_element_node->value = assign_by_element_node->left;
            get_element_node->index = assign_by_element_node->element;
            arithmetic_node->left = get_element_node;
            arithmetic_node->right = assign_by_element_node->value;
            arithmetic_node->op = operation;
            new_assign_by_element_node->value = arithmetic_node;
            return compile_assign_by_element_node(new_assign_by_element_node, scope, options);
        }
    }

    inline NodeCompilationResult* compile_assign_simple_node(const mavka::ast::AssignSimpleNode* assign_simple_node,
                                                             CompilationScope* scope,
                                                             CompilationOptions* options) {
        if (assign_simple_node->op == "=") {
            const auto node_compilation_result = new NodeCompilationResult();
            const auto assign_name = assign_simple_node->name;
            const auto compiled_assign_value = compile_node(assign_simple_node->value, scope, options);
            if (compiled_assign_value->error) {
                node_compilation_result->error = compiled_assign_value->error;
                return node_compilation_result;
            }
            if (const auto assign_error = scope->assign(assign_name)) {
                node_compilation_result->error = assign_error;
                return node_compilation_result;
            }
            node_compilation_result->result = varname(assign_name) + "=" + compiled_assign_value->result;
            return node_compilation_result;
        } else {
            auto operation = assign_simple_node->op;
            if (operation == "+=") {
                operation = "+";
            }
            if (operation == "-=") {
                operation = "-";
            }
            if (operation == "*=") {
                operation = "*";
            }
            if (operation == "/=") {
                operation = "/";
            }
            if (operation == "%=") {
                operation = "%";
            }
            if (operation == "//=") {
                operation = "//";
            }
            if (operation == "**=") {
                operation = "**";
            }
            const auto new_assign_simple_node = new mavka::ast::AssignSimpleNode();
            new_assign_simple_node->name = assign_simple_node->name;
            new_assign_simple_node->op = "=";
            const auto arithmetic_node = new mavka::ast::ArithmeticNode();
            const auto identifier_node = new mavka::ast::IdentifierNode();
            identifier_node->name = assign_simple_node->name;
            arithmetic_node->left = identifier_node;
            arithmetic_node->right = assign_simple_node->value;
            arithmetic_node->op = operation;
            new_assign_simple_node->value = arithmetic_node;
            return compile_assign_simple_node(new_assign_simple_node, scope, options);
        }
    }

    inline NodeCompilationResult* compile_bitwise_node(const mavka::ast::BitwiseNode* bitwise_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, bitwise_node->start_line,
                                             bitwise_node->start_column);
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
                    MAVKA_BIT_AND + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (bitwise_node->op == "|") {
            node_compilation_result->result =
                    MAVKA_BIT_OR + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (bitwise_node->op == "^") {
            node_compilation_result->result =
                    MAVKA_BIT_XOR + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (bitwise_node->op == "<<") {
            node_compilation_result->result =
                    MAVKA_BIT_LSHIFT + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (bitwise_node->op == ">>") {
            node_compilation_result->result =
                    MAVKA_BIT_RSHIFT + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = bitwise_node->start_line;
            node_compilation_result->error->column = bitwise_node->start_column;
            node_compilation_result->error->message = "unsupported bitwise operation: " + bitwise_node->op;
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_bitwise_not_node(const mavka::ast::BitwiseNotNode* bitwise_not_node,
                                                           CompilationScope* scope,
                                                           CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, bitwise_not_node->start_line,
                                             bitwise_not_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto compiled_value = compile_node(bitwise_not_node->value, scope, options);
        if (compiled_value->error) {
            node_compilation_result->error = compiled_value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_BIT_NOT + "(" + compiled_value->result + "," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_break_node(const mavka::ast::BreakNode* break_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        // todo: handle only loops
        node_compilation_result->result = "break";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_call_node(const mavka::ast::CallNode* call_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, call_node->start_line,
                                             call_node->start_column);
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
        node_compilation_result->result = MAVKA_CALL + "(" + value->result + ",{" + args_string + "}," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_arg_node(const mavka::ast::ArgNode* arg_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        if (arg_node->spread) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = arg_node->start_line;
            node_compilation_result->error->column = arg_node->start_column;
            node_compilation_result->error->message = "Оператор розгортання не підтримується в аргументах.";
            return node_compilation_result;
        }
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

    inline NodeCompilationResult* compile_chain_node(const mavka::ast::ChainNode* chain_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, chain_node->start_line,
                                             chain_node->start_column);

        const auto node_compilation_result = new NodeCompilationResult();
        const auto left = compile_node(chain_node->left, scope, options);
        if (left->error) {
            node_compilation_result->error = left->error;
            return node_compilation_result;
        }
        if (jejalyk::tools::instanceof<mavka::ast::IdentifierNode>(chain_node->right)) {
            const auto right = dynamic_cast<mavka::ast::IdentifierNode *>(chain_node->right)->name;
            node_compilation_result->result = MAVKA_GET + "(" + left->result + ",\"" + right + "\",null," + diName +
                                              ")";
        } else {
            const auto right = compile_node(chain_node->right, scope, options);
            if (right->error) {
                node_compilation_result->error = right->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_GET + "(" + left->result + "," + right->result + ",null," + diName +
                                              ")";
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_comparison_node(const mavka::ast::ComparisonNode* comparison_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, comparison_node->start_line,
                                             comparison_node->start_column);
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
        if (comparison_node->op == "==" || comparison_node->op == "рівно") {
            node_compilation_result->result =
                    MAVKA_EQ + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (comparison_node->op == "!=" || comparison_node->op == "не рівно") {
            node_compilation_result->result =
                    "!" + MAVKA_EQ + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (comparison_node->op == "<" || comparison_node->op == "менше") {
            node_compilation_result->result =
                    MAVKA_LT + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (comparison_node->op == "<=" || comparison_node->op == "не більше") {
            node_compilation_result->result =
                    MAVKA_LE + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (comparison_node->op == ">" || comparison_node->op == "більше") {
            node_compilation_result->result =
                    MAVKA_GT + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (comparison_node->op == ">=" || comparison_node->op == "не менше") {
            node_compilation_result->result =
                    MAVKA_GE + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (comparison_node->op == "є") {
            node_compilation_result->result =
                    MAVKA_IS + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (comparison_node->op == "не є") {
            node_compilation_result->result =
                    "!" + MAVKA_IS + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (comparison_node->op == "містить") {
            node_compilation_result->result =
                    MAVKA_CONTAINS + "(" + compiled_left->result + "," + compiled_right->result + "," + diName + ")";
        } else if (comparison_node->op == "не містить") {
            node_compilation_result->result =
                    "!" + MAVKA_CONTAINS + "(" + compiled_left->result + "," + compiled_right->result + "," + diName +
                    ")";
        } else {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = comparison_node->start_line;
            node_compilation_result->error->column = comparison_node->start_column;
            node_compilation_result->error->message = "unsupported comparison operation: " + comparison_node->op;
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_continue_node(mavka::ast::ContinueNode* continue_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        // todo: handle only loops
        node_compilation_result->result = "continue";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_diia_body(const std::vector<mavka::ast::ASTNode *>& body,
                                                    const std::vector<mavka::ast::ParamNode *>& params,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options,
                                                    const bool wrap,
                                                    const bool parent) {
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> before;
        if (parent) {
            before.emplace_back("var м_предок=" + MAVKA_PARENT + "(м_я)");
        }
        for (int i = 0; i < params.size(); ++i) {
            const auto param = params[i];
            if (param->value) {
                const auto compiled_value = compile_node(param->value, scope, options);
                if (compiled_value->error) {
                    node_compilation_result->error = compiled_value->error;
                    return node_compilation_result;
                }
                before.push_back(
                    varname(param->name) + "=args[" + std::to_string(i) + "]===undefined?args[\"" + param->name +
                    "\"]===undefined?(" +
                    compiled_value->result + "):args[\"" + param->name + "\"]:args[" + std::to_string(i) + "]"
                );
            } else {
                if (param->variadic) {
                    before.push_back(
                        varname(param->name) + "=args[\"" + param->name + "\"]===undefined?Object.values(args).slice(" +
                        std::to_string(i) + "):args[\"" + param->name + "\"]");
                } else {
                    before.push_back(
                        varname(param->name) + "=args[" + std::to_string(i) + "]===undefined?args[\"" + param->name +
                        "\"]:args[" + std::to_string(i) + "]");
                }
            }
        }
        const auto body_compilation_result = compile_body(body, scope, options, wrap, tools::implode(before, ";\n"));
        if (body_compilation_result->error) {
            node_compilation_result->error = body_compilation_result->error;
            return node_compilation_result;
        }
        node_compilation_result->result = body_compilation_result->result;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_diia_node(const mavka::ast::DiiaNode* diia_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, diia_node->start_line,
                                             diia_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        scope->assign(diia_node->name);
        const auto diia_scope = new CompilationScope();
        diia_scope->parent = scope;
        const auto params_compilation_result = compile_params(diia_node->params, diia_scope, options);
        if (params_compilation_result->error) {
            node_compilation_result->error = params_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_params = params_compilation_result->result;

        if (diia_node->structure.empty()) {
            const auto body = compile_diia_body(diia_node->body, diia_node->params, diia_scope, options, true);
            if (body->error) {
                node_compilation_result->error = body->error;
                return node_compilation_result;
            }
            node_compilation_result->result = varname(diia_node->name) + "=" +
                                              MAVKA_DIIA + "(" + "\"" + diia_node->name
                                              + "\"" + "," +
                                              compiled_params + "," + (diia_node->async ? "async " : "") +
                                              "function(args)" + body->result + "," + diName + ")";
        } else {
            diia_scope->assign("я");
            diia_scope->assign("предок");
            const auto body = compile_diia_body(diia_node->body, diia_node->params, diia_scope, options, true, true);
            if (body->error) {
                node_compilation_result->error = body->error;
                return node_compilation_result;
            }
            node_compilation_result->result = MAVKA_SET_METHOD + "(" + varname(diia_node->structure) + "," +
                                              MAVKA_METHOD + "(\"" + diia_node->name + "\"," +
                                              compiled_params + ",function(м_я,args)" + body->result + ")," + diName +
                                              ")";
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_each_node(const mavka::ast::EachNode* each_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, each_node->start_line,
                                             each_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(each_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        const auto each_scope = new CompilationMicroScope();
        each_scope->parent = scope;
        each_scope->assign(each_node->name);
        if (!each_node->keyName.empty()) {
            each_scope->assign(each_node->keyName);
        }
        const auto body = compile_body(each_node->body, each_scope, options, true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        if (each_node->keyName.empty()) {
            node_compilation_result->result =
                    "for(" + varname(each_node->name) + " of " + MAVKA_VALUES_ITERATOR + "(" + value->result
                    + "," + diName + "))" + body->result + "";
        } else {
            node_compilation_result->result =
                    "for([" + varname(each_node->keyName) + "," + varname(each_node->name) +
                    "] of " + MAVKA_ENTRIES_ITERATOR + "(" + value->result
                    + "," + diName + "))" + body->result + "";
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_eval_node(mavka::ast::EvalNode* eval_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        if (!options->allow_js) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = eval_node->start_line;
            node_compilation_result->error->column = eval_node->start_column;
            node_compilation_result->error->message =
                    "JS-розширення вимкнені. Додайте опцію \"--розширення=1\", щоб увімкнути.";
            return node_compilation_result;
        }
        if (tools::instanceof<mavka::ast::StringNode>(eval_node->value)) {
            const auto string_value = dynamic_cast<mavka::ast::StringNode *>(eval_node->value)->value;
            node_compilation_result->result = "/* --- js --- */\n" + string_value + "\n/* --- /js --- */";
        } else {
            const auto eval_value = compile_node(eval_node->value, scope, options);
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_function_node(const mavka::ast::FunctionNode* function_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, function_node->start_line,
                                             function_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto function_scope = new CompilationScope();
        function_scope->parent = scope;
        const auto params_compilation_result = compile_params(function_node->params, function_scope, options);
        if (params_compilation_result->error) {
            node_compilation_result->error = params_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_params = params_compilation_result->result;

        const auto body = compile_diia_body(function_node->body, function_node->params, function_scope, options, true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_DIIA + "(null," +
                                          compiled_params + "," + (function_node->async ? "async " : "") +
                                          "function(args)" + body->result + "," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_from_to_simple_node(const mavka::ast::FromToSimpleNode* from_to_simple_node,
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

    inline NodeCompilationResult* compile_from_to_complex_node(
        const mavka::ast::FromToComplexNode* from_to_complex_node,
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

    inline NodeCompilationResult* compile_get_element_node(const mavka::ast::GetElementNode* get_element_node,
                                                           CompilationScope* scope,
                                                           CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, get_element_node->start_line,
                                             get_element_node->start_column);
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
        node_compilation_result->result = MAVKA_GET_ELEMENT + "(" + value->result + "," + index->result + "," + diName +
                                          ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_give_node(const mavka::ast::GiveNode* give_node,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, give_node->start_line,
                                             give_node->start_column);

        const auto node_compilation_result = new NodeCompilationResult();
        const auto elements = new std::vector<std::string>();
        for (const auto& element: give_node->elements) {
            if (!element->as.empty()) {
                elements->push_back(
                    MAVKA_GIVE + "(module,\"" + element->as + "\"," + varname(element->name) + "," + diName + ")");
            } else {
                elements->push_back(
                    MAVKA_GIVE + "(module,\"" + element->name + "\"," + varname(element->name) + "," + diName + ")");
            }
        }
        node_compilation_result->result = tools::implode(*elements, ";\n");
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_god_node(mavka::ast::GodNode* node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        node_compilation_result->error = new CompilationError();
        node_compilation_result->error->path = options->current_module_path;
        node_compilation_result->error->line = node->start_line;
        node_compilation_result->error->column = node->start_column;
        node_compilation_result->error->message = "Бог тимчасово не працює.";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_identifier_node(const mavka::ast::IdentifierNode* identifier_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        if (!scope->has(identifier_node->name)) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = identifier_node->start_line;
            node_compilation_result->error->column = identifier_node->start_column;
            node_compilation_result->error->message = "Субʼєкт \"" + identifier_node->name + "\" не визначено.";
            return node_compilation_result;
        }
        node_compilation_result->result = varname(identifier_node->name);
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_if_node(const mavka::ast::IfNode* if_node,
                                                  CompilationScope* scope,
                                                  CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto condition = compile_node(if_node->condition, scope, options);
        if (condition->error) {
            node_compilation_result->error = condition->error;
            return node_compilation_result;
        }
        const auto if_scope = new CompilationMicroScope();
        if_scope->parent = scope;
        const auto body = compile_body(if_node->body, if_scope, options, true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        if (!if_node->else_body.empty()) {
            const auto else_if_scope = new CompilationMicroScope();
            else_if_scope->parent = scope;
            const auto else_body = compile_body(if_node->else_body, else_if_scope, options, true);
            if (else_body->error) {
                node_compilation_result->error = else_body->error;
                return node_compilation_result;
            }
            node_compilation_result->result = "if(" + condition->result + ")" + body->result + "else" + else_body->
                                              result + "";
        } else {
            node_compilation_result->result = "if(" + condition->result + ")" + body->result + "";
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_module_node(const mavka::ast::ModuleNode* module_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, module_node->start_line,
                                             module_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto module_scope = new CompilationScope();
        module_scope->parent = scope;
        scope->assign(module_node->name);
        const auto body = compile_body(module_node->body, module_scope, options, true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = varname(module_node->name) + "=await " + MAVKA_MODULE + "(" + "\"" +
                                          module_node
                                          ->name + "\"" +
                                          ",async function(module)"
                                          + body->result + "," + diName + ")";
        return node_compilation_result;
    }


    inline NodeCompilationResult* compile_mockup_diia_node(const mavka::ast::MockupDiiaNode* mockup_diia_node,
                                                           CompilationScope* scope,
                                                           CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_diia_node->name;
        scope->assign(name);
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_mockup_module_node(const mavka::ast::MockupModuleNode* mockup_module_node,
                                                             CompilationScope* scope,
                                                             CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_module_node->name;
        scope->assign(name);
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_mockup_object_node(const mavka::ast::MockupObjectNode* mockup_object_node,
                                                             CompilationScope* scope,
                                                             CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_object_node->name;
        scope->assign(name);
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_mockup_structure_node(const mavka::ast::MockupStructureNode* mockup_structure,
                                                                CompilationScope* scope,
                                                                CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_structure->name;
        scope->assign(name);
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_mockup_subject_node(const mavka::ast::MockupSubjectNode* mockup_subject_node,
                                                              CompilationScope* scope,
                                                              CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto name = mockup_subject_node->name;
        scope->assign(name);
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_negative_node(const mavka::ast::NegativeNode* negative_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, negative_node->start_line,
                                             negative_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(negative_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_NEGATIVE + "(" + value->result + "," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_not_node(const mavka::ast::NotNode* not_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, not_node->start_line,
                                             not_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(not_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_NOT + "(" + value->result + "," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_number_node(const mavka::ast::NumberNode* number_node,
                                                      CompilationScope* scope,
                                                      CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        node_compilation_result->result = number_node->value;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_positive_node(const mavka::ast::PositiveNode* positive_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, positive_node->start_line,
                                             positive_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(positive_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_POSITIVE + "(" + value->result + "," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_post_decrement_node(const mavka::ast::PostDecrementNode* post_decrement_node,
                                                              CompilationScope* scope,
                                                              CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, post_decrement_node->start_line,
                                             post_decrement_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(post_decrement_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_POST_DECREMENT + "(" + value->result + ",(v)=>{" + value->result +
                                          "=v;}," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_post_increment_node(const mavka::ast::PostIncrementNode* post_increment_node,
                                                              CompilationScope* scope,
                                                              CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, post_increment_node->start_line,
                                             post_increment_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(post_increment_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_POST_INCREMENT + "(" + value->result + ",(v)=>{" + value->result +
                                          "=v;}," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_pre_decrement_node(const mavka::ast::PreDecrementNode* pre_decrement_node,
                                                             CompilationScope* scope,
                                                             CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, pre_decrement_node->start_line,
                                             pre_decrement_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(pre_decrement_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_PRE_DECREMENT + "(" + value->result + ",(v)=>{" + value->result +
                                          "=v;}," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_pre_increment_node(const mavka::ast::PreIncrementNode* pre_increment_node,
                                                             CompilationScope* scope,
                                                             CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, pre_increment_node->start_line,
                                             pre_increment_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(pre_increment_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = MAVKA_PRE_INCREMENT + "(" + value->result + ",(v)=>{" + value->result +
                                          "=v;}," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_dictionary_node(const mavka::ast::DictionaryNode* dictionary_node,
                                                          CompilationScope* scope,
                                                          CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> compiled_elements;
        for (const auto& element: dictionary_node->elements) {
            const auto value = compile_node(element->value, scope, options);
            if (value->error) {
                node_compilation_result->error = value->error;
                return node_compilation_result;
            }
            compiled_elements.push_back("[\"" + element->key + "\"," + value->result + "]");
        }
        node_compilation_result->result = "new Map([" + tools::implode(compiled_elements, ",") + "])";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_return_node(const mavka::ast::ReturnNode* return_node,
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

    inline NodeCompilationResult* compile_string_node(const mavka::ast::StringNode* string_node,
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

    inline NodeCompilationResult* compile_structure_node(const mavka::ast::StructureNode* structure_node,
                                                         CompilationScope* scope,
                                                         CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, structure_node->start_line,
                                             structure_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        scope->assign(structure_node->name);
        const auto compiled_params = compile_structure_params(structure_node->params, scope, options);
        if (compiled_params->error) {
            node_compilation_result->error = compiled_params->error;
            return node_compilation_result;
        }
        std::string parent = "undefined";
        if (structure_node->parent) {
            const auto compiled_parent = compile_node(structure_node->parent, scope, options);
            if (compiled_parent->error) {
                node_compilation_result->error = compiled_parent->error;
                return node_compilation_result;
            }
            parent = compiled_parent->result;
        }
        node_compilation_result->result = varname(structure_node->name) + "=" + MAVKA_STRUCTURE + "(" + "\""
                                          + structure_node->name + "\"" + "," +
                                          compiled_params->result + "," + parent + "," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_take_module_node(const mavka::ast::TakeModuleNode* take_module_node,
                                                           CompilationScope* scope,
                                                           CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto module_name_result = options->get_module_name(take_module_node->relative, take_module_node->name,
                                                                 options);
        if (!module_name_result->error.empty()) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = take_module_node->start_line;
            node_compilation_result->error->column = take_module_node->start_column;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_name = module_name_result->result;
        const auto module_path_result = options->get_module_path(take_module_node->relative, take_module_node->name,
                                                                 options);
        if (!module_path_result->error.empty()) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = take_module_node->start_line;
            node_compilation_result->error->column = take_module_node->start_column;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_path = module_path_result->result;
        const std::hash<std::string> hash_fn;
        const auto module_variable_name = take_module_node->as.empty() ? module_name : take_module_node->as;
        const auto temp_module_name = "module_" + module_name + "_" + std::to_string(hash_fn(module_path));
        const auto init_module_code = "await init_" + temp_module_name + "();\n" + varname(module_variable_name) + "=" +
                                      temp_module_name;
        if (scope->has_module(module_path)) {
            node_compilation_result->result = init_module_code;
            return node_compilation_result;
        }
        scope->set_module(module_path, "");
        const auto scope_compilation_options = options->clone();
        scope_compilation_options->current_module_path = module_path;
        const auto module_code_result = options->get_module_code(
            take_module_node->relative,
            take_module_node->name,
            scope_compilation_options
        );
        if (!module_code_result->error.empty()) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = take_module_node->start_line;
            node_compilation_result->error->column = take_module_node->start_column;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_code = module_code_result->result;
        if (take_module_node->as.empty()) {
            scope->assign(module_name);
        } else {
            scope->assign(take_module_node->as);
        }
        const auto module_parser_result = mavka::parser::parse(module_code);
        if (module_parser_result->error) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = module_parser_result->error->line;
            node_compilation_result->error->column = module_parser_result->error->column;
            node_compilation_result->error->message = module_parser_result->error->message;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_scope = new CompilationScope();
        module_scope->parent = scope->root();
        const auto module_compilation_result = compile_body(module_parser_result->program_node->body,
                                                            module_scope,
                                                            scope_compilation_options,
                                                            false);
        if (module_compilation_result->error) {
            node_compilation_result->error = module_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_module_code = "var " + temp_module_name + ";\n"
                                          + "var init_" + temp_module_name + "=async function(){\n"
                                          + "if(" + temp_module_name + "){ return; }\n"
                                          + "var module = await " + MAVKA_MODULE + "(" + "\"" + module_name + "\"" +
                                          ",async function(module){\n"
                                          + "var " + varname("___шлях_до_модуля___") + "=\"" + module_path + "\";\n"
                                          + module_compilation_result->result
                                          + "\n});\n"
                                          + temp_module_name + "=module;\n"
                                          + "\n}";
        scope->set_module(module_path, compiled_module_code);
        node_compilation_result->result = init_module_code;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_take_pak_node(const mavka::ast::TakePakNode* take_pak_node,
                                                        CompilationScope* scope,
                                                        CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto module_name_result = options->get_remote_module_name(take_pak_node->name, options);
        if (!module_name_result->error.empty()) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = take_pak_node->start_line;
            node_compilation_result->error->column = take_pak_node->start_column;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_name = module_name_result->result;
        const auto module_path_result = options->get_remote_module_path(take_pak_node->name, options);
        if (!module_path_result->error.empty()) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = take_pak_node->start_line;
            node_compilation_result->error->column = take_pak_node->start_column;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_variable_name = take_pak_node->as.empty() ? module_name : take_pak_node->as;
        const auto module_path = module_path_result->result;
        const std::hash<std::string> hash_fn;
        const auto temp_module_name = "module_" + module_name + "_" + std::to_string(hash_fn(module_path));
        const auto init_module_code = "await init_" + temp_module_name + "();\n" + varname(module_variable_name) + "=" +
                                      temp_module_name;
        if (scope->has_module(module_path)) {
            node_compilation_result->result = init_module_code;
            return node_compilation_result;
        }
        scope->set_module(module_path, "");
        const auto scope_compilation_options = options->clone();
        if (module_name_result->builtin) {
            scope_compilation_options->allow_js = true;
        }
        scope_compilation_options->root_module_path = module_path;
        scope_compilation_options->current_module_path = module_path;
        const auto module_code_result = options->get_remote_module_code(
            take_pak_node->name,
            scope_compilation_options
        );
        if (!module_code_result->error.empty()) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = take_pak_node->start_line;
            node_compilation_result->error->column = take_pak_node->start_column;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_code = module_code_result->result;
        if (take_pak_node->as.empty()) {
            scope->assign(module_name);
        } else {
            scope->assign(take_pak_node->as);
        }
        const auto module_parser_result = mavka::parser::parse(module_code);
        if (module_parser_result->error) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = module_parser_result->error->line;
            node_compilation_result->error->column = module_parser_result->error->column;
            node_compilation_result->error->message = module_parser_result->error->message;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_scope = new CompilationScope();
        module_scope->parent = scope->root();
        const auto module_compilation_result = compile_body(module_parser_result->program_node->body,
                                                            module_scope,
                                                            scope_compilation_options,
                                                            false);
        if (module_compilation_result->error) {
            node_compilation_result->error = module_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_module_code = "var " + temp_module_name + ";\n"
                                          + "var init_" + temp_module_name + "=async function(){\n"
                                          + "if(" + temp_module_name + "){ return; }\n"
                                          + "var module = await " + MAVKA_MODULE + "(" + "\"" + module_name + "\"" +
                                          ",async function(module){\n"
                                          + "var " + varname("___шлях_до_модуля___") + "=\"" + module_path + "\";\n"
                                          + module_compilation_result->result
                                          + "\n});\n"
                                          + temp_module_name + "=module;\n"
                                          + "\n}";
        scope->set_module(module_path, compiled_module_code);
        node_compilation_result->result = init_module_code;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_ternary_node(const mavka::ast::TernaryNode* ternary_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto condition = compile_node(ternary_node->condition, scope, options);
        if (condition->error) {
            node_compilation_result->error = condition->error;
            return node_compilation_result;
        }
        const auto true_value = compile_body(ternary_node->body, scope, options, false);
        if (true_value->error) {
            node_compilation_result->error = true_value->error;
            return node_compilation_result;
        }
        const auto else_body = compile_body(ternary_node->else_body, scope, options, false);
        if (else_body->error) {
            node_compilation_result->error = else_body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "(" + condition->result + ")?" + true_value->result + ":" + else_body
                                          ->result;
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_test_node(const mavka::ast::TestNode* test_node,
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
        if (test_node->op == "і") {
            node_compilation_result->result = "(" + left->result + ")&&(" + right->result + ")";
        } else if (test_node->op == "або") {
            node_compilation_result->result = "(" + left->result + ")||(" + right->result + ")";
        } else {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = test_node->start_line;
            node_compilation_result->error->column = test_node->start_column;
            node_compilation_result->error->message = "unsupported test operation: " + test_node->op;
        }
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_throw_node(const mavka::ast::ThrowNode* throw_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto diName = scope->put_debug(options->current_module_path, throw_node->start_line,
                                             throw_node->start_column);
        const auto node_compilation_result = new NodeCompilationResult();
        const auto value = compile_node(throw_node->value, scope, options);
        if (value->error) {
            node_compilation_result->error = value->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "throw new Падіння(" + value->result + "," + diName + ")";
        return node_compilation_result;
    }

    inline NodeCompilationResult* compile_try_node(const mavka::ast::TryNode* try_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto try_scope = new CompilationMicroScope();
        try_scope->parent = scope;
        const auto body = compile_body(try_node->body, try_scope, options, false);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        scope->assign(try_node->name);
        const auto catch_scope = new CompilationMicroScope();
        catch_scope->parent = scope;
        const auto catch_body = compile_body(try_node->catch_body, catch_scope, options, false);
        if (catch_body->error) {
            node_compilation_result->error = catch_body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = R"(
try {
)" + body->result + R"(
}catch(e){
if(e){
if(e instanceof Падіння){
e=e.значення;
}
}
)" + varname(try_node->name) + R"(=e;
)" + catch_body->result + R"(
}
)";
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

    inline NodeCompilationResult* compile_wait_node(const mavka::ast::WaitNode* wait_node,
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

    inline NodeCompilationResult* compile_while_node(const mavka::ast::WhileNode* while_node,
                                                     CompilationScope* scope,
                                                     CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto condition = compile_node(while_node->condition, scope, options);
        if (condition->error) {
            node_compilation_result->error = condition->error;
            return node_compilation_result;
        }
        const auto while_scope = new CompilationMicroScope();
        while_scope->parent = scope;
        const auto body = compile_body(while_node->body, while_scope, options, true);
        if (body->error) {
            node_compilation_result->error = body->error;
            return node_compilation_result;
        }
        node_compilation_result->result = "while(" + condition->result + ")" + body->result + "";
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

        if (jejalyk::tools::instanceof<mavka::ast::AssignByIdentifierNode>(node)) {
            return compile_assign_by_identifier_node(dynamic_cast<mavka::ast::AssignByIdentifierNode *>(node), scope,
                                                     options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::AssignByElementNode>(node)) {
            return compile_assign_by_element_node(dynamic_cast<mavka::ast::AssignByElementNode *>(node), scope,
                                                  options);
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

        if (jejalyk::tools::instanceof<mavka::ast::MockupDiiaNode>(node)) {
            return compile_mockup_diia_node(dynamic_cast<mavka::ast::MockupDiiaNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::MockupModuleNode>(node)) {
            return compile_mockup_module_node(dynamic_cast<mavka::ast::MockupModuleNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::MockupObjectNode>(node)) {
            return compile_mockup_object_node(dynamic_cast<mavka::ast::MockupObjectNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::MockupStructureNode>(node)) {
            return compile_mockup_structure_node(dynamic_cast<mavka::ast::MockupStructureNode *>(node), scope, options);
        }

        if (jejalyk::tools::instanceof<mavka::ast::MockupSubjectNode>(node)) {
            return compile_mockup_subject_node(dynamic_cast<mavka::ast::MockupSubjectNode *>(node), scope, options);
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

        if (jejalyk::tools::instanceof<mavka::ast::PreIncrementNode>(node)) {
            return compile_pre_increment_node(dynamic_cast<mavka::ast::PreIncrementNode *>(node), scope, options);
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

    inline NodeCompilationResult* compile_body(const std::vector<mavka::ast::ASTNode *>& body,
                                               CompilationScope* scope,
                                               CompilationOptions* options,
                                               const bool wrap,
                                               const std::string& before) {
        const auto options_clone = options->clone();
        options_clone->body_depth = options->body_depth + 1;
        const auto node_compilation_result = new NodeCompilationResult();
        std::vector<std::string> compiled_body;
        for (const auto node: body) {
            const auto item_node_compilation_result = compile_node(node, scope, options_clone);
            if (item_node_compilation_result->error) {
                item_node_compilation_result->error = item_node_compilation_result->error;
                return item_node_compilation_result;
            }
            if (item_node_compilation_result->result.empty()) {
                continue;
            }
            compiled_body.push_back(item_node_compilation_result->result);
        }
        if (!before.empty()) {
            compiled_body.insert(compiled_body.begin(), before);
        }
        std::vector<std::string> vars;
        for (auto subject: scope->subjects) {
            if (subject.first == "я") {
                continue;
            }
            if (subject.first == "предок") {
                continue;
            }
            vars.push_back(varname(subject.first));
        }
        if (!vars.empty()) {
            compiled_body.insert(compiled_body.begin(), "var " + tools::implode(vars, ","));
        }
        const auto prefix = tools::repeat_string("  ", options->body_depth);
        const auto prefix_pre = tools::repeat_string("  ", options->body_depth - 1);
        node_compilation_result->result = (wrap ? "{\n" : "") + tools::implode_with_prefix(compiled_body, ";\n", prefix)
                                          + ";\n" +
                                          (wrap ? (prefix_pre + "}") : "");
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
            scope->assign(param_name);
            std::string compiled_param_type = "undefined";
            std::string compiled_param_value = "undefined";
            // todo: handle type
            std::string param_string = (param->variadic ? MAVKA_VPARAM : MAVKA_PARAM) + "(" + "\"" + param_name + "\"";
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


    // inline TypesCompilationResult* compile_types(std::vector<mavka::ast::ASTNode *> types,
    //                                              CompilationScope* scope,
    //                                              CompilationOptions* options) {
    //     const auto types_compilation_result = new TypesCompilationResult();
    //     std::vector<std::string> compiled_types;
    //     std::vector<CompilationType *> compiled_types_values;
    //     for (int i = 0; i < types.size(); ++i) {
    //         const auto type = types[i];
    //         const auto type_compilation_result = compile_node(type, scope, options);
    //         if (type_compilation_result->error) {
    //             types_compilation_result->error = type_compilation_result->error;
    //             return types_compilation_result;
    //         }
    //         compiled_types.push_back(type_compilation_result->result);
    //         // compiled_types_values.push_back(type_compilation_result->type);
    //     }
    //     types_compilation_result->types = compiled_types_values;
    //     types_compilation_result->result = "[" + tools::implode(compiled_types, ",") + "]";
    //     return types_compilation_result;
    // }


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
            // todo: handle type
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
