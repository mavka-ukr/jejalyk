#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_positive_node(Scope* scope,
                                mavka::ast::PositiveNode* positive_node) {
    const auto value_result = scope->compile_node(positive_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto result = value_result->value->magic_call(
        scope, positive_node, JJ_MAG_BW_POSITIVE, {}, {});
    if (result->error) {
      return result;
    }

    if (value_result->value->is_number(scope)) {
      // +а
      result->js_node = js::make_positive(value_result->js_node);
    } else {
      // а.чародія_додатнє()
      const auto js_chain = js::make_chain(value_result->js_node,
                                           js::make_id(JJ_MAG_BW_POSITIVE));
      result->js_node = js::make_call(js_chain, {});
    }

    return result;
  }
} // namespace jejalyk::typeinterpreter