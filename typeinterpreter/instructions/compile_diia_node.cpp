#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_diia_node(Scope* scope, mavka::ast::DiiaNode* diia_node) {
    if (!diia_node->structure.empty()) {
      return error_from_ast(diia_node, "Методи тимчасово недоступні.");
    }
    if (!scope->has_local(diia_node->name)) {
      return error_from_ast(
          diia_node,
          "[INTERNAL BUG] Дія \"" + diia_node->name + "\" не визначена.");
    }

    const auto diia_subject = scope->get_local(diia_node->name);

    const auto diia_scope = scope->make_child();

    const auto result = complete_diia(scope, false, diia_scope, diia_node,
                                      diia_subject, &diia_node->body);
    if (result->error) {
      return result;
    }

    const auto js_assign_node = new jejalyk::js::JsAssignNode();
    js_assign_node->identifier = jejalyk::js::id(diia_node->name);
    js_assign_node->value = result->js_node;

    return success(result->value, js_assign_node);
  }
} // namespace typeinterpreter