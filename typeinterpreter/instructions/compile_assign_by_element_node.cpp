#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_assign_by_element_node(
      Scope* scope,
      mavka::ast::AssignByElementNode* assign_by_element_node) {
    const auto left_result = scope->compile_node(assign_by_element_node->left);
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

    const auto result = left_result->value->set_element(
        scope, assign_by_element_node, element_result->value,
        value_result->value);
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
    } else if (left_result->value->has_diia(scope, "чародія_покласти")) {
      // а.чародія_покласти(1, б)
      const auto js_chain =
          js::make_chain(left_result->js_node, js::make_id("чародія_покласти"));
      const auto js_call = js::make_call(
          js_chain, {element_result->js_node, value_result->js_node});
      result->js_node = js_call;
      return result;
    } else {
      // мПокласти(а, 1, б)
      const auto js_call =
          js::make_call(js::make_id("мПокласти"),
                        {left_result->js_node, element_result->js_node,
                         value_result->js_node});
      result->js_node = js_call;
      return result;
    }
  }
} // namespace jejalyk::typeinterpreter