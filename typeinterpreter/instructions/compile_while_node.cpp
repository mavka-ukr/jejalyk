#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_while_node(Scope* scope, mavka::ast::WhileNode* while_node) {
    const auto condition_result = scope->compile_node(while_node->condition);
    if (condition_result->error) {
      return condition_result;
    }

    const auto loop_scope = scope->make_proxy();
    loop_scope->is_loop = true;

    const auto body_result = loop_scope->compile_body(while_node->body);
    if (body_result->error) {
      return body_result;
    }

    const auto js_while = new js::JsWhileNode();
    js_while->condition = condition_result->js_node;
    js_while->body = body_result->js_body;

    return success(nullptr, js_while);
  }
} // namespace jejalyk::typeinterpreter