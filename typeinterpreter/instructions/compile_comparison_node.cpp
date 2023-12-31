#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
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

    Result* result = nullptr;
    std::string magic_diia;
    std::string js_comp_symbol;
    std::string m_diia_name;

    if (comparison_node->op == "==" || comparison_node->op == "рівно") {
      result = left_result->value->comp_eq(scope, comparison_node,
                                           right_result->value);
      magic_diia = "";
      js_comp_symbol = "==";
      m_diia_name = "";
    }
    if (comparison_node->op == "!=" || comparison_node->op == "не рівно") {
      result = left_result->value->comp_not_eq(scope, comparison_node,
                                               right_result->value);
      magic_diia = "";
      js_comp_symbol = "!=";
      m_diia_name = "";
    }
    if (comparison_node->op == ">" || comparison_node->op == "більше") {
      result = left_result->value->comp_greater(scope, comparison_node,
                                                right_result->value);
      magic_diia = "чародія_більше";
      js_comp_symbol = ">";
      m_diia_name = "мБільше";
    }
    if (comparison_node->op == "<" || comparison_node->op == "менше") {
      result = left_result->value->comp_lesser(scope, comparison_node,
                                               right_result->value);
      magic_diia = "чародія_менше";
      js_comp_symbol = "<";
      m_diia_name = "мМенше";
    }
    if (comparison_node->op == ">=" || comparison_node->op == "не менше") {
      result = left_result->value->comp_greater_or_eq(scope, comparison_node,
                                                      right_result->value);
      magic_diia = "чародія_не_менше";
      js_comp_symbol = ">=";
      m_diia_name = "мНеМенше";
    }
    if (comparison_node->op == "<=" || comparison_node->op == "не більше") {
      result = left_result->value->comp_lesser_or_eq(scope, comparison_node,
                                                     right_result->value);
      magic_diia = "чародія_не_більше";
      js_comp_symbol = "<=";
      m_diia_name = "мНеБільше";
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
      m_diia_name = "";
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
      m_diia_name = "";
    }

    if (result != nullptr) {
      if (result->error) {
        return result;
      }

      if (js_comp_symbol == "==") {
        // а === б
        const auto js_comparison = js::make_comparison(
            left_result->js_node, "===", right_result->js_node);
        return success(result->value, js_comparison);
      }

      if (js_comp_symbol == "!=") {
        // а !== б
        const auto js_comparison = js::make_comparison(
            left_result->js_node, "!==", right_result->js_node);
        return success(result->value, js_comparison);
      }

      if (magic_diia == "чародія_є") {
        // мЄ(а, б)
        return success(result->value, js::make_call(js::make_id("мЄ"),
                                                    {left_result->js_node,
                                                     right_result->js_node}));
      }

      if (magic_diia == "чародія_не_є") {
        // !мЄ(а, б)
        return success(result->value,
                       js::make_not(js::make_call(
                           js::make_id("мЄ"),
                           {left_result->js_node, right_result->js_node})));
      }

      if (left_result->value->is_number(scope) &&
          right_result->value->is_number(scope)) {
        if (js_comp_symbol.empty()) {
          return error_from_ast(comparison_node,
                                "[INTERNAL BUG] Невідома вказівка \"" +
                                    comparison_node->op + "\".");
        }
        // а > б
        return success(result->value,
                       js::make_comparison(left_result->js_node, js_comp_symbol,
                                           right_result->js_node));
      }

      if (left_result->value->has_diia(scope, magic_diia)) {
        // а.чародія_більше(б)
        const auto js_chain =
            js::make_chain(left_result->js_node, js::make_id(magic_diia));
        const auto js_call = js::make_call(js_chain, {right_result->js_node});
        if (magic_diia == "чародія_не_містить") {
          return success(result->value, js::make_not(js_call));
        }
        return success(result->value, js_call);
      } else {
        // мБільше(а, б)
        const auto js_call =
            js::make_call(js::make_id(m_diia_name),
                          {left_result->js_node, right_result->js_node});
        if (m_diia_name == "мНеМістить") {
          return success(result->value, js::make_not(js_call));
        }
        return success(result->value, js_call);
      }
    }

    return error_from_ast(
          comparison_node, "Невідома вказівка \"" + comparison_node->op + "\".");
  }
} // namespace typeinterpreter