#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_ternary_node(Scope* scope,
                               mavka::ast::TernaryNode* ternary_node) {
    const auto condition_result = scope->compile_node(ternary_node->condition);
    if (condition_result->error) {
      return condition_result;
    }

    const auto result =
        scope->compile_nodes({ternary_node->body, ternary_node->else_body});
    if (result->error) {
      return result;
    }

    const auto js_ternary_node = new jejalyk::js::JsTernaryNode();
    js_ternary_node->condition = condition_result->js_node;
    js_ternary_node->true_value = result->js_body->nodes[0];
    js_ternary_node->false_value = result->js_body->nodes[1];

    result->js_node = js_ternary_node;

    return result;
  }
} // namespace typeinterpreter