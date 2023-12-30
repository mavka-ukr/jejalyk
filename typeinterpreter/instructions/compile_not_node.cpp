#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_not_node(Scope* scope, mavka::ast::NotNode* not_node) {
    const auto value_result = scope->compile_node(not_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto logical_structure_subject = scope->get_root_logical();
    const auto logical_instance_result =
        logical_structure_subject->create_instance(scope, {});
    if (logical_instance_result->error) {
      return logical_instance_result;
    }

    const auto js_not_node = new jejalyk::js::JsNotNode();
    js_not_node->value = value_result->js_node;
    logical_instance_result->js_node = js_not_node;

    return logical_instance_result;
  }
} // namespace typeinterpreter