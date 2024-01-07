#ifndef TYPEINTERPRETER_H
#define TYPEINTERPRETER_H

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../ast.h"
#include "../js/js.h"
#include "../parser.h"
#include "../tools.h"

#define JJ_DEBUG 0

#define JJ_F_IS "мЄ"
#define JJ_F_FROM_TO "мВідДо"
#define JJ_F_TEXT "мТекст"
#define JJ_F_DIIA "мДія"
#define JJ_F_MODULE "мМодуль"
#define JJ_F_STRUCTURE "мСтруктура"

#define JJ_MAG_ADD "чародія_додати"
#define JJ_MAG_SUB "чародія_відняти"
#define JJ_MAG_MUL "чародія_помножити"
#define JJ_MAG_DIV "чародія_поділити"
#define JJ_MAG_MOD "чародія_остача"
#define JJ_MAG_DIVDIV "чародія_частка"
#define JJ_MAG_POW "чародія_степінь"
#define JJ_MAG_BW_NOT "чародія_дні"
#define JJ_MAG_BW_XOR "чародія_вабо"
#define JJ_MAG_BW_OR "чародія_дабо"
#define JJ_MAG_BW_AND "чародія_ді"
#define JJ_MAG_BW_SHIFT_LEFT "чародія_вліво"
#define JJ_MAG_BW_SHIFT_RIGHT "чародія_вправо"
#define JJ_MAG_BW_POSITIVE "чародія_додатнє"
#define JJ_MAG_BW_NEGATIVE "чародія_відʼємне"
#define JJ_MAG_GREATER "чародія_більше"
#define JJ_MAG_LESSER "чародія_менше"
#define JJ_MAG_GREATER_EQUAL "чародія_не_менше"
#define JJ_MAG_LESSER_EQUAL "чародія_не_більше"
#define JJ_MAG_CONTAINS "чародія_містить"
#define JJ_MAG_GET_ELEMENT "чародія_отримати"
#define JJ_MAG_PUT_ELEMENT "чародія_покласти"
#define JJ_MAG_CALL "чародія_викликати"
#define JJ_MAG_ITERATOR "чародія_перебір"

namespace jejalyk::typeinterpreter {
  class Error;
  class Result;
  class Type;
  class Object;
  class Subject;
  class Scope;
  class Param;
  class GenericDefinition;
  class Module;
  class Options;
  class GetModuleResult;

  class Error final {
   public:
    std::string path;
    size_t line = 0;
    size_t column = 0;
    std::string message;
  };

  class Result final {
   public:
    Error* error;
    Subject* value;
    jejalyk::js::JsNode* js_node;
    jejalyk::js::JsBody* js_body;
  };

  class Type final {
   public:
    static Type* create(Object* object);
    static Type* create(GenericDefinition* generic_definition);

    Object* object = nullptr;
    GenericDefinition* generic_definition = nullptr;
    std::vector<Subject*> generic_types;

    bool is_diia(Scope* scope);
    bool is_structure(Scope* scope);
    bool is_number(Scope* scope);
    bool is_string(Scope* scope);
    bool is_array(Scope* scope);
    bool is_object(Scope* scope);
    bool is_empty(Scope* scope);
    bool is_dictionary(Scope* scope);
    std::string get_name();
    std::string get_type_name();
    bool is_method(Scope* scope);

    Type* create_instance(Scope* scope, std::vector<Subject*> generic_types);

    bool has(Scope* scope, std::string name);
    Subject* get(Scope* scope, std::string name);
    Result* set(Scope* scope,
                mavka::ast::ASTNode* node,
                const std::string& name,
                Subject* value);

    Result* call(Scope* scope,
                 mavka::ast::ASTNode* node,
                 std::vector<Subject*> generic_types,
                 std::vector<Subject*> args);
    Result* magic_call(Scope* scope,
                       mavka::ast::ASTNode* node,
                       std::string name,
                       std::vector<Subject*> generic_types,
                       std::vector<Subject*> args);

