#include "compiler.h"

namespace supercompiler {
  bool Scope::has(std::string name) {
    if (this->variables.contains(name)) {
      return true;
    }
    if (this->parent) {
      return this->parent->has(name);
    }
    return false;
  }

  Subject* Scope::get(std::string name) {
    if (this->variables.contains(name)) {
      return this->variables.find(name)->second;
    }
    if (this->parent) {
      return this->parent->get(name);
    }
    return nullptr;
  }

  Subject* Scope::get_local(std::string name) {
    return this->variables.find(name)->second;
  }

  bool Scope::has_local(std::string name) {
    return this->variables.contains(name);
  }

  Result* Scope::compile_node(mavka::ast::ASTNode* node) {
    if (jejalyk::tools::instance_of<mavka::ast::IdentifierNode>(node)) {
      const auto identifier_node =
          dynamic_cast<mavka::ast::IdentifierNode*>(node);
      if (!this->has(identifier_node->name)) {
        return error("Субʼєкт \"" + identifier_node->name + "\" не визначено.");
      }
      const auto subject = this->get(identifier_node->name);
      return success(subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::ChainNode>(node)) {
      const auto chain_node = dynamic_cast<mavka::ast::ChainNode*>(node);

      const auto left_result = this->compile_node(chain_node->left);
      if (left_result->error) {
        return left_result;
      }

      if (jejalyk::tools::instance_of<mavka::ast::IdentifierNode>(
              chain_node->right)) {
        const auto right_identifier_node =
            dynamic_cast<mavka::ast::IdentifierNode*>(chain_node->right);

        if (!left_result->value->has(right_identifier_node->name)) {
          return error("Властивість \"" + right_identifier_node->name +
                       "\" не визначено.");
        }

        const auto subject =
            left_result->value->get(right_identifier_node->name);
        return success(subject);
      } else {
        const auto right_result = this->compile_node(chain_node->right);
        if (right_result->error) {
          return right_result;
        }

        return left_result->value->get_element(right_result->value, this);
      }
    }

    if (jejalyk::tools::instance_of<mavka::ast::GetElementNode>(node)) {
      const auto get_element_node =
          dynamic_cast<mavka::ast::GetElementNode*>(node);

      const auto value_result = this->compile_node(get_element_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto index_result = this->compile_node(get_element_node->index);
      if (index_result->error) {
        return index_result;
      }

      return value_result->value->get_element(index_result->value, this);
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
          const auto subject = this->get_local(assign_simple_node->name);
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

    if (jejalyk::tools::instance_of<mavka::ast::AssignByElementNode>(node)) {
      const auto assign_by_element_node =
          dynamic_cast<mavka::ast::AssignByElementNode*>(node);

      const auto left_result = this->compile_node(assign_by_element_node->left);
      if (left_result->error) {
        return left_result;
      }

      const auto element_result =
          this->compile_node(assign_by_element_node->element);
      if (element_result->error) {
        return element_result;
      }

      const auto value_result =
          this->compile_node(assign_by_element_node->value);
      if (value_result->error) {
        return value_result;
      }

      return left_result->value->set_element(element_result->value,
                                             value_result->value, this);
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

    if (jejalyk::tools::instance_of<mavka::ast::DictionaryNode>(node)) {
      const auto dictionary_node =
          dynamic_cast<mavka::ast::DictionaryNode*>(node);
      const auto dictionary_structure = this->get("словник");
      const auto dictionary = dictionary_structure->types[0]->create_instance();
      const auto dictionary_subject = new Subject();
      dictionary_subject->types.push_back(dictionary);
      return success(dictionary_subject);
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
      std::map<std::string, Subject*> named_args;
      for (const auto arg_node : call_node->args) {
        if (!arg_node->name.empty()) {
          const auto arg_result = this->compile_node(arg_node->value);
          if (arg_result->error) {
            return arg_result;
          }
          named_args.insert_or_assign(arg_node->name, arg_result->value);
        } else {
          const auto arg_result = this->compile_node(arg_node->value);
          if (arg_result->error) {
            return arg_result;
          }
          args.push_back(arg_result->value);
        }
      }
      if (!named_args.empty()) {
        return value_result->value->call_named(named_args, this);
      }
      return value_result->value->call(args, this);
    }

    if (jejalyk::tools::instance_of<mavka::ast::EachNode>(node)) {
      const auto each_node = dynamic_cast<mavka::ast::EachNode*>(node);
      this->variables.insert_or_assign(each_node->name, new Subject());
      if (!each_node->keyName.empty()) {
        this->variables.insert_or_assign(each_node->keyName, new Subject());
      }
      // todo: handle fromto
      const auto body_result = this->compile_body(each_node->body);
      if (body_result->error) {
        return error(body_result->error->message);
      }
      return success(new Subject());
    }

    if (jejalyk::tools::instance_of<mavka::ast::ArithmeticNode>(node)) {
      const auto arithmetic_node =
          dynamic_cast<mavka::ast::ArithmeticNode*>(node);
      const auto left_result = this->compile_node(arithmetic_node->left);
      if (left_result->error) {
        return left_result;
      }
      const auto right_result = this->compile_node(arithmetic_node->right);
      if (right_result->error) {
        return right_result;
      }
      if (arithmetic_node->op == "+") {
        return left_result->value->plus(right_result->value, this);
      }
      if (arithmetic_node->op == "-") {
        return left_result->value->minus(right_result->value, this);
      }
      if (arithmetic_node->op == "*") {
        return left_result->value->multiply(right_result->value, this);
      }
      if (arithmetic_node->op == "/") {
        return left_result->value->divide(right_result->value, this);
      }
      if (arithmetic_node->op == "//") {
        return left_result->value->divdiv(right_result->value, this);
      }
      if (arithmetic_node->op == "**") {
        return left_result->value->pow(right_result->value, this);
      }
    }

    if (jejalyk::tools::instance_of<mavka::ast::ReturnNode>(node)) {
      const auto return_node = dynamic_cast<mavka::ast::ReturnNode*>(node);
      if (!this->diia) {
        return error(
            "Вказівка \"вернути\" може бути використана тільки в "
            "тілі дії.");
      }
      const auto value_result = this->compile_node(return_node->value);
      if (value_result->error) {
        return value_result;
      }
      if (!value_result->value->check_types(this->diia->diia_return)) {
        return error("Неправильний тип значення, що повертається.");
      }
      return value_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NegativeNode>(node)) {
      const auto negative_node = dynamic_cast<mavka::ast::NegativeNode*>(node);
      const auto value_result = this->compile_node(negative_node->value);
      if (value_result->error) {
        return value_result;
      }
      return value_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::IfNode>(node)) {
      const auto if_node = dynamic_cast<mavka::ast::IfNode*>(node);

      const auto body_result = this->compile_body(if_node->body);
      if (body_result->error) {
        return error(body_result->error->message);
      }

      const auto else_body_result = this->compile_body(if_node->body);
      if (else_body_result->error) {
        return error(else_body_result->error->message);
      }

      return success(new Subject());
    }

    return error("unsupported node");
  }

  ParamsResult* Scope::compile_params(
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

  Result* Scope::compile_types(std::vector<mavka::ast::ASTNode*> types,
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

  Result* Scope::define_structure(mavka::ast::StructureNode* structure_node) {
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

    for (int i = 0; i < this->body->size(); ++i) {
      const auto inner_node = this->body->at(i);
      if (!inner_node) {
        continue;
      }

      if (jejalyk::tools::instance_of<mavka::ast::DiiaNode>(inner_node)) {
        const auto inner_diia_node =
            dynamic_cast<mavka::ast::DiiaNode*>(inner_node);
        if (inner_diia_node->structure == structure_node->name) {
          const auto compiled_inner_node = this->compile_node(inner_node);
          if (compiled_inner_node->error) {
            return compiled_inner_node;
          }
          this->body->at(i) = nullptr;
        }
      }
    }

    if (structure_object->structure_methods.contains("чародія_створити")) {
      structure_object->properties["чародія_викликати"] =
          structure_object->structure_methods["чародія_створити"];
    } else {
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
    }

    return success(structure_subject);
  }

  Result* Scope::define_diia(mavka::ast::DiiaNode* diia_node) {
    const auto diia_structure_subject = this->get("Дія");

    const auto diia_object = new Object();
    diia_object->structure = diia_structure_subject->types[0];

    const auto diia_subject = new Subject();
    diia_subject->types.push_back(diia_object);

    const auto diia_scope = this->make_child();
    diia_scope->body = &diia_node->body;

    if (diia_node->structure.empty()) {
      this->variables.insert_or_assign(diia_node->name, diia_subject);
    } else {
      if (!this->has_local(diia_node->structure)) {
        return error("Структуру \"" + diia_node->structure +
                     "\" не визначено.");
      }
      const auto structure_subject = this->get(diia_node->structure);
      if (!structure_subject->is_structure(this)) {
        return error("\"" + diia_node->structure + "\" не є структурою.");
      }
      const auto structure_object = structure_subject->types[0];
      if (structure_object->structure_methods.contains(diia_node->name)) {
        return error("Дію \"" + diia_node->name +
                     "\" вже визначено для структури \"" +
                     diia_node->structure + "\".");
      }
      structure_object->structure_methods.insert_or_assign(diia_node->name,
                                                           diia_subject);
      const auto me = structure_subject->types[0]->create_instance();
      const auto me_subject = new Subject();
      me_subject->types.push_back(me);
      diia_scope->variables.insert_or_assign("я", me_subject);
    }

    const auto params_result = diia_scope->compile_params(diia_node->params);
    if (params_result->error) {
      return error(params_result->error->message);
    }
    for (const auto param : params_result->value) {
      diia_scope->variables.insert_or_assign(param->name, param->types);
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

    diia_scope->diia = diia_object;

    const auto body_result = diia_scope->compile_body(diia_node->body);
    if (body_result->error) {
      return error(body_result->error->message);
    }

    return success(diia_subject);
  }

  Result* Scope::compile_body(std::vector<mavka::ast::ASTNode*> body) {
    const auto result = new Result();

    for (int i = 0; i < body.size(); ++i) {
      const auto node = body[i];
      if (!node) {
        continue;
      }

      const auto compiled_node = this->compile_node(node);
      if (compiled_node->error) {
        result->error = compiled_node->error;
        return result;
      }
    }

    return result;
  }

  Scope* Scope::make_child() {
    const auto child = new Scope();
    child->parent = this;
    return child;
  }
}