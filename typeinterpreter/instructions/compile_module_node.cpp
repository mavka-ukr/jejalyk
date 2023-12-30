#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_module_node(Scope* scope,
                              mavka::ast::ModuleNode* module_node) {
    if (!scope->get_is_async()) {
      return error_from_ast(
          module_node,
          "Модуль може бути визначений лише всередині іншого модуля.");
    }
    const auto module_result =
        scope->compile_module(module_node->name, &module_node->body);
    if (module_result->error) {
      return module_result;
    }

    scope->set_local(module_node->name, module_result->value);

    const auto js_call = js::make_call(js::make_id("мМодуль"),
                                       {js::make_string(module_node->name)});

    // todo: handle body

    return success(module_result->value, js_call);
  }
} // namespace typeinterpreter