    bool is_iterator(Scope* scope);
    Result* get_iterator_type(Scope* scope, mavka::ast::ASTNode* node);
    bool is_awaiting(Scope* scope);
    Result* get_awaiting_type(Scope* scope, mavka::ast::ASTNode* node);
  };

  class Object final {
   public:
    Type* structure = nullptr;
    std::map<std::string, Subject*> properties;

    bool this_is_declaration = false; // for structure and diia
    bool is_diia_async = false; // for diia
    bool is_diia_method = false; // for structure method

    std::string name; // for structure, diia and module
    std::vector<GenericDefinition*>
        generic_definitions; // for structure and diia
    Type* parent = nullptr; // for structure
    js::JsNode* parent_js = nullptr; // for structure
    std::vector<Param*> params; // for structure and diia
    std::map<std::string, Type*> methods; // for structure
    Subject* return_types = nullptr; // for diia
  };

  class Subject {
   public:
    static Subject* create(Type* type);
    static Subject* create(Object* object);
    static Subject* create(GenericDefinition* generic_definition);
    static Subject* create(Scope* scope);

    std::vector<Type*> types;

    bool is_empty_value = false;

    void add_type(Type* type);
    Subject* merge_types(Subject* subject);
    void fix_types(Scope* scope);

    std::string get_name();
    std::string types_string();

    bool check(Subject* subject);

    bool is_number(Scope* scope);
    bool is_string(Scope* scope);
    bool is_array(Scope* scope);
    bool is_diia(Scope* scope);
    bool is_dictionary(Scope* scope);
    bool is_structure(Scope* scope);
    bool is_object(Scope* scope);
    bool is_method(Scope* scope);

    bool has(Scope* scope, const std::string& name);
    Result* get(Scope* scope,
                mavka::ast::ASTNode* node,
                const std::string& name);
    Result* set(Scope* scope,
                mavka::ast::ASTNode* node,
                const std::string& name,
                Subject* value);

    bool has_diia(Scope* scope, std::string name);

    Result* call(Scope* scope,
                 mavka::ast::ASTNode* node,
                 std::vector<Subject*> generic_types,
                 std::vector<Subject*> args);
    Result* magic_call(Scope* scope,
                       mavka::ast::ASTNode* node,
                       std::string name,
                       std::vector<Subject*> generic_types,
                       std::vector<Subject*> args);

    Result* test_and(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* test_or(Scope* scope, mavka::ast::ASTNode* node, Subject* value);

    bool is_iterator(Scope* scope);
    Result* get_iterator_type(Scope* scope, mavka::ast::ASTNode* node);
    bool is_awaiting(Scope* scope);
    Result* get_awaiting_value(Scope* scope, mavka::ast::ASTNode* node);

    Result* create_instance(Scope* scope, std::vector<Subject*> generic_types);
  };

  class PostBodyCompilation final {
   public:
    js::JsBody* js_body;
    std::vector<mavka::ast::ASTSome*>* body;
    Scope* scope;
  };

  class Scope final {
   public:
    Options* options = nullptr;
    Scope* parent = nullptr;
    std::map<std::string, Subject*> variables;
    bool proxy = false;
    std::vector<PostBodyCompilation*> post_bodies_compilation;

    Object* diia_object = nullptr;
    Object* module_object = nullptr;
    bool is_loop = false;
    bool is_async = false;
    size_t iterator_count = 0;
    std::vector<js::JsNode*> additional_nodes_before;
    std::vector<std::string> ignored_variables;
    std::vector<std::string> additional_variables;
    std::vector<std::string> setters;

    Scope* make_child();
    Scope* make_proxy();
    Scope* get_root();
    Subject* get_from_root(std::string name);
    Object* get_diia_object();
    Object* get_module_object();
    Subject* get_root_object();
    Subject* get_root_structure();
    Subject* get_root_empty();
    Subject* get_root_diia();
    Subject* get_root_number();
    Subject* get_root_text();
    Subject* get_root_logical();
    Subject* get_root_list();
    Subject* get_root_dictionary();
    Subject* get_root_iterator();
    Subject* get_root_iterator_with_key();
    Subject* get_root_awaiting();
    bool get_is_loop();
    bool get_is_async();
    size_t get_iterator_count();
    void increment_iterator_count();
    Options* get_options() const;
    std::vector<std::string> get_ignored_variables();
    void put_ignore_variable(std::string name);
    Scope* get_parent();
    void put_setter(std::string name);
    std::vector<std::string> get_setters();

