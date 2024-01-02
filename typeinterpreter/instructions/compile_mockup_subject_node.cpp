#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_mockup_subject_node(
      Scope* scope,
      mavka::ast::MockupSubjectNode* mockup_subject_node) {
    if (scope->has_local(mockup_subject_node->name)) {
      return scope->error(
          mockup_subject_node,
          "Субʼєкт \"" + mockup_subject_node->name + "\" вже визначено.");
    }

    const auto types_result = scope->compile_types(mockup_subject_node->types);
    if (types_result->error) {
      return types_result;
    }

    scope->set_local(mockup_subject_node->name, types_result->value);
    scope->put_ignore_variable(mockup_subject_node->name);

    return success(types_result->value, new jejalyk::js::JsEmptyNode());
  }
} // namespace jejalyk::typeinterpreter