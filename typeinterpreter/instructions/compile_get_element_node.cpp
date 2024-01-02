#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
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
      // а[б]
      const auto js_access =
          js::make_access(value_result->js_node, index_result->js_node);
      result->js_node = js_access;
    } else if (value_result->value->has_diia(scope, "чародія_отримати")) {
      // а.чародія_отримати(б)
      const auto js_chain = js::make_chain(value_result->js_node,
                                           js::make_id("чародія_отримати"));
      const auto js_call = js::make_call(js_chain, {index_result->js_node});
      result->js_node = js_call;
    } else {
      // мОтримати(а, б)
      result->js_node =
          js::make_call(js::make_id(JJ_F_GET_ELEMENT),
                        {value_result->js_node, index_result->js_node});
    }

    return result;
  }
} // namespace typeinterpreter