#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_comparison_node(Scope* scope,
                                  mavka::ast::ComparisonNode* comparison_node) {
    const auto left_result = scope->compile_node(comparison_node->left);
    if (left_result->error) {
      return left_result;
    }
    const auto right_result = scope->compile_node(comparison_node->right);
    if (right_result->error) {
      return right_result;
    }

    Result* result;
    std::string magic_diia;
    std::string js_comp_symbol;
    std::string m_diia_name;

    if (comparison_node->op == "==" || comparison_node->op == "рівно") {
      result = left_result->value->comp_eq(scope, comparison_node,
                                           right_result->value);
      magic_diia = "чародія_рівно";
      js_comp_symbol = "==";
      m_diia_name = "мРівн";
    }
    if (comparison_node->op == "!=" || comparison_node->op == "не рівно") {
      result = left_result->value->comp_not_eq(scope, comparison_node,
                                               right_result->value);
      magic_diia = "чародія_не_рівно";
      js_comp_symbol = "!=";
      m_diia_name = "мНеРівн";
    }
    if (comparison_node->op == ">" || comparison_node->op == "більше") {
      result = left_result->value->comp_greater(scope, comparison_node,
                                                right_result->value);
      magic_diia = "чародія_більше";
      js_comp_symbol = ">";
      m_diia_name = "мБілш";
    }
    if (comparison_node->op == "<" || comparison_node->op == "менше") {
      result = left_result->value->comp_lesser(scope, comparison_node,
                                               right_result->value);
      magic_diia = "чародія_менше";
      js_comp_symbol = "<";
      m_diia_name = "мМенш";
    }
    if (comparison_node->op == ">=" || comparison_node->op == "не менше") {
      result = left_result->value->comp_greater_or_eq(scope, comparison_node,
                                                      right_result->value);
      magic_diia = "чародія_не_менше";
      js_comp_symbol = ">=";
      m_diia_name = "мНеМенш";
    }
    if (comparison_node->op == "<=" || comparison_node->op == "не більше") {
      result = left_result->value->comp_lesser_or_eq(scope, comparison_node,
                                                     right_result->value);
      magic_diia = "чародія_не_більше";
      js_comp_symbol = "<=";
      m_diia_name = "мНеБілш";
    }
    if (comparison_node->op == "є") {
      result = left_result->value->comp_is(scope, comparison_node,
                                           right_result->value);
      magic_diia = "чародія_є";
      m_diia_name = "мЄ";
    }
    if (comparison_node->op == "не є") {
      result = left_result->value->comp_is_not(scope, comparison_node,
                                               right_result->value);
      magic_diia = "чародія_не_є";
      m_diia_name = "мНеЄ";
    }
    if (comparison_node->op == "містить") {
      result = left_result->value->comp_contains(scope, comparison_node,
                                                 right_result->value);
      magic_diia = "чародія_містить";
      m_diia_name = "мМістить";
    }
    if (comparison_node->op == "не містить") {
      result = left_result->value->comp_contains_not(scope, comparison_node,
                                                     right_result->value);
      magic_diia = "чародія_не_містить";
      m_diia_name = "мНеМістить";
    }

    if (result != nullptr) {
      if (result->error) {
        return result;
      }

      if (magic_diia == "чародія_рівно") {
        const auto js_comparison_node = new jejalyk::js::JsComparisonNode();
        js_comparison_node->left = left_result->js_node;
        js_comparison_node->right = right_result->js_node;
        js_comparison_node->op = "==";
        return success(result->value, js_comparison_node);
      }

      if (magic_diia == "чародія_не_рівно") {
        const auto js_comparison_node = new jejalyk::js::JsComparisonNode();
        js_comparison_node->left = left_result->js_node;
        js_comparison_node->right = right_result->js_node;
        js_comparison_node->op = "!=";
        return success(result->value, js_comparison_node);
      }

      if (magic_diia == "чародія_є") {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
        js_call_id_node->name = "мЄ";
        js_call_node->value = js_call_id_node;
        js_call_node->arguments = {left_result->js_node, right_result->js_node};
        return success(result->value, js_call_node);
      }

      if (magic_diia == "чародія_не_є") {
        const auto js_call_node = new jejalyk::js::JsCallNode();
        const auto js_call_id_node = new jejalyk::js::JsIdentifierNode();
        js_call_id_node->name = "мЄ";
        js_call_node->value = js_call_id_node;
        js_call_node->arguments = {left_result->js_node, right_result->js_node};
        const auto js_not_node = new jejalyk::js::JsNotNode();
        js_not_node->value = js_call_node;
        return success(result->value, js_not_node);
      }

      if (left_result->value->is_number(scope) &&
          right_result->value->is_number(scope)) {
        if (js_comp_symbol.empty()) {
          return error_from_ast(comparison_node,
                                "[INTERNAL BUG] Невідома вказівка \"" +
                                    comparison_node->op + "\".");
        }
        const auto js_comparison_node = new jejalyk::js::JsComparisonNode();
        js_comparison_node->left = left_result->js_node;
        js_comparison_node->right = right_result->js_node;
        js_comparison_node->op = js_comp_symbol;
        return success(result->value, js_comparison_node);
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
        js_call_node->arguments = {left_result->js_node,
                                     right_result->js_node};
          return success(result->value, js_call_node);
        }

        return result;
      }

      return error_from_ast(
          comparison_node, "Невідома вказівка \"" + comparison_node->op + "\".");
  }
} // namespace typeinterpreter