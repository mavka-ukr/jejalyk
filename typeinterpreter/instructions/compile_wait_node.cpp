#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_wait_node(Scope* scope, mavka::ast::WaitNode* wait_node) {
    if (!scope->get_is_async()) {
      return error_from_ast(
          wait_node,
          "Вказівка \"чекати\" доступна лише в модулі або тривалій дії.");
    }

    const auto value_result = scope->compile_node(wait_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto result =
        value_result->value->get_awaiting_value(scope, wait_node);

    const auto js_await = new js::JsAwaitNode();
    js_await->value = value_result->js_node;

    result->js_node = js_await;

    return result;
  }
} // namespace typeinterpreter