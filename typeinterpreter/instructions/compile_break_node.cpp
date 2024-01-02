#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_break_node(Scope* scope, mavka::ast::BreakNode* break_node) {
    if (!scope->get_is_loop()) {
      return scope->error(break_node,
                          "Вказівка \"перервати\" може бути "
                          "використана тільки всередині циклу.");
    }

    const auto js_break = new js::JsBreakNode();

    return success(nullptr, js_break);
  }
} // namespace typeinterpreter