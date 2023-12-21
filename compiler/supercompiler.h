#ifndef SUPERCOMPILER_H
#define SUPERCOMPILER_H

#include <map>
#include <string>

#include "../ast.h"
#include "../tools.h"

namespace supercompiler {
  class Error;
  class Result;
  class CompilationResult;
  class ParamsResult;
  class Scope;
  class Object;
  class Subject;
  class Param;

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

  class ParamsResult {
   public:
    Error* error;
    std::vector<Param*> value;
  };

  class Scope {
   public:
    std::map<std::string, Subject*> variables;

    virtual bool has(std::string name);
    virtual Subject* get(std::string name);
    bool has_local(std::string name);
    virtual Result* compile_node(mavka::ast::ASTNode* node);
    virtual ParamsResult* compile_params(
        std::vector<mavka::ast::ParamNode*> params);
    virtual Result* compile_types(std::vector<mavka::ast::ASTNode*> types,
                                  std::string error_message);
    virtual Result* define_structure(mavka::ast::StructureNode* structure_node);
    virtual Result* define_diia(mavka::ast::DiiaNode* diia_node);
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

    std::string diia_name;
    std::vector<Param*> diia_params;
    Subject* diia_return;

    Object* create_instance();
    Subject* get(std::string name);
    Result* set(std::string name, Subject* value);
    bool has(std::string name);
    Result* call(std::vector<Subject*> args, Scope* scope);
    bool is_diia(Scope* scope);
  };

  class Subject {
   public:
    std::vector<Object*> types;
    virtual bool is_structure(Scope* scope);
    virtual bool is_diia(Scope* scope);
    virtual bool check_types(Subject* value);
    virtual bool instance_of(Subject* value);
    virtual Result* call(std::vector<Subject*> args, Scope* scope);
    virtual Result* set(std::string name, Subject* value);
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

  inline Result* error(const std::string& message) {
    const auto result = new Result();
    result->error = new Error();
    result->error->message = message;
    return result;
  }

  inline Result* success(Subject* value) {
    const auto result = new Result();
    result->value = value;
    return result;
  }

  inline bool Scope::has(std::string name) {
    return this->variables.contains(name);
  }

  inline Subject* Scope::get(std::string name) {
    return this->variables.find(name)->second;
  }

  inline bool Scope::has_local(std::string name) {
    return this->variables.contains(name);
  }

