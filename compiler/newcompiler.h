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
  class ParamsResult;
  class Scope;
  class Subject;
  class Object;
  class Param;

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

  class ParamsResult {
   public:
    Error* error;
    std::vector<Param*> params;
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
    virtual ParamsResult* compile_structure_params(
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
    bool instance_of_subject(Subject* value);
    Subject* create_all_instances();
  };

  class Param {
   public:
    int index;
    std::string name;
    Subject* types;
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

    Object* structure_parent;
    std::vector<Param*> structure_params;

    std::vector<Param*> diia_params;
    Subject* diia_return;

    Result* get(std::string name, Scope* scope);
    Result* set(std::string name, Subject* value, Scope* scope);
    Result* call(std::vector<Subject*> args, Scope* scope);
    bool instance_of(Object* type);
    bool instance_of_subject(Subject* value);
    Object* create_instance();
    bool is_structure();
  };

  CompilationResult* compile(mavka::ast::ProgramNode* program_node);

  inline Result* Object::call(std::vector<Subject*> args, Scope* scope) {
    if (this->properties.contains("чародія_викликати")) {
      const auto diia_subject = this->properties["чародія_викликати"];
      return diia_subject->call(args, scope);
    }
    if (this->type != DIIA) {
      return create_result_error("Неможливо викликати не дію.");
    }
    for (const auto param : this->diia_params) {
      if (args.size() <= param->index) {
        return create_result_error("Недостатньо аргументів для виклику.");
      }
      const auto arg = args[param->index];
      if (!arg->instance_of_subject(param->types)) {
        return create_result_error("Неправильний тип аргументу \"" +
                                   param->name + "\".");
      }
    }
    const auto return_subject = this->diia_return->create_all_instances();
    return create_result_value(return_subject);
  }

  inline bool Object::instance_of(Object* type) {
    Object* structure = this->structure;
    while (structure != nullptr) {
      if (structure == type) {
        return true;
      }
      structure = structure->structure_parent;
    }
    return false;
  }

  inline bool Object::instance_of_subject(Subject* value) {
    for (const auto type : value->types) {
      if (this->instance_of(type)) {
        return true;
      }
    }
    return false;
  }

  inline Object* Object::create_instance() {
    const auto object = new Object();
    object->type = OBJECT;
    object->structure = this;
    return object;
  }

  inline bool Object::is_structure() {
    return this->type == STRUCTURE;
  }

  inline Result* Subject::call(std::vector<Subject*> args, Scope* scope) {
    if (this->types.size() == 1) {
      return this->types[0]->call(args, scope);
    }
    return create_result_error("Неможливо викликати.");
  }

  inline ObjectResult* Subject::create_instance() {
    const auto result = new ObjectResult();

    if (this->types.size() == 1) {
      result->value = this->types[0]->create_instance();
      return result;
    }

    result->error = new Error();
    result->error->message = "[BUG] Неможливо створити екземпляр субʼєкта.";

    return result;
  }

  inline bool Subject::is_structure() {
    if (this->types.size() == 1) {
      return this->types[0]->is_structure();
    }
    return false;
  }

  inline bool Subject::instance_of_subject(Subject* value) {
    for (const auto type : this->types) {
      if (type->instance_of_subject(value)) {
        return true;
      }
    }
    return false;
  }

  inline Subject* Subject::create_all_instances() {
    const auto subject = new Subject();
    for (const auto type : this->types) {
      const auto instance = type->create_instance();
      subject->types.push_back(instance);
    }
    return subject;
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

    result->value = new Subject();
    result->value->types.push_back(structure_instance_result->value);
    this->subjects.insert_or_assign(structure_node->name, result->value);

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
      if (!structure_parent_result->value->is_structure()) {
        return create_result_error(
            "Тип батьківської структури не є структурою.");
      }
      structure_instance_result->value->structure_parent =
          structure_parent_result->value->types[0];
    }

    const auto constructor_diia = new Object();
    constructor_diia->type = Object::DIIA;
    constructor_diia->diia_params = structure_params_result->params;
    constructor_diia->diia_return = result->value;
    const auto constructor_diia_subject = new Subject();
    constructor_diia_subject->types.push_back(constructor_diia);
    structure_instance_result->value->properties["чародія_викликати"] =
        constructor_diia_subject;

    return result;
  }

  inline Result* Scope::compile_types(std::vector<mavka::ast::ASTNode*> types) {
    const auto result = new Result();
    result->value = new Subject();
    for (const auto type : types) {
      const auto compiled_type = this->compile_node(type);
      if (compiled_type->error) {
        result->error = compiled_type->error;
        return result;
      }
      if (!compiled_type->value->is_structure()) {
        return create_result_error("Тип параметра не є структурою.");
      }
      result->value->types.push_back(compiled_type->value->types[0]);
    }
    return result;
  }

  inline Result* Scope::compile_node(mavka::ast::ASTNode* node) {
    if (jejalyk::tools::instance_of<mavka::ast::IdentifierNode>(node)) {
      const auto identifier_node =
          dynamic_cast<mavka::ast::IdentifierNode*>(node);
      const auto subject = this->get(identifier_node->name);
      if (subject == nullptr) {
        return create_result_error("Субʼєкт \"" + identifier_node->name +
                                   "\" не визначено.");
      }
      return create_result_value(subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::StructureNode>(node)) {
      const auto structure_node =
          dynamic_cast<mavka::ast::StructureNode*>(node);
      return this->define_structure(structure_node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::AssignSimpleNode>(node)) {
      const auto assign_simple_node =
          dynamic_cast<mavka::ast::AssignSimpleNode*>(node);
      if (assign_simple_node->types.empty()) {
        if (!this->has_local(assign_simple_node->name)) {
          const auto subject = new Subject();
          const auto compiled_value =
              this->compile_node(assign_simple_node->value);
          if (compiled_value->error) {
            return compiled_value;
          }
          this->subjects.insert_or_assign(assign_simple_node->name, subject);
          return create_result_value(subject);
        }
        return create_result_value(this->get(assign_simple_node->name));
      } else {
        if (this->has_local(assign_simple_node->name)) {
          return create_result_error("Субʼєкт \"" + assign_simple_node->name +
                                     "\" вже визначено.");
        }

        const auto compiled_types =
            this->compile_types(assign_simple_node->types);
        if (compiled_types->error) {
          return compiled_types;
        }
        this->subjects.insert_or_assign(assign_simple_node->name,
                                        compiled_types->value);
      }
    }

    if (jejalyk::tools::instance_of<mavka::ast::NumberNode>(node)) {
      const auto number_node = dynamic_cast<mavka::ast::NumberNode*>(node);
      const auto number_structure = this->root()->get("число");
      if (number_structure == nullptr) {
        return create_result_error("[BUG] Субʼєкт \"число\" не знайдено.");
      }
      const auto number_instance_result = number_structure->create_instance();
      if (number_instance_result->error) {
        return create_result_error(number_instance_result->error->message);
      }
      const auto number_instance_subject = new Subject();
      number_instance_subject->types.push_back(number_instance_result->value);
      return create_result_value(number_instance_subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::StringNode>(node)) {
      const auto string_node = dynamic_cast<mavka::ast::StringNode*>(node);
      const auto text_structure = this->root()->get("текст");
      if (text_structure == nullptr) {
        return create_result_error("[BUG] Субʼєкт \"текст\" не знайдено.");
      }
      const auto text_instance_result = text_structure->create_instance();
      if (text_instance_result->error) {
        return create_result_error(text_instance_result->error->message);
      }
      const auto text_instance_subject = new Subject();
      text_instance_subject->types.push_back(text_instance_result->value);
      return create_result_value(text_instance_subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::CallNode>(node)) {
      const auto call_node = dynamic_cast<mavka::ast::CallNode*>(node);
      const auto compiled_value = this->compile_node(call_node->value);
      if (compiled_value->error) {
        return compiled_value;
      }
      std::vector<Subject*> compiled_args;
      for (const auto arg : call_node->args) {
        if (!arg->name.empty()) {
          throw std::runtime_error("Named args not implemented");
        }
        const auto compiled_arg = this->compile_node(arg->value);
        if (compiled_arg->error) {
          return compiled_arg;
        }
        compiled_args.push_back(compiled_arg->value);
      }
      return compiled_value->value->call(compiled_args, this);
    }

    throw std::runtime_error("Node not implemented");
  }

  inline ParamsResult* Scope::compile_structure_params(
      const std::vector<mavka::ast::StructureParamNode*>& params) {
    const auto result = new ParamsResult();

    for (int i = 0; i < params.size(); ++i) {
      const auto param_node = params[i];
      const auto param = new Param();
      param->index = i;
      param->name = param_node->name;

      if (!param_node->types.empty()) {
        const auto types_result = this->compile_types(param_node->types);
        if (types_result->error) {
          result->error = types_result->error;
          return result;
        }
        param->types = types_result->value;
      } else {
        param->types = new Subject();
      }

      if (param_node->value) {
        const auto param_value_result = this->compile_node(param_node->value);
        if (param_value_result->error) {
          result->error = param_value_result->error;
          return result;
        }
        param->value = param_value_result->value;
      }

      result->params.push_back(param);
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
