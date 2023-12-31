#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_assign_simple_node(
      Scope* scope,
      mavka::ast::AssignSimpleNode* assign_simple_node) {
    if (scope->get_root()->has(assign_simple_node->name)) {
      return error_1(assign_simple_node, assign_simple_node->name);
    }

    const auto value_result = scope->compile_node(assign_simple_node->value);
    if (value_result->error) {
      return value_result;
    }

    // а = б
    const auto js_assign_node = js::make_assign(
        js::make_id(assign_simple_node->name), value_result->js_node);

    if (assign_simple_node->types.empty()) {
      if (scope->has_local(assign_simple_node->name)) {
        const auto local_subject = scope->get_local(assign_simple_node->name);
        if (!scope->check_subjects(value_result->value, local_subject)) {
          return error_0(assign_simple_node, assign_simple_node->name,
                         local_subject, value_result->value);
        }
        return success(local_subject, js_assign_node);
      } else {
        value_result->value->is_empty_value = false;
        scope->set_local(assign_simple_node->name, value_result->value);

        return success(value_result->value, js_assign_node);
      }
    } else {
      if (scope->has_local(assign_simple_node->name)) {
        return error_1(assign_simple_node, assign_simple_node->name);
      }

      const auto types_result = scope->compile_types(assign_simple_node->types);
      if (types_result->error) {
        return types_result;
      }

      if (!scope->check_subjects(value_result->value, types_result->value)) {
        return error_0(assign_simple_node, assign_simple_node->name,
                       types_result->value, value_result->value);
      }

      scope->set_local(assign_simple_node->name, types_result->value);

      return success(types_result->value, js_assign_node);
    }
  }
} // namespace jejalyk::typeinterpreter