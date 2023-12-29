#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_mockup_diia_node(
      Scope* scope,
      mavka::ast::MockupDiiaNode* mockup_diia_node) {
    const auto diia_scope = scope->make_child();
    const auto diia_compilation_result = scope->compile_diia(
        diia_scope, mockup_diia_node->async, mockup_diia_node->name,
        mockup_diia_node->generics, mockup_diia_node->params,
        mockup_diia_node->return_types, nullptr);
    if (diia_compilation_result->error) {
      return diia_compilation_result;
    }
    // todo: handle structure
    scope->set_local(mockup_diia_node->name, diia_compilation_result->value);
    return success(diia_compilation_result->value,
                   new jejalyk::js::JsEmptyNode());
  }
} // namespace typeinterpreter