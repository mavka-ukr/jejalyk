#include "typeinterpreter.h"

namespace typeinterpreter {
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
      return error("Неможливо отримати властивість \"" + name +
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
      return error("Неможливо встановити властивість \"" + name +
                   "\" субʼєкта невідомого типу.");
    }
    if (types.size() > 1) {
      return error("Неможливо встановити властивість \"" + name +
                   "\" субʼєкта декількох типів.");
    }
    return types[0]->set(scope, node, name, value);
  }

  Result* Subject::call(Scope* scope,
                        mavka::ast::ASTNode* node,
                        std::vector<Subject*> generic_types,
                        std::vector<Subject*> args) {
    if (types.empty()) {
      return error_from_ast(node, "Неможливо викликати субʼєкт без типів.");
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
      return error_from_ast(
          node,
          "Неможливо отримати спеціальну властивість з субʼєкта невідомого "
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
      return error_from_ast(
          node,
          "Неможливо встановити спеціальну властивість субʼєкта невідомого "
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
      return error_from_ast(node, "Неможливо додати субʼєкт невідомого типу.");
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
      return error_from_ast(node, "Неможливо відняти субʼєкт невідомого типу.");
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
      return error_from_ast(node,
                            "Неможливо помножити субʼєкт невідомого типу.");
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
      return error_from_ast(node,
                            "Неможливо поділити субʼєкт невідомого типу.");
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
      return error_from_ast(node, "Неможливо divmod субʼєкт невідомого типу.");
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
      return error_from_ast(node, "Неможливо divdiv субʼєкт невідомого типу.");
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
      return error_from_ast(
          node, "Неможливо піднести субʼєкт невідомого типу до степеня.");
    }
    if (types.size() > 1) {
      return error_from_ast(
          node, "Неможливо піднести субʼєкт декількох типів до степеня.");
    }
    return types[0]->pow(scope, node, value);
  }

  Result* Subject::bw_not(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(node, "Неможливо bw_not субʼєкт невідомого типу.");
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
      return error_from_ast(node, "Неможливо bw_xor субʼєкт невідомого типу.");
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
      return error_from_ast(node, "Неможливо bw_or субʼєкт невідомого типу.");
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
      return error_from_ast(node, "Неможливо bw_and субʼєкт невідомого типу.");
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
      return error_from_ast(node,
                            "Неможливо bw_shift_left субʼєкт невідомого типу.");
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
          node, "Неможливо bw_shift_right субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(
          node, "Неможливо bw_shift_right субʼєкт декількох типів.");
    }
    return types[0]->bw_shift_right(scope, node, value);
  }

  Result* Subject::negative(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(node,
                            "Неможливо negative субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо negative субʼєкт декількох типів.");
    }
    return types[0]->negative(scope, node);
  }

  Result* Subject::positive(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(node,
                            "Неможливо positive субʼєкт невідомого типу.");
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
          node, "Неможливо post_decrement субʼєкт невідомого типу.");
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
          node, "Неможливо post_increment субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(
          node, "Неможливо post_increment субʼєкт декількох типів.");
    }
    return types[0]->post_increment(scope, node);
  }

  Result* Subject::pre_decrement(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(node,
                            "Неможливо pre_decrement субʼєкт невідомого типу.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо pre_decrement субʼєкт декількох типів.");
    }
    return types[0]->pre_decrement(scope, node);
  }

  Result* Subject::pre_increment(Scope* scope, mavka::ast::ASTNode* node) {
    if (types.empty()) {
      return error_from_ast(node,
                            "Неможливо pre_increment субʼєкт невідомого типу.");
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
    if (types.empty()) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт невідомого "
                            "типу на рівність з іншим субʼєктом.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт декількох "
                            "типів на рівність з іншим субʼєктом.");
    }
    return types[0]->comp_eq(scope, node, value);
  }

  Result* Subject::comp_not_eq(Scope* scope,
                               mavka::ast::ASTNode* node,
                               Subject* value) {
    if (types.empty()) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт невідомого "
                            "типу на нерівність з іншим субʼєктом.");
    }
    if (types.size() > 1) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт декількох "
                            "типів на нерівність з іншим субʼєктом.");
    }
    return types[0]->comp_not_eq(scope, node, value);
  }

  Result* Subject::comp_greater(Scope* scope,
                                mavka::ast::ASTNode* node,
                                Subject* value) {
    if (types.empty()) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт невідомого "
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
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт невідомого "
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
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт невідомого "
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
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт невідомого "
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
    if (types.empty()) {
      return error_from_ast(node,
                            "Неможливо порівняти субʼєкт невідомого типу на рівність з іншим субʼєктом.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо порівняти субʼєкт декількох типів на рівність з іншим субʼєктом.");
    }
    return types[0]->comp_is(scope, node, value);
  }
  Result* Subject::comp_is_not(Scope* scope,
                      mavka::ast::ASTNode* node,
                      Subject* value) {
    if (types.empty()) {
      return error_from_ast(node, "Неможливо порівняти субʼєкт невідомого типу на нерівність з іншим субʼєктом.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо порівняти субʼєкт декількох типів на нерівність з іншим субʼєктом.");
    }
    return types[0]->comp_is_not(scope, node, value);
  }

  Result* Subject::comp_contains(Scope* scope,
                        mavka::ast::ASTNode* node,
                        Subject* value) {
    if (types.empty()) {
      return error_from_ast(node, "Неможливо порівняти субʼєкт невідомого типу на наявність в іншому субʼєкті.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо порівняти субʼєкт декількох типів на наявність в іншому субʼєкті.");
    }
    return types[0]->comp_contains(scope, node, value);
  }

  Result* Subject::comp_contains_not(Scope* scope,
                            mavka::ast::ASTNode* node,
                            Subject* value) {
    if (types.empty()) {
      return error_from_ast(node, "Неможливо порівняти субʼєкт невідомого типу на відсутність в іншому субʼєкті.");
    }
    if (types.size() > 1) {
      return error_from_ast(node, "Неможливо порівняти субʼєкт декількох типів на відсутність в іншому субʼєкті.");
    }
    return types[0]->comp_contains_not(scope, node, value);
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

  Result* Subject::create_instance(Scope* scope,
                                   std::vector<Subject*> generic_types) {
    const auto subject = new Subject();

    for (const auto& type : types) {
      subject->add_type(type->create_instance(scope, generic_types));
    }

    return success(subject);
  }
} // namespace typeinterpreter