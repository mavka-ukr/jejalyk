#include "typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Scope* Scope::make_child() {
    const auto child = new Scope();
    child->parent = this;
    child->proxy = false;
    return child;
  }

  Scope* Scope::make_proxy() {
    const auto child = new Scope();
    child->parent = this;
    child->proxy = true;
    return child;
  }

  Scope* Scope::get_root() {
    if (this->parent) {
      return this->parent->get_root();
    }
    return this;
  }

  Subject* Scope::get_from_root(std::string name) {
    return this->get_root()->get(name);
  }

  Object* Scope::get_diia_object() {
    if (this->diia_object) {
      return this->diia_object;
    }
    if (this->proxy) {
      return this->parent->get_diia_object();
    }
    return nullptr;
  }

  Object* Scope::get_module_object() {
    if (this->module_object) {
      return this->module_object;
    }
    if (this->proxy) {
      return this->parent->get_module_object();
    }
    return nullptr;
  }

  Subject* Scope::get_root_object() {
    return this->get_from_root("обʼєкт");
  }

  Subject* Scope::get_root_structure() {
    return this->get_from_root("Структура");
  }

  Subject* Scope::get_root_empty() {
    return this->get_from_root("пусто");
  }

  Subject* Scope::get_root_diia() {
    return this->get_from_root("Дія");
  }

  Subject* Scope::get_root_number() {
    return this->get_from_root("число");
  }

  Subject* Scope::get_root_text() {
    return this->get_from_root("текст");
  }

  Subject* Scope::get_root_logical() {
    return this->get_from_root("логічне");
  }

  Subject* Scope::get_root_list() {
    return this->get_from_root("список");
  }

  Subject* Scope::get_root_dictionary() {
    return this->get_from_root("словник");
  }

  Subject* Scope::get_root_iterator() {
    return this->get_from_root("перебір");
  }

  Subject* Scope::get_root_iterator_with_key() {
    return this->get_from_root("перебір_з_ключем");
  }

  Subject* Scope::get_root_awaiting() {
    return this->get_from_root("очікування");
  }

  bool Scope::get_is_loop() {
    if (this->is_loop) {
      return true;
    }
    // if (this->proxy) {
    //   return this->parent->get_is_loop();
    // }
    return false;
  }

  bool Scope::get_is_async() {
    if (this->is_async) {
      return true;
    }
    if (this->proxy) {
      return this->parent->get_is_async();
    }
    return false;
  }

  size_t Scope::get_iterator_count() {
    if (this->parent) {
      return this->parent->get_iterator_count();
    }
    return this->iterator_count;
  }

  void Scope::increment_iterator_count() {
    if (this->parent) {
      this->parent->increment_iterator_count();
    } else {
      this->iterator_count++;
    }
  }

  Options* Scope::get_options() const {
    if (this->options) {
      return this->options;
    }
    if (this->parent) {
      return this->parent->get_options();
    }
    return nullptr;
  }

  std::vector<std::string> Scope::get_ignored_variables() {
    if (this->proxy) {
      return this->parent->get_ignored_variables();
    }
    return this->ignored_variables;
  }

  void Scope::put_ignore_variable(std::string name) {
    if (this->proxy) {
      this->parent->put_ignore_variable(name);
    } else {
      this->ignored_variables.push_back(name);
    }
  }

  Scope* Scope::get_parent() {
    if (this->proxy) {
      return this->parent->get_parent();
    }
    if (this->parent) {
      return this->parent;
    }
    return this;
  }

  void Scope::put_setter(std::string name) {
    if (this->proxy) {
      this->parent->put_setter(name);
    } else {
      this->setters.push_back(name);
    }
  }

  std::vector<std::string> Scope::get_setters() {
    if (this->proxy) {
      return this->parent->get_setters();
    }
    return this->setters;
  }

  void Scope::put_additional_node_before(jejalyk::js::JsNode* node) {
    if (this->proxy) {
      this->parent->put_additional_node_before(node);
    } else {
      this->additional_nodes_before.push_back(node);
    }
  }

  std::vector<jejalyk::js::JsNode*> Scope::get_additional_nodes_before() {
    return this->additional_nodes_before;
  }

  void Scope::put_additional_variable(std::string name) {
    if (this->proxy) {
      this->parent->put_additional_variable(name);
    } else {
      for (const auto& additional_variable : this->additional_variables) {
        if (additional_variable == name) {
          return;
        }
      }
      this->additional_variables.push_back(name);
    }
  }

  std::vector<std::string> Scope::get_additional_variables() {
    return this->additional_variables;
  }

  Subject* Scope::create_object_instance_subject() {
    const auto object_structure_subject = this->get_root_object();
    const auto object_instance_subject =
        object_structure_subject->create_instance(this, {});
    if (object_instance_subject->error) {
      debug_print_bug(object_instance_subject->error->message);
      return nullptr;
    }
    return object_instance_subject->value;
  }

  Type* Scope::create_object_instance_type() {
    return this->create_object_instance_subject()->types[0];
  }

  Object* Scope::create_object_instance_object() {
    return this->create_object_instance_subject()->types[0]->object;
  }

  Subject* Scope::get(std::string name) {
    if (this->has_local(name)) {
      return this->get_local(name);
    }
    if (this->parent) {
      return this->parent->get(name);
    }
    std::cout << "[BUG] Scope::get() called for non-existing variable '" << name
              << "'" << std::endl;
    return nullptr;
  }

  Subject* Scope::get_local(std::string name) {
    if (this->variables.contains(name)) {
      return this->variables.find(name)->second;
    }
    if (this->proxy) {
      return this->parent->get_local(name);
    }
    std::cout << "[BUG] Scope::get_local() called for non-existing variable '"
              << name << "'" << std::endl;
    return nullptr;
  }

  void Scope::set_local(std::string name, Subject* value) {
    if (this->proxy) {
      this->parent->set_local(name, value);
    } else {
      this->variables.insert_or_assign(name, value);
    }
  }

  bool Scope::has(std::string name) {
    if (this->has_local(name)) {
      return true;
    }
    if (this->parent) {
      return this->parent->has(name);
    }
    return false;
  }

  bool Scope::has_local(std::string name) {
    if (this->variables.contains(name)) {
      return true;
    }
    if (this->proxy) {
      return this->parent->has_local(name);
    }
    return false;
  }

  void Scope::delete_local(std::string name) {
    if (this->proxy) {
      return this->parent->delete_local(name);
    } else {
      this->variables.erase(name);
    }
  }

  bool Scope::check_subjects(Subject* value, Subject* types) {
    debug_print_check_subjects(value, types);

    for (const auto value_type : value->types) {
      bool type_found = false;

      for (const auto types_type : types->types) {
        if (this->check_type(value->is_empty_value, value_type, types_type)) {
          type_found = true;
          break;
        }
      }

      if (!type_found) {
        return false;
      }
    }

    value->is_empty_value = false;

    return true;
  }

  bool Scope::check_type(bool is_empty_value, Type* value, Type* type) {
    const auto root_object_subject = this->get_root_object();
    const auto root_array_subject = this->get_root_list();
    if (type->object->structure->object ==
        root_object_subject->types[0]->object) {
      return true;
    }
    if (value->generic_definition) {
      if (value->generic_definition == type->generic_definition) {
        return true;
      }
      return false;
    }
    if (type->generic_definition) {
      return false;
    }
    if (is_empty_value) {
      if (value->is_array(this)) {
        if (value->generic_types[0]->is_object(this)) {
          if (type->is_array(this)) {
            return true;
          }
        }
      }
      if (value->is_dictionary(this)) {
        if (value->generic_types[0]->is_object(this) &&
            value->generic_types[1]->is_object(this)) {
          if (type->is_dictionary(this)) {
            return true;
          }
        }
      }
    }
    if (value->object->structure == type->object->structure) {
      if (value->generic_types.size() != type->generic_types.size()) {
        return false;
      }

      for (int i = 0; i < type->generic_types.size(); ++i) {
        const auto valid_types_type_generic = type->generic_types[i];
        const auto valid_value_type_generic = value->generic_types[i];

        if (!this->check_subjects(valid_value_type_generic,
                                  valid_types_type_generic)) {
          return false;
        }
      }

      return true;
    }

    if (value->generic_types.empty() && type->generic_types.empty()) {
      auto structure = value->object->structure;

      while (structure) {
        if (structure == type->object->structure) {
          return true;
        }

        structure = structure->object->parent;
      }
    }

    return false;
  }

  bool Scope::assign(std::string name, Subject* value) {
    if (this->has_local(name)) {
      return value->check(this->get_local(name));
    }
    this->set_local(name, value);
    return true;
  }

  Result* Scope::compile_types(
      std::vector<mavka::ast::TypeValueSingleNode*> types) {
    std::vector<mavka::ast::ASTSome*> nodes;
    for (const auto type : types) {
      nodes.push_back(mavka::ast::make_ast_some(type));
    }
    const auto compiled_nodes = this->compile_nodes(nodes);
    if (compiled_nodes->error) {
      return compiled_nodes;
    }
    if (nodes.empty()) {
      compiled_nodes->js_body->nodes.push_back(jejalyk::js::id("обʼєкт"));
      return success(this->create_object_instance_subject(),
                     compiled_nodes->js_body);
    }
    return success(compiled_nodes->value, compiled_nodes->js_body);
  }

  Result* Scope::compile_nodes(std::vector<mavka::ast::ASTSome*> nodes) {
    const auto subject = new Subject();
    const auto js_body = new jejalyk::js::JsBody();
    for (const auto node : nodes) {
      if (node == nullptr) {
        continue;
      }
      const auto node_result = this->compile_node(node);
      if (node_result->error) {
        return node_result;
      }
      js_body->nodes.push_back(node_result->js_node);
      for (const auto type : node_result->value->types) {
        subject->add_type(type);
      }
    }
    if (subject->types.empty()) {
      subject->add_type(this->create_object_instance_type());
    }
    return success(subject, js_body);
  }

  Result* Scope::compile_node(mavka::ast::ASTSome* node) {
    if (!node) {
      return error(nullptr, "null node");
    }
    if (node->is_nullptr()) {
      return error(nullptr, "nullptr node");
    }

    if (node->AnonDiiaNode) {
      return compile_anon_diia_node(this, node->AnonDiiaNode);
    }

    if (node->ArithmeticNode) {
      return compile_arithmetic_node(this, node->ArithmeticNode);
    }

    if (node->ArrayNode) {
      return compile_array_node(this, node->ArrayNode);
    }

    if (node->AsNode) {
      return compile_as_node(this, node->AsNode);
    }

    if (node->AssignByElementNode) {
      return compile_assign_by_element_node(this, node->AssignByElementNode);
    }

    if (node->AssignByIdentifierNode) {
      return compile_assign_by_identifier_node(this,
                                               node->AssignByIdentifierNode);
    }

    if (node->AssignSimpleNode) {
      return compile_assign_simple_node(this, node->AssignSimpleNode);
    }

    if (node->BitwiseNode) {
      return compile_bitwise_node(this, node->BitwiseNode);
    }

    if (node->BitwiseNotNode) {
      return compile_bitwise_not_node(this, node->BitwiseNotNode);
    }

    if (node->BreakNode) {
      return compile_break_node(this, node->BreakNode);
    }

    if (node->CallNode) {
      return compile_call_node(this, node->CallNode);
    }

    if (node->ChainNode) {
      return compile_chain_node(this, node->ChainNode);
    }

    if (node->ComparisonNode) {
      return compile_comparison_node(this, node->ComparisonNode);
    }

    if (node->ContinueNode) {
      return compile_continue_node(this, node->ContinueNode);
    }

    if (node->DictionaryNode) {
      return compile_dictionary_node(this, node->DictionaryNode);
    }

    if (node->DiiaNode) {
      return compile_diia_node(this, node->DiiaNode);
    }

    if (node->EachNode) {
      return compile_each_node(this, node->EachNode);
    }

    if (node->EvalNode) {
      return compile_eval_node(this, node->EvalNode);
    }

    if (node->FromToComplexNode) {
      return compile_from_to_complex_node(this, node->FromToComplexNode);
    }

    if (node->FromToSimpleNode) {
      return compile_from_to_simple_node(this, node->FromToSimpleNode);
    }

    if (node->FunctionNode) {
      return compile_function_node(this, node->FunctionNode);
    }

    if (node->GetElementNode) {
      return compile_get_element_node(this, node->GetElementNode);
    }

    if (node->GiveNode) {
      return compile_give_node(this, node->GiveNode);
    }

    if (node->GodNode) {
      return compile_god_node(this, node->GodNode);
    }

    if (node->IdentifierNode) {
      return compile_identifier_node(this, node->IdentifierNode);
    }

    if (node->IfNode) {
      return compile_if_node(this, node->IfNode);
    }

    if (node->MethodDeclarationNode) {
      return compile_method_declaration_node(this, node->MethodDeclarationNode);
    }

    if (node->MMLNode) {
      return compile_mml_node(this, node->MMLNode);
    }

    if (node->MockupDiiaNode) {
      return compile_mockup_diia_node(this, node->MockupDiiaNode);
    }

    if (node->MockupModuleNode) {
      return compile_mockup_module_node(this, node->MockupModuleNode);
    }

    if (node->MockupStructureNode) {
      return compile_mockup_structure_node(this, node->MockupStructureNode);
    }

    if (node->MockupSubjectNode) {
      return compile_mockup_subject_node(this, node->MockupSubjectNode);
    }

    if (node->ModuleNode) {
      return compile_module_node(this, node->ModuleNode);
    }

    if (node->NegativeNode) {
      return compile_negative_node(this, node->NegativeNode);
    }

    if (node->NotNode) {
      return compile_not_node(this, node->NotNode);
    }

    if (node->NumberNode) {
      return compile_number_node(this, node->NumberNode);
    }

    if (node->PositiveNode) {
      return compile_positive_node(this, node->PositiveNode);
    }

    if (node->PostDecrementNode) {
      return compile_post_decrement_node(this, node->PostDecrementNode);
    }

    if (node->PostIncrementNode) {
      return compile_post_increment_node(this, node->PostIncrementNode);
    }

    if (node->PreDecrementNode) {
      return compile_pre_decrement_node(this, node->PreDecrementNode);
    }

    if (node->PreIncrementNode) {
      return compile_pre_increment_node(this, node->PreIncrementNode);
    }

    if (node->ReturnNode) {
      return compile_return_node(this, node->ReturnNode);
    }

    if (node->StringNode) {
      return compile_string_node(this, node->StringNode);
    }

    if (node->StructureNode) {
      return compile_structure_node(this, node->StructureNode);
    }

    if (node->TakeModuleNode) {
      return compile_take_module_node(this, node->TakeModuleNode);
    }

    if (node->TakePakNode) {
      return compile_take_pak_node(this, node->TakePakNode);
    }

    if (node->TernaryNode) {
      return compile_ternary_node(this, node->TernaryNode);
    }

    if (node->TestNode) {
      return compile_test_node(this, node->TestNode);
    }

    if (node->ThrowNode) {
      return compile_throw_node(this, node->ThrowNode);
    }

    if (node->TryNode) {
      return compile_try_node(this, node->TryNode);
    }

    if (node->TypeValueSingleNode) {
      return compile_type_value_single_node(this, node->TypeValueSingleNode);
    }

    if (node->WaitNode) {
      return compile_wait_node(this, node->WaitNode);
    }

    if (node->WhileNode) {
      return compile_while_node(this, node->WhileNode);
    }

    return this->error(mavka::ast::get_ast_node(node), "unsupported node");
  }

  Result* Scope::compile_body(const std::vector<mavka::ast::ASTSome*>& body) {
    const auto result = new Result();
    result->js_body = new jejalyk::js::JsBody();

    std::vector<mavka::ast::ASTSome*> processed_body;

    for (const auto node : body) {
      if (!node) {
        continue;
      }
      if (node->is_nullptr()) {
        continue;
      }

      if (node->CompInstAssignNode) {
      } else if (node->CompInstBlockProgramNode) {
        if (node->CompInstBlockProgramNode->name == "строгість") {
          if (node->CompInstBlockProgramNode->value ==
              this->get_options()->arg_strictness) {
            for (const auto comp_inst_block_program_node_body_node :
                 node->CompInstBlockProgramNode->body) {
              processed_body.push_back(comp_inst_block_program_node_body_node);
            }
          }
        } else {
          return this->error(mavka::ast::get_ast_node(node),
                             "Невідомий компіляторний інструкційний блок \"" +
                                 node->CompInstBlockProgramNode->name + "\".");
        }
      } else {
        processed_body.push_back(node);
      }
    }

    for (const auto node : processed_body) {
      if (!node) {
        continue;
      }
      if (node->is_nullptr()) {
        continue;
      }

      if (const auto mockup_structure_node = node->MockupStructureNode) {
        if (this->has_local(mockup_structure_node->name) ||
            this->get_root()->has_local(mockup_structure_node->name)) {
          return this->error(
              node->MockupStructureNode,
              "Субʼєкт \"" + mockup_structure_node->name + "\" вже визначено.");
        }
        const auto structure_declaration_result = declare_structure(
            this, mockup_structure_node, mockup_structure_node->name,
            mockup_structure_node->generics, mockup_structure_node->parent,
            mockup_structure_node->parent_generics);
        if (structure_declaration_result->error) {
          return structure_declaration_result;
        }
        this->set_local(mockup_structure_node->name,
                        structure_declaration_result->value);
        this->put_ignore_variable(mockup_structure_node->name);
      }

      if (const auto structure_node = node->StructureNode) {
        if (this->has_local(structure_node->name) ||
            this->get_root()->has_local(structure_node->name)) {
          return this->error(
              node->StructureNode,
              "Субʼєкт \"" + structure_node->name + "\" вже визначено.");
        }
        const auto structure_declaration_result =
            declare_structure(this, structure_node, structure_node->name,
                              structure_node->generics, structure_node->parent,
                              structure_node->parent_generics);
        if (structure_declaration_result->error) {
          return structure_declaration_result;
        }
        this->set_local(structure_node->name,
                        structure_declaration_result->value);
      }
    }

    for (const auto node : processed_body) {
      if (!node) {
        continue;
      }
      if (node->is_nullptr()) {
        continue;
      }

      bool is_diia = false;
      bool is_mockup = false;
      bool diia_async = false;
      std::string diia_structure;
      std::string diia_name;
      std::vector<mavka::ast::GenericNode*> diia_generics;
      std::vector<mavka::ast::ParamNode*> diia_params;
      std::vector<mavka::ast::TypeValueSingleNode*> diia_return_types;

      if (const auto mockup_diia_node = node->MockupDiiaNode) {
        is_diia = true;
        is_mockup = true;
        diia_async = mockup_diia_node->async;
        diia_structure = mockup_diia_node->structure;
        diia_name = mockup_diia_node->name;
        diia_generics = mockup_diia_node->generics;
        diia_params = mockup_diia_node->params;
        diia_return_types = mockup_diia_node->return_types;
      }

      if (const auto diia_node = node->DiiaNode) {
        is_diia = true;
        diia_async = diia_node->async;
        diia_structure = diia_node->structure;
        diia_name = diia_node->name;
        diia_generics = diia_node->generics;
        diia_params = diia_node->params;
        diia_return_types = diia_node->return_types;
      }

      if (is_diia) {
        if (diia_structure.empty()) {
          if (this->has_local(diia_name) ||
              this->get_root()->has_local(diia_name)) {
            return this->error(mavka::ast::get_ast_node(node),
                               "Субʼєкт \"" + diia_name + "\" вже визначено.");
          }
          const auto scope = this->make_child();
          const auto diia_declaration_result = declare_diia(
              this, scope, mavka::ast::get_ast_node(node), diia_async,
              diia_name, diia_generics, diia_params, diia_return_types);
          if (diia_declaration_result->error) {
            return diia_declaration_result;
          }
          this->set_local(diia_name, diia_declaration_result->value);
          if (is_mockup) {
            this->put_ignore_variable(diia_name);
          }
        } else {
          if (this->has_local(diia_structure)) {
            const auto structure_subject = this->get_local(diia_structure);
            if (!structure_subject->is_structure(this)) {
              return this->error(
                  mavka::ast::get_ast_node(node),
                  "Субʼєкт \"" + diia_structure + "\" не є структурою.");
            }

            const auto structure_type = structure_subject->types[0];
            const auto structure_object = structure_type->object;

            if (structure_object->properties.contains(diia_name)) {
              return this->error(mavka::ast::get_ast_node(node),
                                 "Властивість \"" + diia_name +
                                     "\" вже визначено в структурі \"" +
                                     diia_structure + "\".");
            }

            if (structure_object->methods.contains(diia_name)) {
              return this->error(mavka::ast::get_ast_node(node),
                                 "Метод \"" + diia_name +
                                     "\" вже визначено в структурі \"" +
                                     diia_structure + "\".");
            }

            const auto diia_scope = this->make_child();
            for (const auto structure_generic_definition :
                 structure_object->generic_definitions) {
              diia_scope->variables.insert_or_assign(
                  structure_generic_definition->name,
                  Subject::create(structure_generic_definition));
            }
            const auto diia_declaration_result = declare_diia(
                this, diia_scope, mavka::ast::get_ast_node(node), diia_async,
                diia_name, diia_generics, diia_params, diia_return_types);
            if (diia_declaration_result->error) {
              return diia_declaration_result;
            }

            structure_object->methods.insert_or_assign(
                diia_name, diia_declaration_result->value->types[0]);
          } else {
            return this->error(
                mavka::ast::get_ast_node(node),
                "Субʼєкт \"" + diia_structure + "\" не визначено.");
          }
        }
      }
    }

    for (const auto node : processed_body) {
      if (!node) {
        continue;
      }
      if (node->is_nullptr()) {
        continue;
      }

      const auto compiled_node_result = this->compile_node(node);
      if (compiled_node_result->error) {
        return compiled_node_result;
      }

      result->js_body->nodes.push_back(compiled_node_result->js_node);
    }

    for (const auto post_body_compilation : this->post_bodies_compilation) {
      const auto body_result = post_body_compilation->scope->compile_body(
          *post_body_compilation->body);
      if (body_result->error) {
        return body_result;
      }
      post_body_compilation->js_body->nodes.insert(
          post_body_compilation->js_body->nodes.end(),
          body_result->js_body->nodes.begin(),
          body_result->js_body->nodes.end());
    }

    std::vector<std::string> var_names;
    if (!this->proxy) {
      const auto diia_object = this->get_diia_object();

      for (const auto& setter : this->setters) {
        const auto js_function = new js::JsFunctionNode();
        js_function->async = false;
        js_function->name = "мs" + setter;
        js_function->params.push_back(js::make_id("мv"));
        js_function->body = new js::JsBody();
        js_function->body->nodes.push_back(
            js::make_assign(js::make_id(setter), js::make_id("мv")));
        result->js_body->nodes.insert(result->js_body->nodes.begin(),
                                      js_function);
      }

      for (const auto& [variable_name, variable_subject] : this->variables) {
        bool ignored = false;
        if (diia_object) {
          for (const auto& param : diia_object->params) {
            if (param->name == variable_name) {
              ignored = true;
              break;
            }
          }
        }
        for (const auto& ignored_variable : this->get_ignored_variables()) {
          if (ignored_variable == variable_name) {
            ignored = true;
            break;
          }
        }
        if (ignored) {
          continue;
        }

        var_names.push_back("м_" + variable_name);
      }
      for (const auto js_node_before : this->get_additional_nodes_before()) {
        result->js_body->nodes.insert(result->js_body->nodes.begin(),
                                      js_node_before);
      }
      for (const auto& additional_variable : this->get_additional_variables()) {
        bool ignored = false;
        for (const auto& ignored_variable : this->get_ignored_variables()) {
          if (ignored_variable == additional_variable) {
            ignored = true;
            break;
          }
        }
        if (ignored) {
          continue;
        }
        result->js_body->nodes.insert(result->js_body->nodes.begin(),
                                      js::make_var("м_" + additional_variable));
      }
      if (!var_names.empty()) {
        result->js_body->nodes.insert(result->js_body->nodes.begin(),
                                      jejalyk::js::vars(var_names));
      }
    }

    return result;
  }

  Result* Scope::compile_module(std::string name,
                                std::vector<mavka::ast::ASTSome*>* body,
                                std::string path,
                                std::vector<js::JsNode*> before) {
    Subject* module_subject = nullptr;
    Type* module_type = nullptr;
    Object* module_object = nullptr;

    const auto module_structure_subject = this->get_root()->get("Модуль");

    module_object = new Object();
    module_object->structure = module_structure_subject->types[0];
    module_object->name = name;

    module_type = new Type();
    module_type->object = module_object;

    module_subject = new Subject();
    module_subject->add_type(module_type);

    const auto module_scope = this->make_child();

    const auto js_function = new js::JsFunctionNode();
    js_function->name = name;
    js_function->async = true;
    js_function->params.push_back(js::make_id("мmodule"));

    if (!path.empty()) {
      // var м____шлях_до_модуля___
      js_function->body->nodes.push_back(js::var("м____шлях_до_модуля___"));
      // м____шлях_до_модуля___ = "..."
      js_function->body->nodes.push_back(js::make_assign(
          js::make_id("м____шлях_до_модуля___"), js::make_string(path)));
    }

    if (body != nullptr) {
      module_scope->module_object = module_object;
      module_scope->is_async = true;

      const auto compiled_body = module_scope->compile_body(*body);
      if (compiled_body->error) {
        return compiled_body;
      }

      js_function->body = compiled_body->js_body;
    }

    for (const auto before_js_node : before) {
      js_function->body->nodes.insert(js_function->body->nodes.begin(),
                                      before_js_node);
    }

    const auto js_call = js::make_call(js::make_id(JJ_F_MODULE), {js_function});

    return success(module_subject, js::make_await(js_call));
  }

  Result* Scope::error(mavka::ast::ASTNode* node,
                       const std::string& message) const {
    const auto result = new Result();
    const auto error = new Error();
    error->path = this->get_options()->current_module_path;
    if (node) {
      error->line = node->start_line;
      error->column = node->start_column;
    }
    error->message = message;
    result->error = error;
    return result;
  }
} // namespace typeinterpreter