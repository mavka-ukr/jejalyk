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
    std::string m_diia_name;

    if (bitwise_node->op == "^") {
      result =
          left_result->value->bw_xor(scope, bitwise_node, right_result->value);
      magic_diia = "чародія_вабо";
      m_diia_name = JJ_F_BW_XOR;
    }
    if (bitwise_node->op == "|") {
      result =
          left_result->value->bw_or(scope, bitwise_node, right_result->value);
      magic_diia = "чародія_ді";
      m_diia_name = JJ_F_BW_AND;
    }
    if (bitwise_node->op == "&") {
      result =
          left_result->value->bw_and(scope, bitwise_node, right_result->value);
      magic_diia = "чародія_дабо";
      m_diia_name = JJ_F_BW_OR;
    }
    if (bitwise_node->op == "<<") {
      result = left_result->value->bw_shift_left(scope, bitwise_node,
                                                 right_result->value);
      magic_diia = "чародія_вліво";
      m_diia_name = JJ_F_BW_SHIFT_LEFT;
    }
    if (bitwise_node->op == ">>") {
      result = left_result->value->bw_shift_right(scope, bitwise_node,
                                                  right_result->value);
      magic_diia = "чародія_вправо";
      m_diia_name = JJ_F_BW_SHIFT_RIGHT;
    }

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

      if (left_result->value->has_diia(scope, magic_diia)) {
        // а.чародія_вабо(б)
        const auto js_chain =
            js::make_chain(left_result->js_node, js::make_id(magic_diia));
        const auto js_call = js::make_call(js_chain, {right_result->js_node});
        return success(result->value, js_call);
      } else {
        // мВабо(а, б)
        const auto js_call =
            js::make_call(js::make_id(m_diia_name),
                          {left_result->js_node, right_result->js_node});
        return success(result->value, js_call);
      }
    }

    return scope->error(bitwise_node,
                        "Невідома вказівка \"" + bitwise_node->op + "\".");
  }
} // namespace typeinterpreter