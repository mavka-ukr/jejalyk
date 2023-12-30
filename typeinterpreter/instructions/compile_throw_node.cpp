#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_throw_node(Scope* scope, mavka::ast::ThrowNode* throw_node) {
    const auto value_result = scope->compile_node(throw_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto js_throw = new jejalyk::js::JsThrowNode();
    js_throw->value = value_result->js_node;

    value_result->js_node = js_throw;

    return value_result;
  }
} // namespace jejalyk::typeinterpreter