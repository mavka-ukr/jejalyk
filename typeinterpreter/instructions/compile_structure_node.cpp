#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_structure_node(Scope* scope,
                                 mavka::ast::StructureNode* structure_node) {
    if (!scope->has_local(structure_node->name)) {
      return error_from_ast(structure_node, "[INTERNAL BUG] Структура \"" +
                                                structure_node->name +
                                                "\" не визначена.");
    }

    const auto structure_subject = scope->get_local(structure_node->name);

    const auto result =
        complete_structure(scope, false, structure_node, structure_subject,
                           structure_node->params, structure_node->methods);

    const auto js_assign_node = new jejalyk::js::JsAssignNode();
    js_assign_node->identifier = jejalyk::js::id(structure_node->name);
    js_assign_node->value = result->js_node;

    return success(result->value, js_assign_node);
  }
} // namespace typeinterpreter