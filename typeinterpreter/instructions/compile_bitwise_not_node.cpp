#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_bitwise_not_node(
      Scope* scope,
      mavka::ast::BitwiseNotNode* bitwise_not_node) {
    const auto value_result = scope->compile_node(bitwise_not_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto result = value_result->value->bw_not(scope, bitwise_not_node);
    if (result->error) {
      return result;
    }

    if (value_result->value->is_number(scope)) {
      const auto js_negative_node = new jejalyk::js::JsNegativeNode();
      js_negative_node->value = value_result->js_node;
      result->js_node = js_negative_node;
    } else if (value_result->value->has_diia(scope, "чародія_дні")) {
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
} // namespace typeinterpreter