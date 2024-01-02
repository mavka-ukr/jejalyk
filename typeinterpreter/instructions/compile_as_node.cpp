#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_as_node(Scope* scope, mavka::ast::AsNode* as_node) {
    const auto left_result = scope->compile_node(as_node->left);
    if (left_result->error) {
      return left_result;
    }

    const auto right_result = scope->compile_node(as_node->right);
    if (right_result->error) {
      return right_result;
    }

    if (!scope->check_subjects(right_result->value, left_result->value)) {
      return scope->error(
          as_node, "Неможливо застосувати вказівку \"як " +
                       right_result->value->types_string() + "\" до типу \"" +
                       left_result->value->types_string() + "\".");
    }

    return success(right_result->value, left_result->js_node);
  }
} // namespace jejalyk::typeinterpreter