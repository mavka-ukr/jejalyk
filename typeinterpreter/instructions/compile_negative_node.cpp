#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_negative_node(Scope* scope,
                                mavka::ast::NegativeNode* negative_node) {
    const auto value_result = scope->compile_node(negative_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto result = value_result->value->negative(scope, negative_node);
    if (result->error) {
      return result;
    }

    if (value_result->value->is_number(scope)) {
      // -а
      result->js_node = js::make_negative(value_result->js_node);
    } else if (value_result->value->has_diia(scope, "чародія_відʼємне")) {
      // а.чародія_відʼємне()
      const auto js_chain = js::make_chain(value_result->js_node,
                                           js::make_id("чародія_відʼємне"));
      result->js_node = js::make_call(js_chain, {});
    } else {
      // мВідʼємне(а)
      result->js_node =
          js::make_call(js::make_id("мВідʼємне"), {value_result->js_node});
    }

    return result;
  }
} // namespace typeinterpreter