    void put_additional_node_before(js::JsNode* node);
    std::vector<js::JsNode*> get_additional_nodes_before();

    void put_additional_variable(std::string name);
    std::vector<std::string> get_additional_variables();

    Subject* create_object_instance_subject();
    Type* create_object_instance_type();
    Object* create_object_instance_object();

    Subject* get(std::string name);
    Subject* get_local(std::string name);
    void set_local(std::string name, Subject* value);
    bool has(std::string name);
    bool has_local(std::string name);
    void delete_local(std::string name);

    bool assign(std::string name, Subject* value);

    bool check_subjects(Subject* value, Subject* types);
    bool check_type(bool is_empty_value, Type* value, Type* type);

    Result* compile_types(std::vector<mavka::ast::TypeValueSingleNode*> types);
    Result* compile_nodes(std::vector<mavka::ast::ASTSome*> nodes);
    Result* compile_node(mavka::ast::ASTSome* node);
    Result* compile_body(std::vector<mavka::ast::ASTSome*>& body);

    Result* compile_module(std::string name,
                           std::vector<mavka::ast::ASTSome*> body,
                           std::string path,
                           std::vector<js::JsNode*> before);

    Result* error(mavka::ast::ASTNode* node, const std::string& message) const;
  };

  class Param final {
   public:
    std::string name;
    Subject* types = nullptr;
    Subject* value = nullptr;
    js::JsNode* types_js_node = nullptr;
    js::JsNode* value_js_node = nullptr;
    bool variadic;

    Param* clone();
  };

  class GenericDefinition final {
   public:
    Object* object;
    size_t index;
    std::string name;
  };

  class GetModuleResult final {
   public:
    std::string error;
    std::string result;
    bool builtin = false;
  };

  class Module final {
   public:
    Subject* subject = nullptr;
    js::JsNode* js_node = nullptr;
  };

  class Options final {
   public:
    Options* parent = nullptr;
    std::string main_module_path;
    std::string root_module_path;
    std::string current_module_path;
    std::string std_code;
    std::string args;
    std::string arg_extensions = "0";
    std::string arg_strictness = "0";
    std::map<std::string, Module*> modules;

    GetModuleResult* (*get_module_name)(bool, std::string, Options*) = nullptr;
    GetModuleResult* (*get_module_path)(bool, std::string, Options*) = nullptr;
    GetModuleResult* (*get_module_code)(bool, std::string, Options*) = nullptr;
    GetModuleResult* (*get_pak)(std::string,
                                std::string,
                                std::string,
                                Options*) = nullptr;

    bool has_module(std::string path);
    void set_module(std::string path, Module* module);
    Module* get_module(std::string path);
    bool is_extensions_allowed() const;
    bool is_strict_mode() const;
    Options* clone();
  };

  Subject* process_subject_generics(Object* object,
                                    std::vector<Subject*> generic_types,
                                    Subject* subject);

  Result* error_0(Scope* scope,
                  mavka::ast::ASTNode* node,
                  const std::string& subject_name,
                  Subject* expected,
                  Subject* got);
  Result* error_1(Scope* scope,
                  mavka::ast::ASTNode* node,
                  const std::string& subject_name);
  Result* error_2(Scope* scope,
                  mavka::ast::ASTNode* node,
                  const std::string& property_name,
                  Subject* subject);
  Result* error_3(Scope* scope,
                  mavka::ast::ASTNode* node,
                  const std::string& magic_diia_name);
  Result* error_4(Scope* scope,
                  mavka::ast::ASTNode* node,
                  const std::string& magic_diia_name,
                  Type* type);

