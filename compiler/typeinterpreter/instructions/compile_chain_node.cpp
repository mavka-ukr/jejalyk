#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_chain_node(Scope* scope, mavka::ast::ChainNode* chain_node) {
    if (jejalyk::tools::instance_of<mavka::ast::IdentifierNode>(
            chain_node->right)) {
      const auto left_result = scope->compile_node(chain_node->left);
      if (left_result->error) {
        return left_result;
      }

      const auto right_identifier_node =
          dynamic_cast<mavka::ast::IdentifierNode*>(chain_node->right);

      if (!left_result->value->has(right_identifier_node->name)) {
        return error_2(chain_node, right_identifier_node->name,
                       left_result->value);
      }

      const auto subject_result =
          left_result->value->get(right_identifier_node->name);
      if (subject_result->error) {
        return subject_result;
      }

      const auto js_chain_node = new jejalyk::js::JsChainNode();
      js_chain_node->left = left_result->js_node;
      const auto js_chain_node_right = new jejalyk::js::JsIdentifierNode();
      js_chain_node_right->name = right_identifier_node->name;
      js_chain_node->right = js_chain_node_right;

      return success(subject_result->value, js_chain_node);
    } else {
      const auto get_element_node = new mavka::ast::GetElementNode();
      get_element_node->start_line = chain_node->start_line;
      get_element_node->start_column = chain_node->start_column;
      get_element_node->end_line = chain_node->end_line;
      get_element_node->end_column = chain_node->end_column;
      get_element_node->value = chain_node->left;
      get_element_node->index = chain_node->right;
      return scope->compile_node(get_element_node);
    }
  }
} // namespace typeinterpreter