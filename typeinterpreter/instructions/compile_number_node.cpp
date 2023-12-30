#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_number_node(Scope* scope,
                              mavka::ast::NumberNode* number_node) {
    const auto number_structure = scope->get_root_number();
    const auto number_result = number_structure->create_instance(scope, {});

    const auto js_number = js::make_number(number_node->value);

    return success(number_result->value, js_number);
  }
} // namespace jejalyk::typeinterpreter