#ifndef NEWCOMPILER_H
#define NEWCOMPILER_H

#include <map>
#include <string>
#include <vector>

#include "../ast.h"
#include "../tools.h"

namespace newcompiler {
  class Options;
  class State;
  class Error;
  class Result;
  class CompilationResult;
  class ObjectResult;
  class StructureParamsResult;
  class DiiaParamsResult;
  class Scope;
  class Subject;
  class Object;
  class StructureParam;
  class StructureMethod;
  class DiiaParam;

  class Options {
   public:
  };

  class State {
   public:
    Options* options;
  };

  class Error {
   public:
    std::string message;
  };

  class Result {
   public:
    Error* error;
    Subject* value;
  };

  class CompilationResult {
   public:
    Error* error;
  };

  class ObjectResult {
   public:
    Error* error;
    Object* value;
  };

  class StructureParamsResult {
   public:
    Error* error;
    std::vector<StructureParam*> params;
  };

  class DiiaParamsResult {
   public:
    Error* error;
    std::vector<DiiaParam*> params;
  };

  inline Result* create_result_error(const std::string& message) {
    const auto result = new Result();
    result->error = new Error();
    result->error->message = message;
    return result;
  }

  inline Result* create_result_value(Subject* value) {
    const auto result = new Result();
    result->value = value;
    return result;
  }

  class Scope {
   public:
    State* state;
    Scope* parent;
    std::map<std::string, Subject*> subjects;

    virtual bool has_local(std::string name);
    virtual bool has(std::string name);
    virtual Result* define_structure(mavka::ast::StructureNode* structure_node);
    virtual Result* compile_types(std::vector<mavka::ast::ASTNode*> types);
    virtual Result* compile_node(mavka::ast::ASTNode* node);
    virtual StructureParamsResult* compile_structure_params(
        const std::vector<mavka::ast::StructureParamNode*>& params);
    // virtual Result* define_diia(mavka::ast::DiiaNode* diia_node, Scope*
    // scope); virtual Result* define_module(mavka::ast::ModuleNode* diia_node,
    // Scope* scope);
    // virtual Result* take_module(mavka::ast::TakeModuleNode* diia_node,
    // Scope* scope);
    // virtual Result* take_pak(mavka::ast::TakePakNode* diia_node, Scope*
    // scope);
    virtual Subject* get(std::string name);
    virtual Scope* root();
    // virtual Scope* make_child();
  };

  class Subject {
   public:
    std::vector<Object*> types;

    Result* get(std::string name, Scope* scope);
    Result* set(std::string name, Subject* value, Scope* scope);
    Result* call(std::vector<Subject*> args, Scope* scope);
    ObjectResult* create_instance();
    bool is_structure();
  };

  class StructureParam {
   public:
    int index;
    std::string name;
    Subject* types;
    Subject* value;
  };

  class StructureMethod {
   public:
    Subject* diia;
  };

  class DiiaParam {
   public:
    int index;
    std::string name;
    Subject* type;
    Subject* value;
    bool variadic;
  };

  class Object {
   public:
    static constexpr int OBJECT = 0;
    static constexpr int DIIA = 1;
    static constexpr int STRUCTURE = 2;

    int type = OBJECT;
    Object* structure;
    std::map<std::string, Subject*> properties;

    Subject* structure_parent;
    std::vector<StructureParam*> structure_params;
    std::vector<StructureMethod*> structure_methods;

    std::vector<DiiaParam*> diia_params;
    Subject* diia_return;

    Result* get(std::string name, Scope* scope);
    Result* set(std::string name, Subject* value, Scope* scope);
    Result* call(std::vector<Subject*> args, Scope* scope);
  };

  CompilationResult* compile(mavka::ast::ProgramNode* program_node);

  inline ObjectResult* Subject::create_instance() {
    const auto result = new ObjectResult();

    if (this->types.size() == 1) {
      const auto object = new Object();
      object->type = Object::OBJECT;
      object->structure = this->types[0];
      result->value = object;
      return result;
    }

    result->error = new Error();
    result->error->message = "[BUG] Неможливо створити екземпляр субʼєкта.";

    return result;
  }

  inline bool Subject::is_structure() {
    if (this->types.size() == 1) {
      return this->types[0]->type == Object::STRUCTURE;
    }
    return false;
  }

  inline bool Scope::has_local(const std::string name) {
    return this->subjects.contains(name);
  }

  inline bool Scope::has(const std::string name) {
    if (this->has_local(name)) {
      return true;
    }
    if (this->parent) {
      return this->parent->has(name);
    }
    return false;
  }

