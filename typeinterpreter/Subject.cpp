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

  Subject* Subject::create(Scope* scope) {
    const auto subject = new Subject();
    subject->fix_types(scope);
    return subject;
  }

  void Subject::add_type(Type* type) {
    for (const auto& existing_type : types) {
      if (existing_type->is_equal_to(type)) {
        return;
      }
    }
    this->types.push_back(type);
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
    return jejalyk::tools::implode(names, "/");
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
    if (types.size() == 1) {
      return types[0]->is_number(scope);
    }
    return false;
  }

  bool Subject::is_string(Scope* scope) {
    if (types.size() == 1) {
      return types[0]->is_string(scope);
    }
    return false;
  }

  bool Subject::is_array(Scope* scope) {
    if (types.size() == 1) {
      return types[0]->is_array(scope);
    }
    return false;
  }

  bool Subject::is_diia(Scope* scope) {
    if (types.size() == 1) {
      return types[0]->is_diia(scope);
    }
    return false;
  }

  bool Subject::is_dictionary(Scope* scope) {
    if (types.size() == 1) {
      return types[0]->is_dictionary(scope);
    }
    return false;
  }

  bool Subject::is_structure(Scope* scope) {
    if (types.size() == 1) {
      return types[0]->is_structure(scope);
    }
    return false;
  }

  bool Subject::is_object(Scope* scope) {
    if (types.size() == 1) {
      return types[0]->is_object(scope);
    }
    return false;
  }

  bool Subject::is_method(Scope* scope) {
    if (types.size() == 1) {
      return types[0]->is_method(scope);
    }
    return false;
  }

  bool Subject::has(Scope* scope, const std::string& name) {
    if (types.size() == 1) {
      return types[0]->has(scope, name);
    }
    return false;
  }

  Result* Subject::get(Scope* scope,
                       mavka::ast::ASTNode* node,
                       const std::string& name) {
    if (types.size() == 1) {
      return success(types[0]->get(scope, name));
    }
    return scope->error(node, "Неможливо отримати властивість \"" + name +
                                  "\" з субʼєкта декількох типів.");
  }

  Result* Subject::set(Scope* scope,
                       mavka::ast::ASTNode* node,
                       const std::string& name,
                       Subject* value) {
    if (types.size() == 1) {
      return types[0]->set(scope, node, name, value);
    }
    return scope->error(node, "Неможливо змінити властивість \"" + name +
                                  "\" субʼєкта декількох типів.");
  }

  bool Subject::has_diia(Scope* scope, std::string name) {
    if (this->has(scope, name)) {
      const auto subject_result = this->get(scope, nullptr, name);
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
    if (types.size() == 1) {
      return types[0]->call(scope, node, generic_types, args);
    }
    return scope->error(node, "Неможливо викликати субʼєкт декількох типів.");
  }

  Result* Subject::magic_call(Scope* scope,
                              mavka::ast::ASTNode* node,
                              std::string name,
                              std::vector<Subject*> generic_types,
                              std::vector<Subject*> args) {
    if (this->types.size() == 1) {
      return this->types[0]->magic_call(scope, node, name, generic_types, args);
    }
    return error_3(scope, node, name);
  }

  Result* Subject::test_and(Scope* scope,
                            mavka::ast::ASTNode* node,
                            Subject* value) {
    const auto newsubj = new Subject();
    for (const auto type : this->types) {
      newsubj->add_type(type);
    }
    for (const auto type : value->types) {
      newsubj->add_type(type);
    }
    return success(newsubj);
  }

  Result* Subject::test_or(Scope* scope,
                           mavka::ast::ASTNode* node,
                           Subject* value) {
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
    if (types.size() == 1) {
      return types[0]->is_iterator(scope);
    }
    return false;
  }

  Result* Subject::get_iterator_type(Scope* scope, mavka::ast::ASTNode* node) {
    if (!this->is_iterator(scope)) {
      return scope->error(node, "Неможливо отримати тип ітератора.");
    }
    return types[0]->get_iterator_type(scope, node);
  }

  bool Subject::is_awaiting(Scope* scope) {
    if (types.size() == 1) {
      return types[0]->is_awaiting(scope);
    }
    return false;
  }

  Result* Subject::get_awaiting_value(Scope* scope, mavka::ast::ASTNode* node) {
    if (!this->is_awaiting(scope)) {
      return scope->error(node, "Неможливо отримати тип очікування.");
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