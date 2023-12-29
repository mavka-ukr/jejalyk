#ifndef TYPEINTERPRETER_H
#define TYPEINTERPRETER_H

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../ast.h"
#include "../../parser.h"
#include "../../tools.h"
#include "../js/js.h"

#define JJ_DEBUG 0

namespace typeinterpreter {
  class Error;
  class Result;
  class Type;
  class Object;
  class Subject;
  class Scope;
  class Param;
  class Method;
  class GenericDefinition;

  class Error final {
   public:
    bool full = false;
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
    std::string get_name();
    std::string get_type_name();

    Type* create_instance(Scope* scope, std::vector<Subject*> generic_types);

    bool has(std::string name);
    Subject* get(std::string name);
    Result* set(Scope* scope,
                mavka::ast::ASTNode* node,
                const std::string& name,
                Subject* value);

    Result* call(Scope* scope,
                 mavka::ast::ASTNode* node,
                 std::vector<Subject*> vector,
                 std::vector<Subject*> args);
    Result* get_element(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* value);
    Result* set_element(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* element,
                        Subject* value);
    Result* plus(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* minus(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* multiply(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* divide(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* divmod(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* divdiv(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* pow(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* bw_not(Scope* scope, mavka::ast::ASTNode* node);
    Result* bw_xor(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* bw_or(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* bw_and(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* bw_shift_left(Scope* scope,
                          mavka::ast::ASTNode* node,
                          Subject* value);
    Result* bw_shift_right(Scope* scope,
                           mavka::ast::ASTNode* node,
                           Subject* value);
    Result* negative(Scope* scope, mavka::ast::ASTNode* node);
    Result* positive(Scope* scope, mavka::ast::ASTNode* node);
    Result* post_decrement(Scope* scope, mavka::ast::ASTNode* node);
    Result* post_increment(Scope* scope, mavka::ast::ASTNode* node);
    Result* pre_decrement(Scope* scope, mavka::ast::ASTNode* node);
    Result* pre_increment(Scope* scope, mavka::ast::ASTNode* node);
    Result* comp_greater(Scope* scope,
                         mavka::ast::ASTNode* node,
                         Subject* value);
    Result* comp_lesser(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* value);
    Result* comp_greater_or_eq(Scope* scope,
                               mavka::ast::ASTNode* node,
                               Subject* value);
    Result* comp_lesser_or_eq(Scope* scope,
                              mavka::ast::ASTNode* node,
                              Subject* value);
    Result* comp_contains(Scope* scope,
                          mavka::ast::ASTNode* node,
                          Subject* value);
    Result* comp_contains_not(Scope* scope,
                              mavka::ast::ASTNode* node,
                              Subject* value);

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

    std::string name; // for structure, diia and module
    std::vector<GenericDefinition*>
        generic_definitions; // for structure and diia
    Type* parent = nullptr; // for structure
    std::vector<Param*> params; // for structure and diia
    std::map<std::string, Type*> methods; // for structure
    Subject* return_types = nullptr; // for diia
  };

  class Subject {
   public:
    std::vector<Type*> types;

    void add_type(Type* type);

    std::string get_name();
    std::string types_string();

    bool check(Subject* subject);

    bool is_number(Scope* scope);
    bool is_string(Scope* scope);
    bool is_array(Scope* scope);
    bool is_diia(Scope* scope);

    bool has(const std::string& name);
    Result* get(const std::string& name);
    Result* set(Scope* scope,
                mavka::ast::ASTNode* node,
                const std::string& name,
                Subject* value);

    bool has_diia(Scope* scope, std::string name);

    Result* call(Scope* scope,
                 mavka::ast::ASTNode* node,
                 std::vector<Subject*> generic_types,
                 std::vector<Subject*> args);
    Result* get_element(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* value);
    Result* set_element(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* element,
                        Subject* value);
    Result* plus(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* minus(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* multiply(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* divide(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* divmod(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* divdiv(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* pow(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* bw_not(Scope* scope, mavka::ast::ASTNode* node);
    Result* bw_xor(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* bw_or(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* bw_and(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* bw_shift_left(Scope* scope,
                          mavka::ast::ASTNode* node,
                          Subject* value);
    Result* bw_shift_right(Scope* scope,
                           mavka::ast::ASTNode* node,
                           Subject* value);
    Result* negative(Scope* scope, mavka::ast::ASTNode* node);
    Result* positive(Scope* scope, mavka::ast::ASTNode* node);
    Result* post_decrement(Scope* scope, mavka::ast::ASTNode* node);
    Result* post_increment(Scope* scope, mavka::ast::ASTNode* node);
    Result* pre_decrement(Scope* scope, mavka::ast::ASTNode* node);
    Result* pre_increment(Scope* scope, mavka::ast::ASTNode* node);
    Result* comp_eq(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* comp_not_eq(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* value);
    Result* comp_greater(Scope* scope,
                         mavka::ast::ASTNode* node,
                         Subject* value);
    Result* comp_lesser(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* value);
    Result* comp_greater_or_eq(Scope* scope,
                               mavka::ast::ASTNode* node,
                               Subject* value);
    Result* comp_lesser_or_eq(Scope* scope,
                              mavka::ast::ASTNode* node,
                              Subject* value);
    Result* comp_is(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* comp_is_not(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* value);
    Result* comp_contains(Scope* scope,
                          mavka::ast::ASTNode* node,
                          Subject* value);
    Result* comp_contains_not(Scope* scope,
                              mavka::ast::ASTNode* node,
                              Subject* value);
    Result* test_and(Scope* scope, mavka::ast::ASTNode* node, Subject* value);
    Result* test_or(Scope* scope, mavka::ast::ASTNode* node, Subject* value);

    bool is_iterator(Scope* scope);
    Result* get_iterator_type(Scope* scope, mavka::ast::ASTNode* node);
    bool is_awaiting(Scope* scope);
    Result* get_awaiting_value(Scope* scope, mavka::ast::ASTNode* node);

    Result* create_instance(Scope* scope, std::vector<Subject*> generic_types);
  };

  class Scope final {
   public:
    Scope* parent = nullptr;
    std::map<std::string, Subject*> variables;
    bool proxy = false;

    Object* diia_object = nullptr;
    Object* module_object = nullptr;
    bool is_loop = false;
    bool is_async = false;
    size_t iterator_count = 0;

    Scope* make_child();
    Scope* make_proxy();
    Scope* get_root();
    Object* get_diia_object();
    Object* get_module_object();
    bool get_is_loop();
    bool get_is_async();
    size_t get_iterator_count();
    void increment_iterator_count();

    Subject* create_object_instance_subject();
    Type* create_object_instance_type();
    Object* create_object_instance_object();

    Subject* get(std::string name);
    Subject* get_local(std::string name);
    void set_local(std::string name, Subject* value);
    bool has(std::string name);
    bool has_local(std::string name);

    bool assign(std::string name, Subject* value);

    bool check_subjects(Subject* value, Subject* types);
    bool check_type(Type* value, Type* type);

    Result* compile_types(std::vector<mavka::ast::TypeValueSingleNode*> types);
    Result* compile_nodes(std::vector<mavka::ast::ASTNode*> nodes);
    Result* compile_node(mavka::ast::ASTNode* node);
    Result* compile_body(std::vector<mavka::ast::ASTNode*> body);

    Result* compile_structure(
        std::string name,
        std::vector<mavka::ast::GenericNode*> generic_definitions,
        std::string parent,
        std::vector<std::vector<mavka::ast::TypeValueSingleNode*>>
            parent_generics,
        std::vector<mavka::ast::ParamNode*> params,
        std::vector<mavka::ast::MethodDeclarationNode*> method_declarations);

    Result* compile_diia(
        Scope* diia_scope,
        bool async,
        std::string name,
        std::vector<mavka::ast::GenericNode*> generic_definitions,
        std::vector<mavka::ast::ParamNode*> params,
        std::vector<mavka::ast::TypeValueSingleNode*> return_types,
        std::vector<mavka::ast::ASTNode*>* body);

    Result* compile_module(std::string name,
                           std::vector<mavka::ast::ASTNode*>* body);
  };

  class Param final {
   public:
    std::string name;
    Subject* types;
    Subject* value;
    bool variadic;

    Param* clone();
  };

  class GenericDefinition final {
   public:
    Object* object;
    size_t index;
    std::string name;
  };

  Subject* process_subject_generics(Object* object,
                                    std::vector<Subject*> generic_types,
                                    Subject* subject);

  Result* error_0(const mavka::ast::ASTNode* node,
                  const std::string& subject_name,
                  Subject* expected,
                  Subject* got);
  Result* error_1(const mavka::ast::ASTNode* node,
                  const std::string& subject_name);
  Result* error_2(const mavka::ast::ASTNode* node,
                  const std::string& property_name,
                  Subject* subject);

  Result* error_from_ast(const mavka::ast::ASTNode* node,
                         const std::string& message);
  Result* error(const std::string& message);
  Result* success(Subject* value);
  Result* success(Subject* value, jejalyk::js::JsNode* js_node);
  Result* success(Subject* value, jejalyk::js::JsBody* js_body);

  Result* compile(std::string code);

  void debug_print_call(Type* value,
                        std::vector<Subject*> generic_types,
                        std::vector<Subject*> args);
  void debug_print_check_subjects(Subject* value, Subject* types);
  void debug_print_got_from_scope(Scope* scope,
                                  std::string name,
                                  Subject* value);

  void debug_print_bug(const std::vector<std::string>& messages);
  void debug_print_bug(const std::string& message);

} // namespace typeinterpreter

#endif // TYPEINTERPRETER_H
