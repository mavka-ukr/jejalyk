#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_break_node(Scope* scope, mavka::ast::BreakNode* break_node) {
    if (!scope->get_is_loop()) {
      return error_from_ast(break_node,
                            "Вказівка \"перервати\" може бути "
                            "використана тільки всередині циклу.");
    }

    const auto js_break_node = new jejalyk::js::JsBreakNode();

    return success(nullptr, js_break_node);
  }
} // namespace typeinterpreter