  Result* error(const std::string& message);
  Result* success(Subject* value);
  Result* success(Subject* value, jejalyk::js::JsNode* js_node);
  Result* success(Subject* value, jejalyk::js::JsBody* js_body);

  Result* compile_anon_diia_node(Scope* scope,
                                 mavka::ast::AnonDiiaNode* anon_diia_node);
  Result* compile_arithmetic_node(Scope* scope,
                                  mavka::ast::ArithmeticNode* arithmetic_node);
  Result* compile_array_node(Scope* scope, mavka::ast::ArrayNode* array_node);
  Result* compile_as_node(Scope* scope, mavka::ast::AsNode* as_node);
  Result* compile_assign_by_element_node(
      Scope* scope,
      mavka::ast::AssignByElementNode* assign_by_element_node);
  Result* compile_assign_by_identifier_node(
      Scope* scope,
      mavka::ast::AssignByIdentifierNode* assign_by_identifier_node);
  Result* compile_assign_simple_node(
      Scope* scope,
      mavka::ast::AssignSimpleNode* assign_simple_node);
  Result* compile_bitwise_node(Scope* scope,
                               mavka::ast::BitwiseNode* bitwise_node);
  Result* compile_bitwise_not_node(
      Scope* scope,
      mavka::ast::BitwiseNotNode* bitwise_not_node);
  Result* compile_break_node(Scope* scope, mavka::ast::BreakNode* break_node);
  Result* compile_call_node(Scope* scope, mavka::ast::CallNode* call_node);
  Result* compile_chain_node(Scope* scope, mavka::ast::ChainNode* chain_node);
  Result* compile_comparison_node(Scope* scope,
                                  mavka::ast::ComparisonNode* comparison_node);
  Result* compile_continue_node(Scope* scope,
                                mavka::ast::ContinueNode* continue_node);
  Result* compile_dictionary_node(Scope* scope,
                                  mavka::ast::DictionaryNode* dictionary_node);
  Result* compile_diia_node(Scope* scope, mavka::ast::DiiaNode* diia_node);
  Result* compile_diia_or_mockup_diia_node(
      Scope* scope,
      mavka::ast::ASTNode* node,
      bool mockup,
      bool ee,
      bool async,
      std::string structure,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generics,
      std::vector<mavka::ast::ParamNode*> params,
      std::vector<mavka::ast::TypeValueSingleNode*> return_types,
      std::vector<mavka::ast::ASTSome*>* body);
  Result* compile_each_node(Scope* scope, mavka::ast::EachNode* each_node);
  Result* compile_eval_node(Scope* scope, mavka::ast::EvalNode* eval_node);
  Result* compile_from_to_complex_node(
      Scope* scope,
      mavka::ast::FromToComplexNode* from_to_complex_node);
  Result* compile_from_to_simple_node(
      Scope* scope,
      mavka::ast::FromToSimpleNode* from_to_simple_node);
  Result* compile_function_node(Scope* scope,
                                mavka::ast::FunctionNode* function_node);
  Result* compile_get_element_node(
      Scope* scope,
      mavka::ast::GetElementNode* get_element_node);
  Result* compile_give_node(Scope* scope, mavka::ast::GiveNode* give_node);
  Result* compile_god_node(Scope* scope, mavka::ast::GodNode* god_node);
  Result* compile_identifier_node(Scope* scope,
                                  mavka::ast::IdentifierNode* identifier_node);
  Result* compile_if_node(Scope* scope, mavka::ast::IfNode* if_node);
  Result* compile_method_declaration_node(
      Scope* scope,
      mavka::ast::MethodDeclarationNode* method_declaration_node);
  Result* compile_mml_node(Scope* scope, mavka::ast::MMLNode* mml_node);
  Result* compile_mockup_diia_node(
      Scope* scope,
      mavka::ast::MockupDiiaNode* mockup_diia_node);
  Result* compile_mockup_module_node(
      Scope* scope,
      mavka::ast::MockupModuleNode* mockup_module_node);
  Result* compile_mockup_structure_node(
      Scope* scope,
      mavka::ast::MockupStructureNode* mockup_structure_node);
  Result* compile_mockup_subject_node(
      Scope* scope,
      mavka::ast::MockupSubjectNode* mockup_subject_node);
  Result* compile_module_node(Scope* scope,
                              mavka::ast::ModuleNode* module_node);
  Result* compile_mrm_diia_node(Scope* scope,
                                mavka::ast::MRMDiiaNode* mrm_diia_node);
  Result* compile_negative_node(Scope* scope,
                                mavka::ast::NegativeNode* negative_node);
  Result* compile_not_node(Scope* scope, mavka::ast::NotNode* not_node);
  Result* compile_number_node(Scope* scope,
                              mavka::ast::NumberNode* number_node);
  Result* compile_positive_node(Scope* scope,
                                mavka::ast::PositiveNode* positive_node);
  Result* compile_post_decrement_node(
      Scope* scope,
      mavka::ast::PostDecrementNode* post_decrement_node);
  Result* compile_post_increment_node(
      Scope* scope,
      mavka::ast::PostIncrementNode* post_increment_node);
  Result* compile_pre_decrement_node(
      Scope* scope,
      mavka::ast::PreDecrementNode* pre_decrement_node);
  Result* compile_pre_increment_node(
      Scope* scope,
      mavka::ast::PreIncrementNode* pre_increment_node);
  Result* compile_return_node(Scope* scope,
                              mavka::ast::ReturnNode* return_node);
  Result* compile_string_node(Scope* scope,
                              mavka::ast::StringNode* string_node);
  Result* compile_structure_node(Scope* scope,
                                 mavka::ast::StructureNode* structure_node);
  Result* compile_take_module_node(
      Scope* scope,
      mavka::ast::TakeModuleNode* take_module_node);
  Result* compile_take_pak_node(Scope* scope,
                                mavka::ast::TakePakNode* take_pak_node);
  Result* compile_ternary_node(Scope* scope,
                               mavka::ast::TernaryNode* ternary_node);
  Result* compile_test_node(Scope* scope, mavka::ast::TestNode* test_node);
  Result* compile_throw_node(Scope* scope, mavka::ast::ThrowNode* throw_node);
  Result* compile_try_node(Scope* scope, mavka::ast::TryNode* try_node);
  Result* compile_type_value_single_node(
      Scope* scope,
      mavka::ast::TypeValueSingleNode* type_value_single_node);
  Result* compile_wait_node(Scope* scope, mavka::ast::WaitNode* wait_node);
  Result* compile_while_node(Scope* scope, mavka::ast::WhileNode* while_node);

