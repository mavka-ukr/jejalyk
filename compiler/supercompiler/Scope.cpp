#include "compiler.h"

namespace supercompiler {
  void Scope::set(std::string name, Subject* value) {
    if (this->micro) {
      this->parent->set(name, value);
    } else {
      this->variables.insert_or_assign(name, value);
    }
  }

  bool Scope::has(std::string name) {
    if (this->micro) {
      return this->parent->has(name);
    }
    if (this->has_local(name)) {
      return true;
    }
    if (this->parent) {
      return this->parent->has(name);
    }
    return false;
  }

  Subject* Scope::get(std::string name) {
    if (this->micro) {
      return this->parent->get(name);
    }
    if (this->has_local(name)) {
      return this->get_local(name);
    }
    if (this->parent) {
      return this->parent->get(name);
    }
    return nullptr;
  }

  Subject* Scope::get_local(std::string name) {
    if (this->micro) {
      return this->parent->get_local(name);
    }
    return this->variables.find(name)->second;
  }

  bool Scope::has_local(std::string name) {
    if (this->micro) {
      return this->parent->has_local(name);
    }
    return this->variables.contains(name);
  }

  Result* Scope::assign(std::string name, Subject* value) {
    if (this->has_local(name)) {
      const auto subject = this->get_local(name);
      if (!value->check_types({}, subject)) {
        return error("Невірне значення субʼєкта \"" + name + "\".");
      }
      return success(subject);
    }
    this->set(name, value);
    return success(value);
  }

  Result* Scope::make_diia_from_ast(
      Scope* diia_scope,
      bool declaration,
      bool ee,
      bool async,
      const std::string& name,
      const std::string& structure,
      const std::vector<mavka::ast::GenericNode*>& generics,
      const std::vector<mavka::ast::ParamNode*>& params,
      const std::vector<mavka::ast::TypeValueSingleNode*>& return_types) {
    const auto diia_structure_subject = this->get("Дія");

    const auto diia_object = new Object();
    diia_object->structure = diia_structure_subject->types[0];

    for (int i = 0; i < generics.size(); ++i) {
      const auto generic_node = generics[i];
      const auto generic = new Generic();
      generic->index = i;
      generic->name = generic_node->name;
      diia_object->diia_generics.push_back(generic);
    }

    diia_scope->diia = diia_object;

    const auto diia_subject = new Subject();
    diia_subject->types.push_back(diia_object);

    if (structure.empty()) {
      if (ee) {
        if (!declaration) {
          return error("Не вказано структури для її дії.");
        }
      }
      this->set(name, diia_subject);
    } else {
      if (!this->has_local(structure)) {
        return error("Структуру \"" + structure + "\" не визначено.");
      }
      const auto structure_subject = this->get(structure);
      if (!structure_subject->is_structure(this)) {
        return error("\"" + structure + "\" не є структурою.");
      }
      const auto structure_object = structure_subject->types[0];
      if (ee) {
        if (structure_object->properties.contains(name)) {
          return error("Її дію \"" + name +
                       "\" вже визначено для структури \"" + structure + "\".");
        }
        structure_object->properties.insert_or_assign(name, diia_subject);
      } else {
        if (structure_object->structure_methods.contains(name)) {
          return error("Дію \"" + name + "\" вже визначено для структури \"" +
                       structure + "\".");
        }
        structure_object->structure_methods.insert_or_assign(name,
                                                             diia_subject);
        const auto me = structure_subject->types[0]->create_instance();
        const auto me_subject = new Subject();
        me_subject->types.push_back(me);
        diia_scope->set("я", me_subject);
      }
    }

    const auto params_scope = this->make_child();
    params_scope->micro = true;
    params_scope->generics = diia_object->diia_generics;
    const auto params_result = params_scope->compile_params(params);
    if (params_result->error) {
      return new Result(params_result->error);
    }
    for (const auto param : params_result->value) {
      diia_scope->set(param->name, param->types);
    }

    diia_object->diia_params = params_result->value;

    if (!return_types.empty()) {
      const auto return_type_scope = this->make_child();
      return_type_scope->micro = true;
      return_type_scope->generics = diia_object->diia_generics;
      const auto return_types_result = return_type_scope->compile_types(
          return_types, "Тип поверненого значення повинен бути структурою.");
      if (return_types_result->error) {
        return return_types_result;
      }
      diia_object->diia_return = return_types_result->value;
    } else {
      diia_object->diia_return = new Subject();
    }

    return success(diia_subject);
  }

