#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_mockup_subject_node(
      Scope* scope,
      mavka::ast::MockupSubjectNode* mockup_subject_node) {
    if (scope->has_local(mockup_subject_node->name)) {
      return error_from_ast(
          mockup_subject_node,
          "Субʼєкт \"" + mockup_subject_node->name + "\" вже визначено.");
    }

    const auto types_result = scope->compile_types(mockup_subject_node->types);
    if (types_result->error) {
      return types_result;
    }

    scope->set_local(mockup_subject_node->name, types_result->value);

    return success(types_result->value, new jejalyk::js::JsEmptyNode());
  }
} // namespace typeinterpreter