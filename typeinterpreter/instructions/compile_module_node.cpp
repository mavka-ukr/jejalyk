#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_module_node(Scope* scope,
                              mavka::ast::ModuleNode* module_node) {
    if (!scope->get_is_async()) {
      return scope->error(
          module_node,
          "Модуль може бути визначений лише всередині іншого модуля.");
    }
    const auto module_result =
        scope->compile_module(module_node->name, &module_node->body, "", {});
    if (module_result->error) {
      return module_result;
    }

    scope->set_local(module_node->name, module_result->value);

    // а = await мМодуль("а", ...)
    const auto js_assign = js::make_assign(
        js::make_id("м_" + module_node->name), module_result->js_node);

    return success(module_result->value, js_assign);
  }
} // namespace typeinterpreter