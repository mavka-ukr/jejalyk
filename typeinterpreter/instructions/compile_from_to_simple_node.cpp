#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_from_to_simple_node(
      Scope* scope,
      mavka::ast::FromToSimpleNode* from_to_simple_node) {
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
    return iterator_instance_result;
  }
} // namespace typeinterpreter