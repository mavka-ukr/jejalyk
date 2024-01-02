#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_structure_node(Scope* scope,
                                 mavka::ast::StructureNode* structure_node) {
    if (!scope->has_local(structure_node->name)) {
      return scope->error(structure_node, "[INTERNAL BUG] Структура \"" +
                                              structure_node->name +
                                              "\" не визначена.");
    }

    const auto structure_subject = scope->get_local(structure_node->name);

    const auto structure_result =
        complete_structure(scope, false, structure_node, structure_subject,
                           structure_node->params);
    if (structure_result->error) {
      return structure_result;
    }

    // а = мСтруктура("а", ...)
    const auto js_assign = js::make_assign(
        js::make_id("м_" + structure_node->name), structure_result->js_node);

    return success(structure_result->value, js_assign);
  }
} // namespace jejalyk::typeinterpreter