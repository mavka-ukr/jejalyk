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
      return error(
          "Неможливо отримати спеціальну властивість з субʼєкта невідомого "
          "типу.");
    }
    if (types.size() > 1) {
      return error(
          "Неможливо отримати спеціальну властивість з субʼєкта декількох "
          "типів.");
    }
    return types[0]->get_element(scope, node, value);
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