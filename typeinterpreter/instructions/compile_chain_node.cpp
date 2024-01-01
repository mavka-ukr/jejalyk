#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_chain_node(Scope* scope, mavka::ast::ChainNode* chain_node) {
    if (const auto right_identifier_node = chain_node->right->IdentifierNode) {
      const auto left_result = scope->compile_node(chain_node->left);
      if (left_result->error) {
        return left_result;
      }

      if (!left_result->value->has(scope, right_identifier_node->name)) {
        return error_2(chain_node, right_identifier_node->name,
                       left_result->value);
      }

      const auto subject_result =
          left_result->value->get(scope, right_identifier_node->name);
      if (subject_result->error) {
        return subject_result;
      }

      // а.б
      const auto js_chain = js::make_chain(
          left_result->js_node, js::make_id(right_identifier_node->name));

      return success(subject_result->value, js_chain);
    } else {
      const auto get_element_node = new mavka::ast::GetElementNode();
      get_element_node->start_line = chain_node->start_line;
      get_element_node->start_column = chain_node->start_column;
      get_element_node->end_line = chain_node->end_line;
      get_element_node->end_column = chain_node->end_column;
      get_element_node->value = chain_node->left;
      get_element_node->index = chain_node->right;
      return scope->compile_node(mavka::ast::make_ast_some(get_element_node));
    }
  }
} // namespace jejalyk::typeinterpreter