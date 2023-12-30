#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_module_node(Scope* scope,
                              mavka::ast::ModuleNode* module_node) {
    if (!scope->get_is_async()) {
      return error_from_ast(
          module_node,
          "Модуль може бути визначений лише всередині іншого модуля.");
    }
    const auto module_compilation_result =
        scope->compile_module(module_node->name, &module_node->body);
    if (module_compilation_result->error) {
      return module_compilation_result;
    }
    scope->set_local(module_node->name, module_compilation_result->value);
    return module_compilation_result;
  }
} // namespace typeinterpreter