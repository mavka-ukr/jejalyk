#include "typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Subject* process_subject_generics(Object* object,
                                    std::vector<Subject*> generic_types,
                                    Subject* subject) {
    const auto processed_subject = new Subject();
    for (const auto type : subject->types) {
      if (type->generic_definition) {
        if (type->generic_definition->object == object) {
          if constexpr (JJ_DEBUG) {
            std::cout << "[debug] process_subject_generics: "
                      << type->generic_definition->name << " | "
                      << type->generic_definition->object->name
                      << " == " << object->name << std::endl;
          }
          const auto generic = generic_types[type->generic_definition->index];
          const auto generic_type = generic->types[0];

          processed_subject->add_type(generic_type);
        } else {
          if constexpr (JJ_DEBUG) {
            std::cout << "[debug] process_subject_generics: "
                      << type->generic_definition->name << " | "
                      << type->generic_definition->object->name << "["
                      << type->generic_definition->object
                      << "] != " << object->name << "[" << object << "]"
                      << std::endl;
          }
          processed_subject->add_type(type);
        }
      } else {
        const auto newtype = new Type();
        newtype->object = type->object;

        for (const auto& generic_type_value : type->generic_types) {
          newtype->generic_types.push_back(process_subject_generics(
              object, generic_types, generic_type_value));
        }

        processed_subject->types.push_back(newtype);
      }
    }
    return processed_subject;
  }

  Result* error_0(Scope* scope,
                  mavka::ast::ASTNode* node,
                  const std::string& subject_name,
                  Subject* expected,
                  Subject* got) {
    return scope->error(node, "Невірний тип субʼєкта \"" + subject_name +
                                  "\": "
                                  "очікується \"" +
                                  expected->types_string() + "\", отримано \"" +
                                  got->types_string() + "\".");
  }

  Result* error_1(Scope* scope,
                  mavka::ast::ASTNode* node,
                  const std::string& subject_name) {
    return scope->error(node,
                        "Субʼєкт \"" + subject_name + "\" вже визначено.");
  }

  Result* error_2(Scope* scope,
                  mavka::ast::ASTNode* node,
                  const std::string& property_name,
                  Subject* subject) {
    return scope->error(node, "Неможливо отримати властивість \"" +
                                  property_name + "\" з типу \"" +
                                  subject->types_string() + "\".");
  }

  Result* error(const std::string& message) {
    const auto result = new Result();
    result->error = new Error();
    result->error->message = message;
    return result;
  }

  Result* success(Subject* value) {
    const auto result = new Result();
    result->value = value;
    return result;
  }

  Result* success(Subject* value, jejalyk::js::JsNode* js_node) {
    const auto result = new Result();
    result->value = value;
    result->js_node = js_node;
    return result;
  }

  Result* success(Subject* value, jejalyk::js::JsBody* js_body) {
    const auto result = new Result();
    result->value = value;
    result->js_body = js_body;
    return result;
  }

  void debug_print_call(Type* value,
                        std::vector<Subject*> generic_types,
                        std::vector<Subject*> args) {
    if constexpr (JJ_DEBUG) {
      std::cout << "[debug] CALL " << value->get_name();
      if (generic_types.size()) {
        std::cout << "<";
        for (int i = 0; i < generic_types.size(); ++i) {
          if (i > 0) {
            std::cout << ", ";
          }
          std::cout << generic_types[i]->types_string();
        }
        std::cout << ">";
      }
      std::cout << "(";
      for (int i = 0; i < args.size(); ++i) {
        if (i > 0) {
          std::cout << ", ";
        }
        std::cout << args[i]->types_string();
      }
      std::cout << ")" << std::endl;
    }
  }

  void debug_print_check_subjects(Subject* value, Subject* types) {
    if constexpr (JJ_DEBUG) {
      std::cout << "[debug] CHECK " << value->types_string() << " AND "
                << types->types_string() << std::endl;
    }
  }

  void debug_print_got_from_scope(Scope* scope,
                                  std::string name,
                                  Subject* value) {
    if constexpr (JJ_DEBUG) {
      std::cout << "[debug] GOT " << name << " " << value->types_string()
                << std::endl;
    }
  }

  void debug_print_bug(const std::vector<std::string>& messages) {
    std::cout << "[INTERNAL BUG]";
    for (const auto& message : messages) {
      std::cout << " " << message;
    }
    std::cout << std::endl;
  }

  void debug_print_bug(const std::string& message) {
    std::cout << "[INTERNAL BUG] " << message << std::endl;
  }
} // namespace typeinterpreter