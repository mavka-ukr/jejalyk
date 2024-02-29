#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_wait_node(Scope* scope, mavka::ast::WaitNode* wait_node) {
    if (!scope->get_is_async()) {
      return scope->error(
          wait_node,
          "Вказівка \"чекати\" доступна лише в модулі або тривалій дії.");
    }

    const auto value_result = scope->compile_node(wait_node->value);
    if (value_result->error) {
      return value_result;
    }

    if (scope->get_options()->is_strict_mode()) {
      const auto result =
          value_result->value->get_awaiting_value(scope, wait_node);

      // await а
      const auto js_await = new js::JsAwaitNode();
      js_await->value = value_result->js_node;

      result->js_node = js_await;

      return result;
    } else {
      const auto js_await = new js::JsAwaitNode();
      js_await->value = value_result->js_node;

      const auto js_node = js_await;

      return success(value_result->value, js_node);
    }
  }
} // namespace typeinterpreter