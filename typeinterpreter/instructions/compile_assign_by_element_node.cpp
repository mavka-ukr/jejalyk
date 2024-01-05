#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_assign_by_element_node(
      Scope* scope,
      mavka::ast::AssignByElementNode* assign_by_element_node) {
    if (assign_by_element_node->op == "=" ||
        assign_by_element_node->op == "це") {
      const auto left_result =
          scope->compile_node(assign_by_element_node->left);
      if (left_result->error) {
        return left_result;
      }

      const auto element_result =
          scope->compile_node(assign_by_element_node->element);
      if (element_result->error) {
        return element_result;
      }

      const auto value_result =
          scope->compile_node(assign_by_element_node->value);
      if (value_result->error) {
        return value_result;
      }

      if (value_result->value->is_method(scope)) {
        return scope->error(
            mavka::ast::get_ast_node(assign_by_element_node->value),
            "Не можна передавати дію обʼєкта як значення.");
      }

      const auto result = left_result->value->magic_call(
          scope, assign_by_element_node, JJ_MAG_PUT_ELEMENT, {},
          {element_result->value, value_result->value});
      if (result->error) {
        return result;
      }

      if (left_result->value->is_array(scope)) {
        // а[1] = б
        const auto js_chain =
            js::make_element(left_result->js_node, element_result->js_node);
        const auto js_assign = js::make_assign(js_chain, value_result->js_node);
        result->js_node = js_assign;
        return result;
      }

      // а.чародія_покласти(1, б)
      const auto js_chain =
          js::make_chain(left_result->js_node, js::make_id(JJ_MAG_PUT_ELEMENT));
      const auto js_call = js::make_call(
          js_chain, {element_result->js_node, value_result->js_node});
      result->js_node = js_call;
      return result;
    } else {
      std::string op;
      bool bitwise = false;
      if (assign_by_element_node->op == "+=") {
        op = "+";
      } else if (assign_by_element_node->op == "-=") {
        op = "-";
      } else if (assign_by_element_node->op == "*=") {
        op = "*";
      } else if (assign_by_element_node->op == "/=") {
        op = "/";
      } else if (assign_by_element_node->op == "//=") {
        op = "//";
      } else if (assign_by_element_node->op == "%=") {
        op = "%";
      } else if (assign_by_element_node->op == "**=") {
        op = "**";
      } else if (assign_by_element_node->op == "&=") {
        op = "&";
        bitwise = true;
      } else if (assign_by_element_node->op == "|=") {
        op = "|";
        bitwise = true;
      } else if (assign_by_element_node->op == "<<=") {
        op = "<<";
        bitwise = true;
      } else if (assign_by_element_node->op == ">>=") {
        op = ">>";
        bitwise = true;
      } else if (assign_by_element_node->op == "^=") {
        op = "^";
        bitwise = true;
      } else {
        return scope->error(
            assign_by_element_node,
            "Невідома вказівка \"" + assign_by_element_node->op + "\".");
      }

      const auto new_assign_by_element_node =
          new mavka::ast::AssignByElementNode();
      new_assign_by_element_node->op = "=";
      new_assign_by_element_node->left = assign_by_element_node->left;
      new_assign_by_element_node->element = assign_by_element_node->element;
      const auto get_element_node = new mavka::ast::GetElementNode();
      get_element_node->value = assign_by_element_node->left;
      get_element_node->index = assign_by_element_node->element;
      if (bitwise) {
        const auto bitwise_node = new mavka::ast::BitwiseNode();
        bitwise_node->left = mavka::ast::make_ast_some(get_element_node);
        bitwise_node->right = assign_by_element_node->value;
        bitwise_node->op = op;
        new_assign_by_element_node->value =
            mavka::ast::make_ast_some(bitwise_node);
      } else {
        const auto arithmetic_node = new mavka::ast::ArithmeticNode();
        arithmetic_node->left = mavka::ast::make_ast_some(get_element_node);
        arithmetic_node->right = assign_by_element_node->value;
        arithmetic_node->op = op;
        new_assign_by_element_node->value =
            mavka::ast::make_ast_some(arithmetic_node);
      }
      return compile_assign_by_element_node(scope, new_assign_by_element_node);
    }
  }
} // namespace jejalyk::typeinterpreter