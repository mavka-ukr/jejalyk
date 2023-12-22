#ifndef COMPILER_H
#define COMPILER_H

#include <map>
#include <string>
#include <vector>

#include "../../ast.h"
#include "../../tools.h"

namespace supercompiler {
  class CompilationResut;
  class Error;
  class Object;
  class Param;
  class ParamsResult;
  class Result;
  class Scope;
  class Subject;

  class Error {
   public:
    std::string message;
  };

  class CompilationResult {
   public:
    Error* error;
  };

  class Object {
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

    std::string diia_name;
    std::vector<Param*> diia_params;
    Subject* diia_return;

    virtual Object* create_instance();
    virtual Subject* get(std::string name);
    virtual Result* set(std::string name, Subject* value);
    virtual Result* set_element(Subject* element, Subject* value, Scope* scope);
    virtual bool has(std::string name);
    virtual Result* call(std::vector<Subject*> args, Scope* scope);
    virtual Result* call_named(std::map<std::string, Subject*> args,
                               Scope* scope);
    virtual Result* get_element(Subject* value, Scope* scope);
    virtual bool is_diia(Scope* scope);
    virtual Result* plus(Subject* value, Scope* scope);
    virtual Result* minus(Subject* value, Scope* scope);
    virtual Result* multiply(Subject* value, Scope* scope);
    virtual Result* divide(Subject* value, Scope* scope);
    virtual Result* divdiv(Subject* value, Scope* scope);
    virtual Result* pow(Subject* value, Scope* scope);
  };

  class Param {
   public:
    int index;
    std::string name;
    Subject* types;
    Subject* value;
    bool variadic;

    Param* clone();
  };

  class ParamsResult {
   public:
    Error* error;
    std::vector<Param*> value;
  };

  class Result {
   public:
    Error* error;
    Subject* value;
  };

  class Scope {
   public:
    Scope* parent;
    std::map<std::string, Subject*> variables;
    std::vector<mavka::ast::ASTNode*>* body;
    Object* diia;

    virtual bool has(std::string name);
    virtual Subject* get(std::string name);
    virtual Subject* get_local(std::string name);
    virtual bool has_local(std::string name);
    virtual Result* compile_node(mavka::ast::ASTNode* node);
    virtual ParamsResult* compile_params(
        std::vector<mavka::ast::ParamNode*> params);
    virtual Result* compile_types(std::vector<mavka::ast::ASTNode*> types,
                                  std::string error_message);
    virtual Result* define_structure(mavka::ast::StructureNode* structure_node);
    virtual Result* define_diia(mavka::ast::DiiaNode* diia_node);
    virtual Result* compile_body(std::vector<mavka::ast::ASTNode*> body);
    virtual Scope* make_child();
  };

  class Subject {
   public:
    std::vector<Object*> types;
    virtual bool is_structure(Scope* scope);
    virtual bool is_diia(Scope* scope);
    virtual bool check_types(Subject* value);
    virtual bool instance_of(Subject* value);
    virtual Result* call(std::vector<Subject*> args, Scope* scope);
    virtual Result* call_named(std::map<std::string, Subject*> args,
                               Scope* scope);
    virtual Result* set(std::string name, Subject* value);
    virtual Result* set_element(Subject* element, Subject* value, Scope* scope);
    virtual Subject* get(std::string name);
    virtual Result* get_element(Subject* value, Scope* scope);
    virtual bool has(std::string name);
    virtual Result* plus(Subject* value, Scope* scope);
    virtual Result* minus(Subject* value, Scope* scope);
    virtual Result* multiply(Subject* value, Scope* scope);
    virtual Result* divide(Subject* value, Scope* scope);
    virtual Result* divdiv(Subject* value, Scope* scope);
    virtual Result* pow(Subject* value, Scope* scope);
    virtual std::string types_string();
  };

  Result* error(const std::string& message);
  Result* success(Subject* value);
  CompilationResult* compile(mavka::ast::ProgramNode* program_node);
}  // namespace supercompiler

#endif  // COMPILER_H
