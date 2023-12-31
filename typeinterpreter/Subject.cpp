#include "typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Subject* Subject::create(Type* type) {
    const auto subject = new Subject();
    subject->add_type(type);
    return subject;
  }

  Subject* Subject::create(Object* object) {
    const auto subject = new Subject();
    subject->add_type(Type::create(object));
    return subject;
  }

  Subject* Subject::create(GenericDefinition* generic_definition) {
    const auto subject = new Subject();
    subject->add_type(Type::create(generic_definition));
    return subject;
  }

  void Subject::add_type(Type* type) {
    for (const auto& existing_type : types) {
      if (existing_type->generic_definition) {
        if (type->generic_definition) {
          if (existing_type->generic_definition->object ==
              type->generic_definition->object) {
            if (existing_type->generic_definition->name ==
                type->generic_definition->name) {
              // todo: check generic types
            }
          }
        }
      }
      if (existing_type->object) {
        if (type->object) {
          if (existing_type->object->structure == type->object->structure) {
            if (existing_type->generic_types.size() ==
                type->generic_types.size()) {
              bool generics_good = false;
              for (int i = 0; i < existing_type->generic_types.size(); ++i) {
                const auto existing_type_generic =
                    existing_type->generic_types[i];
                const auto type_generic = type->generic_types[i];

                // todo: doto
              }
              if (generics_good) {
                return;
              }
            }
          }
        }
      }
    }
    types.push_back(type);
  }

  Subject* Subject::merge_types(Subject* subject) {
    for (const auto& type : subject->types) {
      this->add_type(type);
    }
    return this;
  }

  void Subject::fix_types(Scope* scope) {
    if (this->types.empty()) {
      this->types.push_back(scope->create_object_instance_type());
    }
  }

  std::string Subject::get_name() {
    std::vector<std::string> names;
    for (const auto type : this->types) {
      names.push_back(type->get_name());
    }
    return jejalyk::tools::implode(names, "|");
  }

  std::string Subject::types_string() {
    std::vector<std::string> names;
    for (const auto type : this->types) {
      names.push_back(type->get_type_name());
    }
    return jejalyk::tools::implode(names, " або ");
  }

  bool Subject::check(Subject* subject) {
    return false;
  }

  bool Subject::is_number(Scope* scope) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->is_number(scope);
  }

  bool Subject::is_string(Scope* scope) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->is_string(scope);
  }

  bool Subject::is_array(Scope* scope) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->is_array(scope);
  }

  bool Subject::is_diia(Scope* scope) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->is_diia(scope);
  }

  bool Subject::is_dictionary(Scope* scope) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->is_dictionary(scope);
  }

  bool Subject::is_structure(Scope* scope) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->is_structure(scope);
  }

  bool Subject::is_object(Scope* scope) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->is_object(scope);
  }

  bool Subject::has(const std::string& name) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->has(name);
  }

  Result* Subject::get(const std::string& name) {
    if (types.empty()) {
      return error("[INTERNAL BUG] Неможливо отримати властивість \"" + name +
                   "\" з субʼєкта невідомого типу.");
    }
    if (types.size() > 1) {
      return error("Неможливо отримати властивість \"" + name +
                   "\" з субʼєкта декількох типів.");
    }
    return success(types[0]->get(name));
  }

  Result* Subject::set(Scope* scope,
                       mavka::ast::ASTNode* node,
                       const std::string& name,
                       Subject* value) {
    if (types.empty()) {
      return error("[INTERNAL BUG] Неможливо встановити властивість \"" + name +
                   "\" субʼєкта невідомого типу.");
    }
    if (types.size() > 1) {
      return error("Неможливо встановити властивість \"" + name +
                   "\" субʼєкта декількох типів.");
    }
    return types[0]->set(scope, node, name, value);
  }

  bool Subject::has_diia(Scope* scope, std::string name) {
    if (this->has(name)) {
      const auto subject_result = this->get(name);
      if (subject_result->error) {
        return false;
      }
      return subject_result->value->is_diia(scope);
    }
    return false;
  }

  Result* Subject::call(Scope* scope,
                        mavka::ast::ASTNode* node,
                        std::vector<Subject*> generic_types,
                        std::vector<Subject*> args) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо викликати субʼєкт без типів.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо викликати субʼєкт з декількома типами.");
    }
    return types[0]->call(scope, node, generic_types, args);
  }

  Result* Subject::get_element(Scope* scope,
                               mavka::ast::ASTNode* node,
                               Subject* value) {
    if (types.empty()) {
      return error_from_ast(node,
                            "[INTERNAL BUG] Неможливо отримати спеціальну "
                            "властивість з субʼєкта невідомого "
                            "типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(
          node,
          "Неможливо отримати спеціальну властивість з субʼєкта декількох "
          "типів.");
    }
    return types[0]->get_element(scope, node, value);
  }

  Result* Subject::set_element(Scope* scope,
                               mavka::ast::ASTNode* node,
                               Subject* element,
                               Subject* value) {
    if (types.empty()) {
      return error_from_ast(node,
                            "[INTERNAL BUG] Неможливо встановити спеціальну "
                            "властивість субʼєкта невідомого "
                            "типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(
          node,
          "Неможливо встановити спеціальну властивість субʼєкта декількох "
          "типів.");
    }
    return types[0]->set_element(scope, node, element, value);
  }

  Result* Subject::plus(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо додати субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо додати субʼєкт декількох типів.");
    }
    return types[0]->plus(scope, node, value);
  }

  Result* Subject::minus(Scope* scope,
                         mavka::ast::ASTNode* node,
                         Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо відняти субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо відняти субʼєкт декількох типів.");
    }
    return types[0]->minus(scope, node, value);
  }

  Result* Subject::multiply(Scope* scope,
                            mavka::ast::ASTNode* node,
                            Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо помножити субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо помножити субʼєкт декількох типів.");
    }
    return types[0]->multiply(scope, node, value);
  }

  Result* Subject::divide(Scope* scope,
                          mavka::ast::ASTNode* node,
                          Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо поділити субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо поділити субʼєкт декількох типів.");
    }
    return types[0]->divide(scope, node, value);
  }

  Result* Subject::divmod(Scope* scope,
                          mavka::ast::ASTNode* node,
                          Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо divmod субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо divmod субʼєкт декількох типів.");
    }
    return types[0]->divmod(scope, node, value);
  }

  Result* Subject::divdiv(Scope* scope,
                          mavka::ast::ASTNode* node,
                          Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо divdiv субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо divdiv субʼєкт декількох типів.");
    }
    return types[0]->divdiv(scope, node, value);
  }

  Result* Subject::pow(Scope* scope,
                       mavka::ast::ASTNode* node,
                       Subject* value) {
    if (types.empty()) {
      return error_from_ast(node,
                            "[INTERNAL BUG] Неможливо піднести субʼєкт "
                            "невідомого типу до степеня.");
    }
    if (types.size() > 1) {
      return error_from_ast(
          node, "Неможливо піднести субʼєкт декількох типів до степеня.");
    }
    return types[0]->pow(scope, node, value);
  }

  Result* Subject::bw_not(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо bw_not субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо bw_not субʼєкт декількох типів.");
    }
    return types[0]->bw_not(scope, node);
  }

  Result* Subject::bw_xor(Scope* scope,
                          mavka::ast::ASTNode* node,
                          Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо bw_xor субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо bw_xor субʼєкт декількох типів.");
    }
    return types[0]->bw_xor(scope, node, value);
  }

  Result* Subject::bw_or(Scope* scope,
                         mavka::ast::ASTNode* node,
                         Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо bw_or субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо bw_or субʼєкт декількох типів.");
    }
    return types[0]->bw_or(scope, node, value);
  }

  Result* Subject::bw_and(Scope* scope,
                          mavka::ast::ASTNode* node,
                          Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо bw_and субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо bw_and субʼєкт декількох типів.");
    }
    return types[0]->bw_and(scope, node, value);
  }

  Result* Subject::bw_shift_left(Scope* scope,
                                 mavka::ast::ASTNode* node,
                                 Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо bw_shift_left субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо bw_shift_left субʼєкт декількох типів.");
    }
    return types[0]->bw_shift_left(scope, node, value);
  }

  Result* Subject::bw_shift_right(Scope* scope,
                                  mavka::ast::ASTNode* node,
                                  Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо bw_shift_right субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(
          node, "Неможливо bw_shift_right субʼєкт декількох типів.");
    }
    return types[0]->bw_shift_right(scope, node, value);
  }

  Result* Subject::negative(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо negative субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо negative субʼєкт декількох типів.");
    }
    return types[0]->negative(scope, node);
  }

  Result* Subject::positive(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(
          node, "[INTERNAL BUG] Неможливо positive субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо positive субʼєкт декількох типів.");
    }
    return types[0]->positive(scope, node);
  }

  Result* Subject::post_decrement(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо post_decrement субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(
          node, "Неможливо post_decrement субʼєкт декількох типів.");
    }
    return types[0]->post_decrement(scope, node);
  }

  Result* Subject::post_increment(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо post_increment субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(
          node, "Неможливо post_increment субʼєкт декількох типів.");
    }
    return types[0]->post_increment(scope, node);
  }

  Result* Subject::pre_decrement(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо pre_decrement субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо pre_decrement субʼєкт декількох типів.");
    }
    return types[0]->pre_decrement(scope, node);
  }

  Result* Subject::pre_increment(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо pre_increment субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо pre_increment субʼєкт декількох типів.");
    }
    return types[0]->pre_increment(scope, node);
  }

  Result* Subject::comp_eq(Scope* scope,
                           mavka::ast::ASTNode* node,
                           Subject* value) {
    const auto logical_structure_subject = scope->get_root_logical();
    const auto logical_instance_result =
        logical_structure_subject->create_instance(scope, {});
    if (logical_instance_result->error) {
      return logical_instance_result;
    }
    return success(logical_instance_result->value);
  }

  Result* Subject::comp_not_eq(Scope* scope,
                               mavka::ast::ASTNode* node,
                               Subject* value) {
    const auto logical_structure_subject = scope->get_root_logical();
    const auto logical_instance_result =
        logical_structure_subject->create_instance(scope, {});
    if (logical_instance_result->error) {
      return logical_instance_result;
    }
    return success(logical_instance_result->value);
  }

  Result* Subject::comp_greater(Scope* scope,
                                mavka::ast::ASTNode* node,
                                Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо порівняти субʼєкт невідомого "
          "типу на більше з іншим субʼєктом.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт декількох "
                            "типів на більше з іншим субʼєктом.");
    }
    return types[0]->comp_greater(scope, node, value);
  }

  Result* Subject::comp_lesser(Scope* scope,
                               mavka::ast::ASTNode* node,
                               Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо порівняти субʼєкт невідомого "
          "типу на менше з іншим субʼєктом.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт декількох "
                            "типів на менше з іншим субʼєктом.");
    }
    return types[0]->comp_lesser(scope, node, value);
  }

  Result* Subject::comp_greater_or_eq(Scope* scope,
                                      mavka::ast::ASTNode* node,
                                      Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо порівняти субʼєкт невідомого "
          "типу на більше або дорівнює з іншим "
          "субʼєктом.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт декількох "
                            "типів на більше або дорівнює з іншим "
                            "субʼєктом.");
    }
    return types[0]->comp_greater_or_eq(scope, node, value);
  }

  Result* Subject::comp_lesser_or_eq(Scope* scope,
                                     mavka::ast::ASTNode* node,
                                     Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо порівняти субʼєкт невідомого "
          "типу на менше або дорівнює з іншим "
          "субʼєктом.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт декількох "
                            "типів на менше або дорівнює з іншим "
                            "субʼєктом.");
    }
    return types[0]->comp_lesser_or_eq(scope, node, value);
  }

  Result* Subject::comp_is(Scope* scope,
                           mavka::ast::ASTNode* node,
                           Subject* value) {
    // todo: check if value is structure
    const auto logical_structure_subject = scope->get_root_logical();
    const auto logical_instance_result =
        logical_structure_subject->create_instance(scope, {});
    if (logical_instance_result->error) {
      return logical_instance_result;
    }
    return success(logical_instance_result->value);
  }
  Result* Subject::comp_is_not(Scope* scope,
                               mavka::ast::ASTNode* node,
                               Subject* value) {
    // todo: check if value is structure
    const auto logical_structure_subject = scope->get_root_logical();
    const auto logical_instance_result =
        logical_structure_subject->create_instance(scope, {});
    if (logical_instance_result->error) {
      return logical_instance_result;
    }
    return success(logical_instance_result->value);
  }

  Result* Subject::comp_contains(Scope* scope,
                                 mavka::ast::ASTNode* node,
                                 Subject* value) {
    if (types.empty()) {
      return error_from_ast(
          node,
          "[INTERNAL BUG] Неможливо порівняти субʼєкт невідомого типу на "
          "наявність в іншому субʼєкті.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт декількох типів на "
                            "наявність в іншому субʼєкті.");
    }
    return types[0]->comp_contains(scope, node, value);
  }

  Result* Subject::comp_contains_not(Scope* scope,
                            mavka::ast::ASTNode* node,
                            Subject* value) {
    if (types.empty()) {
      return error_from_ast(node, "[INTERNAL BUG] Неможливо порівняти субʼєкт невідомого типу на відсутність в іншому субʼєкті.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо порівняти субʼєкт декількох типів на відсутність в іншому субʼєкті.");
    }
    return types[0]->comp_contains_not(scope, node, value);
  }

  Result* Subject::test_and(Scope* scope, mavka::ast::ASTNode* node, Subject* value) {
    const auto newsubj = new Subject();
    for (const auto type : this->types) {
      newsubj->add_type(type);
    }
    for (const auto type : value->types) {
      newsubj->add_type(type);
    }
    return success(newsubj);
  }

  Result* Subject::test_or(Scope* scope, mavka::ast::ASTNode* node, Subject* value) {
    const auto newsubj = new Subject();
    for (const auto type : this->types) {
      newsubj->add_type(type);
    }
    for (const auto type : value->types) {
      newsubj->add_type(type);
    }
    return success(newsubj);
  }

  bool Subject::is_iterator(Scope* scope) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->is_iterator(scope);
  }

  Result* Subject::get_iterator_type(Scope* scope, mavka::ast::ASTNode* node) {
    if (!this->is_iterator(scope)) {
      return error_from_ast(node, "Неможливо отримати тип ітератора.");
    }
    return types[0]->get_iterator_type(scope, node);
  }

  bool Subject::is_awaiting(Scope* scope) {
    if (types.empty()) {
      return false;
    }
    if (types.size() > 1) {
      return false;
    }
    return types[0]->is_awaiting(scope);
  }

  Result* Subject::get_awaiting_value(Scope* scope, mavka::ast::ASTNode* node) {
    if (!this->is_awaiting(scope)) {
      return error_from_ast(node, "Неможливо отримати тип очікування.");
    }
    return types[0]->get_awaiting_type(scope, node);
  }

  Result* Subject::create_instance(Scope* scope,
                                   std::vector<Subject*> generic_types) {
    const auto subject = new Subject();

    for (const auto& type : types) {
      subject->add_type(type->create_instance(scope, generic_types));
    }

    return success(subject);
  }
} // namespace typeinterpreter