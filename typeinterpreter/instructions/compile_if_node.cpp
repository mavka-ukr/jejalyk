#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_if_node(Scope* scope, mavka::ast::IfNode* if_node) {
    const auto condition_result = scope->compile_node(if_node->condition);
    if (condition_result->error) {
      return condition_result;
    }
    const auto body_result = scope->compile_body(if_node->body);
    if (body_result->error) {
      return body_result;
    }

    const auto else_body_result = scope->compile_body(if_node->else_body);
    if (else_body_result->error) {
      return else_body_result;
    }

    const auto js_if_node = new jejalyk::js::JsIfNode();
    js_if_node->condition = condition_result->js_node;
    js_if_node->body = body_result->js_body;
    js_if_node->else_body = else_body_result->js_body;

    return success(nullptr, js_if_node);
  }
} // namespace typeinterpreter