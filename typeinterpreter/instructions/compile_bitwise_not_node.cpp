#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_bitwise_not_node(
      Scope* scope,
      mavka::ast::BitwiseNotNode* bitwise_not_node) {
    const auto value_result = scope->compile_node(bitwise_not_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto result = value_result->value->magic_call(scope, bitwise_not_node,
                                                        JJ_MAG_BW_NOT, {}, {});
    if (result->error) {
      return result;
    }

    if (value_result->value->is_number(scope)) {
      // ~а
      result->js_node = js::make_negative(value_result->js_node);
    } else {
      // а.чародія_дні()
      const auto js_chain =
          js::make_chain(value_result->js_node, js::make_id(JJ_MAG_BW_NOT));
      result->js_node = js::make_call(js_chain, {});
    }

    return result;
  }
} // namespace jejalyk::typeinterpreter