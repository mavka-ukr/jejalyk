#include "typeinterpreter.h"

namespace typeinterpreter {
  Scope* Scope::make_child() {
    const auto child = new Scope();
    child->parent = this;
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
    std::cout << "[BUG] Scope::get_local() called for non-existing variable"
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
    return false;
  }

  bool Scope::check_subjects(Subject* value, Subject* types) {
    debug_print_check_subjects(value, types);

    Type* valid_value_type = nullptr;
    Type* valid_types_type = nullptr;

    for (const auto value_type : value->types) {
      if (value_type->generic_definition) {
        debug_print_bug({"got value generic_definition in check_subjects:",
                         value_type->generic_definition->name});
      }

      for (const auto types_type : types->types) {
        if (types_type->generic_definition) {
          debug_print_bug({"got types generic_definition in check_subjects",
                           types_type->generic_definition->name});
        }

        if (value_type->object->structure->object ==
            types_type->object->structure->object) {
          valid_value_type = value_type;
          valid_types_type = types_type;
          break;
        }
      }
    }

    // todo: move this up
    if (valid_value_type != nullptr && valid_types_type != nullptr) {
      if (valid_types_type->generic_types.size() !=
          valid_value_type->generic_types.size()) {
        return false;
      }

      for (int i = 0; i < valid_types_type->generic_types.size(); ++i) {
        const auto valid_types_type_generic =
            valid_types_type->generic_types[i];
        const auto valid_value_type_generic =
            valid_value_type->generic_types[i];
        if (!this->check_subjects(valid_value_type_generic,
                                  valid_types_type_generic)) {
          return false;
        }
      }

      return true;
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

  Result* Scope::compile_node(mavka::ast::ASTNode* node) {
    if (!node) {
      return error("empty node");
    }

    if (jejalyk::tools::instance_of<mavka::ast::AnonDiiaNode>(node)) {
      const auto anon_diia_node = dynamic_cast<mavka::ast::AnonDiiaNode*>(node);
      const auto diia_scope = this->make_child();
      return this->compile_diia(diia_scope, anon_diia_node->async, false, "",
                                {}, anon_diia_node->params,
                                anon_diia_node->return_types);
    }

    if (jejalyk::tools::instance_of<mavka::ast::ArgNode>(node)) {
      const auto arg_node = dynamic_cast<mavka::ast::ArgNode*>(node);
      std::cout << "ArgNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ArithmeticNode>(node)) {
      const auto arithmetic_node =
          dynamic_cast<mavka::ast::ArithmeticNode*>(node);
      std::cout << "ArithmeticNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ArrayNode>(node)) {
      const auto array_node = dynamic_cast<mavka::ast::StringNode*>(node);
      const auto array_structure_subject = this->get_root()->get("список");
      const auto array_subject =
          array_structure_subject->create_instance(this, {});
      return array_subject;
    }

    if (jejalyk::tools::instance_of<mavka::ast::AsNode>(node)) {
      const auto as_node = dynamic_cast<mavka::ast::AsNode*>(node);
      std::cout << "AsNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::AssignByElementNode>(node)) {
      const auto assign_by_element_node =
          dynamic_cast<mavka::ast::AssignByElementNode*>(node);
      std::cout << "AssignByElementNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::AssignByIdentifierNode>(node)) {
      const auto assign_by_identifier_node =
          dynamic_cast<mavka::ast::AssignByIdentifierNode*>(node);
      std::cout << "AssignByIdentifierNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::AssignSimpleNode>(node)) {
      const auto assign_simple_node =
          dynamic_cast<mavka::ast::AssignSimpleNode*>(node);
      std::cout << "AssignSimpleNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::BitwiseNode>(node)) {
      const auto bitwise_node = dynamic_cast<mavka::ast::BitwiseNode*>(node);
      std::cout << "BitwiseNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::BitwiseNotNode>(node)) {
      const auto bitwise_not_node =
          dynamic_cast<mavka::ast::BitwiseNotNode*>(node);
      std::cout << "BitwiseNotNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::CallNode>(node)) {
      const auto call_node = dynamic_cast<mavka::ast::CallNode*>(node);

      const auto value_result = this->compile_node(call_node->value);
      if (value_result->error) {
        return value_result;
      }

      std::vector<Subject*> generic_types;
      for (const auto& generic_type_nodes : call_node->generics) {
        Subject* generic_subject = nullptr;
        for (const auto type_value_single_node : generic_type_nodes) {
          const auto type_value_single_result =
              this->compile_node(type_value_single_node);
          if (type_value_single_result->error) {
            return type_value_single_result;
          }
          generic_subject = type_value_single_result->value;
        }
        generic_types.push_back(generic_subject);
      }

      std::vector<Subject*> args;
      for (const auto arg_node : call_node->args) {
        const auto arg_result = this->compile_node(arg_node->value);
        if (arg_result->error) {
          return arg_result;
        }
        args.push_back(arg_result->value);
      }

      return value_result->value->call(this, call_node, generic_types, args);
    }

    if (jejalyk::tools::instance_of<mavka::ast::ChainNode>(node)) {
      const auto chain_node = dynamic_cast<mavka::ast::ChainNode*>(node);
      std::cout << "ChainNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ComparisonNode>(node)) {
      const auto comparison_node =
          dynamic_cast<mavka::ast::ComparisonNode*>(node);
      std::cout << "ComparisonNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ContinueNode>(node)) {
      const auto continue_node = dynamic_cast<mavka::ast::ContinueNode*>(node);
      std::cout << "ContinueNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::DictionaryNode>(node)) {
      const auto dictionary_node =
          dynamic_cast<mavka::ast::DictionaryNode*>(node);
      const auto dictionary_structure = this->get_root()->get("словник");
      const auto dictionary_subject =
          dictionary_structure->create_instance(this, {});
      return dictionary_subject;
    }

    if (jejalyk::tools::instance_of<mavka::ast::DiiaNode>(node)) {
      const auto diia_node = dynamic_cast<mavka::ast::DiiaNode*>(node);
      const auto diia_scope = this->make_child();
      const auto diia_compilation_result = this->compile_diia(
          diia_scope, diia_node->async, diia_node->ee, diia_node->name,
          diia_node->generics, diia_node->params, diia_node->return_types);
      if (diia_compilation_result->error) {
        return diia_compilation_result;
      }
      // todo: handle structure
      this->set_local(diia_node->name, diia_compilation_result->value);
      return diia_compilation_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::EachNode>(node)) {
      const auto each_node = dynamic_cast<mavka::ast::EachNode*>(node);
      std::cout << "EachNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::EvalNode>(node)) {
      const auto eval_node = dynamic_cast<mavka::ast::EvalNode*>(node);
      std::cout << "EvalNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::FromToComplexNode>(node)) {
      const auto from_to_complex_node =
          dynamic_cast<mavka::ast::FromToComplexNode*>(node);
      std::cout << "FromToComplexNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::FromToSimpleNode>(node)) {
      const auto from_to_simple_node =
          dynamic_cast<mavka::ast::FromToSimpleNode*>(node);
      std::cout << "FromToSimpleNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::FunctionNode>(node)) {
      const auto function_node = dynamic_cast<mavka::ast::FunctionNode*>(node);
      const auto diia_scope = this->make_child();
      return this->compile_diia(diia_scope, function_node->async, false, "", {},
                                function_node->params,
                                function_node->return_types);
    }

    if (jejalyk::tools::instance_of<mavka::ast::GetElementNode>(node)) {
      const auto get_element_node =
          dynamic_cast<mavka::ast::GetElementNode*>(node);
      std::cout << "GetElementNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::GiveNode>(node)) {
      const auto give_node = dynamic_cast<mavka::ast::GiveNode*>(node);
      std::cout << "GiveNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::GodNode>(node)) {
      const auto god_node = dynamic_cast<mavka::ast::GodNode*>(node);
      std::cout << "GodNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::IdentifierNode>(node)) {
      const auto identifier_node =
          dynamic_cast<mavka::ast::IdentifierNode*>(node);
      if (!this->has(identifier_node->name)) {
        return error_from_ast(
            node, "Субʼєкт \"" + identifier_node->name + "\" не визначено.");
      }
      const auto subject = this->get(identifier_node->name);
      debug_print_got_from_scope(this, identifier_node->name, subject);
      return success(subject);
    }

    if (jejalyk::tools::instance_of<mavka::ast::IfNode>(node)) {
      const auto if_node = dynamic_cast<mavka::ast::IfNode*>(node);
      std::cout << "IfNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::MethodDeclarationNode>(node)) {
      const auto method_declaration_node =
          dynamic_cast<mavka::ast::MethodDeclarationNode*>(node);
      const auto diia_scope = this->make_child();
      return this->compile_diia(
          diia_scope, method_declaration_node->async,
          method_declaration_node->ee, method_declaration_node->name,
          method_declaration_node->generics, method_declaration_node->params,
          method_declaration_node->return_types);
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupDiiaNode>(node)) {
      const auto mockup_diia_node =
          dynamic_cast<mavka::ast::MockupDiiaNode*>(node);
      const auto diia_scope = this->make_child();
      const auto diia_compilation_result = this->compile_diia(
          diia_scope, mockup_diia_node->async, mockup_diia_node->ee,
          mockup_diia_node->name, mockup_diia_node->generics,
          mockup_diia_node->params, mockup_diia_node->return_types);
      if (diia_compilation_result->error) {
        return diia_compilation_result;
      }
      // todo: handle structure
      this->set_local(mockup_diia_node->name, diia_compilation_result->value);
      return diia_compilation_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupModuleNode>(node)) {
      const auto mockup_module_node =
          dynamic_cast<mavka::ast::MockupModuleNode*>(node);
      std::cout << "MockupModuleNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupObjectNode>(node)) {
      const auto mockup_object_node =
          dynamic_cast<mavka::ast::MockupObjectNode*>(node);
      std::cout << "MockupObjectNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupStructureNode>(node)) {
      const auto mockup_structure_node =
          dynamic_cast<mavka::ast::MockupStructureNode*>(node);
      const auto structure_compilation_result = this->compile_structure(
          mockup_structure_node->name, mockup_structure_node->generics, "", {},
          mockup_structure_node->params, mockup_structure_node->methods);
      if (structure_compilation_result->error) {
        return structure_compilation_result;
      }
      this->set_local(mockup_structure_node->name,
                      structure_compilation_result->value);
      return structure_compilation_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupSubjectNode>(node)) {
      const auto mockup_subject_node =
          dynamic_cast<mavka::ast::MockupSubjectNode*>(node);
      std::cout << "MockupSubjectNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ModuleNode>(node)) {
      const auto module_node = dynamic_cast<mavka::ast::ModuleNode*>(node);
      std::cout << "ModuleNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NegativeNode>(node)) {
      const auto negative_node = dynamic_cast<mavka::ast::NegativeNode*>(node);
      std::cout << "NegativeNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NotNode>(node)) {
      const auto not_node = dynamic_cast<mavka::ast::NotNode*>(node);
      std::cout << "NotNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NumberNode>(node)) {
      const auto number_node = dynamic_cast<mavka::ast::NumberNode*>(node);
      const auto number_structure = this->get_root()->get("число");
      const auto number_subject = number_structure->create_instance(this, {});
      return number_subject;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PositiveNode>(node)) {
      const auto positive_node = dynamic_cast<mavka::ast::PositiveNode*>(node);
      std::cout << "PositiveNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PostDecrementNode>(node)) {
      const auto post_decrement_node =
          dynamic_cast<mavka::ast::PostDecrementNode*>(node);
      std::cout << "PostDecrementNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PostIncrementNode>(node)) {
      const auto post_increment_node =
          dynamic_cast<mavka::ast::PostIncrementNode*>(node);
      std::cout << "PostIncrementNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PreDecrementNode>(node)) {
      const auto pre_decrement_node =
          dynamic_cast<mavka::ast::PreDecrementNode*>(node);
      std::cout << "PreDecrementNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PreIncrementNode>(node)) {
      const auto pre_increment_node =
          dynamic_cast<mavka::ast::PreIncrementNode*>(node);
      std::cout << "PreIncrementNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ReturnNode>(node)) {
      const auto return_node = dynamic_cast<mavka::ast::ReturnNode*>(node);
      std::cout << "ReturnNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::StringNode>(node)) {
      const auto string_node = dynamic_cast<mavka::ast::StringNode*>(node);
      const auto string_structure = this->get("текст");
      const auto string_subject = string_structure->create_instance(this, {});
      return string_subject;
    }

    if (jejalyk::tools::instance_of<mavka::ast::StructureNode>(node)) {
      const auto structure_node =
          dynamic_cast<mavka::ast::StructureNode*>(node);
      std::cout << "StructureNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TakeModuleNode>(node)) {
      const auto take_module_node =
          dynamic_cast<mavka::ast::TakeModuleNode*>(node);
      std::cout << "TakeModuleNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TakePakNode>(node)) {
      const auto take_pak_node = dynamic_cast<mavka::ast::TakePakNode*>(node);
      std::cout << "TakePakNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TernaryNode>(node)) {
      const auto ternary_node = dynamic_cast<mavka::ast::TernaryNode*>(node);
      std::cout << "TernaryNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TestNode>(node)) {
      const auto test_node = dynamic_cast<mavka::ast::TestNode*>(node);
      std::cout << "TestNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::ThrowNode>(node)) {
      const auto throw_node = dynamic_cast<mavka::ast::ThrowNode*>(node);
      std::cout << "ThrowNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TryNode>(node)) {
      const auto try_node = dynamic_cast<mavka::ast::TryNode*>(node);
      std::cout << "TryNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TypeValueSingleNode>(node)) {
      const auto type_value_single_node =
          dynamic_cast<mavka::ast::TypeValueSingleNode*>(node);

      const auto value_compilation_result =
          this->compile_node(type_value_single_node->value);
      if (value_compilation_result->error) {
        return value_compilation_result;
      }

      if (!value_compilation_result->value->types.empty()) {
        if (value_compilation_result->value->types[0]->object) {
          if (type_value_single_node->generics.size() >
              value_compilation_result->value->types[0]
                  ->object->generic_definitions.size()) {
            return error_from_ast(node, "Забагато аргументів шаблону.");
          }

          if (type_value_single_node->generics.size() <
              value_compilation_result->value->types[0]
                  ->object->generic_definitions.size()) {
            return error_from_ast(node, "Недостатньо аргументів шаблону.");
          }
        }
      }

      if (!type_value_single_node->generics.empty()) {
        if (value_compilation_result->value->types.size() != 1) {
          return error_from_ast(node,
                                "Неможливо застосувати аргументи шаблону до "
                                "типу з різними можливими значеннями.");
        }

        if (value_compilation_result->value->types[0]->generic_definition) {
          return error_from_ast(
              node, "Неможливо використовувати аргументи шаблону для шаблону.");
        }

        std::vector<Subject*> generic_types;
        for (const auto& generic_type_value :
             type_value_single_node->generics) {
          const auto generic_type_subject = new Subject();
          for (const auto generic_type_value_single_node : generic_type_value) {
            const auto generic_type_value_single_result =
                this->compile_node(generic_type_value_single_node);
            if (generic_type_value_single_result->error) {
              return generic_type_value_single_result;
            }
            for (const auto generic_generic_type_value :
                 generic_type_value_single_result->value->types) {
              generic_type_subject->types.push_back(generic_generic_type_value);
            }
          }
          generic_types.push_back(generic_type_subject);
        }

        return value_compilation_result->value->create_instance(this,
                                                                generic_types);
      }

      return value_compilation_result->value->create_instance(this, {});
    }

    if (jejalyk::tools::instance_of<mavka::ast::WaitNode>(node)) {
      const auto wait_node = dynamic_cast<mavka::ast::WaitNode*>(node);
      std::cout << "WaitNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::WhileNode>(node)) {
      const auto while_node = dynamic_cast<mavka::ast::WhileNode*>(node);
      std::cout << "WhileNode" << std::endl;
    }

    return error("unsupported node");
  }

  Result* Scope::compile_body(std::vector<mavka::ast::ASTNode*> body) {
    return new Result();
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

      if (!parent.empty()) {
        // todo: handle parent
      }

      structure_type = new Type(structure_object);
      structure_subject = new Subject();
      structure_subject->types.push_back(structure_type);

      structure_object->return_types = new Subject();
      structure_object->return_types->types.push_back(
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
          param->types->types.push_back(param_type);
        }
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

    return success(structure_subject);
  }

  Result* Scope::compile_diia(
      Scope* diia_scope,
      bool async,
      bool ee,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generic_definitions,
      std::vector<mavka::ast::ParamNode*> params,
      std::vector<mavka::ast::TypeValueSingleNode*> return_types) {
    Subject* diia_subject = nullptr;
    Type* diia_type = nullptr;
    Object* diia_object = nullptr;
    Scope* scope_with_generics = nullptr;
    std::vector<Subject*> generic_definition_subjects;

    const auto diia_structure_subject = this->get_root()->get("Дія");

    diia_object = new Object();
    diia_object->structure = diia_structure_subject->types[0];
    diia_object->name = name;

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
    diia_subject->types.push_back(diia_type);

    const auto return_types_subject = new Subject();
    for (const auto return_type : return_types) {
      const auto compiled_return_type =
          scope_with_generics->compile_node(return_type);
      if (compiled_return_type->error) {
        return compiled_return_type;
      }
      for (const auto return_type_single : compiled_return_type->value->types) {
        return_types_subject->types.push_back(return_type_single);
      }
    }
    diia_object->return_types = return_types_subject;

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
          param->types->types.push_back(param_type);
        }
      }
      param->value = nullptr;
      param->variadic = param_node->variadic;

      diia_object->params.push_back(param);
    }

    return success(diia_subject);
  }

} // namespace typeinterpreter