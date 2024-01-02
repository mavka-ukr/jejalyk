#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_give_node(Scope* scope, mavka::ast::GiveNode* give_node) {
    const auto module_object = scope->get_module_object();
    if (module_object == nullptr) {
      return scope->error(give_node, "Вказівка \"дати\" працює лише в модулі.");
    }

    const auto js_flat_body = new js::JsFlatBodyNode();

    for (const auto element_node : give_node->elements) {
      if (scope->has_local(element_node->name)) {
        const auto subject = scope->get_local(element_node->name);
        if (element_node->as.empty()) {
          js_flat_body->nodes.push_back(
              js::make_assign(js::make_chain("мmodule", element_node->name),
                              js::make_id(element_node->name)));
          module_object->properties.insert_or_assign(element_node->name,
                                                     subject);
        } else {
          js_flat_body->nodes.push_back(
              js::make_assign(js::make_chain("мmodule", element_node->as),
                              js::make_id(element_node->name)));
          module_object->properties.insert_or_assign(element_node->as, subject);
        }
      } else {
        return scope->error(give_node, "Невідомий субʼєкт для давання \"" +
                                           element_node->name + "\".");
      }
    }

    return success(nullptr, js_flat_body);
  }
} // namespace typeinterpreter