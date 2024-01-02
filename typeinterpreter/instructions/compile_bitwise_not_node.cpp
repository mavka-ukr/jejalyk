#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
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
      // ~а
      result->js_node = js::make_negative(value_result->js_node);
    } else if (value_result->value->has_diia(scope, "чародія_дні")) {
      // а.чародія_дні()
      const auto js_chain =
          js::make_chain(value_result->js_node, js::make_id("чародія_дні"));
      result->js_node = js::make_call(js_chain, {});
    } else {
      // мДні(а)
      result->js_node =
          js::make_call(js::make_id(JJ_F_BW_NOT), {value_result->js_node});
    }

    return result;
  }
} // namespace jejalyk::typeinterpreter