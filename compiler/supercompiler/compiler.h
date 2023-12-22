#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../ast.h"
#include "../../tools.h"

namespace supercompiler {
  class Error;
  class Result;
  class ParamsResult;
  class CompilationResut;
  class BodyToCompile;
  class Scope;
  class Object;
  class Subject;
  class Param;
  class Generic;

  class Error final {
   public:
    bool full = false;
    int line = 0;
    int column = 0;
    std::string message;
  };

  class Result final {
   public:
    Error* error;
    Subject* value;
  };

  class ParamsResult final {
   public:
    Error* error;
    std::vector<Param*> value;
  };

  class CompilationResult final {
   public:
    Error* error;
  };

  class BodyToCompile final {
   public:
    Scope* scope;
    std::vector<mavka::ast::ASTNode*> body;
  };

  class Scope final {
   public:
    Scope* parent;
    std::map<std::string, Subject*> variables;
    std::vector<mavka::ast::ASTNode*>* body;
    Object* diia;
    std::vector<BodyToCompile*> bodies_to_compile;

    bool has(std::string name);
    Subject* get(std::string name);
    Subject* get_local(std::string name);
    bool has_local(std::string name);
    Result* assign(std::string name, Subject* value);
    Result* make_diia_from_ast(
        Scope* diia_scope,
        bool declaration,
        bool ee,
        bool async,
        const std::string& name,
        const std::string& structure,
        const std::vector<mavka::ast::ParamNode*>& params,
        const std::vector<mavka::ast::ASTNode*>& return_types);
    Result* compile_node(mavka::ast::ASTNode* node);
    ParamsResult* compile_params(std::vector<mavka::ast::ParamNode*> params);
    Result* compile_types(const std::vector<mavka::ast::ASTNode*>& types,
                          const std::string& error_message);
    Result* define_module_from_ast(std::string name,
                                   std::vector<mavka::ast::ASTNode*> elements);
    Result* define_structure_from_ast(
        bool mockup,
        std::string name,
        std::vector<mavka::ast::GenericNode*> generics,
        mavka::ast::ASTNode* parent,
        std::vector<mavka::ast::ASTNode*> params);
    Result* define_diia_from_ast(
        bool declaration,
        bool ee,
        bool async,
        const std::string& name,
        const std::string& structure,
        const std::vector<mavka::ast::ParamNode*>& params,
        const std::vector<mavka::ast::ASTNode*>& return_types,
        std::vector<mavka::ast::ASTNode*> body);
    Result* compile_body(std::vector<mavka::ast::ASTNode*> body,
                         bool with_bodies_to_compile = false);
    Scope* make_child();
  };

  class Object final {
   public:
    static constexpr int OBJECT = 0;
    static constexpr int DIIA = 1;
    static constexpr int STRUCTURE = 2;

    int type = OBJECT;
    Object* structure;
    std::map<std::string, Subject*> properties;

    std::string structure_name;
    Object* structure_parent;
    std::vector<Param*> structure_params;
    std::map<std::string, Subject*> structure_methods;
    std::vector<Generic*> structure_generics;

    std::string diia_name;
    std::vector<Param*> diia_params;
    Subject* diia_return;
    std::vector<Generic*> diia_generics;

    Object* create_instance();
    Subject* get(std::string name);
    Result* set(std::string name, Subject* value);
    Result* set_element(Subject* element, Subject* value, Scope* scope);
    bool has(std::string name);
    Result* call(std::vector<Subject*> generics,
                 std::vector<Subject*> args,
                 Scope* scope);
    Result* call_named(std::map<std::string, Subject*> args, Scope* scope);
    Result* get_element(Subject* value, Scope* scope);
    bool is_diia(Scope* scope);
    Result* plus(Subject* value, Scope* scope);
    Result* minus(Subject* value, Scope* scope);
    Result* multiply(Subject* value, Scope* scope);
    Result* divide(Subject* value, Scope* scope);
    Result* divdiv(Subject* value, Scope* scope);
    Result* pow(Subject* value, Scope* scope);
  };

  class Subject final {
   public:
    std::vector<Object*> types;
    bool is_structure(Scope* scope);
    bool is_diia(Scope* scope);
    bool check_types(Subject* value);
    bool instance_of(Subject* value);
    Result* call(std::vector<Subject*> generics,
                 std::vector<Subject*> args,
                 Scope* scope);
    Result* call_named(std::map<std::string, Subject*> args, Scope* scope);
    Result* set(std::string name, Subject* value);
    Result* set_element(Subject* element, Subject* value, Scope* scope);
    Subject* get(std::string name);
    Result* get_element(Subject* value, Scope* scope);
    bool has(std::string name);
    Result* plus(Subject* value, Scope* scope);
    Result* minus(Subject* value, Scope* scope);
    Result* multiply(Subject* value, Scope* scope);
    Result* divide(Subject* value, Scope* scope);
    Result* divdiv(Subject* value, Scope* scope);
    Result* pow(Subject* value, Scope* scope);
    std::string types_string();
  };

  class Param final {
   public:
    int index;
    std::string name;
    Subject* types;
    Subject* value;
    bool variadic;

    Param* clone();
  };

  class Generic final {
   public:
    int index;
    std::string name;
  };

  Result* error(const std::string& message);
  Result* error_from_ast(const mavka::ast::ASTNode* node,
                         const std::string& message);
  Result* success(Subject* value);
  CompilationResult* compile(mavka::ast::ProgramNode* program_node);
}  // namespace supercompiler

#endif  // COMPILER_H
