#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_array_node(Scope* scope, mavka::ast::ArrayNode* array_node) {
    const auto js_array = new js::JsArrayNode();
    const auto array_structure_subject = scope->get_root_list();
    const auto array_values_type_result =
        scope->compile_nodes(array_node->elements);
    if (array_values_type_result->error) {
      return array_values_type_result;
    }
    js_array->elements = array_values_type_result->js_body->nodes;
    const auto result = array_structure_subject->create_instance(
        scope, {array_values_type_result->value});
    result->value->is_empty_value = array_node->elements.empty();
    result->js_node = js_array;
    return result;
  }
} // namespace jejalyk::typeinterpreter