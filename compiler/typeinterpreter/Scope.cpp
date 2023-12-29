#include "typeinterpreter.h"

namespace typeinterpreter {
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

  void Scope::put_additional_node_before(jejalyk::js::JsNode* node) {
    if (this->proxy) {
      this->parent->put_additional_node_before(node);
    } else {
      this->additional_nodes_before.push_back(node);
    }
  }

  std::vector<jejalyk::js::JsNode*> Scope::get_additional_nodes_before() {
    if (this->proxy) {
      return this->parent->get_additional_nodes_before();
    }
    return this->additional_nodes_before;
  }

  Subject* Scope::create_object_instance_subject() {
    const auto object_structure_subject = this->get_root()->get("обʼєкт");
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
      if (this->parent) {
        this->parent->set_local(name, value);
      } else {
        std::cout << "[BUG] Scope::set() called for proxy without parent '"
                  << name << "'" << std::endl;
      }
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
    this->variables.erase(name);
    if (this->proxy) {
      return this->parent->delete_local(name);
    }
  }

  bool Scope::check_subjects(Subject* value, Subject* types) {
    debug_print_check_subjects(value, types);

    for (const auto value_type : value->types) {
      bool type_found = false;

      for (const auto types_type : types->types) {
        if (this->check_type(value_type, types_type)) {
          type_found = true;
          break;
        }
      }

      if (!type_found) {
        return false;
      }
    }

    return true;
  }

  bool Scope::check_type(Type* value, Type* type) {
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
    std::vector<mavka::ast::ASTNode*> nodes;
    for (const auto type : types) {
      nodes.push_back(type);
    }
    const auto compiled_nodes = this->compile_nodes(nodes);
    if (compiled_nodes->error) {
      return compiled_nodes;
    }
    if (nodes.empty()) {
      const auto object_structure = this->get_root()->get("обʼєкт");
      const auto object_instance_subject =
          object_structure->create_instance(this, {});
      compiled_nodes->js_body->nodes.push_back(jejalyk::js::id("обʼєкт"));
      return success(object_instance_subject->value, compiled_nodes->js_body);
    }
    return success(compiled_nodes->value, compiled_nodes->js_body);
  }

