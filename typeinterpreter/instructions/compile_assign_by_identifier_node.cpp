#include "../typeinterpreter.h"

namespace typeinterpreter {
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

    return left_result->value->set(scope, assign_by_identifier_node,
                                   assign_by_identifier_node->identifier,
                                   value_result->value);
  }
} // namespace typeinterpreter