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

    const auto js_arithmetic_node = new jejalyk::js::JsArithmeticNode();

    Result* result = nullptr;
    std::string magic_diia;
    std::string m_diia_name;

    if (bitwise_node->op == "^") {
      result =
          left_result->value->bw_xor(scope, bitwise_node, right_result->value);
      magic_diia = "чародія_вабо";
      m_diia_name = "мВабо";
    }
    if (bitwise_node->op == "|") {
      result =
          left_result->value->bw_or(scope, bitwise_node, right_result->value);
      magic_diia = "чародія_ді";
      m_diia_name = "мДі";
    }
    if (bitwise_node->op == "&") {
      result =
          left_result->value->bw_and(scope, bitwise_node, right_result->value);
      magic_diia = "чародія_дабо";
      m_diia_name = "мДабо";
    }
    if (bitwise_node->op == "<<") {
      result = left_result->value->bw_shift_left(scope, bitwise_node,
                                                 right_result->value);
      magic_diia = "чародія_вліво";
      m_diia_name = "мВліво";
    }
    if (bitwise_node->op == ">>") {
      result = left_result->value->bw_shift_right(scope, bitwise_node,
                                                  right_result->value);
      magic_diia = "чародія_вправо";
      m_diia_name = "мВправо";
    }

    if (result != nullptr) {
      if (result->error) {
        return result;
      }

      if (left_result->value->is_number(scope) &&
          right_result->value->is_number(scope)) {
        js_arithmetic_node->left = left_result->js_node;
        js_arithmetic_node->right = right_result->js_node;
        js_arithmetic_node->op = bitwise_node->op;
        return success(result->value, js_arithmetic_node);
      }

      if (left_result->value->has_diia(scope, magic_diia)) {
        const auto js_chain_node = new jejalyk::js::JsChainNode();
        js_chain_node->left = left_result->js_node;
        const auto js_chain_node_right = new jejalyk::js::JsIdentifierNode();
        js_chain_node_right->name = magic_diia;
        js_chain_node->right = js_chain_node_right;
        const auto js_call_node = new jejalyk::js::JsCallNode();
        js_call_node->value = js_chain_node;
        js_call_node->arguments = {right_result->js_node};
        result->js_node = js_call_node;
        return success(result->value, js_chain_node);
      } else {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_id_node = new jejalyk::js::JsIdentifierNode();
        js_id_node->name = m_diia_name;
        js_call_node->value = js_id_node;
        js_call_node->arguments = {left_result->js_node, right_result->js_node};
        return success(result->value, js_call_node);
      }

      return result;
    }

    return error_from_ast(bitwise_node,
                          "Невідома вказівка \"" + bitwise_node->op + "\".");
  }
} // namespace typeinterpreter