  inline Result* Scope::compile_node(mavka::ast::ASTNode* node) {
    if (jejalyk::tools::instance_of<mavka::ast::IdentifierNode>(node)) {
      const auto identifier_node =
          dynamic_cast<mavka::ast::IdentifierNode*>(node);
      if (!this->has(identifier_node->name)) {
        return error("Субʼєкт \"" + identifier_node->name + "\" не визначено.");
      }
      const auto subject = this->get(identifier_node->name);
      return success(subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::AssignSimpleNode>(node)) {
      const auto assign_simple_node =
          dynamic_cast<mavka::ast::AssignSimpleNode*>(node);

      const auto value_result = this->compile_node(assign_simple_node->value);
      if (value_result->error) {
        return value_result;
      }

      if (assign_simple_node->types.empty()) {
        if (this->has_local(assign_simple_node->name)) {
          const auto subject = this->get(assign_simple_node->name);
          if (!value_result->value->check_types(subject)) {
            return error("Неправильний тип значення субʼєкта \"" +
                         assign_simple_node->name + "\".");
          }
          return success(subject);
        } else {
          this->variables.insert_or_assign(assign_simple_node->name,
                                           value_result->value);
          return success(value_result->value);
        }
      } else {
        if (this->has_local(assign_simple_node->name)) {
          return error("Субʼєкт \"" + assign_simple_node->name +
                       "\" вже визначено.");
        }

        const auto types_result =
            this->compile_types(assign_simple_node->types,
                                "Тип субʼєкта \"" + assign_simple_node->name +
                                    "\" не є структурою.");
        if (types_result->error) {
          return types_result;
        }

        if (!value_result->value->check_types(types_result->value)) {
          return error("Субʼєкт \"" + assign_simple_node->name +
                       "\" вже визначено.");
        }

        this->variables.insert_or_assign(assign_simple_node->name,
                                         types_result->value);

        return success(types_result->value);
      }
    }

    if (jejalyk::tools::instance_of<mavka::ast::AssignByIdentifierNode>(node)) {
      const auto assign_by_identifier_node =
          dynamic_cast<mavka::ast::AssignByIdentifierNode*>(node);

      const auto left_result =
          this->compile_node(assign_by_identifier_node->left);
      if (left_result->error) {
        return left_result;
      }

      const auto value_result =
          this->compile_node(assign_by_identifier_node->value);
      if (value_result->error) {
        return value_result;
      }

      return left_result->value->set(assign_by_identifier_node->identifier,
                                     value_result->value);
    }

    if (jejalyk::tools::instance_of<mavka::ast::NumberNode>(node)) {
      const auto number_node = dynamic_cast<mavka::ast::NumberNode*>(node);
      const auto number_structure = this->get("число");
      const auto number = number_structure->types[0]->create_instance();
      const auto number_subject = new Subject();
      number_subject->types.push_back(number);
      return success(number_subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::StringNode>(node)) {
      const auto string_node = dynamic_cast<mavka::ast::StringNode*>(node);
      const auto string_structure = this->get("текст");
      const auto string = string_structure->types[0]->create_instance();
      const auto string_subject = new Subject();
      string_subject->types.push_back(string);
      return success(string_subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::ArrayNode>(node)) {
      const auto array_node = dynamic_cast<mavka::ast::StringNode*>(node);
      const auto array_structure = this->get("список");
      const auto array = array_structure->types[0]->create_instance();
      const auto array_subject = new Subject();
      array_subject->types.push_back(array);
      return success(array_subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::StructureNode>(node)) {
      const auto structure_node =
          dynamic_cast<mavka::ast::StructureNode*>(node);
      return this->define_structure(structure_node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::DiiaNode>(node)) {
      const auto diia_node = dynamic_cast<mavka::ast::DiiaNode*>(node);
      return this->define_diia(diia_node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::CallNode>(node)) {
      const auto call_node = dynamic_cast<mavka::ast::CallNode*>(node);
      const auto value_result = this->compile_node(call_node->value);
      if (value_result->error) {
        return value_result;
      }
      std::vector<Subject*> args;
      for (const auto arg_node : call_node->args) {
        if (!arg_node->name.empty()) {
          throw std::runtime_error("Named args not implemented");
        }
        const auto arg_result = this->compile_node(arg_node->value);
        if (arg_result->error) {
          return arg_result;
        }
        args.push_back(arg_result->value);
      }
      return value_result->value->call(args, this);
    }

    return error("unsupported node");
  }

  inline ParamsResult* Scope::compile_params(
      std::vector<mavka::ast::ParamNode*> params) {
    const auto result = new ParamsResult();

    for (int i = 0; i < params.size(); ++i) {
      const auto param_node = params[i];
      const auto param = new Param();
      param->index = i;
      param->name = param_node->name;
      param->variadic = param_node->variadic;

      const auto types_result = this->compile_types(
          param_node->types,
          "Тип параметра \"" + param->name + "\" повинен бути структурою.");
      if (types_result->error) {
        const auto error_result = new ParamsResult();
        error_result->error = types_result->error;
        return error_result;
      }
      if (param->variadic) {
        const auto list_structure_subject = this->get("список");
        if (!types_result->value->instance_of(list_structure_subject)) {
          const auto error_result = new ParamsResult();
          error_result->error = new Error();
          error_result->error->message = "Тип збірного параметра \"" +
                                         param->name +
                                         "\" повинен бути списком.";
          return error_result;
        }
      }
      param->types = types_result->value;

      if (param_node->value) {
        const auto value_result = this->compile_node(param_node->value);
        if (value_result->error) {
          const auto error_result = new ParamsResult();
          error_result->error = value_result->error;
          return error_result;
        }
        if (!value_result->value->check_types(types_result->value)) {
          const auto error_result = new ParamsResult();
          error_result->error = new Error();
          error_result->error->message = "Значення параметра \"" + param->name +
                                         "\" не відповідає його типу.";
          return error_result;
        }
        param->value = value_result->value;
      }

      result->value.push_back(param);
    }

    return result;
  }

  inline Result* Scope::compile_types(std::vector<mavka::ast::ASTNode*> types,
                                      std::string error_message) {
    const auto result = new Result();
    result->value = new Subject();

    for (const auto type_node : types) {
      const auto type_result = this->compile_node(type_node);
      if (type_result->error) {
        result->error = type_result->error;
        return result;
      }
      if (!type_result->value->is_structure(this)) {
        const auto error_result = new Result();
        error_result->error = new Error();
        error_result->error->message = error_message;
        return error_result;
      }
      result->value->types.push_back(
          type_result->value->types[0]->create_instance());
    }

    return result;
  }

  inline Result* Scope::define_structure(
      mavka::ast::StructureNode* structure_node) {
    const auto structure_structure_subject = this->get("Структура");

    const auto structure_object = new Object();
    structure_object->structure = structure_structure_subject->types[0];

    const auto object_structure_subject = this->get("обʼєкт");
    structure_object->structure_parent = object_structure_subject->types[0];

    structure_object->structure_name = structure_node->name;

    const auto structure_subject = new Subject();
    structure_subject->types.push_back(structure_object);

    this->variables.insert_or_assign(structure_node->name, structure_subject);

    const auto params_result = this->compile_params(structure_node->params);
    if (params_result->error) {
      return error(params_result->error->message);
    }

    if (structure_node->parent) {
      const auto parent_result = this->compile_node(structure_node->parent);
      if (parent_result->error) {
        return error(parent_result->error->message);
      }
      if (!parent_result->value->is_structure(this)) {
        return error("Батьківський тип повинен бути структурою.");
      }
      structure_object->structure_parent = parent_result->value->types[0];

      const auto params_size = params_result->value.size();

      for (int i = 0;
           i < parent_result->value->types[0]->structure_params.size(); ++i) {
        const auto param = parent_result->value->types[0]->structure_params[i];
        const auto param_clone = param->clone();
        param_clone->index = params_size + i;
        params_result->value.push_back(param_clone);
      }
    }

    structure_object->structure_params = params_result->value;

    const auto constructor_diia = new Object();
    const auto diia_structure_subject = this->get("Дія");
    constructor_diia->structure = diia_structure_subject->types[0];
    constructor_diia->diia_params = structure_object->structure_params;
    const auto structure_type_subject = new Subject();
    structure_type_subject->types.push_back(
        structure_object->create_instance());
    constructor_diia->diia_return = structure_type_subject;
    const auto constructor_diia_subject = new Subject();
    constructor_diia_subject->types.push_back(constructor_diia);
    structure_object->properties["чародія_викликати"] =
        constructor_diia_subject;

    return success(structure_subject);
  }

  inline Result* Scope::define_diia(mavka::ast::DiiaNode* diia_node) {
    const auto diia_structure_subject = this->get("Дія");

    const auto diia_object = new Object();
    diia_object->structure = diia_structure_subject->types[0];

    const auto diia_subject = new Subject();
    diia_subject->types.push_back(diia_object);

    this->variables.insert_or_assign(diia_node->name, diia_subject);

    const auto params_result = this->compile_params(diia_node->params);
    if (params_result->error) {
      return error(params_result->error->message);
    }

    diia_object->diia_params = params_result->value;

    if (!diia_node->return_types.empty()) {
      const auto return_types_result =
          this->compile_types(diia_node->return_types,
                              "Тип поверненого значення повинен бути "
                              "структурою.");
      if (return_types_result->error) {
        return return_types_result;
      }
      diia_object->diia_return = return_types_result->value;
    } else {
      diia_object->diia_return = new Subject();
    }

    return success(diia_subject);
  }

  inline Object* Object::create_instance() {
    const auto instance = new Object();
    instance->structure = this;
    instance->type = OBJECT;
    for (const auto param : this->structure_params) {
      instance->properties.insert_or_assign(param->name, param->types);
    }
    return instance;
  }

  inline Subject* Object::get(std::string name) {
    return this->properties.find(name)->second;
  }

  inline Result* Object::set(std::string name, Subject* value) {
    if (!this->has(name)) {
      const auto error_result = new Result();
      error_result->error = new Error();
      error_result->error->message =
          "Властивість \"" + name + "\" не визначено.";
      return error_result;
    }
    const auto property_subject = this->get(name);
    if (!value->check_types(property_subject)) {
      const auto error_result = new Result();
      error_result->error = new Error();
      error_result->error->message =
          "Значення властивості \"" + name + "\" не відповідає її типу.";
      return error_result;
    }
    return success(value);
  }

  inline bool Object::has(std::string name) {
    return this->properties.contains(name);
  }

  inline Result* Object::call(std::vector<Subject*> args, Scope* scope) {
    if (this->properties.contains("чародія_викликати")) {
      if (const auto magic_diia = this->get("чародія_викликати")) {
        return magic_diia->call(args, scope);
      }
    }
    if (this->is_diia(scope)) {
      if (args.size() > this->diia_params.size()) {
        if (this->diia_params.empty() ||
            !this->diia_params[this->diia_params.size() - 1]->variadic) {
          return error("Забагато аргументів.");
        }
      }
      for (const auto param : this->diia_params) {
        if (param->variadic) {
          break;
        }
        if (args.size() > param->index) {
          const auto arg = args[param->index];
          if (!arg->check_types(param->types)) {
            return error("Аргумент \"" + param->name +
                         "\" не відповідає його типу.");
          }
        } else {
          if (param->value) {
            continue;
          }

          return error("Недостатня кількість аргументів.");
        }
      }
      return success(this->diia_return);
    }
    return error("unsupported call");
  }

  inline bool Object::is_diia(Scope* scope) {
    return this->structure == scope->get("Дія")->types[0];
  }

  inline bool Subject::is_structure(Scope* scope) {
    if (this->types.size() == 1) {
      const auto structure_structure_subject = scope->get("Структура");
      auto structure = this->types[0]->structure;
      while (structure) {
        if (structure == structure_structure_subject->types[0]) {
          return true;
        }
        structure = structure->structure_parent;
      }
    }
    return false;
  }

  inline bool Subject::is_diia(Scope* scope) {
    if (this->types.size() == 1) {
      const auto diia_structure_subject = scope->get("Дія");
      if (this->types[0]->structure == diia_structure_subject->types[0]) {
        return true;
      }
    }
    return false;
  }

  inline bool Subject::check_types(Subject* value) {
    if (this->types.empty() && value->types.empty()) {
      return true;
    }
    if (this->types.empty()) {
      return false;
    }
    if (value->types.empty()) {
      return true;
    }
    auto structure = this->types[0]->structure;
    while (structure) {
      if (value->types[0]->structure == structure) {
        return true;
      }
      structure = structure->structure_parent;
    }
    return false;
  }

  inline bool Subject::instance_of(Subject* value) {
    auto structure = this->types[0]->structure;
    while (structure) {
      if (value->types[0] == structure) {
        return true;
      }
      structure = structure->structure_parent;
    }
    return false;
  }

  inline Result* Subject::call(std::vector<Subject*> args, Scope* scope) {
    if (this->types.size() == 1) {
      return this->types[0]->call(args, scope);
    }
    return error("Неможливо викликати.");
  }

  inline Result* Subject::set(std::string name, Subject* value) {
    if (this->types.size() == 1) {
      return this->types[0]->set(name, value);
    }
    return error("Неможливо встановити.");
  }

  inline Param* Param::clone() {
    const auto param = new Param();
    param->index = this->index;
    param->name = this->name;
    param->types = this->types;
    param->value = this->value;
    param->variadic = this->variadic;
    return param;
  }

  inline CompilationResult* compile(mavka::ast::ProgramNode* program_node) {
    const auto result = new CompilationResult();

    const auto scope = new Scope();

    const auto object = new Object();
    const auto structure = new Object();
    structure->structure = object;

    const auto object_subject = new Subject();
    object_subject->types.push_back(object);
    const auto structure_subject = new Subject();
    structure_subject->types.push_back(structure);

    scope->variables.insert_or_assign("обʼєкт", object_subject);
    scope->variables.insert_or_assign("Структура", structure_subject);

    for (const auto node : program_node->body) {
      const auto compiled_node = scope->compile_node(node);
      if (compiled_node->error) {
        result->error = compiled_node->error;
        return result;
      }
    }

    return result;
  }
}  // namespace supercompiler

#endif  // SUPERCOMPILER_H
