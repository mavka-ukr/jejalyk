#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_mockup_module_node(
      Scope* scope,
      mavka::ast::MockupModuleNode* mockup_module_node) {
    if (!scope->get_is_async()) {
      return error_from_ast(
          mockup_module_node,
          "Модуль може бути визначений лише всередині іншого модуля.");
    }
    const auto module_compilation_result = scope->compile_module(
        mockup_module_node->name, &mockup_module_node->elements);
    if (module_compilation_result->error) {
      return module_compilation_result;
    }
    scope->set_local(mockup_module_node->name,
                     module_compilation_result->value);
    return success(module_compilation_result->value,
                   new jejalyk::js::JsEmptyNode());
  }
} // namespace typeinterpreter