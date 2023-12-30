#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_give_node(Scope* scope, mavka::ast::GiveNode* give_node) {
    const auto module_object = scope->get_module_object();
    if (module_object == nullptr) {
      return error_from_ast(give_node,
                            "Вказівка \"дати\" працює лише в модулі.");
    }

    for (const auto element_node : give_node->elements) {
      if (scope->has_local(element_node->name)) {
        const auto subject = scope->get_local(element_node->name);
        if (element_node->as.empty()) {
          module_object->properties.insert_or_assign(element_node->name,
                                                     subject);
        } else {
          module_object->properties.insert_or_assign(element_node->as, subject);
        }
      } else {
        return error_from_ast(give_node, "Невідомий субʼєкт для давання \"" +
                                             element_node->name + "\".");
      }
    }

    return success(nullptr);
  }
} // namespace typeinterpreter