#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_if_node(Scope* scope, mavka::ast::IfNode* if_node) {
    const auto if_scope = scope->make_proxy();

    if (if_node->condition->ComparisonNode) {
      if (if_node->condition->ComparisonNode->op == "є") {
        const auto left_result =
            if_scope->compile_node(if_node->condition->ComparisonNode->left);
        if (left_result->error) {
          return left_result;
        }

        const auto right_result =
            if_scope->compile_node(if_node->condition->ComparisonNode->right);
        if (right_result->error) {
          return right_result;
        }

        if (!right_result->value->is_structure(scope) &&
            !right_result->value->is_object(scope)) {
          return scope->error(
              mavka::ast::get_ast_node(
                  if_node->condition->ComparisonNode->right),
              "Права частина вказівки \"як\" має бути структурою.");
        }

        const auto temp_left_subject_types = left_result->value->types;
        left_result->value->types =
            right_result->value->create_instance(scope, {})->value->types;

        const auto body_result = if_scope->compile_body(if_node->body);
        if (body_result->error) {
          return body_result;
        }

        left_result->value->types = temp_left_subject_types;

        const auto else_body_result =
            if_scope->compile_body(if_node->else_body);
        if (else_body_result->error) {
          return else_body_result;
        }

        const auto js_if_node = new js::JsIfNode();
        js_if_node->condition =
            js::make_call(js::make_id(JJ_F_IS),
                          {left_result->js_node, right_result->js_node});
        js_if_node->body = body_result->js_body;
        js_if_node->else_body = else_body_result->js_body;

        return success(nullptr, js_if_node);
      }
    }

    const auto condition_result = if_scope->compile_node(if_node->condition);
    if (condition_result->error) {
      return condition_result;
    }
    const auto body_result = if_scope->compile_body(if_node->body);
    if (body_result->error) {
      return body_result;
    }

    const auto else_body_result = if_scope->compile_body(if_node->else_body);
    if (else_body_result->error) {
      return else_body_result;
    }

    const auto js_if_node = new jejalyk::js::JsIfNode();
    js_if_node->condition = condition_result->js_node;
    js_if_node->body = body_result->js_body;
    js_if_node->else_body = else_body_result->js_body;

    return success(nullptr, js_if_node);
  }
} // namespace jejalyk::typeinterpreter