#ifndef XCOMPILER_H
#define XCOMPILER_H

#include <map>
#include <string>

#include "../ast.h"
#include "../tools.h"

namespace xcompiler {
  class Error;
  class Result;
  class Scope;
  class Type;
  class DiiaType;
  class Subject;

  class Error {
   public:
    std::string message;
  };

  class Result {
   public:
    Error* error;
    Subject* value;
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

  class Scope final {
   public:
    Scope* parent = nullptr;
    std::map<std::string, Subject*> variables;

    virtual bool has_local(std::string name);
    virtual bool has(std::string name);
    virtual Subject* get(std::string name);
    virtual Result* define_structure(mavka::ast::StructureNode* structure_node);
    virtual Result* compile_types(
        const std::vector<mavka::ast::ASTNode*>& types,
        const std::string& error_message);
    virtual Result* compile_node(mavka::ast::ASTNode* node);

    virtual ~Scope() = default;
  };

  class Type {
   public:
    std::string name;
    Type* parent = nullptr;
    std::map<std::string, Subject*> params;

    virtual bool intersect(Subject* value);

    virtual ~Type() = default;
  };

  class DiiaType final : public Type {
   public:
    std::map<std::string, Type*> param_types;
    Type* return_type = nullptr;

    ~DiiaType() override = default;
  };

  class Subject final {
   public:
    std::vector<Type*> types;

    virtual bool intersect(Subject* value);

    virtual ~Subject() = default;
  };

  inline bool Scope::has_local(std::string name) {
    return this->variables.contains(name);
  }

  inline bool Scope::has(std::string name) {
    if (this->has_local(name)) {
      return true;
    }
    if (this->parent != nullptr) {
      return this->parent->has(name);
    }
    return false;
  }

  inline Subject* Scope::get(std::string name) {
    return this->variables[name];
  }

  inline Result* Scope::define_structure(
      mavka::ast::StructureNode* structure_node) {
    const auto type = new Type();
    type->name = structure_node->name;

    const auto subject = new Subject();
    subject->types.push_back(type);

    this->variables.insert_or_assign(structure_node->name, subject);

    const auto result = new Result();
    result->value = subject;

    return result;
  }

  inline Result* Scope::compile_types(
      const std::vector<mavka::ast::ASTNode*>& types,
      const std::string& error_message) {
    const auto result = new Result();
    result->value = new Subject();

    for (int i = 0; i < types.size(); ++i) {
      const auto type_node = types[i];
      const auto type_result = this->compile_node(type_node);
      if (type_result->error) {
        return type_result;
      }
      result->value->types.push_back(type_result->value->types[0]);
    }

    return result;
  }

  inline Result* Scope::compile_node(mavka::ast::ASTNode* node) {
    if (jejalyk::tools::instance_of<mavka::ast::IdentifierNode>(node)) {
      const auto identifier_node =
          dynamic_cast<mavka::ast::IdentifierNode*>(node);
      const auto subject = this->get(identifier_node->name);
      if (subject == nullptr) {
        return error("Субʼєкт \"" + identifier_node->name + "\" не визначено.");
      }
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
          if (!value_result->value->intersect(subject)) {
            return error("Неправильний тип значення субʼєкта.");
          }
          return success(subject);
        } else {
          const auto subject = new Subject();
          this->variables.insert_or_assign(assign_simple_node->name, subject);
          return success(subject);
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

        if (!value_result->value->intersect(types_result->value)) {
          return error("Неправильний тип значення субʼєкта.");
        }

        this->variables.insert_or_assign(assign_simple_node->name,
                                         types_result->value);

        return success(types_result->value);
      }
    }

    if (jejalyk::tools::instance_of<mavka::ast::StructureNode>(node)) {
      const auto structure_node =
          dynamic_cast<mavka::ast::StructureNode*>(node);
      return this->define_structure(structure_node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::NumberNode>(node)) {
      const auto number_node = dynamic_cast<mavka::ast::NumberNode*>(node);
      const auto number = this->get("число");
      if (number == nullptr) {
        return error("[BUG] Не знайдено структуру \"число\".");
      }
      return success(number);
    }

    throw std::runtime_error("Node not implemented");
  }

  inline bool Type::intersect(Subject* value) {
    for (const auto& type : value->types) {
      if (type == this) {
        return true;
      }
      if (type->parent != nullptr && type->parent->intersect(value)) {
        return true;
      }
    }
    return false;
  }

  inline bool Subject::intersect(Subject* value) {
    if (this->types.empty()) {
      return true;
    }
    for (const auto& type : this->types) {
      if (type->intersect(value)) {
        return true;
      }
    }
    return false;
  }

  inline Result* compile(const mavka::ast::ProgramNode* program_node) {
    const auto scope = new Scope();

    const auto object_type = new Type();
    object_type->name = "обʼєкт";

    for (const auto& node : program_node->body) {
      const auto result = scope->compile_node(node);
      if (result->error) {
        return result;
      }
    }

    const auto result = new Result();
    result->value = new Subject();
    return result;
  }
}  // namespace xcompiler

#endif  // XCOMPILER_H
