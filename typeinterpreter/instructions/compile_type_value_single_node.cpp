#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_type_value_single_node(
      Scope* scope,
      mavka::ast::TypeValueSingleNode* type_value_single_node) {
    const auto type_value_single_result =
        scope->compile_node(type_value_single_node->value);
    if (type_value_single_result->error) {
      return type_value_single_result;
    }

    if (!type_value_single_result->value->types.empty()) {
      if (type_value_single_result->value->types[0]->object) {
        if (type_value_single_node->generics.empty() &&
            !type_value_single_result->value->types[0]
                 ->object->generic_definitions.empty()) {
          for (const auto g : type_value_single_result->value->types[0]
                                  ->object->generic_definitions) {
            const auto identifier = new mavka::ast::IdentifierNode();
            identifier->name = "обʼєкт";
            const auto identifier_type_value =
                new mavka::ast::TypeValueSingleNode();
            identifier_type_value->value =
                mavka::ast::make_ast_some(identifier);
            type_value_single_node->generics.push_back({identifier_type_value});
          }
        } else {
          if (type_value_single_node->generics.size() >
              type_value_single_result->value->types[0]
                  ->object->generic_definitions.size()) {
            return scope->error(type_value_single_node,
                                "Забагато аргументів шаблону.");
          }

          if (type_value_single_node->generics.size() <
              type_value_single_result->value->types[0]
                  ->object->generic_definitions.size()) {
            return scope->error(type_value_single_node,
                                "Недостатньо аргументів шаблону.");
          }
        }
      }
    }

    if (!type_value_single_node->generics.empty()) {
      if (type_value_single_result->value->types.size() != 1) {
        return scope->error(type_value_single_node,
                            "Неможливо застосувати аргументи шаблону до "
                            "типу з різними можливими значеннями.");
      }

      if (type_value_single_result->value->types[0]->generic_definition) {
        return scope->error(
            type_value_single_node,
            "Неможливо використовувати аргументи шаблону для шаблону.");
      }

      std::vector<Subject*> generic_types;
      for (const auto& generic_type_value : type_value_single_node->generics) {
        const auto generic_type_subject = new Subject();
        for (const auto generic_type_value_single_node : generic_type_value) {
          const auto generic_type_value_single_result = scope->compile_node(
              mavka::ast::make_ast_some(generic_type_value_single_node));
          if (generic_type_value_single_result->error) {
            return generic_type_value_single_result;
          }
          for (const auto generic_generic_type_value :
               generic_type_value_single_result->value->types) {
            generic_type_subject->add_type(generic_generic_type_value);
          }
        }
        generic_types.push_back(generic_type_subject);
      }

      return type_value_single_result->value->create_instance(scope, generic_types);
    }

    return type_value_single_result->value->create_instance(scope, {});
  }
} // namespace typeinterpreter