#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_arithmetic_node(Scope* scope,
                                  mavka::ast::ArithmeticNode* arithmetic_node) {
    const auto left_result = scope->compile_node(arithmetic_node->left);
    if (left_result->error) {
      return left_result;
    }
    const auto right_result = scope->compile_node(arithmetic_node->right);
    if (right_result->error) {
      return right_result;
    }

    const auto js_arithmetic_node = new jejalyk::js::JsArithmeticNode();

    Result* result;
    std::string magic_diia;
    std::string m_diia_name;

    if (arithmetic_node->op == "+") {
      result =
          left_result->value->plus(scope, arithmetic_node, right_result->value);
      magic_diia = "чародія_додати";
      m_diia_name = "мДодати";
    }
    if (arithmetic_node->op == "-") {
      result = left_result->value->minus(scope, arithmetic_node,
                                         right_result->value);
      magic_diia = "чародія_відняти";
      m_diia_name = "мВідняти";
    }
    if (arithmetic_node->op == "*") {
      result = left_result->value->multiply(scope, arithmetic_node,
                                            right_result->value);
      magic_diia = "чародія_помножити";
      m_diia_name = "мПомножити";
    }
    if (arithmetic_node->op == "/") {
      result = left_result->value->divide(scope, arithmetic_node,
                                          right_result->value);
      magic_diia = "чародія_поділити";
      m_diia_name = "мПоділити";
    }
    if (arithmetic_node->op == "%") {
      result = left_result->value->divmod(scope, arithmetic_node,
                                          right_result->value);
      magic_diia = "чародія_остача";
      m_diia_name = "мОстача";
    }
    if (arithmetic_node->op == "//") {
      result = left_result->value->divdiv(scope, arithmetic_node,
                                          right_result->value);
      magic_diia = "чародія_частка";
      m_diia_name = "мЧастка";
    }
    if (arithmetic_node->op == "**") {
      result =
          left_result->value->pow(scope, arithmetic_node, right_result->value);
      magic_diia = "чародія_степінь";
      m_diia_name = "мСтепінь";
    }

    if (result != nullptr) {
      if (result->error) {
        return result;
      }

      if (left_result->value->is_number(scope) &&
          right_result->value->is_number(scope)) {
        if (arithmetic_node->op == "//") {
          const auto js_chain_node = new jejalyk::js::JsChainNode();
          js_chain_node->left = jejalyk::js::id("Math");
          js_chain_node->right = jejalyk::js::id("floor");
          const auto js_call_node = new jejalyk::js::JsCallNode();
          js_call_node->value = js_chain_node;
          const auto js_call_arithmetic = new jejalyk::js::JsArithmeticNode();
          js_call_arithmetic->left = left_result->js_node;
          js_call_arithmetic->right = right_result->js_node;
          js_call_arithmetic->op = "/";
          js_call_node->arguments = {js_call_arithmetic};
          return success(result->value, js_call_node);
        } else {
          js_arithmetic_node->left = left_result->js_node;
          js_arithmetic_node->right = right_result->js_node;
          js_arithmetic_node->op = arithmetic_node->op;
          return success(result->value, js_arithmetic_node);
        }
      }

      if (arithmetic_node->op == "+") {
        if (left_result->value->is_string(scope) &&
            right_result->value->is_string(scope)) {
          js_arithmetic_node->left = left_result->js_node;
          js_arithmetic_node->right = right_result->js_node;
          js_arithmetic_node->op = "+";
          return success(result->value, js_arithmetic_node);
        }
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

      return error_from_ast(
          arithmetic_node, "Невідома вказівка \"" + arithmetic_node->op + "\".");
  }
} // namespace typeinterpreter