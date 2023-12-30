#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_positive_node(Scope* scope,
                                mavka::ast::PositiveNode* positive_node) {
    const auto value_result = scope->compile_node(positive_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto result = value_result->value->positive(scope, positive_node);
    if (result->error) {
      return result;
    }

    if (value_result->value->is_number(scope)) {
      // +а
      result->js_node = js::make_positive(value_result->js_node);
    } else if (value_result->value->has_diia(scope, "чародія_додатнє")) {
      // а.чародія_додатнє()
      const auto js_chain =
          js::make_chain(value_result->js_node, js::make_id("чародія_додатнє"));
      result->js_node = js::make_call(js_chain, {});
    } else {
      // мДодатнє(а)
      result->js_node =
          js::make_call(js::make_id("мДодатнє"), {value_result->js_node});
    }

    return result;
  }
} // namespace typeinterpreter