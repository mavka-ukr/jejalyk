#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_return_node(Scope* scope,
                              mavka::ast::ReturnNode* return_node) {
    const auto value_result = scope->compile_node(return_node->value);
    if (value_result->error) {
      return value_result;
    }

    const auto diia_object = scope->get_diia_object();
    if (!diia_object) {
      return error_from_ast(return_node, "Неможливо вернути за межами дії.");
    }

    Subject* return_types = nullptr;
    if (diia_object->is_diia_async) {
      const auto awaiting_value =
          diia_object->return_types->get_awaiting_value(scope, return_node);
      if (awaiting_value->error) {
        return awaiting_value;
      }
      return_types = awaiting_value->value;
    } else {
      return_types = diia_object->return_types;
    }

    if (!scope->check_subjects(value_result->value, return_types)) {
      return error_from_ast(
          return_node, "Неправильний тип поверненого значення: очікується \"" +
                           return_types->types_string() + "\", отримано \"" +
                           value_result->value->types_string() + "\".");
    }

    const auto js_return_node = new jejalyk::js::JsReturnNode();
    js_return_node->value = value_result->js_node;

    value_result->js_node = js_return_node;

    return value_result;
  }
} // namespace typeinterpreter