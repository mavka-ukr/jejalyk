#include "typeinterpreter.h"

namespace typeinterpreter {
  Subject* process_subject_generics(Object* object,
                                    std::vector<Subject*> generic_types,
                                    Subject* subject) {
    const auto processed_subject = new Subject();
    for (int i = 0; i < subject->types.size(); ++i) {
      const auto type = subject->types[i];

      if (type->generic_definition) {
        if (type->generic_definition->object == object) {
          const auto generic = generic_types[type->generic_definition->index];
          const auto generic_type = generic->types[0];

          processed_subject->add_type(generic_type);
        } else {
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

  Result* error_0(const mavka::ast::ASTNode* node,
                  const std::string& subject_name,
                  Subject* expected,
                  Subject* got) {
    return error_from_ast(node, "Невірний тип субʼєкта \"" + subject_name +
                                    "\": "
                                    "очікується \"" +
                                    expected->types_string() +
                                    "\", отримано \"" + got->types_string() +
                                    "\".");
  }

  Result* error_1(const mavka::ast::ASTNode* node,
                  const std::string& subject_name) {
    return error_from_ast(node,
                          "Субʼєкт \"" + subject_name + "\" вже визначено.");
  }

  Result* error_2(const mavka::ast::ASTNode* node,
                  const std::string& property_name,
                  Subject* subject) {
    return error_from_ast(node, "Неможливо отримати властивість \"" +
                                    property_name + "\" з типу \"" +
                                    subject->types_string() + "\".");
  }

  Result* error_from_ast(const mavka::ast::ASTNode* node,
                         const std::string& message) {
    const auto result = new Result();
    result->error = new Error();
    result->error->full = true;
    result->error->line = node->start_line;
    result->error->column = node->start_column;
    result->error->message = message;
    return result;
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

  Result* compile(mavka::ast::ProgramNode* program_node) {
    const auto result = new Result();

    const auto scope = new Scope();

    const auto empty_object = new Object();
    empty_object->name = "пусто";
    const auto empty_type = new Type(empty_object);
    const auto empty_subject = new Subject();
    empty_subject->add_type(empty_type);

    const auto object_object = new Object();
    object_object->name = "обʼєкт";
    const auto object_type = new Type(object_object);
    const auto object_subject = new Subject();
    object_subject->add_type(object_type);

    const auto structure_object = new Object();
    structure_object->name = "Структура";
    structure_object->structure = object_type;
    const auto structure_type = new Type(structure_object);
    const auto structure_subject = new Subject();
    structure_subject->add_type(structure_type);

    empty_object->structure = object_type;
    object_object->structure = structure_type;

    scope->set_local("пусто", empty_subject);
    scope->set_local("обʼєкт", object_subject);
    scope->set_local("Структура", structure_subject);

    for (int i = 0; i < program_node->body.size(); ++i) {
      const auto node = program_node->body[i];
      if (!node) {
        continue;
      }

      if (jejalyk::tools::instance_of<mavka::ast::MockupStructureNode>(node)) {
        const auto mockup_structure_node =
            dynamic_cast<mavka::ast::MockupStructureNode*>(node);
        const auto compiled_structure_result = scope->compile_structure(
            mockup_structure_node->name, mockup_structure_node->generics, "",
            {}, {}, {});
        if (compiled_structure_result->error) {
          return compiled_structure_result;
        }
        compiled_structure_result->value->types[0]
            ->object->this_is_declaration = true;
        scope->set_local(mockup_structure_node->name,
                         compiled_structure_result->value);
      }
    }

    for (int i = 0; i < program_node->body.size(); ++i) {
      const auto node = program_node->body[i];
      if (!node) {
        continue;
      }

      const auto compiled_node_result = scope->compile_node(node);
      if (compiled_node_result->error) {
        return compiled_node_result;
      }
    }

    return new Result();
  }

  void debug_print_call(Type* value,
                        std::vector<Subject*> generic_types,
                        std::vector<Subject*> args) {
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

  void debug_print_check_subjects(Subject* value, Subject* types) {
    std::cout << "[debug] CHECK " << value->types_string() << " AND "
              << types->types_string() << std::endl;
  }

  void debug_print_got_from_scope(Scope* scope,
                                  std::string name,
                                  Subject* value) {
    std::cout << "[debug] GOT " << name << " " << value->types_string()
              << std::endl;
  }

  void debug_print_bug(const std::vector<std::string>& messages) {
    std::cout << "[BUG]";
    for (const auto& message : messages) {
      std::cout << " " << message;
    }
    std::cout << std::endl;
  }

  void debug_print_bug(const std::string& message) {
    std::cout << "[BUG] " << message << std::endl;
  }
} // namespace typeinterpreter