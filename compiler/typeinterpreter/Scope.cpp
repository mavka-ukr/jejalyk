#include <algorithm>

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
    return this->compile_nodes(nodes);
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

    if (jejalyk::tools::instance_of<mavka::ast::AnonDiiaNode>(node)) {
      const auto anon_diia_node = dynamic_cast<mavka::ast::AnonDiiaNode*>(node);
      const auto diia_scope = this->make_child();
      return this->compile_diia(
          diia_scope, anon_diia_node->async, "", {}, anon_diia_node->params,
          anon_diia_node->return_types, &anon_diia_node->body);
    }

    if (jejalyk::tools::instance_of<mavka::ast::ArgNode>(node)) {
      const auto arg_node = dynamic_cast<mavka::ast::ArgNode*>(node);
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

      const auto js_arithmetic_node = new jejalyk::js::JsArithmeticNode();

      Result* result;
      std::string magic_diia;
      std::string m_diia_name;

      if (arithmetic_node->op == "+") {
        result = left_result->value->plus(this, node, right_result->value);
        magic_diia = "чародія_додати";
        m_diia_name = "мДодати";
      }
      if (arithmetic_node->op == "-") {
        result = left_result->value->minus(this, node, right_result->value);
        magic_diia = "чародія_відняти";
        m_diia_name = "мВідняти";
      }
      if (arithmetic_node->op == "*") {
        result = left_result->value->multiply(this, node, right_result->value);
        magic_diia = "чародія_помножити";
        m_diia_name = "мПомножити";
      }
      if (arithmetic_node->op == "/") {
        result = left_result->value->divide(this, node, right_result->value);
        magic_diia = "чародія_поділити";
        m_diia_name = "мПоділити";
      }
      if (arithmetic_node->op == "%") {
        result = left_result->value->divmod(this, node, right_result->value);
        magic_diia = "чародія_остача";
        m_diia_name = "мОстача";
      }
      if (arithmetic_node->op == "//") {
        result = left_result->value->divdiv(this, node, right_result->value);
        magic_diia = "чародія_частка";
        m_diia_name = "мЧастка";
      }
      if (arithmetic_node->op == "**") {
        result = left_result->value->pow(this, node, right_result->value);
        magic_diia = "чародія_степінь";
        m_diia_name = "мСтепінь";
      }

      if (result != nullptr) {
        if (result->error) {
          return result;
        }

        if (left_result->value->is_number(this) &&
            right_result->value->is_number(this)) {
          js_arithmetic_node->left = left_result->js_node;
          js_arithmetic_node->right = right_result->js_node;
          js_arithmetic_node->op = arithmetic_node->op;
          return success(result->value, js_arithmetic_node);
        }

        if (arithmetic_node->op == "+") {
          if (left_result->value->is_string(this) &&
              right_result->value->is_string(this)) {
            js_arithmetic_node->left = left_result->js_node;
            js_arithmetic_node->right = right_result->js_node;
            js_arithmetic_node->op = "+";
            return success(result->value, js_arithmetic_node);
          }
        }

        if (left_result->value->has_diia(this, magic_diia)) {
          const auto js_chain_node = new jejalyk::js::JsChainNode();
          js_chain_node->left = left_result->js_node;
          const auto js_chain_node_right = new jejalyk::js::JsIdentifierNode();
          js_chain_node_right->name = magic_diia;
          js_chain_node->right = js_chain_node_right;
          const auto js_call_node = new jejalyk::js::JsCallNode();
          js_call_node->value = js_chain_node;
          js_call_node->arguments = {right_result->js_node};
          result->js_node = js_call_node;
          return success(result->value, js_chain_node);
        } else {
          const auto js_call_node = new jejalyk::js::JsCallNode();
          const auto js_id_node = new jejalyk::js::JsIdentifierNode();
          js_id_node->name = m_diia_name;
          js_call_node->value = js_id_node;
          js_call_node->arguments = {left_result->js_node,
                                     right_result->js_node};
          return success(result->value, js_call_node);
        }

        return result;
      }

      return error_from_ast(
          node, "Невідома вказівка \"" + arithmetic_node->op + "\".");
    }

    if (jejalyk::tools::instance_of<mavka::ast::ArrayNode>(node)) {
      const auto array_node = dynamic_cast<mavka::ast::ArrayNode*>(node);
      const auto js_array_node = new jejalyk::js::JsArrayNode();
      const auto array_structure_subject = this->get_root()->get("список");
      const auto array_values_type_result =
          this->compile_nodes(array_node->elements);
      if (array_values_type_result->error) {
        return array_values_type_result;
      }
      js_array_node->elements = array_values_type_result->js_body->nodes;
      if (array_node->types.empty()) {
        const auto result = array_structure_subject->create_instance(
            this, {array_values_type_result->value});
        result->js_node = js_array_node;
        return result;
      } else {
        const auto array_type_subject = new Subject();
        for (const auto type_value_single_node : array_node->types) {
          const auto type_value_single_result =
              this->compile_node(type_value_single_node);
          if (type_value_single_result->error) {
            return type_value_single_result;
          }
          for (const auto type : type_value_single_result->value->types) {
            array_type_subject->add_type(type);
          }
        }

        if (!array_node->elements.empty()) {
          if (!this->check_subjects(array_values_type_result->value,
                                    array_type_subject)) {
            return error_from_ast(
                node,
                "Неправильний тип елементів масиву: очікується \"" +
                    array_type_subject->types_string() + "\", отримано \"" +
                    array_values_type_result->value->types_string() + "\".");
          }
        }

        const auto result = array_structure_subject->create_instance(
            this, {array_type_subject});
        result->js_node = js_array_node;
        return result;
      }
    }

    if (jejalyk::tools::instance_of<mavka::ast::AsNode>(node)) {
      const auto as_node = dynamic_cast<mavka::ast::AsNode*>(node);
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

      return left_result->value->set_element(this, node, element_result->value,
                                             value_result->value);
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

      return left_result->value->set(this, node,
                                     assign_by_identifier_node->identifier,
                                     value_result->value);
    }

    if (jejalyk::tools::instance_of<mavka::ast::AssignSimpleNode>(node)) {
      const auto assign_simple_node =
          dynamic_cast<mavka::ast::AssignSimpleNode*>(node);

      const auto value_result = this->compile_node(assign_simple_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto js_assign_node = new jejalyk::js::JsAssignNode();
      js_assign_node->identifier = new jejalyk::js::JsIdentifierNode();
      js_assign_node->identifier->name = assign_simple_node->name;
      js_assign_node->value = value_result->js_node;

      if (assign_simple_node->types.empty()) {
        if (this->has_local(assign_simple_node->name)) {
          const auto local_subject = this->get_local(assign_simple_node->name);
          if (!this->check_subjects(value_result->value, local_subject)) {
            return error_0(node, assign_simple_node->name, local_subject,
                           value_result->value);
          }
          return success(local_subject, js_assign_node);
        } else {
          this->set_local(assign_simple_node->name, value_result->value);
          return success(value_result->value, js_assign_node);
        }
      } else {
        if (this->has_local(assign_simple_node->name)) {
          return error_1(node, assign_simple_node->name);
        }

        const auto types_result =
            this->compile_types(assign_simple_node->types);
        if (types_result->error) {
          return types_result;
        }

        if (!this->check_subjects(value_result->value, types_result->value)) {
          return error_0(node, assign_simple_node->name, types_result->value,
                         value_result->value);
        }

        this->set_local(assign_simple_node->name, types_result->value);

        return success(types_result->value, js_assign_node);
      }
    }

    if (jejalyk::tools::instance_of<mavka::ast::BitwiseNode>(node)) {
      const auto bitwise_node = dynamic_cast<mavka::ast::BitwiseNode*>(node);

      const auto left_result = this->compile_node(bitwise_node->left);
      if (left_result->error) {
        return left_result;
      }
      const auto right_result = this->compile_node(bitwise_node->right);
      if (right_result->error) {
        return right_result;
      }
      if (bitwise_node->op == "^") {
        return left_result->value->bw_xor(this, node, right_result->value);
      }
      if (bitwise_node->op == "|") {
        return left_result->value->bw_or(this, node, right_result->value);
      }
      if (bitwise_node->op == "&") {
        return left_result->value->bw_and(this, node, right_result->value);
      }
      if (bitwise_node->op == "<<") {
        return left_result->value->bw_shift_left(this, node,
                                                 right_result->value);
      }
      if (bitwise_node->op == ">>") {
        return left_result->value->bw_shift_right(this, node,
                                                  right_result->value);
      }

      return error_from_ast(node,
                            "Невідома вказівка \"" + bitwise_node->op + "\".");
    }

    if (jejalyk::tools::instance_of<mavka::ast::BitwiseNotNode>(node)) {
      const auto bitwise_not_node =
          dynamic_cast<mavka::ast::BitwiseNotNode*>(node);

      const auto value_result = this->compile_node(bitwise_not_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto result = value_result->value->bw_not(this, node);
      if (result->error) {
        return result;
      }

      if (value_result->value->is_number(this)) {
        const auto js_negative_node = new jejalyk::js::JsNegativeNode();
        js_negative_node->value = value_result->js_node;
        result->js_node = js_negative_node;
      } else if (value_result->value->has_diia(this, "чародія_дні")) {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_chain_node = new jejalyk::js::JsChainNode();
        js_chain_node->left = value_result->js_node;
        const auto js_chain_node_right = new jejalyk::js::JsIdentifierNode();
        js_chain_node_right->name = "чародія_дні";
        js_chain_node->right = js_chain_node_right;
        js_call_node->value = js_chain_node;
        js_call_node->arguments = {};
        result->js_node = js_call_node;
      } else {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_id_node = new jejalyk::js::JsIdentifierNode();
        js_id_node->name = "мДні";
        js_call_node->value = js_id_node;
        js_call_node->arguments = {value_result->js_node};
        result->js_node = js_call_node;
      }

      return result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::BreakNode>(node)) {
      const auto break_node = dynamic_cast<mavka::ast::BreakNode*>(node);

      if (!this->get_is_loop()) {
        return error_from_ast(node,
                              "Вказівка \"перервати\" може бути "
                              "використана тільки всередині циклу.");
      }

      const auto js_break_node = new jejalyk::js::JsBreakNode();

      return success(nullptr, js_break_node);
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
      std::vector<jejalyk::js::JsNode*> js_args;
      for (const auto arg_node : call_node->args) {
        const auto arg_result = this->compile_node(arg_node->value);
        if (arg_result->error) {
          return arg_result;
        }
        args.push_back(arg_result->value);
        js_args.push_back(arg_result->js_node);
      }

      const auto result =
          value_result->value->call(this, call_node, generic_types, args);

      const auto js_call_node = new jejalyk::js::JsCallNode();
      js_call_node->value = value_result->js_node;
      js_call_node->arguments = js_args;

      result->js_node = js_call_node;

      return result;
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
          return error_2(node, right_identifier_node->name, left_result->value);
        }

        const auto subject_result =
            left_result->value->get(right_identifier_node->name);
        if (subject_result->error) {
          return subject_result;
        }
        return success(subject_result->value);
      } else {
        const auto right_result = this->compile_node(chain_node->right);
        if (right_result->error) {
          return right_result;
        }

        return left_result->value->get_element(this, node, right_result->value);
      }
    }

    if (jejalyk::tools::instance_of<mavka::ast::ComparisonNode>(node)) {
      const auto comparison_node =
          dynamic_cast<mavka::ast::ComparisonNode*>(node);

      const auto left_result = this->compile_node(comparison_node->left);
      if (left_result->error) {
        return left_result;
      }
      const auto right_result = this->compile_node(comparison_node->right);
      if (right_result->error) {
        return right_result;
      }

      Result* result;
      std::string magic_diia;
      std::string js_comp_symbol;
      std::string m_diia_name;

      if (comparison_node->op == "==" || comparison_node->op == "рівно") {
        result = left_result->value->comp_eq(this, node, right_result->value);
        magic_diia = "чародія_рівно";
        js_comp_symbol = "==";
        m_diia_name = "мРівн";
      }
      if (comparison_node->op == "!=" || comparison_node->op == "не рівно") {
        result =
            left_result->value->comp_not_eq(this, node, right_result->value);
        magic_diia = "чародія_не_рівно";
        js_comp_symbol = "!=";
        m_diia_name = "мНеРівн";
      }
      if (comparison_node->op == ">" || comparison_node->op == "більше") {
        result =
            left_result->value->comp_greater(this, node, right_result->value);
        magic_diia = "чародія_більше";
        js_comp_symbol = ">";
        m_diia_name = "мБілш";
      }
      if (comparison_node->op == "<" || comparison_node->op == "менше") {
        result =
            left_result->value->comp_lesser(this, node, right_result->value);
        magic_diia = "чародія_менше";
        js_comp_symbol = "<";
        m_diia_name = "мМенш";
      }
      if (comparison_node->op == ">=" || comparison_node->op == "не менше") {
        result = left_result->value->comp_greater_or_eq(this, node,
                                                        right_result->value);
        magic_diia = "чародія_не_менше";
        js_comp_symbol = ">=";
        m_diia_name = "мНеМенш";
      }
      if (comparison_node->op == "<=" || comparison_node->op == "не більше") {
        result = left_result->value->comp_lesser_or_eq(this, node,
                                                       right_result->value);
        magic_diia = "чародія_не_більше";
        js_comp_symbol = "<=";
        m_diia_name = "мНеБілш";
      }
      if (comparison_node->op == "є") {
        result = left_result->value->comp_is(this, node, right_result->value);
        magic_diia = "чародія_є";
        m_diia_name = "мЄ";
      }
      if (comparison_node->op == "не є") {
        result =
            left_result->value->comp_is_not(this, node, right_result->value);
        magic_diia = "чародія_не_є";
        m_diia_name = "мНеЄ";
      }
      if (comparison_node->op == "містить") {
        result =
            left_result->value->comp_contains(this, node, right_result->value);
        magic_diia = "чародія_містить";
        m_diia_name = "мМістить";
      }
      if (comparison_node->op == "не містить") {
        result = left_result->value->comp_contains_not(this, node,
                                                       right_result->value);
        magic_diia = "чародія_не_містить";
        m_diia_name = "мНеМістить";
      }

      if (result != nullptr) {
        if (result->error) {
          return result;
        }

        if (magic_diia == "чародія_рівно") {
          const auto js_comparison_node = new jejalyk::js::JsComparisonNode();
          js_comparison_node->left = left_result->js_node;
          js_comparison_node->right = right_result->js_node;
          js_comparison_node->op = "==";
          return success(result->value, js_comparison_node);
        }

        if (magic_diia == "чародія_не_рівно") {
          const auto js_comparison_node = new jejalyk::js::JsComparisonNode();
          js_comparison_node->left = left_result->js_node;
          js_comparison_node->right = right_result->js_node;
          js_comparison_node->op = "!=";
          return success(result->value, js_comparison_node);
        }

        if (magic_diia == "чародія_є") {
          const auto js_call_node = new jejalyk::js::JsCallNode();
          const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
          js_call_id_node->name = "мЄ";
          js_call_node->value = js_call_id_node;
          js_call_node->arguments = {left_result->js_node,
                                     right_result->js_node};
          return success(result->value, js_call_node);
        }

        if (magic_diia == "чародія_не_є") {
          const auto js_call_node = new jejalyk::js::JsCallNode();
          const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
          js_call_id_node->name = "мЄ";
          js_call_node->value = js_call_id_node;
          js_call_node->arguments = {left_result->js_node,
                                     right_result->js_node};
          const auto js_not_node = new jejalyk::js::JsNotNode();
          js_not_node->value = js_call_node;
          return success(result->value, js_not_node);
        }

        if (left_result->value->is_number(this) &&
            right_result->value->is_number(this)) {
          if (js_comp_symbol.empty()) {
            return error_from_ast(node, "[INTERNAL BUG] Невідома вказівка \"" +
                                            comparison_node->op + "\".");
          }
          const auto js_comparison_node = new jejalyk::js::JsComparisonNode();
          js_comparison_node->left = left_result->js_node;
          js_comparison_node->right = right_result->js_node;
          js_comparison_node->op = js_comp_symbol;
          return success(result->value, js_comparison_node);
        }

        if (left_result->value->has_diia(this, magic_diia)) {
          const auto js_chain_node = new jejalyk::js::JsChainNode();
          js_chain_node->left = left_result->js_node;
          const auto js_chain_node_right = new jejalyk::js::JsIdentifierNode();
          js_chain_node_right->name = magic_diia;
          js_chain_node->right = js_chain_node_right;
          const auto js_call_node = new jejalyk::js::JsCallNode();
          js_call_node->value = js_chain_node;
          js_call_node->arguments = {right_result->js_node};
          result->js_node = js_call_node;
          return success(result->value, js_chain_node);
        } else {
          const auto js_call_node = new jejalyk::js::JsCallNode();
          const auto js_id_node = new jejalyk::js::JsIdentifierNode();
          js_id_node->name = m_diia_name;
          js_call_node->value = js_id_node;
          js_call_node->arguments = {left_result->js_node,
                                     right_result->js_node};
          return success(result->value, js_call_node);
        }

        return result;
      }

      return error_from_ast(
          node, "Невідома вказівка \"" + comparison_node->op + "\".");
    }

    if (jejalyk::tools::instance_of<mavka::ast::ContinueNode>(node)) {
      const auto continue_node = dynamic_cast<mavka::ast::ContinueNode*>(node);

      if (!this->get_is_loop()) {
        return error_from_ast(node,
                              "Вказівка \"продовжити\" може бути "
                              "використана тільки всередині циклу.");
      }

      const auto js_continue_node = new jejalyk::js::JsContinueNode();

      return success(nullptr, js_continue_node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::DictionaryNode>(node)) {
      const auto dictionary_node =
          dynamic_cast<mavka::ast::DictionaryNode*>(node);
      const auto dictionary_structure = this->get_root()->get("словник");
      const auto object_structure_subject = this->get_root()->get("обʼєкт");
      const auto object_instance_subject =
          object_structure_subject->create_instance(this, {});
      if (object_instance_subject->error) {
        return object_instance_subject;
      }
      const auto dictionary_subject = dictionary_structure->create_instance(
          this,
          {object_instance_subject->value, object_instance_subject->value});
      return dictionary_subject;
    }

    if (jejalyk::tools::instance_of<mavka::ast::DiiaNode>(node)) {
      const auto diia_node = dynamic_cast<mavka::ast::DiiaNode*>(node);
      const auto diia_scope = this->make_child();
      const auto diia_compilation_result = this->compile_diia(
          diia_scope, diia_node->async, diia_node->name, diia_node->generics,
          diia_node->params, diia_node->return_types, &diia_node->body);
      if (diia_compilation_result->error) {
        return diia_compilation_result;
      }
      // todo: handle structure
      this->set_local(diia_node->name, diia_compilation_result->value);
      return diia_compilation_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::EachNode>(node)) {
      const auto each_node = dynamic_cast<mavka::ast::EachNode*>(node);

      const auto value_result = this->compile_node(each_node->value);
      if (value_result->error) {
        return value_result;
      }

      if (each_node->keyName.empty()) {
        if (value_result->value->is_iterator(this)) {
          const auto iterator_type_result =
              value_result->value->get_iterator_type(this, each_node->value);
          if (iterator_type_result->error) {
            return iterator_type_result;
          }
          this->set_local(each_node->name, iterator_type_result->value);
        } else if (value_result->value->has("чародія_перебір")) {
          const auto iterator_diia_type_result =
              value_result->value->get("чародія_перебір");
          if (iterator_diia_type_result->error) {
            return iterator_diia_type_result;
          }
          const auto iterator_diia_return_types =
              iterator_diia_type_result->value->call(this, each_node->value, {},
                                                     {});
          if (iterator_diia_return_types->value->is_iterator(this)) {
            const auto iterator_type_result =
                iterator_diia_return_types->value->get_iterator_type(
                    this, each_node->value);
            if (iterator_type_result->error) {
              return iterator_type_result;
            }
            this->set_local(each_node->name, iterator_type_result->value);
          } else {
            return error_from_ast(
                node, "Неможливо перебрати \"" +
                          value_result->value->types_string() + "\".");
          }
        } else {
          return error_from_ast(node, "Неможливо перебрати \"" +
                                          value_result->value->types_string() +
                                          "\".");
        }
      } else {
        return error_from_ast(node, "Неможливо перебрати \"" +
                                        value_result->value->types_string() +
                                        "\".");
      }

      const auto loop_scope = this->make_proxy();
      loop_scope->is_loop = true;

      const auto compiled_body = loop_scope->compile_body(each_node->body);
      if (compiled_body->error) {
        return compiled_body;
      }

      return success(nullptr);
    }

    if (jejalyk::tools::instance_of<mavka::ast::EvalNode>(node)) {
      const auto eval_node = dynamic_cast<mavka::ast::EvalNode*>(node);
      std::cout << "EvalNode" << std::endl;
    }

    if (jejalyk::tools::instance_of<mavka::ast::FromToComplexNode>(node)) {
      const auto from_to_complex_node =
          dynamic_cast<mavka::ast::FromToComplexNode*>(node);
      const auto iterator_structure_subject = this->get_root()->get("перебір");
      const auto number_structure_subject = this->get_root()->get("число");
      const auto number_instance_result =
          number_structure_subject->create_instance(this, {});
      if (number_instance_result->error) {
        return number_instance_result;
      }
      const auto iterator_instance_result =
          iterator_structure_subject->create_instance(
              this, {number_instance_result->value});
      if (iterator_instance_result->error) {
        return iterator_instance_result;
      }
      return iterator_instance_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::FromToSimpleNode>(node)) {
      const auto from_to_simple_node =
          dynamic_cast<mavka::ast::FromToSimpleNode*>(node);
      const auto iterator_structure_subject = this->get_root()->get("перебір");
      const auto number_structure_subject = this->get_root()->get("число");
      const auto number_instance_result =
          number_structure_subject->create_instance(this, {});
      if (number_instance_result->error) {
        return number_instance_result;
      }
      const auto iterator_instance_result =
          iterator_structure_subject->create_instance(
              this, {number_instance_result->value});
      if (iterator_instance_result->error) {
        return iterator_instance_result;
      }
      return iterator_instance_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::FunctionNode>(node)) {
      const auto function_node = dynamic_cast<mavka::ast::FunctionNode*>(node);
      const auto diia_scope = this->make_child();
      return this->compile_diia(
          diia_scope, function_node->async, "", {}, function_node->params,
          function_node->return_types, &function_node->body);
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

      const auto result =
          value_result->value->get_element(this, node, index_result->value);
      if (result->error) {
        return result;
      }

      if (value_result->value->is_array(this)) {
        const auto js_access_node = new jejalyk::js::JsAccessNode();
        js_access_node->value = value_result->js_node;
        js_access_node->index = index_result->js_node;
        result->js_node = js_access_node;
      } else if (value_result->value->has_diia(this, "чародія_отримати")) {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_chain_node = new jejalyk::js::JsChainNode();
        js_chain_node->left = value_result->js_node;
        const auto js_chain_node_right = new jejalyk::js::JsIdentifierNode();
        js_chain_node_right->name = "чародія_отримати";
        js_chain_node->right = js_chain_node_right;
        js_call_node->value = js_chain_node;
        js_call_node->arguments = {index_result->js_node};
        result->js_node = js_call_node;
      } else {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_id_node = new jejalyk::js::JsIdentifierNode();
        js_id_node->name = "мОтрЕ";
        js_call_node->value = js_id_node;
        js_call_node->arguments = {value_result->js_node,
                                   index_result->js_node};
        result->js_node = js_call_node;
      }

      return result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::GiveNode>(node)) {
      const auto give_node = dynamic_cast<mavka::ast::GiveNode*>(node);

      const auto module_object = this->get_module_object();
      if (module_object == nullptr) {
        return error_from_ast(node, "Вказівка \"дати\" працює лише в модулі.");
      }

      for (const auto element_node : give_node->elements) {
        if (this->has_local(element_node->name)) {
          const auto subject = this->get_local(element_node->name);
          if (element_node->as.empty()) {
            module_object->properties.insert_or_assign(element_node->name,
                                                       subject);
          } else {
            module_object->properties.insert_or_assign(element_node->as,
                                                       subject);
          }
        } else {
          return error_from_ast(node, "Невідомий субʼєкт для давання \"" +
                                          element_node->name + "\".");
        }
      }

      return success(nullptr);
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
      const auto js_identifier_node = new jejalyk::js::JsIdentifierNode();
      js_identifier_node->name = identifier_node->name;
      return success(subject, js_identifier_node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::IfNode>(node)) {
      const auto if_node = dynamic_cast<mavka::ast::IfNode*>(node);

      const auto condition_result = this->compile_node(if_node->condition);
      if (condition_result->error) {
        return condition_result;
      }
      const auto body_result = this->compile_body(if_node->body);
      if (body_result->error) {
        return body_result;
      }

      const auto else_body_result = this->compile_body(if_node->else_body);
      if (else_body_result->error) {
        return else_body_result;
      }

      const auto js_if_node = new jejalyk::js::JsIfNode();
      js_if_node->condition = condition_result->js_node;
      js_if_node->body = body_result->js_body;
      js_if_node->else_body = else_body_result->js_body;
      std::cout << "watafak " << if_node->else_body.size() << std::endl;

      return success(nullptr, js_if_node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::MethodDeclarationNode>(node)) {
      const auto method_declaration_node =
          dynamic_cast<mavka::ast::MethodDeclarationNode*>(node);
      const auto diia_scope = this->make_child();
      return this->compile_diia(diia_scope, method_declaration_node->async,
                                method_declaration_node->name,
                                method_declaration_node->generics,
                                method_declaration_node->params,
                                method_declaration_node->return_types, nullptr);
    }

    if (jejalyk::tools::instance_of<mavka::ast::MMLNode>(node)) {
      const auto mml_node = dynamic_cast<mavka::ast::MMLNode*>(node);
      return error_from_ast(node, "МРМ тимчасово недоступна.");
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupDiiaNode>(node)) {
      const auto mockup_diia_node =
          dynamic_cast<mavka::ast::MockupDiiaNode*>(node);
      const auto diia_scope = this->make_child();
      const auto diia_compilation_result = this->compile_diia(
          diia_scope, mockup_diia_node->async, mockup_diia_node->name,
          mockup_diia_node->generics, mockup_diia_node->params,
          mockup_diia_node->return_types, nullptr);
      if (diia_compilation_result->error) {
        return diia_compilation_result;
      }
      // todo: handle structure
      this->set_local(mockup_diia_node->name, diia_compilation_result->value);
      return success(diia_compilation_result->value,
                     new jejalyk::js::JsEmptyNode());
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupModuleNode>(node)) {
      const auto mockup_module_node =
          dynamic_cast<mavka::ast::MockupModuleNode*>(node);
      if (!this->get_is_async()) {
        return error_from_ast(
            node, "Модуль може бути визначений лише всередині іншого модуля.");
      }
      const auto module_compilation_result = this->compile_module(
          mockup_module_node->name, &mockup_module_node->elements);
      if (module_compilation_result->error) {
        return module_compilation_result;
      }
      this->set_local(mockup_module_node->name,
                      module_compilation_result->value);
      return success(module_compilation_result->value,
                     new jejalyk::js::JsEmptyNode());
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
      return success(structure_compilation_result->value,
                     new jejalyk::js::JsEmptyNode());
    }

    if (jejalyk::tools::instance_of<mavka::ast::MockupSubjectNode>(node)) {
      const auto mockup_subject_node =
          dynamic_cast<mavka::ast::MockupSubjectNode*>(node);

      if (this->has_local(mockup_subject_node->name)) {
        return error_from_ast(node, "Субʼєкт \"" + mockup_subject_node->name +
                                        "\" вже визначено.");
      }

      const auto types_result = this->compile_types(mockup_subject_node->types);
      if (types_result->error) {
        return types_result;
      }

      this->set_local(mockup_subject_node->name, types_result->value);

      return success(types_result->value, new jejalyk::js::JsEmptyNode());
    }

    if (jejalyk::tools::instance_of<mavka::ast::ModuleNode>(node)) {
      const auto module_node = dynamic_cast<mavka::ast::ModuleNode*>(node);
      if (!this->get_is_async()) {
        return error_from_ast(
            node, "Модуль може бути визначений лише всередині іншого модуля.");
      }
      const auto module_compilation_result =
          this->compile_module(module_node->name, &module_node->body);
      if (module_compilation_result->error) {
        return module_compilation_result;
      }
      this->set_local(module_node->name, module_compilation_result->value);
      return module_compilation_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NegativeNode>(node)) {
      const auto negative_node = dynamic_cast<mavka::ast::NegativeNode*>(node);

      const auto value_result = this->compile_node(negative_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto result = value_result->value->negative(this, node);
      if (result->error) {
        return result;
      }

      if (value_result->value->is_number(this)) {
        const auto js_negative_node = new jejalyk::js::JsNegativeNode();
        js_negative_node->value = value_result->js_node;
        result->js_node = js_negative_node;
      } else if (value_result->value->has_diia(this, "чародія_відʼємне")) {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_chain_node = new jejalyk::js::JsChainNode();
        js_chain_node->left = value_result->js_node;
        const auto js_chain_node_right = new jejalyk::js::JsIdentifierNode();
        js_chain_node_right->name = "чародія_відʼємне";
        js_chain_node->right = js_chain_node_right;
        js_call_node->value = js_chain_node;
        js_call_node->arguments = {};
        result->js_node = js_call_node;
      } else {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_id_node = new jejalyk::js::JsIdentifierNode();
        js_id_node->name = "мНегт";
        js_call_node->value = js_id_node;
        js_call_node->arguments = {value_result->js_node};
        result->js_node = js_call_node;
      }

      return result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NotNode>(node)) {
      const auto not_node = dynamic_cast<mavka::ast::NotNode*>(node);

      const auto value_result = this->compile_node(not_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto logical_structure_subject = this->get_root()->get("логічне");
      const auto logical_instance_result =
          logical_structure_subject->create_instance(this, {});
      if (logical_instance_result->error) {
        return logical_instance_result;
      }

      const auto js_not_node = new jejalyk::js::JsNotNode();
      js_not_node->value = value_result->js_node;
      logical_instance_result->js_node = js_not_node;

      return logical_instance_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::NumberNode>(node)) {
      const auto number_node = dynamic_cast<mavka::ast::NumberNode*>(node);
      const auto number_structure = this->get_root()->get("число");
      const auto number_result = number_structure->create_instance(this, {});
      const auto js_number_node = new jejalyk::js::JsNumberNode();
      js_number_node->value = number_node->value;
      return success(number_result->value, js_number_node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::PositiveNode>(node)) {
      const auto positive_node = dynamic_cast<mavka::ast::PositiveNode*>(node);

      const auto value_result = this->compile_node(positive_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto result = value_result->value->positive(this, node);
      if (result->error) {
        return result;
      }

      if (value_result->value->is_number(this)) {
        const auto js_negative_node = new jejalyk::js::JsPositiveNode();
        js_negative_node->value = value_result->js_node;
        result->js_node = js_negative_node;
      } else if (value_result->value->has_diia(this, "чародія_додатнє")) {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_chain_node = new jejalyk::js::JsChainNode();
        js_chain_node->left = value_result->js_node;
        const auto js_chain_node_right = new jejalyk::js::JsIdentifierNode();
        js_chain_node_right->name = "чародія_додатнє";
        js_chain_node->right = js_chain_node_right;
        js_call_node->value = js_chain_node;
        js_call_node->arguments = {};
        result->js_node = js_call_node;
      } else {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_id_node = new jejalyk::js::JsIdentifierNode();
        js_id_node->name = "мПозт";
        js_call_node->value = js_id_node;
        js_call_node->arguments = {value_result->js_node};
        result->js_node = js_call_node;
      }

      return result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::PostDecrementNode>(node)) {
      const auto post_decrement_node =
          dynamic_cast<mavka::ast::PostDecrementNode*>(node);

      return error_from_ast(node,
                            "Постфіксний декремент тимчасово недоступний.");
    }

    if (jejalyk::tools::instance_of<mavka::ast::PostIncrementNode>(node)) {
      const auto post_increment_node =
          dynamic_cast<mavka::ast::PostIncrementNode*>(node);

      return error_from_ast(node,
                            "Постфіксний інкремент тимчасово недоступний.");
    }

    if (jejalyk::tools::instance_of<mavka::ast::PreDecrementNode>(node)) {
      const auto pre_decrement_node =
          dynamic_cast<mavka::ast::PreDecrementNode*>(node);

      return error_from_ast(node,
                            "Префіксний декремент тимчасово недоступний.");

      const auto value_result = this->compile_node(pre_decrement_node->value);
      if (value_result->error) {
        return value_result;
      }

      return value_result->value->pre_decrement(this, node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::PreIncrementNode>(node)) {
      const auto pre_increment_node =
          dynamic_cast<mavka::ast::PreIncrementNode*>(node);

      return error_from_ast(node,
                            "Префіксний інкремент тимчасово недоступний.");
    }

    if (jejalyk::tools::instance_of<mavka::ast::ReturnNode>(node)) {
      const auto return_node = dynamic_cast<mavka::ast::ReturnNode*>(node);

      const auto value_result = this->compile_node(return_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto diia_object = this->get_diia_object();
      if (!diia_object) {
        return error_from_ast(node, "Неможливо вернути за межами дії.");
      }

      Subject* return_types = nullptr;
      if (diia_object->is_diia_async) {
        const auto awaiting_value =
            diia_object->return_types->get_awaiting_value(this, node);
        if (awaiting_value->error) {
          return awaiting_value;
        }
        return_types = awaiting_value->value;
      } else {
        return_types = diia_object->return_types;
      }

      if (!this->check_subjects(value_result->value, return_types)) {
        return error_from_ast(
            node, "Неправильний тип поверненого значення: очікується \"" +
                      return_types->types_string() + "\", отримано \"" +
                      value_result->value->types_string() + "\".");
      }

      const auto js_return_node = new jejalyk::js::JsReturnNode();
      js_return_node->value = value_result->js_node;

      value_result->js_node = js_return_node;

      return value_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::StringNode>(node)) {
      const auto string_node = dynamic_cast<mavka::ast::StringNode*>(node);
      // todo: interpolate
      const auto string_structure = this->get("текст");
      const auto string_result = string_structure->create_instance(this, {});
      const auto js_string_node = new jejalyk::js::JsStringNode();
      js_string_node->value = string_node->value;
      return success(string_result->value, js_string_node);
    }

    if (jejalyk::tools::instance_of<mavka::ast::StructureNode>(node)) {
      const auto structure_node =
          dynamic_cast<mavka::ast::StructureNode*>(node);
      const auto structure_compilation_result = this->compile_structure(
          structure_node->name, structure_node->generics, "", {},
          structure_node->params, structure_node->methods);
      if (structure_compilation_result->error) {
        return structure_compilation_result;
      }
      this->set_local(structure_node->name,
                      structure_compilation_result->value);
      return structure_compilation_result;
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

      const auto condition_result = this->compile_node(ternary_node->condition);
      if (condition_result->error) {
        return condition_result;
      }

      const auto result =
          this->compile_nodes({ternary_node->body, ternary_node->else_body});
      if (result->error) {
        return result;
      }

      const auto js_ternary_node = new jejalyk::js::JsTernaryNode();
      js_ternary_node->condition = condition_result->js_node;
      js_ternary_node->true_value = result->js_body->nodes[0];
      js_ternary_node->false_value = result->js_body->nodes[1];

      result->js_node = js_ternary_node;

      return result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TestNode>(node)) {
      const auto test_node = dynamic_cast<mavka::ast::TestNode*>(node);

      const auto left_result = this->compile_node(test_node->left);
      if (left_result->error) {
        return left_result;
      }
      const auto right_result = this->compile_node(test_node->right);
      if (right_result->error) {
        return right_result;
      }
      if (test_node->op == "&&" || test_node->op == "і") {
        const auto result =
            left_result->value->test_and(this, node, right_result->value);
        if (result->error) {
          return result;
        }

        const auto js_and_node = new jejalyk::js::JsTestNode();
        js_and_node->left = left_result->js_node;
        js_and_node->right = right_result->js_node;
        js_and_node->op = "&&";

        result->js_node = js_and_node;

        return result;
      }
      if (test_node->op == "||" || test_node->op == "або") {
        const auto result =
            left_result->value->test_or(this, node, right_result->value);
        if (result->error) {
          return result;
        }

        const auto js_or_node = new jejalyk::js::JsTestNode();
        js_or_node->left = left_result->js_node;
        js_or_node->right = right_result->js_node;
        js_or_node->op = "||";

        result->js_node = js_or_node;

        return result;
      }

      return error_from_ast(node,
                            "Невідома вказівка \"" + test_node->op + "\".");
    }

    if (jejalyk::tools::instance_of<mavka::ast::ThrowNode>(node)) {
      const auto throw_node = dynamic_cast<mavka::ast::ThrowNode*>(node);

      const auto value_result = this->compile_node(throw_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto js_throw_node = new jejalyk::js::JsThrowNode();
      js_throw_node->value = value_result->js_node;

      value_result->js_node = js_throw_node;

      return value_result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::TryNode>(node)) {
      const auto try_node = dynamic_cast<mavka::ast::TryNode*>(node);

      const auto body_result = this->compile_body(try_node->body);
      if (body_result->error) {
        return body_result;
      }

      const auto object_structure_subject = this->get_root()->get("обʼєкт");
      const auto object_instance_result =
          object_structure_subject->create_instance(this, {});
      if (object_instance_result->error) {
        return object_instance_result;
      }

      const auto catch_scope = this->make_child();
      catch_scope->is_async = this->is_async;
      catch_scope->set_local(try_node->name, object_instance_result->value);
      const auto catch_body_result =
          catch_scope->compile_body(try_node->catch_body);
      if (catch_body_result->error) {
        return catch_body_result;
      }

      const auto js_try_node = new jejalyk::js::JsTryNode();
      js_try_node->try_body = body_result->js_body;
      js_try_node->catch_body = catch_body_result->js_body;
      js_try_node->name = try_node->name;

      return success(nullptr, js_try_node);
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
              generic_type_subject->add_type(generic_generic_type_value);
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

      if (!this->get_is_async()) {
        return error_from_ast(
            node,
            "Вказівка \"чекати\" доступна лише в модулі або тривалій дії.");
      }

      const auto value_result = this->compile_node(wait_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto result = value_result->value->get_awaiting_value(this, node);

      const auto js_await_node = new jejalyk::js::JsAwaitNode();
      js_await_node->value = value_result->js_node;

      result->js_node = js_await_node;

      return result;
    }

    if (jejalyk::tools::instance_of<mavka::ast::WhileNode>(node)) {
      const auto while_node = dynamic_cast<mavka::ast::WhileNode*>(node);

      const auto condition_result = this->compile_node(while_node->condition);
      if (condition_result->error) {
        return condition_result;
      }

      const auto loop_scope = this->make_proxy();
      loop_scope->is_loop = true;

      const auto body_result = loop_scope->compile_body(while_node->body);
      if (body_result->error) {
        return body_result;
      }

      const auto js_while_node = new jejalyk::js::JsWhileNode();
      js_while_node->condition = condition_result->js_node;
      js_while_node->body = body_result->js_body;

      return success(nullptr, js_while_node);
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
      for (const auto& [variable_name, variable_subject] : this->variables) {
        var_names.push_back(variable_name);
      }
      result->js_body->nodes.insert(result->js_body->nodes.begin(),
                                    jejalyk::js::vars(var_names));
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

      const auto js_call_node = new jejalyk::js::JsCallNode();
      const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
      js_call_id_node->name = "мСтрк";
      js_call_node->value = js_call_id_node;
      js_call_node->arguments = {jejalyk::js::string(name),
                                 jejalyk::js::null()};

      const auto js_assign_node = new jejalyk::js::JsAssignNode();
      const auto js_id_node = new jejalyk::js::JsIdentifierNode();
      js_id_node->name = name;
      js_assign_node->identifier = js_id_node;
      js_assign_node->value = js_call_node;

      return success(structure_subject, js_assign_node);
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

    if (this->has_local(name)) {
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
        param->value = nullptr;
        param->variadic = param_node->variadic;

        diia_object->params.push_back(param);
      }
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