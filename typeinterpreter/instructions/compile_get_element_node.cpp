#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_get_element_node(
      Scope* scope,
      mavka::ast::GetElementNode* get_element_node) {
    const auto value_result = scope->compile_node(get_element_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto index_result = scope->compile_node(get_element_node->index);
    if (index_result->error) {
      return index_result;
    }

    const auto result = value_result->value->get_element(
        scope, get_element_node, index_result->value);
    if (result->error) {
      return result;
    }

    if (value_result->value->is_array(scope)) {
      const auto js_access_node = new jejalyk::js::JsAccessNode();
      js_access_node->value = value_result->js_node;
      js_access_node->index = index_result->js_node;
      result->js_node = js_access_node;
    } else if (value_result->value->has_diia(scope, "чародія_отримати")) {
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
      js_call_node->arguments = {value_result->js_node, index_result->js_node};
      result->js_node = js_call_node;
    }

    return result;
  }
} // namespace typeinterpreter