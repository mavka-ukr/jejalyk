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
  class Generic;

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
    std::map<std::string, Type*> generic_types;
  };

  class Object final {
   public:
    Type* structure = nullptr;
    std::map<std::string, Subject*> properties;

    std::string name; // for structure, diia and module
    std::vector<Generic*> generic_definitions; // for structure and diia
    Type* parent = nullptr; // for structure
    std::vector<Param*> params; // for structure and diia
    std::vector<Method*> methods; // for structure
    Subject* return_types = nullptr; // for diia
  };

  class Subject {
    std::vector<Type*> types;
  };

  class Scope final {
   public:
    Scope* parent = nullptr;
    std::map<std::string, Subject*> variables;
    bool proxy = false;

    Scope* make_child();

    Subject* get(std::string name);
    Subject* get_local(std::string name);
    void set(std::string name, Subject* value);
    void set_local(std::string name, Subject* value);
    bool has(std::string name);
    bool has_local(std::string name);

    Result* assign(std::string name, Subject* value);

    Result* compile_node(mavka::ast::ASTNode* node);
    Result* compile_body(std::vector<mavka::ast::ASTNode*> body);
  };

  Result* error(const std::string& message);
  Result* error_from_ast(const mavka::ast::ASTNode* node,
                         const std::string& message);
  Result* success(Subject* value);
  Result* compile(mavka::ast::ProgramNode* program_node);

} // namespace typeinterpreter

#endif // TYPEINTERPRETER_H
