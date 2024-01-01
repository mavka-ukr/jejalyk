#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_from_to_simple_node(
      Scope* scope,
      mavka::ast::FromToSimpleNode* from_to_simple_node) {
    const auto from_result = scope->compile_node(from_to_simple_node->from);
    if (from_result->error) {
      return from_result;
    }

    const auto to_result = scope->compile_node(from_to_simple_node->to);
    if (to_result->error) {
      return to_result;
    }
    const auto to_symbol = from_to_simple_node->toSymbol.empty()
                               ? "<="
                               : from_to_simple_node->toSymbol;

    const auto iterator_structure_subject = scope->get_root_iterator();
    const auto number_structure_subject = scope->get_root_number();
    const auto number_instance_result =
        number_structure_subject->create_instance(scope, {});
    if (number_instance_result->error) {
      return number_instance_result;
    }
    const auto iterator_instance_result =
        iterator_structure_subject->create_instance(
            scope, {number_instance_result->value});
    if (iterator_instance_result->error) {
      return iterator_instance_result;
    }

    // мВідДо(а, "+", 1, "<=", б)
    const auto js_call = js::make_call(
        js::make_id("мВідДо"),
        {from_result->js_node, js::make_string("+"), js::make_number("1"),
         js::make_string(to_symbol), to_result->js_node});

    return success(iterator_instance_result->value, js_call);
  }
} // namespace jejalyk::typeinterpreter