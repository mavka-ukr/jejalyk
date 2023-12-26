#include "typeinterpreter.h"

namespace typeinterpreter {
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

  Result* Subject::create_instance(Scope* scope,
                                   std::vector<Subject*> generic_types) {
    const auto subject = new Subject();

    for (const auto& type : types) {
      subject->types.push_back(type->create_instance(scope, generic_types));
    }

    return success(subject);
  }
} // namespace typeinterpreter