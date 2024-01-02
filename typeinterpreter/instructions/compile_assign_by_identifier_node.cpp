#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_assign_by_identifier_node(
      Scope* scope,
      mavka::ast::AssignByIdentifierNode* assign_by_identifier_node) {
    if (assign_by_identifier_node->op == "=" ||
        assign_by_identifier_node->op == "це") {
      const auto left_result =
          scope->compile_node(assign_by_identifier_node->left);
      if (left_result->error) {
        return left_result;
      }

      const auto value_result =
          scope->compile_node(assign_by_identifier_node->value);
      if (value_result->error) {
        return value_result;
      }

      const auto result = left_result->value->set(
          scope, assign_by_identifier_node,
          assign_by_identifier_node->identifier, value_result->value);
      if (result->error) {
        return result;
      }

      // а.б = в
      const auto js_chain =
          js::make_chain(left_result->js_node,
                         js::make_id(assign_by_identifier_node->identifier));
      const auto js_assign = js::make_assign(js_chain, value_result->js_node);
      result->js_node = js_assign;
      return result;
    } else {
      std::string op;
      bool bitwise = false;
      if (assign_by_identifier_node->op == "+=") {
        op = "+";
      } else if (assign_by_identifier_node->op == "-=") {
        op = "-";
      } else if (assign_by_identifier_node->op == "*=") {
        op = "*";
      } else if (assign_by_identifier_node->op == "/=") {
        op = "/";
      } else if (assign_by_identifier_node->op == "//=") {
        op = "//";
      } else if (assign_by_identifier_node->op == "%=") {
        op = "%";
      } else if (assign_by_identifier_node->op == "**=") {
        op = "**";
      } else if (assign_by_identifier_node->op == "&=") {
        op = "&";
        bitwise = true;
      } else if (assign_by_identifier_node->op == "|=") {
        op = "|";
        bitwise = true;
      } else if (assign_by_identifier_node->op == "<<=") {
        op = "<<";
        bitwise = true;
      } else if (assign_by_identifier_node->op == ">>=") {
        op = ">>";
        bitwise = true;
      } else if (assign_by_identifier_node->op == "^=") {
        op = "^";
        bitwise = true;
      } else {
        return scope->error(
            assign_by_identifier_node,
            "Невідома вказівка \"" + assign_by_identifier_node->op + "\".");
      }

      const auto new_assign_by_identifier_node =
          new mavka::ast::AssignByIdentifierNode();
      new_assign_by_identifier_node->op = "=";
      new_assign_by_identifier_node->left = assign_by_identifier_node->left;
      new_assign_by_identifier_node->identifier =
          assign_by_identifier_node->identifier;
      const auto chain_node = new mavka::ast::ChainNode();
      const auto identifier_node = new mavka::ast::IdentifierNode();
      identifier_node->name = assign_by_identifier_node->identifier;
      chain_node->left = assign_by_identifier_node->left;
      chain_node->right = mavka::ast::make_ast_some(identifier_node);
      if (bitwise) {
        const auto bitwise_node = new mavka::ast::BitwiseNode();
        bitwise_node->left = mavka::ast::make_ast_some(chain_node);
        bitwise_node->right = assign_by_identifier_node->value;
        bitwise_node->op = op;
        new_assign_by_identifier_node->value =
            mavka::ast::make_ast_some(bitwise_node);
      } else {
        const auto arithmetic_node = new mavka::ast::ArithmeticNode();
        arithmetic_node->left = mavka::ast::make_ast_some(chain_node);
        arithmetic_node->right = assign_by_identifier_node->value;
        arithmetic_node->op = op;
        new_assign_by_identifier_node->value =
            mavka::ast::make_ast_some(arithmetic_node);
      }
      return compile_assign_by_identifier_node(scope,
                                               new_assign_by_identifier_node);
    }
  }
} // namespace jejalyk::typeinterpreter