#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_dictionary_node(Scope* scope,
                                  mavka::ast::DictionaryNode* dictionary_node) {
    const auto dictionary_structure = scope->get_root_dictionary();

    const auto js_map = new js::JsMapNode();

    const auto key_types = new Subject();
    const auto value_types = new Subject();

    for (const auto element : dictionary_node->elements) {
      const auto element_key_result = scope->compile_node(element->key);
      if (element_key_result->error) {
        return element_key_result;
      }
      for (const auto type : element_key_result->value->types) {
        key_types->add_type(type);
      }

      const auto element_value_result = scope->compile_node(element->value);
      if (element_value_result->error) {
        return element_value_result;
      }
      if (element_value_result->value->is_method(scope)) {
        return scope->error(
            mavka::ast::get_ast_node(element->value),
            "Не можна передавати дію обʼєкта як значення.");
      }
      for (const auto type : element_value_result->value->types) {
        value_types->add_type(type);
      }

      const auto js_map_element_node = new jejalyk::js::JsMapElementNode();
      js_map_element_node->key = element_key_result->js_node;
      js_map_element_node->value = element_value_result->js_node;

      js_map->elements.push_back(js_map_element_node);
    }

    key_types->fix_types(scope);
    value_types->fix_types(scope);

    const auto dictionary_result =
        dictionary_structure->create_instance(scope, {key_types, value_types});

    dictionary_result->value->is_empty_value =
        dictionary_node->elements.empty();

    dictionary_result->js_node = js_map;

    return dictionary_result;
  }
} // namespace jejalyk::typeinterpreter