  inline Subject* Scope::get(const std::string name) {
    if (this->has_local(name)) {
      return this->subjects.find(name)->second;
    }
    return nullptr;
  }

  inline Scope* Scope::root() {
    if (this->parent) {
      return this->parent->root();
    }
    return this;
  }

  inline Result* Scope::define_structure(
      mavka::ast::StructureNode* structure_node) {
    if (this->has_local(structure_node->name)) {
      return create_result_error("Субʼєкт \"" + structure_node->name +
                                 "\" вже визначено.");
    }

    const auto result = new Result();

    const auto structure_structure = this->root()->get("Структура");
    if (structure_structure == nullptr) {
      result->error = new Error();
      result->error->message = "[BUG] Субʼєкт \"Структура\" не знайдено.";
      return result;
    }

    const auto structure_instance_result =
        structure_structure->create_instance();
    if (structure_instance_result->error) {
      result->error = structure_instance_result->error;
      return result;
    }

    structure_instance_result->value->type = Object::STRUCTURE;

    const auto structure_params_result =
        this->compile_structure_params(structure_node->params);
    if (structure_params_result->error) {
      result->error = structure_params_result->error;
      return result;
    }

    structure_instance_result->value->structure_params =
        structure_params_result->params;

    if (structure_node->parent) {
      const auto structure_parent_result =
          this->compile_node(structure_node->parent);
      if (structure_parent_result->error) {
        result->error = structure_parent_result->error;
        return result;
      }
      structure_instance_result->value->structure_parent =
          structure_parent_result->value;
    }

    result->value = new Subject();
    result->value->types.push_back(structure_instance_result->value);

    this->subjects.insert_or_assign(structure_node->name, result->value);

    return result;
  }

  inline Result* Scope::compile_types(std::vector<mavka::ast::ASTNode*> types) {
    const auto result = new Result();
    for (const auto type : types) {
      const auto compiled_type = this->compile_node(type);
      if (compiled_type->error) {
        result->error = compiled_type->error;
        return result;
      }
      if (!compiled_type->value->is_structure()) {
        return create_result_error("Тип параметра не є структурою.");
      }
    }
    return result;
  }

  inline Result* Scope::compile_node(mavka::ast::ASTNode* node) {
    if (jejalyk::tools:: instanceof <mavka::ast::IdentifierNode>(node)) {
      const auto identifier_node =
          dynamic_cast<mavka::ast::IdentifierNode*>(node);
      const auto subject = this->get(identifier_node->name);
      if (subject == nullptr) {
        return create_result_error("Субʼєкт \"" + identifier_node->name +
                                   "\" не визначено.");
      }
      return create_result_value(subject);
    }
    if (jejalyk::tools:: instanceof <mavka::ast::StructureNode>(node)) {
      const auto structure_node =
          dynamic_cast<mavka::ast::StructureNode*>(node);
      return this->define_structure(structure_node);
    }
    return create_result_value(nullptr);
  }

  inline StructureParamsResult* Scope::compile_structure_params(
      const std::vector<mavka::ast::StructureParamNode*>& params) {
    const auto result = new StructureParamsResult();

    for (int i = 0; i < params.size(); ++i) {
      const auto param = params[i];
      const auto structure_param = new StructureParam();
      structure_param->index = i;
      structure_param->name = param->name;

      if (!param->types.empty()) {
        const auto types_result = this->compile_types(param->types);
        if (types_result->error) {
          result->error = types_result->error;
          return result;
        }
        structure_param->types = types_result->value;
      } else {
        structure_param->types = new Subject();
      }

      if (param->value) {
        const auto param_value_result = this->compile_node(param->value);
        if (param_value_result->error) {
          result->error = param_value_result->error;
          return result;
        }
        structure_param->value = param_value_result->value;
      }

      result->params.push_back(structure_param);
    }

    return result;
  }

  inline CompilationResult* compile(mavka::ast::ProgramNode* program_node) {
    const auto result = new CompilationResult();

    const auto scope = new Scope();

    const auto structure_structure = new Object();
    structure_structure->type = Object::STRUCTURE;
    const auto structure_structure_subject = new Subject();
    structure_structure_subject->types.push_back(structure_structure);
    scope->subjects.insert_or_assign("Структура", structure_structure_subject);

    for (const auto node : program_node->body) {
      const auto compiled_node = scope->compile_node(node);
      if (compiled_node->error) {
        result->error = compiled_node->error;
        return result;
      }
    }

    return result;
  }
}  // namespace newcompiler

#endif  // NEWCOMPILER_H
