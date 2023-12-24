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
    std::map<std::string, Subject*> generic_types;
  };

  class Object final {
   public:
    Type* structure = nullptr;
    std::map<std::string, Subject*> properties;

    std::string name; // for structure, diia and module
    std::map<std::string, GenericDefinition*>
        generic_definitions; // for structure and diia
    Type* parent = nullptr; // for structure
    std::map<std::string, Param*> params; // for structure and diia
    std::map<std::string, Type*> methods; // for structure
    Subject* return_types = nullptr; // for diia
  };

  class Subject {
   public:
    std::vector<Type*> types;

    bool check(Subject* subject);

    Result* call(Scope* scope,
                 mavka::ast::ASTNode* node,
                 const std::vector<Subject*>& generics,
                 const std::vector<Subject*>& args);
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

    Result* compile_node(mavka::ast::ASTNode* node);
    Result* compile_body(std::vector<mavka::ast::ASTNode*> body);

    Result* Scope::compile_structure(
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
        std::string structure_name,
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
    std::string name;
  };

  Result* error(const std::string& message);
  Result* error_from_ast(const mavka::ast::ASTNode* node,
                         const std::string& message);
  Result* success(Subject* value);
  Result* compile(mavka::ast::ProgramNode* program_node);

} // namespace typeinterpreter

#endif // TYPEINTERPRETER_H