  Result* declare_structure(
      Scope* scope,
      mavka::ast::ASTNode* node,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generic_definitions,
      mavka::ast::ASTSome* parent,
      std::vector<mavka::ast::GenericNode*> parent_generic_definitions);
  Result* complete_structure(Scope* scope,
                             bool mockup,
                             mavka::ast::ASTNode* node,
                             Subject* structure_subject,
                             std::vector<mavka::ast::ParamNode*> params);

  Result* declare_diia(
      Scope* scope,
      Scope* diia_scope,
      mavka::ast::ASTNode* node,
      bool async,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generic_definitions,
      std::vector<mavka::ast::ParamNode*> params,
      std::vector<mavka::ast::TypeValueSingleNode*> return_types);
  Result* complete_diia(Scope* scope,
                        bool mockup,
                        Scope* diia_scope,
                        mavka::ast::ASTNode* node,
                        Type* diia_structure,
                        Subject* diia_subject,
                        std::vector<mavka::ast::ASTSome*>* body);

  void debug_print(std::string message);
  void debug_print_call(Type* value,
                        std::vector<Subject*> generic_types,
                        std::vector<Subject*> args);
  void debug_print_check_subjects(Subject* value, Subject* types);
  void debug_print_got_from_scope(Scope* scope,
                                  std::string name,
                                  Subject* value);

  void debug_print_bug(const std::vector<std::string>& messages);
  void debug_print_bug(const std::string& message);

} // namespace jejalyk::typeinterpreter

#endif // TYPEINTERPRETER_H