  Result* Scope::compile_node(mavka::ast::ASTNode* node) {
    if (!node) {
      return error("empty node");
    }

    if (jejalyk::tools::instance_of<mavka::ast::AnonDiiaNode>(node)) {
      const auto anon_diia_node = dynamic_cast<mavka::ast::AnonDiiaNode*>(node);
      const auto diia_scope = this->make_child();
      const auto diia_subject_result = this->make_diia_from_ast(
          diia_scope, false, false, anon_diia_node->async, "", "", {},
          anon_diia_node->params, anon_diia_node->return_types);
      if (diia_subject_result->error) {
        return diia_subject_result;
      }
      this->bodies_to_compile.push_back(
          new BodyToCompile(diia_scope, anon_diia_node->body));
      return diia_subject_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ArgNode>(node)) {
      const auto arg_node = dynamic_cast<mavka::ast::ArgNode*>(node);
      // todo
      std::cout << "ArgNode" << std::endl;
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

    if (jejalyk::tools::instance_of<mavka::ast::ArrayNode>(node)) {
      const auto array_node = dynamic_cast<mavka::ast::StringNode*>(node);
      const auto array_structure = this->get("список");
      const auto array = array_structure->types[0]->create_instance();
      const auto array_subject = new Subject();
      array_subject->types.push_back(array);
      return success(array_subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::AsNode>(node)) {
      const auto as_node = dynamic_cast<mavka::ast::AsNode*>(node);
      // todo
      std::cout << "AsNode" << std::endl;
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
          if (!value_result->value->check_types({}, subject)) {
            return error_from_ast(
                node, "Невірне значення субʼєкта \"" +
                          assign_simple_node->name + "\": очікується " +
                          subject->types_string({}) + ", отримано " +
                          value_result->value->types_string({}) + ".");
          }
          return success(subject);
        } else {
          this->set(assign_simple_node->name, value_result->value);
          return success(value_result->value);
        }
      } else {
        if (this->has_local(assign_simple_node->name)) {
          return error_from_ast(node, "Субʼєкт \"" + assign_simple_node->name +
                                          "\" вже визначено.");
        }

        const auto types_result =
            this->compile_types(assign_simple_node->types,
                                "Тип субʼєкта \"" + assign_simple_node->name +
                                    "\" не є структурою.");
        if (types_result->error) {
          return types_result;
        }

        if (!value_result->value->check_types({}, types_result->value)) {
          return error_from_ast(
              node, "Невірне значення субʼєкта \"" + assign_simple_node->name +
                        "\": очікується " +
                        types_result->value->types_string({}) + ", отримано " +
                        value_result->value->types_string({}) + ".");
        }

        this->set(assign_simple_node->name, types_result->value);

        return success(types_result->value);
      }
    }

    if (jejalyk::tools::instance_of<mavka::ast::BitwiseNode>(node)) {
      const auto bitwise_node = dynamic_cast<mavka::ast::BitwiseNode*>(node);
      // todo
      std::cout << "BitwiseNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::BitwiseNotNode>(node)) {
      const auto bitwise_not_node =
          dynamic_cast<mavka::ast::BitwiseNotNode*>(node);
      // todo
      std::cout << "BitwiseNotNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::CallNode>(node)) {
      const auto call_node = dynamic_cast<mavka::ast::CallNode*>(node);
      const auto value_result = this->compile_node(call_node->value);
      if (value_result->error) {
        return value_result;
      }
      std::vector<Subject*> generics;
      for (const auto& generic_node : call_node->generics) {
        Subject* generic_subject = nullptr;
        for (const auto type_value_node : generic_node) {
          const auto type_value_result = this->compile_node(type_value_node);
          if (type_value_result->error) {
            return type_value_result;
          }
          generic_subject = type_value_result->value;
        }
        generics.push_back(generic_subject);
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
      return value_result->value->call(generics, args, this);
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
                       "\" не визначено для " +
                       left_result->value->types_string({}) + ".");
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

    if (jejalyk::tools::instance_of<mavka::ast::ComparisonNode>(node)) {
      const auto comparison_node =
          dynamic_cast<mavka::ast::ComparisonNode*>(node);
      // todo
      std::cout << "ComparisonNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ContinueNode>(node)) {
      const auto continue_node = dynamic_cast<mavka::ast::ContinueNode*>(node);
      // todo
      std::cout << "ContinueNode" << std::endl;
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

    if (jejalyk::tools::instance_of<mavka::ast::DiiaNode>(node)) {
      const auto diia_node = dynamic_cast<mavka::ast::DiiaNode*>(node);
      return this->define_diia_from_ast(
          false, diia_node->ee, diia_node->async, diia_node->name,
          diia_node->structure, diia_node->generics, diia_node->params,
          diia_node->return_types, diia_node->body);
    }

    if (jejalyk::tools::instance_of<mavka::ast::EachNode>(node)) {
      const auto each_node = dynamic_cast<mavka::ast::EachNode*>(node);
      this->set(each_node->name, new Subject());
      if (!each_node->keyName.empty()) {
        this->set(each_node->keyName, new Subject());
      }
      // todo: handle fromto
      const auto body_result = this->compile_body(each_node->body, false);
      if (body_result->error) {
        return body_result;
      }
      return success(new Subject());
    }

    if (jejalyk::tools::instance_of<mavka::ast::EvalNode>(node)) {
      const auto eval_node = dynamic_cast<mavka::ast::EvalNode*>(node);
      // todo
      std::cout << "EvalNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::FromToComplexNode>(node)) {
      const auto from_to_complex_node =
          dynamic_cast<mavka::ast::FromToComplexNode*>(node);
      // todo
      std::cout << "FromToComplexNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::FromToSimpleNode>(node)) {
      const auto from_to_simple_node =
          dynamic_cast<mavka::ast::FromToSimpleNode*>(node);
      // todo
      std::cout << "FromToSimpleNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::FunctionNode>(node)) {
      const auto function_node = dynamic_cast<mavka::ast::FunctionNode*>(node);
      const auto diia_scope = this->make_child();
      const auto diia_subject_result = this->make_diia_from_ast(
          diia_scope, false, false, function_node->async, "", "", {},
          function_node->params, function_node->return_types);
      if (diia_subject_result->error) {
        return diia_subject_result;
      }
      this->bodies_to_compile.push_back(
          new BodyToCompile(diia_scope, function_node->body));
      return diia_subject_result;
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

    if (jejalyk::tools::instance_of<mavka::ast::GiveNode>(node)) {
      const auto give_node = dynamic_cast<mavka::ast::GiveNode*>(node);
      // todo
      std::cout << "GiveNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::GodNode>(node)) {
      const auto god_node = dynamic_cast<mavka::ast::GodNode*>(node);
      // todo
      std::cout << "GodNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::IdentifierNode>(node)) {
      const auto identifier_node =
          dynamic_cast<mavka::ast::IdentifierNode*>(node);
      Generic* generic = nullptr;
      for (auto& g : this->generics) {
        if (g->name == identifier_node->name) {
          generic = g;
          break;
        }
      }
      if (generic) {
        const auto generic_subject = new Subject();
        const auto newobj = new Object();
        newobj->generic = generic;
        generic_subject->types.push_back(newobj);
        return success(generic_subject);
      }
      if (!this->has(identifier_node->name)) {
        return error_from_ast(
            node, "Субʼєкт \"" + identifier_node->name + "\" не визначено.");
      }
      const auto subject = this->get(identifier_node->name);
      return success(subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::IfNode>(node)) {
      const auto if_node = dynamic_cast<mavka::ast::IfNode*>(node);

      const auto body_result = this->compile_body(if_node->body, false);
      if (body_result->error) {
        return body_result;
      }

      const auto else_body_result = this->compile_body(if_node->body, false);
      if (else_body_result->error) {
        return body_result;
      }

      return success(new Subject());
    }

    if (jejalyk::tools::instance_of<mavka::ast::MethodDeclarationNode>(node)) {
      const auto method_declaration_node =
          dynamic_cast<mavka::ast::MethodDeclarationNode*>(node);
      const auto diia_scope = this->make_child();
      const auto diia_subject_result = this->make_diia_from_ast(
          diia_scope, true, method_declaration_node->ee,
          method_declaration_node->async, method_declaration_node->name, "",
          method_declaration_node->generics, method_declaration_node->params,
          method_declaration_node->return_types);
      return diia_subject_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupDiiaNode>(node)) {
      const auto mockup_diia_node =
          dynamic_cast<mavka::ast::MockupDiiaNode*>(node);
      return this->define_diia_from_ast(
          false, mockup_diia_node->ee, mockup_diia_node->async,
          mockup_diia_node->name, "", mockup_diia_node->generics,
          mockup_diia_node->params, mockup_diia_node->return_types, {});
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupModuleNode>(node)) {
      const auto mockup_module_node =
          dynamic_cast<mavka::ast::MockupModuleNode*>(node);
      // todo
      std::cout << "MockupModuleNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupObjectNode>(node)) {
      const auto mockup_object_node =
          dynamic_cast<mavka::ast::MockupObjectNode*>(node);
      // todo
      std::cout << "MockupObjectNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupStructureNode>(node)) {
      const auto mockup_structure_node =
          dynamic_cast<mavka::ast::MockupStructureNode*>(node);
      return this->define_structure_from_ast(
          true, mockup_structure_node->name, mockup_structure_node->generics,
          mockup_structure_node->parent, mockup_structure_node->params);
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupSubjectNode>(node)) {
      const auto mockup_subject_node =
          dynamic_cast<mavka::ast::MockupSubjectNode*>(node);
      if (this->has_local(mockup_subject_node->name)) {
        return error_from_ast(node, "Субʼєкт \"" + mockup_subject_node->name +
                                        "\" вже визначено.");
      }
      const auto types_result =
          this->compile_types(mockup_subject_node->types,
                              "Тип субʼєкта \"" + mockup_subject_node->name +
                                  "\" не є структурою.");
      if (types_result->error) {
        return types_result;
      }
      this->set(mockup_subject_node->name, types_result->value);
      return types_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ModuleNode>(node)) {
      const auto module_node = dynamic_cast<mavka::ast::ModuleNode*>(node);
      // todo
      std::cout << "ModuleNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NegativeNode>(node)) {
      const auto negative_node = dynamic_cast<mavka::ast::NegativeNode*>(node);
      const auto value_result = this->compile_node(negative_node->value);
      if (value_result->error) {
        return value_result;
      }
      return value_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NotNode>(node)) {
      const auto not_node = dynamic_cast<mavka::ast::NotNode*>(node);
      // todo
      std::cout << "NotNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NumberNode>(node)) {
      const auto number_node = dynamic_cast<mavka::ast::NumberNode*>(node);
      const auto number_structure = this->get("число");
      const auto number = number_structure->types[0]->create_instance();
      const auto number_subject = new Subject();
      number_subject->types.push_back(number);
      return success(number_subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::PositiveNode>(node)) {
      const auto positive_node = dynamic_cast<mavka::ast::PositiveNode*>(node);
      // todo
      std::cout << "PositiveNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PostDecrementNode>(node)) {
      const auto post_decrement_node =
          dynamic_cast<mavka::ast::PostDecrementNode*>(node);
      // todo
      std::cout << "PostDecrementNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PostIncrementNode>(node)) {
      const auto post_increment_node =
          dynamic_cast<mavka::ast::PostIncrementNode*>(node);
      // todo
      std::cout << "PostIncrementNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PreDecrementNode>(node)) {
      const auto pre_decrement_node =
          dynamic_cast<mavka::ast::PreDecrementNode*>(node);
      // todo
      std::cout << "PreDecrementNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PreIncrementNode>(node)) {
      const auto pre_increment_node =
          dynamic_cast<mavka::ast::PreIncrementNode*>(node);
      // todo
      std::cout << "PreIncrementNode" << std::endl;
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
      if (!value_result->value->check_types({}, this->diia->diia_return)) {
        return error_from_ast(return_node,
                              "Невірне значення, що повертається.");
      }
      return value_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::StringNode>(node)) {
      const auto string_node = dynamic_cast<mavka::ast::StringNode*>(node);
      const auto string_structure = this->get("текст");
      const auto string = string_structure->types[0]->create_instance();
      const auto string_subject = new Subject();
      string_subject->types.push_back(string);
      return success(string_subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::StructureNode>(node)) {
      const auto structure_node =
          dynamic_cast<mavka::ast::StructureNode*>(node);
      return this->define_structure_from_ast(
          false, structure_node->name, structure_node->generics,
          structure_node->parent, structure_node->params);
    }

    if (jejalyk::tools::instance_of<mavka::ast::TakeModuleNode>(node)) {
      const auto take_module_node =
          dynamic_cast<mavka::ast::TakeModuleNode*>(node);
      // todo
      std::cout << "TakeModuleNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TakePakNode>(node)) {
      const auto take_pak_node = dynamic_cast<mavka::ast::TakePakNode*>(node);
      // todo
      std::cout << "TakePakNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TernaryNode>(node)) {
      const auto ternary_node = dynamic_cast<mavka::ast::TernaryNode*>(node);
      // todo
      std::cout << "TernaryNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TestNode>(node)) {
      const auto test_node = dynamic_cast<mavka::ast::TestNode*>(node);
      // todo
      std::cout << "TestNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ThrowNode>(node)) {
      const auto throw_node = dynamic_cast<mavka::ast::ThrowNode*>(node);
      // todo
      std::cout << "ThrowNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TryNode>(node)) {
      const auto try_node = dynamic_cast<mavka::ast::TryNode*>(node);
      // todo
      std::cout << "TryNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TypeValueSingleNode>(node)) {
      const auto type_value_single_node =
          dynamic_cast<mavka::ast::TypeValueSingleNode*>(node);
      return this->compile_node(type_value_single_node->value);
    }

    if (jejalyk::tools::instance_of<mavka::ast::WaitNode>(node)) {
      const auto wait_node = dynamic_cast<mavka::ast::WaitNode*>(node);
      // todo
      std::cout << "WaitNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::WhileNode>(node)) {
      const auto while_node = dynamic_cast<mavka::ast::WhileNode*>(node);
      // todo
      std::cout << "WhileNode" << std::endl;
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
        if (!value_result->value->check_types({}, types_result->value)) {
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

  Result* Scope::compile_types(
      const std::vector<mavka::ast::TypeValueSingleNode*>& types,
      const std::string& error_message) {
    const auto result = new Result();
    result->value = new Subject();

    for (const auto type_node : types) {
      const auto type_result = this->compile_node(type_node);
      if (type_result->error) {
        result->error = type_result->error;
        return result;
      }
      if (!type_result->value->is_structure(this)) {
        return error_from_ast(type_node, error_message);
      }
      result->value->types.push_back(
          type_result->value->types[0]->create_instance());
    }

    return result;
  }

  Result* Scope::define_module_from_ast(
      std::string name,
      std::vector<mavka::ast::ASTNode*> elements) {
    return error("false");
  }

  Result* Scope::define_structure_from_ast(
      bool mockup,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generics,
      mavka::ast::ASTNode* parent,
      std::vector<mavka::ast::ASTNode*> params) {
    Object* structure_object;
    Subject* structure_subject;

    bool redefine = false;

    if (this->has(name)) {
      structure_subject = this->get(name);
      if (!structure_subject->is_structure(this)) {
        return error("Субʼєкт \"" + name + "\" вже визначено.");
      }
      structure_object = structure_subject->types[0];
      redefine = true;
    } else {
      const auto structure_structure_subject = this->get("Структура");

      structure_object = new Object();
      structure_object->structure_name = name;
      structure_object->structure = structure_structure_subject->types[0];

      const auto object_structure_subject = this->get("обʼєкт");
      structure_object->structure_parent = object_structure_subject->types[0];

      structure_subject = new Subject();
      structure_subject->types.push_back(structure_object);

      this->set(name, structure_subject);
    }

    if (!redefine) {
      for (int i = 0; i < generics.size(); ++i) {
        const auto generic_node = generics[i];
        const auto generic = new Generic();
        generic->index = i;
        generic->name = generic_node->name;
        structure_object->structure_generics.push_back(generic);
      }
    }

    std::vector<mavka::ast::ParamNode*> only_params;
    for (const auto param : params) {
      if (jejalyk::tools::instance_of<mavka::ast::ParamNode>(param)) {
        const auto param_param = dynamic_cast<mavka::ast::ParamNode*>(param);
        // todo: check if param already defined
        if (param_param->ee) {
          if (!mockup && !param_param->value) {
            return error_from_ast(param_param, "Її властивість \"" +
                                                   param_param->name +
                                                   "\" повинна мати значення.");
          }
          const auto param_scope = this->make_child();
          param_scope->micro = true;
          param_scope->generics = structure_object->structure_generics;
          const auto param_param_types_result = param_scope->compile_types(
              param_param->types, "Тип властивості \"" + param_param->name +
                                      "\" повинен бути структурою.");
          if (param_param_types_result->error) {
            return param_param_types_result;
          }
          structure_object->properties.insert_or_assign(
              param_param->name, param_param_types_result->value);
        } else {
          only_params.push_back(dynamic_cast<mavka::ast::ParamNode*>(param));
        }
      } else if (jejalyk::tools::instance_of<mavka::ast::MethodDeclarationNode>(
                     param)) {
        const auto method_declaration_node =
            dynamic_cast<mavka::ast::MethodDeclarationNode*>(param);

        if (method_declaration_node->ee) {
          const auto method_declaration_result =
              this->compile_node(method_declaration_node);
          if (method_declaration_result->error) {
            return method_declaration_result;
          }

          structure_object->properties.insert_or_assign(
              method_declaration_node->name, method_declaration_result->value);
        } else {
          if (structure_object->structure_methods.contains(
                  method_declaration_node->name)) {
            return error("Дію \"" + method_declaration_node->name +
                         "\" вже визначено для структури \"" + name + "\".");
          }
          const auto method_scope = this->make_child();
          method_scope->micro = true;
          method_scope->generics = structure_object->structure_generics;
          const auto method_declaration_result =
              method_scope->compile_node(method_declaration_node);
          if (method_declaration_result->error) {
            return method_declaration_result;
          }
          structure_object->structure_methods.insert_or_assign(
              method_declaration_node->name, method_declaration_result->value);
        }
      }
    }
    const auto params_scope = this->make_child();
    params_scope->micro = true;
    params_scope->generics = structure_object->structure_generics;
    const auto params_result = params_scope->compile_params(only_params);
    if (params_result->error) {
      return new Result(params_result->error);
    }

    if (parent) {
      const auto parent_result = this->compile_node(parent);
      if (parent_result->error) {
        return parent_result;
      }
      if (!parent_result->value->is_structure(this)) {
        return error_from_ast(parent,
                              "Батьківський тип повинен бути структурою.");
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
        if (inner_diia_node->structure == name) {
          const auto compiled_inner_node = this->compile_node(inner_node);
          if (compiled_inner_node->error) {
            return compiled_inner_node;
          }
          this->body->at(i) = nullptr;
        }
      }
    }

    if (structure_object->structure_methods.contains("чародія_створити")) {
      structure_object->properties.insert_or_assign(
          "чародія_викликати",
          structure_object->structure_methods["чародія_створити"]);
    } else {
      const auto constructor_diia = new Object();
      const auto diia_structure_subject = this->get("Дія");
      constructor_diia->structure = diia_structure_subject->types[0];
      constructor_diia->diia_generics = structure_object->structure_generics;
      constructor_diia->diia_params = structure_object->structure_params;
      const auto structure_type_subject = new Subject();
      structure_type_subject->types.push_back(
          structure_object->create_instance());
      constructor_diia->diia_return = structure_type_subject;
      const auto constructor_diia_subject = new Subject();
      constructor_diia_subject->types.push_back(constructor_diia);
      structure_object->properties.insert_or_assign("чародія_викликати",
                                                    constructor_diia_subject);
    }

    return success(structure_subject);
  }

  Result* Scope::define_diia_from_ast(
      bool declaration,
      bool ee,
      bool async,
      const std::string& name,
      const std::string& structure,
      const std::vector<mavka::ast::GenericNode*>& generics,
      const std::vector<mavka::ast::ParamNode*>& params,
      const std::vector<mavka::ast::TypeValueSingleNode*>& return_types,
      std::vector<mavka::ast::ASTNode*> body) {
    const auto diia_scope = this->make_child();
    diia_scope->body = &body;

    const auto diia_subject_result =
        this->make_diia_from_ast(diia_scope, declaration, ee, async, name,
                                 structure, generics, params, return_types);
    if (diia_subject_result->error) {
      return diia_subject_result;
    }

    this->bodies_to_compile.push_back(new BodyToCompile(diia_scope, body));

    return diia_subject_result;
  }

  Result* Scope::compile_body(std::vector<mavka::ast::ASTNode*> body,
                              bool with_bodies_to_compile) {
    const auto result = new Result();

    for (int i = 0; i < body.size(); ++i) {
      const auto node = body[i];
      if (!node) {
        continue;
      }

      const auto compiled_node = this->compile_node(node);
      if (compiled_node->error) {
        return compiled_node;
      }
    }

    if (with_bodies_to_compile) {
      for (int i = 0; i < this->bodies_to_compile.size(); ++i) {
        const auto body_to_compile = this->bodies_to_compile[i];

        const auto compilation_result =
            body_to_compile->scope->compile_body(body_to_compile->body, true);
        if (compilation_result->error) {
          return compilation_result;
        }
      }
    }

    return result;
  }

  Scope* Scope::make_child() {
    const auto child = new Scope();
    child->parent = this;
    child->generics = this->generics;
    return child;
  }
}