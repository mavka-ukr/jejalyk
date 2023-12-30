#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_diia_or_mockup_diia_node(
      Scope* scope,
      mavka::ast::ASTNode* node,
      bool mockup,
      bool ee,
      bool async,
      std::string structure,
      std::string name,
      std::vector<mavka::ast::GenericNode*> generics,
      std::vector<mavka::ast::ParamNode*> params,
      std::vector<mavka::ast::TypeValueSingleNode*> return_types,
      std::vector<mavka::ast::ASTNode*>* body) {
    if (!structure.empty()) {
      if (ee) {
        return error_from_ast(node, "Спеціальні дії тимчасово недоступні.");
      }
      if (!scope->has_local(structure)) {
        return error_from_ast(
            node, "[INTERNAL BUG] Субʼєкт \"" + structure + "\" не визначено.");
      }
      const auto structure_subject = scope->get_local(structure);
      if (!structure_subject->is_structure(scope)) {
        return error_from_ast(node, "[INTERNAL BUG] Субʼєкт \"" + structure +
                                        "\" не є структурою.");
      }
      const auto structure_type = structure_subject->types[0];
      const auto structure_object = structure_type->object;
      for (const auto param : structure_object->params) {
        if (param->name == name) {
          return error_from_ast(node, "[INTERNAL BUG] Параметр \"" + name +
                                          "\" вже визначено в структурі \"" +
                                          structure + "\".");
        }
      }
      if (!structure_object->methods.contains(name)) {
        return error_from_ast(node, "[INTERNAL BUG] Субʼєкт \"" + structure +
                                        "\" не має методу \"" + name + "\".");
      }

      const auto diia_subject = structure_object->methods[name];
      const auto diia_scope = scope->make_child();
      std::vector<Subject*> generic_definition_subjects;
      for (const auto generic_definition :
           structure_object->generic_definitions) {
        const auto generic_definition_subject =
            Subject::create(generic_definition);
        generic_definition_subjects.push_back(generic_definition_subject);
      }
      diia_scope->set_local("я",
                            Subject::create(structure_type->create_instance(
                                scope, generic_definition_subjects)));

      const auto diia_result = complete_diia(
          scope, mockup, diia_scope, node, Subject::create(diia_subject), body);
      if (diia_result->error) {
        return diia_result;
      }

      if (mockup) {
        return diia_result;
      }

      // назва[М].методи.метод = мДія()
      const auto js_assign = js::make_assign(
          js::make_chain(js::make_chain(js::make_access(js::make_id(structure),
                                                        js::make_id("М")),
                                        js::make_id("методи")),
                         js::make_id(name)),
          diia_result->js_node);

      return success(diia_result->value, js_assign);
    }

    if (!scope->has_local(name)) {
      return error_from_ast(
          node, "[INTERNAL BUG] Дія \"" + name + "\" попередньо не визначена.");
    }

    const auto diia_subject = scope->get_local(name);
    const auto diia_scope = scope->make_child();

    const auto diia_result =
        complete_diia(scope, mockup, diia_scope, node, diia_subject, body);
    if (diia_result->error) {
      return diia_result;
    }

    if (mockup) {
      return diia_result;
    }

    // а = мДія()
    const auto js_assign =
        js::make_assign(js::make_id(name), diia_result->js_node);

    return success(diia_result->value, js_assign);
  }
} // namespace jejalyk::typeinterpreter