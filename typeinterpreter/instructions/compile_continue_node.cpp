#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_continue_node(Scope* scope,
                                mavka::ast::ContinueNode* continue_node) {
    if (!scope->get_is_loop()) {
      return error_from_ast(continue_node,
                            "Вказівка \"продовжити\" може бути "
                            "використана тільки всередині циклу.");
    }

    const auto js_continue_node = new jejalyk::js::JsContinueNode();

    return success(nullptr, js_continue_node);
  }
} // namespace typeinterpreter