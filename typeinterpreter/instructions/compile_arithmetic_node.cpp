#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
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

    Result* result = nullptr;
    std::string magic_diia;
    std::string m_diia_name;

    if (arithmetic_node->op == "+") {
      magic_diia = JJ_MAG_ADD;
      m_diia_name = JJ_F_ADD;
    }
    if (arithmetic_node->op == "-") {
      magic_diia = JJ_MAG_SUB;
      m_diia_name = JJ_F_SUB;
    }
    if (arithmetic_node->op == "*") {
      magic_diia = JJ_MAG_MUL;
      m_diia_name = JJ_F_MUL;
    }
    if (arithmetic_node->op == "/") {
      magic_diia = JJ_MAG_DIV;
      m_diia_name = JJ_F_DIV;
    }
    if (arithmetic_node->op == "%") {
      magic_diia = JJ_MAG_MOD;
      m_diia_name = JJ_F_MOD;
    }
    if (arithmetic_node->op == "//") {
      magic_diia = JJ_MAG_DIVDIV;
      m_diia_name = JJ_F_DIVDIV;
    }
    if (arithmetic_node->op == "**") {
      magic_diia = JJ_MAG_POW;
      m_diia_name = JJ_F_POW;
    }

    result = left_result->value->magic_call(scope, arithmetic_node, magic_diia,
                                            {}, {right_result->value});

    if (result != nullptr) {
      if (result->error) {
        return result;
      }

      if (left_result->value->is_number(scope) &&
          right_result->value->is_number(scope)) {
        if (arithmetic_node->op == "//") {
          // Math.floor(а / б)
          const auto js_chain = js::make_chain("Math", "floor");
          const auto js_call = js::make_call(
              js_chain, {js::make_arithmetic(left_result->js_node, "/",
                                             right_result->js_node)});
          return success(result->value, js_call);
        } else {
          // а + б
          return success(
              result->value,
              js::make_arithmetic(left_result->js_node, arithmetic_node->op,
                                  right_result->js_node));
        }
      }

      if (arithmetic_node->op == "+") {
        if (left_result->value->is_string(scope) &&
            right_result->value->is_string(scope)) {
          // а + б
          return success(result->value,
                         js::make_arithmetic(left_result->js_node, "+",
                                             right_result->js_node));
        }
      }

      if (left_result->value->has_diia(scope, magic_diia)) {
        // а.чародія_додати(б)
        const auto js_chain =
            js::make_chain(left_result->js_node, js::make_id(magic_diia));
        const auto js_call = js::make_call(js_chain, {right_result->js_node});
        return success(result->value, js_call);
      } else {
        // мДодати(а, б)
        const auto js_call =
            js::make_call(js::make_id(m_diia_name),
                          {left_result->js_node, right_result->js_node});
        return success(result->value, js_call);
      }

      return result;
    }

    return scope->error(arithmetic_node,
                        "Невідома вказівка \"" + arithmetic_node->op + "\".");
  }
} // namespace typeinterpreter