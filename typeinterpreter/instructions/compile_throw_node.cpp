#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_throw_node(Scope* scope, mavka::ast::ThrowNode* throw_node) {
    const auto value_result = scope->compile_node(throw_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto value_string = js::stringify(value_result->js_node);

    const auto js_throw = new js::JsThrowNode();
    js_throw->value = js::make_raw("new Падіння(" + value_string + ")");

    value_result->js_node = js_throw;

    return value_result;
  }
} // namespace jejalyk::typeinterpreter