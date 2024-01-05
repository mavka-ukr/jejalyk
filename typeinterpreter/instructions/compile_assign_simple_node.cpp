#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_assign_simple_node(
      Scope* scope,
      mavka::ast::AssignSimpleNode* assign_simple_node) {
    const auto value_result = scope->compile_node(assign_simple_node->value);
    if (value_result->error) {
      return value_result;
    }

    if (value_result->value->is_method(scope)) {
      return scope->error(mavka::ast::get_ast_node(assign_simple_node->value),
                          "Не можна передавати дію обʼєкта як значення.");
    }

    if (assign_simple_node->op == "=" || assign_simple_node->op == "це") {
      if (scope->get_root()->has(assign_simple_node->name)) {
        return error_1(scope, assign_simple_node, assign_simple_node->name);
      }

      // а = б
      const auto js_assign_node = js::make_assign(
          js::make_id("м_" + assign_simple_node->name), value_result->js_node);

      if (assign_simple_node->types.empty()) {
        if (scope->has_local(assign_simple_node->name)) {
          const auto local_subject = scope->get_local(assign_simple_node->name);
          if (!scope->check_subjects(value_result->value, local_subject)) {
            return error_0(scope, assign_simple_node, assign_simple_node->name,
                           local_subject, value_result->value);
          }
          return success(local_subject, js_assign_node);
        } else {
          value_result->value->is_empty_value = false;
          scope->set_local(assign_simple_node->name, value_result->value);

          return success(value_result->value, js_assign_node);
        }
      } else {
        if (scope->has_local(assign_simple_node->name)) {
          return error_1(scope, assign_simple_node, assign_simple_node->name);
        }

        const auto types_result =
            scope->compile_types(assign_simple_node->types);
        if (types_result->error) {
          return types_result;
        }

        if (!scope->check_subjects(value_result->value, types_result->value)) {
          return error_0(scope, assign_simple_node, assign_simple_node->name,
                         types_result->value, value_result->value);
        }

        scope->set_local(assign_simple_node->name, types_result->value);

        return success(types_result->value, js_assign_node);
      }
    } else if (assign_simple_node->op == ":=") {
      const auto parent_scope = scope->get_parent();
      if (!parent_scope->has(assign_simple_node->name)) {
        return scope->error(
            assign_simple_node,
            "Субʼєкт \"" + assign_simple_node->name + "\" не визначено.");
      }
      assign_simple_node->op = "=";
      const auto parent_assign_result =
          compile_assign_simple_node(parent_scope, assign_simple_node);
      if (parent_assign_result->error) {
        return parent_assign_result;
      }
      parent_scope->put_setter(assign_simple_node->name);
      const auto js_call =
          js::make_call(js::make_id("мs" + assign_simple_node->name),
                        {value_result->js_node});
      return success(parent_assign_result->value, js_call);
    } else {
      std::string op;
      bool bitwise = false;
      if (assign_simple_node->op == "+=") {
        op = "+";
      } else if (assign_simple_node->op == "-=") {
        op = "-";
      } else if (assign_simple_node->op == "*=") {
        op = "*";
      } else if (assign_simple_node->op == "/=") {
        op = "/";
      } else if (assign_simple_node->op == "//=") {
        op = "//";
      } else if (assign_simple_node->op == "%=") {
        op = "%";
      } else if (assign_simple_node->op == "**=") {
        op = "**";
      } else if (assign_simple_node->op == "&=") {
        op = "&";
        bitwise = true;
      } else if (assign_simple_node->op == "|=") {
        op = "|";
        bitwise = true;
      } else if (assign_simple_node->op == "<<=") {
        op = "<<";
        bitwise = true;
      } else if (assign_simple_node->op == ">>=") {
        op = ">>";
        bitwise = true;
      } else if (assign_simple_node->op == "^=") {
        op = "^";
        bitwise = true;
      } else {
        return scope->error(
            assign_simple_node,
            "Невідома вказівка \"" + assign_simple_node->op + "\".");
      }

      const auto new_assign_simple_node = new mavka::ast::AssignSimpleNode();
      new_assign_simple_node->name = assign_simple_node->name;
      new_assign_simple_node->op = "=";
      const auto identifier_node = new mavka::ast::IdentifierNode();
      identifier_node->name = assign_simple_node->name;
      if (bitwise) {
        const auto bitwise_node = new mavka::ast::BitwiseNode();
        bitwise_node->left = mavka::ast::make_ast_some(identifier_node);
        bitwise_node->right = assign_simple_node->value;
        bitwise_node->op = op;
        new_assign_simple_node->value = mavka::ast::make_ast_some(bitwise_node);
      } else {
        const auto arithmetic_node = new mavka::ast::ArithmeticNode();
        arithmetic_node->left = mavka::ast::make_ast_some(identifier_node);
        arithmetic_node->right = assign_simple_node->value;
        arithmetic_node->op = op;
        new_assign_simple_node->value =
            mavka::ast::make_ast_some(arithmetic_node);
      }
      return compile_assign_simple_node(scope, new_assign_simple_node);
    }
  }
} // namespace jejalyk::typeinterpreter