#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_array_node(Scope* scope, mavka::ast::ArrayNode* array_node) {
    const auto js_array_node = new jejalyk::js::JsArrayNode();
    const auto array_structure_subject = scope->get_root_list();
    const auto array_values_type_result =
        scope->compile_nodes(array_node->elements);
    if (array_values_type_result->error) {
      return array_values_type_result;
    }
    js_array_node->elements = array_values_type_result->js_body->nodes;
    if (array_node->types.empty()) {
      const auto result = array_structure_subject->create_instance(
          scope, {array_values_type_result->value});
      result->js_node = js_array_node;
      return result;
    } else {
      const auto array_type_subject = new Subject();
      for (const auto type_value_single_node : array_node->types) {
        const auto type_value_single_result =
            scope->compile_node(type_value_single_node);
        if (type_value_single_result->error) {
          return type_value_single_result;
        }
        for (const auto type : type_value_single_result->value->types) {
          array_type_subject->add_type(type);
        }
      }

      if (!array_node->elements.empty()) {
        if (!scope->check_subjects(array_values_type_result->value,
                                   array_type_subject)) {
          return error_from_ast(
              array_node,
              "Неправильний тип елементів масиву: очікується \"" +
                  array_type_subject->types_string() + "\", отримано \"" +
                  array_values_type_result->value->types_string() + "\".");
        }
      }

      const auto result =
          array_structure_subject->create_instance(scope, {array_type_subject});
      result->js_node = js_array_node;
      return result;
    }
  }
} // namespace typeinterpreter