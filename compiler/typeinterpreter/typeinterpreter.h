#ifndef TYPEINTERPRETER_H
#define TYPEINTERPRETER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../ast.h"
#include "../../tools.h"

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
  };

  class Type final {
   public:
    Object* object = nullptr;
    GenericDefinition* generic_definition = nullptr;
    std::vector<Subject*> generic_types;

    bool is_diia(Scope* scope);
    bool is_structure(Scope* scope);
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

    bool is_iterator(Scope* scope);
    Result* get_iterator_type(Scope* scope, mavka::ast::ASTNode* node);
  };

  class Object final {
   public:
    Type* structure = nullptr;

    bool this_is_declaration = false;

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

    bool has(const std::string& name);
    Result* get(const std::string& name);
    Result* set(Scope* scope,
                mavka::ast::ASTNode* node,
                const std::string& name,
                Subject* value);

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

    bool is_iterator(Scope* scope);
    Result* get_iterator_type(Scope* scope, mavka::ast::ASTNode* node);

    Result* create_instance(Scope* scope, std::vector<Subject*> generic_types);
  };

  class Scope final {
   public:
    Scope* parent = nullptr;
    std::map<std::string, Subject*> variables;
    bool proxy = false;

    Scope* make_child();
    Scope* make_proxy();
    Scope* get_root();

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
        bool ee,
        std::string name,
        std::vector<mavka::ast::GenericNode*> generic_definitions,
        std::vector<mavka::ast::ParamNode*> params,
        std::vector<mavka::ast::TypeValueSingleNode*> return_types);
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

  Result* compile(mavka::ast::ProgramNode* program_node);

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
