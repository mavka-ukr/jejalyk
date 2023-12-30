#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_assign_by_element_node(
      Scope* scope,
      mavka::ast::AssignByElementNode* assign_by_element_node) {
    const auto left_result = scope->compile_node(assign_by_element_node->left);
    if (left_result->error) {
      return left_result;
    }

    const auto element_result =
        scope->compile_node(assign_by_element_node->element);
    if (element_result->error) {
      return element_result;
    }

    const auto value_result =
        scope->compile_node(assign_by_element_node->value);
    if (value_result->error) {
      return value_result;
    }

    return left_result->value->set_element(scope, assign_by_element_node,
                                           element_result->value,
                                           value_result->value);
  }
} // namespace typeinterpreter