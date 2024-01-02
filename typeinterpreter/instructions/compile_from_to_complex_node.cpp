#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_from_to_complex_node(
      Scope* scope,
      mavka::ast::FromToComplexNode* from_to_complex_node) {
    const auto from_result = scope->compile_node(from_to_complex_node->from);
    if (from_result->error) {
      return from_result;
    }

    const auto step_result = scope->compile_node(from_to_complex_node->step);
    if (step_result->error) {
      return step_result;
    }
    const auto step_symbol = from_to_complex_node->stepSymbol.empty()
                                 ? "+"
                                 : from_to_complex_node->stepSymbol;

    const auto to_result = scope->compile_node(from_to_complex_node->to);
    if (to_result->error) {
      return to_result;
    }
    const auto to_symbol = from_to_complex_node->toSymbol.empty()
                               ? "<="
                               : from_to_complex_node->toSymbol;

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

    // todo: optimize with raw for loop
    // мВідДо(а, "+", б, "<=", в)
    const auto js_call = js::make_call(
        js::make_id(JJ_F_FROM_TO),
        {from_result->js_node, js::make_string(step_symbol),
         step_result->js_node, js::make_string(to_symbol), to_result->js_node});

    return success(iterator_instance_result->value, js_call);
  }
} // namespace jejalyk::typeinterpreter