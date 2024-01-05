#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_bitwise_node(Scope* scope,
                               mavka::ast::BitwiseNode* bitwise_node) {
    const auto left_result = scope->compile_node(bitwise_node->left);
    if (left_result->error) {
      return left_result;
    }
    const auto right_result = scope->compile_node(bitwise_node->right);
    if (right_result->error) {
      return right_result;
    }

    Result* result = nullptr;
    std::string magic_diia;

    if (bitwise_node->op == "^") {
      magic_diia = JJ_MAG_BW_XOR;
    }
    if (bitwise_node->op == "|") {
      magic_diia = JJ_MAG_BW_AND;
    }
    if (bitwise_node->op == "&") {
      magic_diia = JJ_MAG_BW_OR;
    }
    if (bitwise_node->op == "<<") {
      magic_diia = JJ_MAG_BW_SHIFT_LEFT;
    }
    if (bitwise_node->op == ">>") {
      magic_diia = JJ_MAG_BW_SHIFT_RIGHT;
    }

    result = left_result->value->magic_call(scope, bitwise_node, magic_diia, {},
                                            {right_result->value});

    if (result != nullptr) {
      if (result->error) {
        return result;
      }

      if (left_result->value->is_number(scope) &&
          right_result->value->is_number(scope)) {
        // а ^ б
        return success(
            result->value,
            js::make_arithmetic(left_result->js_node, bitwise_node->op,
                                right_result->js_node));
      }

      // а.чародія_вабо(б)
      const auto js_chain =
          js::make_chain(left_result->js_node, js::make_id(magic_diia));
      const auto js_call = js::make_call(js_chain, {right_result->js_node});
      return success(result->value, js_call);
    }

    return scope->error(bitwise_node,
                        "Невідома вказівка \"" + bitwise_node->op + "\".");
  }
} // namespace typeinterpreter