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

    const auto logical_structure_subject = scope->get_root_logical();

    Result* result = nullptr;
    std::string magic_diia;
    std::string js_comp_symbol;

    if (comparison_node->op == "==" || comparison_node->op == "рівно") {
      result = logical_structure_subject->create_instance(scope, {});
      magic_diia = "";
      js_comp_symbol = "==";
    }
    if (comparison_node->op == "!=" || comparison_node->op == "не рівно") {
      result = logical_structure_subject->create_instance(scope, {});
      magic_diia = "";
      js_comp_symbol = "!=";
    }
    if (comparison_node->op == ">" || comparison_node->op == "більше") {
      result = left_result->value->magic_call(
          scope, comparison_node, JJ_MAG_GREATER, {}, {right_result->value});
      magic_diia = JJ_MAG_GREATER;
      js_comp_symbol = ">";
    }
    if (comparison_node->op == "<" || comparison_node->op == "менше") {
      result = left_result->value->magic_call(
          scope, comparison_node, JJ_MAG_LESSER, {}, {right_result->value});
      magic_diia = JJ_MAG_LESSER;
      js_comp_symbol = "<";
    }
    if (comparison_node->op == ">=" || comparison_node->op == "не менше") {
      result = left_result->value->magic_call(scope, comparison_node,
                                              JJ_MAG_GREATER_EQUAL, {},
                                              {right_result->value});
      magic_diia = JJ_MAG_GREATER_EQUAL;
      js_comp_symbol = ">=";
    }
    if (comparison_node->op == "<=" || comparison_node->op == "не більше") {
      result = left_result->value->magic_call(scope, comparison_node,
                                              JJ_MAG_LESSER_EQUAL, {},
                                              {right_result->value});
      magic_diia = JJ_MAG_LESSER_EQUAL;
      js_comp_symbol = "<=";
    }
    if (comparison_node->op == "є") {
      result = logical_structure_subject->create_instance(scope, {});
    }
    if (comparison_node->op == "не є") {
      result = logical_structure_subject->create_instance(scope, {});
    }
    if (comparison_node->op == "містить") {
      result = left_result->value->magic_call(
          scope, comparison_node, JJ_MAG_CONTAINS, {}, {right_result->value});
      magic_diia = JJ_MAG_CONTAINS;
    }
    if (comparison_node->op == "не містить") {
      result = left_result->value->magic_call(
          scope, comparison_node, JJ_MAG_CONTAINS, {}, {right_result->value});
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

      if (comparison_node->op == "є") {
        // мЄ(а, б)
        return success(result->value, js::make_call(js::make_id(JJ_F_IS),
                                                    {left_result->js_node,
                                                     right_result->js_node}));
      }

      if (comparison_node->op == "не є") {
        // !мЄ(а, б)
        return success(result->value,
                       js::make_not(js::make_call(
                           js::make_id(JJ_F_IS),
                           {left_result->js_node, right_result->js_node})));
      }

      if (left_result->value->is_number(scope) &&
          right_result->value->is_number(scope)) {
        if (js_comp_symbol.empty()) {
          return scope->error(comparison_node,
                              "[INTERNAL BUG] Невідома вказівка \"" +
                                  comparison_node->op + "\".");
        }
        // а > б
        return success(result->value,
                       js::make_comparison(left_result->js_node, js_comp_symbol,
                                           right_result->js_node));
      }

      // а.чародія_більше(б)
      const auto js_chain =
          js::make_chain(left_result->js_node, js::make_id(magic_diia));
      const auto js_call = js::make_call(js_chain, {right_result->js_node});
      if (comparison_node->op == "не містить") {
        return success(result->value, js::make_not(js_call));
      }
      return success(result->value, js_call);
    }

    return scope->error(comparison_node, "Невідома вказівка \"" + comparison_node->op + "\".");
  }
} // namespace typeinterpreter