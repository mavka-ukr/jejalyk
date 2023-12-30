#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_assign_by_identifier_node(
      Scope* scope,
      mavka::ast::AssignByIdentifierNode* assign_by_identifier_node) {
    const auto left_result =
        scope->compile_node(assign_by_identifier_node->left);
    if (left_result->error) {
      return left_result;
    }

    const auto value_result =
        scope->compile_node(assign_by_identifier_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto result = left_result->value->set(
        scope, assign_by_identifier_node, assign_by_identifier_node->identifier,
        value_result->value);
    if (result->error) {
      return result;
    }

    // а.б = в
    const auto js_chain =
        js::make_chain(left_result->js_node,
                       js::make_id(assign_by_identifier_node->identifier));
    const auto js_assign = js::make_assign(js_chain, value_result->js_node);
    result->js_node = js_assign;
    return result;
  }
} // namespace jejalyk::typeinterpreter