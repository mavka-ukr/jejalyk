#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_test_node(Scope* scope, mavka::ast::TestNode* test_node) {
    const auto left_result = scope->compile_node(test_node->left);
    if (left_result->error) {
      return left_result;
    }
    const auto right_result = scope->compile_node(test_node->right);
    if (right_result->error) {
      return right_result;
    }
    if (test_node->op == "&&" || test_node->op == "і") {
      const auto result =
          left_result->value->test_and(scope, test_node, right_result->value);
      if (result->error) {
        return result;
      }

      const auto js_and_node = new jejalyk::js::JsTestNode();
      js_and_node->left = left_result->js_node;
      js_and_node->right = right_result->js_node;
      js_and_node->op = "&&";

      result->js_node = js_and_node;

      return result;
    }
    if (test_node->op == "||" || test_node->op == "або") {
      const auto result =
          left_result->value->test_or(scope, test_node, right_result->value);
      if (result->error) {
        return result;
      }

      const auto js_or_node = new jejalyk::js::JsTestNode();
      js_or_node->left = left_result->js_node;
      js_or_node->right = right_result->js_node;
      js_or_node->op = "||";

      result->js_node = js_or_node;

      return result;
    }

    return error_from_ast(test_node,
                          "Невідома вказівка \"" + test_node->op + "\".");
  }
} // namespace typeinterpreter