  Result* Scope::compile_nodes(std::vector<mavka::ast::ASTNode*> nodes) {
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
      const auto object_structure_subject = this->get_root()->get("обʼєкт");
      const auto object_instance_subject =
          object_structure_subject->create_instance(this, {});
      if (object_instance_subject->error) {
        return object_instance_subject;
      }
      subject->add_type(object_instance_subject->value->types[0]);
    }
    return success(subject, js_body);
  }

  Result* Scope::compile_node(mavka::ast::ASTNode* node) {
    if (!node) {
      return error("empty node");
    }

    if (const auto anon_diia_node =
            dynamic_cast<mavka::ast::AnonDiiaNode*>(node)) {
      return compile_anon_diia_node(this, anon_diia_node);
    }

    if (const auto arithmetic_node =
            dynamic_cast<mavka::ast::ArithmeticNode*>(node)) {
      return compile_arithmetic_node(this, arithmetic_node);
    }

    if (const auto array_node = dynamic_cast<mavka::ast::ArrayNode*>(node)) {
      return compile_array_node(this, array_node);
    }

    if (const auto as_node = dynamic_cast<mavka::ast::AsNode*>(node)) {
      return compile_as_node(this, as_node);
    }

    if (const auto assign_by_element_node =
            dynamic_cast<mavka::ast::AssignByElementNode*>(node)) {
      return compile_assign_by_element_node(this, assign_by_element_node);
    }

    if (const auto assign_by_identifier_node =
            dynamic_cast<mavka::ast::AssignByIdentifierNode*>(node)) {
      return compile_assign_by_identifier_node(this, assign_by_identifier_node);
    }

    if (const auto assign_simple_node =
            dynamic_cast<mavka::ast::AssignSimpleNode*>(node)) {
      return compile_assign_simple_node(this, assign_simple_node);
    }

    if (const auto bitwise_node =
            dynamic_cast<mavka::ast::BitwiseNode*>(node)) {
      return compile_bitwise_node(this, bitwise_node);
    }

    if (const auto bitwise_not_node =
            dynamic_cast<mavka::ast::BitwiseNotNode*>(node)) {
      return compile_bitwise_not_node(this, bitwise_not_node);
    }

    if (const auto break_node = dynamic_cast<mavka::ast::BreakNode*>(node)) {
      return compile_break_node(this, break_node);
    }

    if (const auto call_node = dynamic_cast<mavka::ast::CallNode*>(node)) {
      return compile_call_node(this, call_node);
    }

    if (const auto chain_node = dynamic_cast<mavka::ast::ChainNode*>(node)) {
      return compile_chain_node(this, chain_node);
    }

    if (const auto comparison_node =
            dynamic_cast<mavka::ast::ComparisonNode*>(node)) {
      return compile_comparison_node(this, comparison_node);
    }

    if (const auto continue_node =
            dynamic_cast<mavka::ast::ContinueNode*>(node)) {
      return compile_continue_node(this, continue_node);
    }

    if (const auto dictionary_node =
            dynamic_cast<mavka::ast::DictionaryNode*>(node)) {
      return compile_dictionary_node(this, dictionary_node);
    }

    if (const auto diia_node = dynamic_cast<mavka::ast::DiiaNode*>(node)) {
      return compile_diia_node(this, diia_node);
    }

    if (const auto each_node = dynamic_cast<mavka::ast::EachNode*>(node)) {
      return compile_each_node(this, each_node);
    }

    if (const auto eval_node = dynamic_cast<mavka::ast::EvalNode*>(node)) {
      return compile_eval_node(this, eval_node);
    }

    if (const auto from_to_complex_node =
            dynamic_cast<mavka::ast::FromToComplexNode*>(node)) {
      return compile_from_to_complex_node(this, from_to_complex_node);
    }

    if (const auto from_to_simple_node =
            dynamic_cast<mavka::ast::FromToSimpleNode*>(node)) {
      return compile_from_to_simple_node(this, from_to_simple_node);
    }

    if (const auto function_node =
            dynamic_cast<mavka::ast::FunctionNode*>(node)) {
      return compile_function_node(this, function_node);
    }

    if (const auto get_element_node =
            dynamic_cast<mavka::ast::GetElementNode*>(node)) {
      return compile_get_element_node(this, get_element_node);
    }

    if (const auto give_node = dynamic_cast<mavka::ast::GiveNode*>(node)) {
      return compile_give_node(this, give_node);
    }

    if (const auto god_node = dynamic_cast<mavka::ast::GodNode*>(node)) {
      return compile_god_node(this, god_node);
    }

    if (const auto identifier_node =
            dynamic_cast<mavka::ast::IdentifierNode*>(node)) {
      return compile_identifier_node(this, identifier_node);
    }

    if (const auto if_node = dynamic_cast<mavka::ast::IfNode*>(node)) {
      return compile_if_node(this, if_node);
    }

    if (const auto method_declaration_node =
            dynamic_cast<mavka::ast::MethodDeclarationNode*>(node)) {
      return compile_method_declaration_node(this, method_declaration_node);
    }

    if (const auto mml_node = dynamic_cast<mavka::ast::MMLNode*>(node)) {
      return compile_mml_node(this, mml_node);
    }

    if (const auto mockup_diia_node =
            dynamic_cast<mavka::ast::MockupDiiaNode*>(node)) {
      return compile_mockup_diia_node(this, mockup_diia_node);
    }

    if (const auto mockup_module_node =
            dynamic_cast<mavka::ast::MockupModuleNode*>(node)) {
      return compile_mockup_module_node(this, mockup_module_node);
    }

    if (const auto mockup_structure_node =
            dynamic_cast<mavka::ast::MockupStructureNode*>(node)) {
      return compile_mockup_structure_node(this, mockup_structure_node);
    }

    if (const auto mockup_subject_node =
            dynamic_cast<mavka::ast::MockupSubjectNode*>(node)) {
      return compile_mockup_subject_node(this, mockup_subject_node);
    }

    if (const auto module_node = dynamic_cast<mavka::ast::ModuleNode*>(node)) {
      return compile_module_node(this, module_node);
    }

    if (const auto negative_node =
            dynamic_cast<mavka::ast::NegativeNode*>(node)) {
      return compile_negative_node(this, negative_node);
    }

    if (const auto not_node = dynamic_cast<mavka::ast::NotNode*>(node)) {
      return compile_not_node(this, not_node);
    }

    if (const auto number_node = dynamic_cast<mavka::ast::NumberNode*>(node)) {
      return compile_number_node(this, number_node);
    }

    if (const auto positive_node =
            dynamic_cast<mavka::ast::PositiveNode*>(node)) {
      return compile_positive_node(this, positive_node);
    }

    if (const auto post_decrement_node =
            dynamic_cast<mavka::ast::PostDecrementNode*>(node)) {
      return compile_post_decrement_node(this, post_decrement_node);
    }

    if (const auto post_increment_node =
            dynamic_cast<mavka::ast::PostIncrementNode*>(node)) {
      return compile_post_increment_node(this, post_increment_node);
    }

    if (const auto pre_decrement_node =
            dynamic_cast<mavka::ast::PreDecrementNode*>(node)) {
      return compile_pre_decrement_node(this, pre_decrement_node);
    }

    if (const auto pre_increment_node =
            dynamic_cast<mavka::ast::PreIncrementNode*>(node)) {
      return compile_pre_increment_node(this, pre_increment_node);
    }

    if (const auto return_node = dynamic_cast<mavka::ast::ReturnNode*>(node)) {
      return compile_return_node(this, return_node);
    }

    if (const auto string_node = dynamic_cast<mavka::ast::StringNode*>(node)) {
      return compile_string_node(this, string_node);
    }

    if (const auto structure_node =
            dynamic_cast<mavka::ast::StructureNode*>(node)) {
      return compile_structure_node(this, structure_node);
    }

    if (const auto take_module_node =
            dynamic_cast<mavka::ast::TakeModuleNode*>(node)) {
      return compile_take_module_node(this, take_module_node);
    }

    if (const auto take_pak_node =
            dynamic_cast<mavka::ast::TakePakNode*>(node)) {
      return compile_take_pak_node(this, take_pak_node);
    }

    if (const auto ternary_node =
            dynamic_cast<mavka::ast::TernaryNode*>(node)) {
      return compile_ternary_node(this, ternary_node);
    }

    if (const auto test_node = dynamic_cast<mavka::ast::TestNode*>(node)) {
      return compile_test_node(this, test_node);
    }

    if (const auto throw_node = dynamic_cast<mavka::ast::ThrowNode*>(node)) {
      return compile_throw_node(this, throw_node);
    }

    if (const auto try_node = dynamic_cast<mavka::ast::TryNode*>(node)) {
      return compile_try_node(this, try_node);
    }

    if (const auto type_value_single_node =
            dynamic_cast<mavka::ast::TypeValueSingleNode*>(node)) {
      return compile_type_value_single_node(this, type_value_single_node);
    }

    if (const auto wait_node = dynamic_cast<mavka::ast::WaitNode*>(node)) {
      return compile_wait_node(this, wait_node);
    }

    if (const auto while_node = dynamic_cast<mavka::ast::WhileNode*>(node)) {
      return compile_while_node(this, while_node);
    }

    return error("unsupported node");
  }

  Result* Scope::compile_body(std::vector<mavka::ast::ASTNode*> body) {
    const auto result = new Result();
    result->js_body = new jejalyk::js::JsBody();

    for (const auto node : body) {
      if (!node) {
        continue;
      }

      if (jejalyk::tools::instance_of<mavka::ast::MockupStructureNode>(node)) {
        const auto mockup_structure_node =
            dynamic_cast<mavka::ast::MockupStructureNode*>(node);
        const auto compiled_structure_result = this->compile_structure(
            mockup_structure_node->name, mockup_structure_node->generics, "",
            {}, {}, {});
        if (compiled_structure_result->error) {
          return compiled_structure_result;
        }
        compiled_structure_result->value->types[0]
            ->object->this_is_declaration = true;
        this->set_local(mockup_structure_node->name,
                        compiled_structure_result->value);
      }

      if (jejalyk::tools::instance_of<mavka::ast::StructureNode>(node)) {
        const auto structure_node =
            dynamic_cast<mavka::ast::StructureNode*>(node);
        const auto compiled_structure_result = this->compile_structure(
            structure_node->name, structure_node->generics, "", {}, {}, {});
        if (compiled_structure_result->error) {
          return compiled_structure_result;
        }
        compiled_structure_result->value->types[0]
            ->object->this_is_declaration = true;
        this->set_local(structure_node->name, compiled_structure_result->value);
      }
    }

    for (const auto node : body) {
      if (!node) {
        continue;
      }

      if (jejalyk::tools::instance_of<mavka::ast::MockupDiiaNode>(node)) {
        const auto mockup_diia_node =
            dynamic_cast<mavka::ast::MockupDiiaNode*>(node);
        const auto diia_scope = this->make_child();
        const auto compiled_diia_result = this->compile_diia(
            diia_scope, mockup_diia_node->async, mockup_diia_node->name,
            mockup_diia_node->generics, mockup_diia_node->params,
            mockup_diia_node->return_types, nullptr);
        if (compiled_diia_result->error) {
          return compiled_diia_result;
        }
        compiled_diia_result->value->types[0]->object->this_is_declaration =
            true;
        this->set_local(mockup_diia_node->name, compiled_diia_result->value);
      }

      if (jejalyk::tools::instance_of<mavka::ast::DiiaNode>(node)) {
        const auto diia_node = dynamic_cast<mavka::ast::DiiaNode*>(node);
        const auto diia_scope = this->make_child();
        const auto compiled_diia_result = this->compile_diia(
            diia_scope, diia_node->async, diia_node->name, diia_node->generics,
            diia_node->params, diia_node->return_types, nullptr);
        if (compiled_diia_result->error) {
          return compiled_diia_result;
        }
        compiled_diia_result->value->types[0]->object->this_is_declaration =
            true;
        this->set_local(diia_node->name, compiled_diia_result->value);
      }
    }

    for (const auto node : body) {
      if (!node) {
        continue;
      }

      const auto compiled_node_result = this->compile_node(node);
      if (compiled_node_result->error) {
        return compiled_node_result;
      }

      result->js_body->nodes.push_back(compiled_node_result->js_node);
    }

    std::vector<std::string> var_names;
    if (!this->proxy) {
      const auto diia_object = this->get_diia_object();

      for (const auto& [variable_name, variable_subject] : this->variables) {
        if (diia_object) {
          bool is_param = false;
          for (const auto& param : diia_object->params) {
            if (param->name == variable_name) {
              is_param = true;
              break;
            }
          }
          if (is_param) {
            continue;
          }
        }

        var_names.push_back(variable_name);
      }
      if (!var_names.empty()) {
        result->js_body->nodes.insert(result->js_body->nodes.begin(),
                                      jejalyk::js::vars(var_names));
      }
    }

    for (const auto js_node_before : this->get_additional_nodes_before()) {
      result->js_body->nodes.insert(result->js_body->nodes.begin(),
                                    js_node_before);
    }

    return result;
  }

  Result* Scope::compile_structure(
      std::string name,
      std::vector<mavka::ast::GenericNode*> generic_definitions,
      std::string parent,
      std::vector<std::vector<mavka::ast::TypeValueSingleNode*>>
          parent_generics,
      std::vector<mavka::ast::ParamNode*> params,
      std::vector<mavka::ast::MethodDeclarationNode*> method_declarations) {
    Subject* structure_subject = nullptr;
    Type* structure_type = nullptr;
    Object* structure_object = nullptr;
    Scope* scope_with_generics = nullptr;
    std::vector<Subject*> generic_definition_subjects;

    if (this->has_local(name)) {
      structure_subject = this->get_local(name);
      structure_type = structure_subject->types[0];
      structure_object = structure_type->object;

      if (!structure_object->this_is_declaration) {
        return error("Структура \"" + name + "\" вже визначена.");
      }

      structure_object->this_is_declaration = false;
      scope_with_generics = this->make_proxy();

      for (const auto generic_definition :
           structure_object->generic_definitions) {
        const auto generic_definition_type = new Type();
        generic_definition_type->generic_definition = generic_definition;
        const auto generic_definition_subject =
            new Subject({generic_definition_type});
        scope_with_generics->variables.insert_or_assign(
            generic_definition->name, generic_definition_subject);
        generic_definition_subjects.push_back(generic_definition_subject);
      }
    } else {
      const auto structure_structure_subject =
          this->get_root()->get("Структура");
      const auto object_subject = this->get_root()->get("обʼєкт");

      structure_object = new Object();
      structure_object->structure = structure_structure_subject->types[0];
      structure_object->name = name;

      scope_with_generics = this->make_proxy();

      for (int i = 0; i < generic_definitions.size(); ++i) {
        const auto generic_definition_node = generic_definitions[i];
        const auto generic_definition = new GenericDefinition();
        generic_definition->object = structure_object;
        generic_definition->index = i;
        generic_definition->name = generic_definition_node->name;
        structure_object->generic_definitions.push_back(generic_definition);
      }

      for (const auto generic_definition :
           structure_object->generic_definitions) {
        const auto generic_definition_type = new Type();
        generic_definition_type->generic_definition = generic_definition;
        const auto generic_definition_subject =
            new Subject({generic_definition_type});
        scope_with_generics->variables.insert_or_assign(
            generic_definition->name, generic_definition_subject);
        generic_definition_subjects.push_back(generic_definition_subject);
      }

      if (parent.empty()) {
        structure_object->parent = object_subject->types[0];
      } else {
        // todo: handle parent
      }

      structure_type = new Type(structure_object);
      structure_subject = new Subject();
      structure_subject->add_type(structure_type);

      structure_object->return_types = new Subject();
      structure_object->return_types->add_type(
          structure_type->create_instance(this, generic_definition_subjects));
    }

    for (const auto param_node : params) {
      const auto param = new Param();
      param->name = param_node->name;
      param->types = new Subject();
      for (const auto type_value_single_node : param_node->types) {
        const auto type_value_single_result =
            scope_with_generics->compile_node(type_value_single_node);
        if (type_value_single_result->error) {
          return type_value_single_result;
        }
        for (const auto param_type : type_value_single_result->value->types) {
          param->types->add_type(param_type);
        }
      }
      if (param->types->types.empty()) {
        const auto object_subject = this->get_root()->get("обʼєкт");
        const auto object_instance_result =
            object_subject->create_instance(this, {});
        if (object_instance_result->error) {
          return object_instance_result;
        }
        const auto object_type = object_instance_result->value->types[0];
        param->types->add_type(object_type);
      }
      param->value = nullptr;
      param->variadic = param_node->variadic;

      structure_object->params.push_back(param);
    }

    for (const auto method_declaration_node : method_declarations) {
      const auto method_declaration_result =
          scope_with_generics->compile_node(method_declaration_node);
      if (method_declaration_result->error) {
        return method_declaration_result;
      }

      structure_object->methods.insert_or_assign(
          method_declaration_node->name,
          method_declaration_result->value->types[0]);
    }

    const auto diia_structure_subject = this->get_root()->get("Дія");

    const auto structure_constuctor_diia_object = new Object();
    structure_constuctor_diia_object->structure =
        diia_structure_subject->types[0];
    structure_constuctor_diia_object->name = "створити";
    structure_constuctor_diia_object->this_is_declaration = true;
    structure_constuctor_diia_object->is_diia_async = false;
    structure_constuctor_diia_object->params = structure_object->params;
    structure_constuctor_diia_object->return_types =
        structure_object->return_types;
    const auto structure_constuctor_diia_type = new Type();
    structure_constuctor_diia_type->object = structure_constuctor_diia_object;
    const auto structure_constuctor_diia_subject = new Subject();
    structure_constuctor_diia_subject->add_type(structure_constuctor_diia_type);

    structure_object->properties.insert_or_assign(
        "створити", structure_constuctor_diia_subject);
    structure_object->properties.insert_or_assign(
        "чародія_викликати", structure_constuctor_diia_subject);

    const auto js_call_node = new jejalyk::js::JsCallNode();
    const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
    js_call_id_node->name = "мСтрк";
    js_call_node->value = js_call_id_node;
    js_call_node->arguments = {jejalyk::js::string(name), jejalyk::js::null()};

    const auto js_assign_node = new jejalyk::js::JsAssignNode();
    const auto js_id_node = new jejalyk::js::JsIdentifierNode();
    js_id_node->name = name;
    js_assign_node->identifier = js_id_node;
    js_assign_node->value = js_call_node;

    return success(structure_subject, js_assign_node);
  }

  Result* Scope::compile_diia(
      Scope* diia_scope,
      bool async,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generic_definitions,
      std::vector<mavka::ast::ParamNode*> params,
      std::vector<mavka::ast::TypeValueSingleNode*> return_types,
      std::vector<mavka::ast::ASTNode*>* body) {
    Subject* diia_subject = nullptr;
    Type* diia_type = nullptr;
    Object* diia_object = nullptr;
    Scope* scope_with_generics = nullptr;
    std::vector<Subject*> generic_definition_subjects;

    if (!name.empty() && this->has_local(name)) {
      diia_subject = this->get_local(name);
      diia_type = diia_subject->types[0];
      diia_object = diia_type->object;

      if (!diia_object->this_is_declaration) {
        return error("Дія \"" + name + "\" вже визначена.");
      }

      diia_object->this_is_declaration = false;
      diia_object->is_diia_async = async;
      scope_with_generics = this->make_proxy();

      for (const auto generic_definition : diia_object->generic_definitions) {
        const auto generic_definition_type = new Type();
        generic_definition_type->generic_definition = generic_definition;
        const auto generic_definition_subject =
            new Subject({generic_definition_type});
        scope_with_generics->variables.insert_or_assign(
            generic_definition->name, generic_definition_subject);
        generic_definition_subjects.push_back(generic_definition_subject);
      }

      for (const auto param : diia_object->params) {
        diia_scope->set_local(param->name, param->types);
      }

      Result* compiled_body = nullptr;

      if (body != nullptr) {
        diia_scope->diia_object = diia_object;
        diia_scope->is_async = async;

        compiled_body = diia_scope->compile_body(*body);
        if (compiled_body->error) {
          return compiled_body;
        }
      }

      const auto js_function_node = new jejalyk::js::JsFunctionNode();
      js_function_node->async = async;
      for (const auto param : diia_object->params) {
        const auto js_id_node = new jejalyk::js::JsIdentifierNode();
        js_id_node->name = param->name;
        js_function_node->params.push_back(js_id_node);
      }
      if (compiled_body) {
        js_function_node->body = compiled_body->js_body;
      }

      const auto js_call_node = new jejalyk::js::JsCallNode();
      const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
      js_call_id_node->name = "мДія";
      js_call_node->value = js_call_id_node;
      js_call_node->arguments = {jejalyk::js::string(name), jejalyk::js::null(),
                                 js_function_node};

      const auto js_assign_node = new jejalyk::js::JsAssignNode();
      const auto js_id_node = new jejalyk::js::JsIdentifierNode();
      js_id_node->name = name;
      js_assign_node->identifier = js_id_node;
      js_assign_node->value = js_call_node;

      return success(diia_subject, js_assign_node);
    } else {
      const auto diia_structure_subject = this->get_root()->get("Дія");

      diia_object = new Object();
      diia_object->structure = diia_structure_subject->types[0];
      diia_object->name = name;
      diia_object->is_diia_async = async;

      scope_with_generics = this->make_proxy();

      for (int i = 0; i < generic_definitions.size(); ++i) {
        const auto generic_definition_node = generic_definitions[i];
        const auto generic_definition = new GenericDefinition();
        generic_definition->object = diia_object;
        generic_definition->index = i;
        generic_definition->name = generic_definition_node->name;
        diia_object->generic_definitions.push_back(generic_definition);
      }

      for (const auto generic_definition : diia_object->generic_definitions) {
        const auto generic_definition_type = new Type();
        generic_definition_type->generic_definition = generic_definition;
        const auto generic_definition_subject =
            new Subject({generic_definition_type});
        scope_with_generics->variables.insert_or_assign(
            generic_definition->name, generic_definition_subject);
        generic_definition_subjects.push_back(generic_definition_subject);
      }

      diia_type = new Type(diia_object);
      diia_subject = new Subject();
      diia_subject->add_type(diia_type);

      const auto return_types_subject = new Subject();
      for (const auto return_type : return_types) {
        const auto compiled_return_type =
            scope_with_generics->compile_node(return_type);
        if (compiled_return_type->error) {
          return compiled_return_type;
        }
        for (const auto return_type_single :
             compiled_return_type->value->types) {
          return_types_subject->add_type(return_type_single);
        }
      }
      if (return_types.empty()) {
        return_types_subject->types.push_back(
            this->create_object_instance_type());
      }
      if (async) {
        const auto awaiting_structure_subject =
            this->get_root()->get("очікування");
        const auto awaiting_instance_result =
            awaiting_structure_subject->create_instance(this,
                                                        {return_types_subject});
        if (awaiting_instance_result->error) {
          return awaiting_instance_result;
        }
        diia_object->return_types = awaiting_instance_result->value;
      } else {
        diia_object->return_types = return_types_subject;
      }

      for (const auto param_node : params) {
        const auto param = new Param();
        param->name = param_node->name;
        param->types = new Subject();
        for (const auto type_value_single_node : param_node->types) {
          const auto type_value_single_result =
              scope_with_generics->compile_node(type_value_single_node);
          if (type_value_single_result->error) {
            return type_value_single_result;
          }
          for (const auto param_type : type_value_single_result->value->types) {
            param->types->add_type(param_type);
          }
        }
        if (param->types->types.empty()) {
          const auto object_subject = this->get_root()->get("обʼєкт");
          const auto object_instance_result =
              object_subject->create_instance(this, {});
          if (object_instance_result->error) {
            return object_instance_result;
          }
          const auto object_type = object_instance_result->value->types[0];
          param->types->add_type(object_type);
        }
        param->value = nullptr;
        param->variadic = param_node->variadic;

        diia_object->params.push_back(param);
        diia_scope->set_local(param->name, param->types);
      }

      Result* compiled_body = nullptr;

      if (body != nullptr) {
        diia_scope->diia_object = diia_object;
        diia_scope->is_async = async;

        compiled_body = diia_scope->compile_body(*body);
        if (compiled_body->error) {
          return compiled_body;
        }
      }

      const auto js_function_node = new jejalyk::js::JsFunctionNode();
      js_function_node->async = async;
      for (const auto param : diia_object->params) {
        const auto js_id_node = new jejalyk::js::JsIdentifierNode();
        js_id_node->name = param->name;
        js_function_node->params.push_back(js_id_node);
      }
      if (compiled_body) {
        js_function_node->body = compiled_body->js_body;
      }

      const auto js_call_node = new jejalyk::js::JsCallNode();
      const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
      js_call_id_node->name = "мДія";
      js_call_node->value = js_call_id_node;
      js_call_node->arguments = {jejalyk::js::string(name), jejalyk::js::null(),
                                 js_function_node};

      return success(diia_subject, js_call_node);
    }

    return success(diia_subject);
  }

  Result* Scope::compile_module(std::string name,
                                std::vector<mavka::ast::ASTNode*>* body) {
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

    if (body != nullptr) {
      module_scope->module_object = module_object;
      module_scope->is_async = true;

      const auto compiled_body = module_scope->compile_body(*body);
      if (compiled_body->error) {
        return compiled_body;
      }
    }

    return success(module_subject);
  }

} // namespace typeinterpreter