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

  Result* compile(std::string code) {
    const auto root_code = R"(
макет структура Дія
  назва текст
кінець

макет структура Модуль
  назва текст
кінець

макет структура очікування<Т>
кінець

макет структура перебір<З>
  завершено логічне
  значення З
  далі()
кінець

макет структура перебір_з_ключем<К, З>
  завершено логічне
  ключ К
  значення З
  далі()
кінець

макет структура логічне
  чародія_логічне() логічне
  чародія_число() число
  чародія_текст() текст
кінець

макет субʼєкт так логічне
макет субʼєкт ні логічне

макет структура число
  чародія_додати(значення число) число
  чародія_відняти(значення число) число
  чародія_помножити(значення число) число
  чародія_поділити(значення число) число
  чародія_бні() число
  чародія_додатнє() число
  чародія_відʼємне() число
  чародія_більше(значення число) логічне
  чародія_менше(значення число) логічне
  чародія_не_більше(значення число) логічне
  чародія_не_менше(значення число) логічне
  чародія_зменшити_після() число
  чародія_збільшити_після() число
  чародія_логічне() логічне
  чародія_число() число
  чародія_текст() текст
кінець

макет структура текст
  довжина число

  чародія_додати(значення текст) текст
  чародія_логічне() логічне
  чародія_число() число
  чародія_текст() текст
  чародія_перебір() перебір<текст>
  чародія_перебір_з_ключем() перебір_з_ключем<число, текст>
кінець

макет структура список<Т>
  довжина число

  додати(значення Т) список<Т>
  отримати(позиція число) Т або пусто
  очистити() список<Т>

  чародія_отримати(позиція число) Т
  чародія_покласти(позиція число, значення Т) Т
  чародія_логічне() логічне
  чародія_число() число
  чародія_текст() текст
  чародія_перебір() перебір<Т>
  чародія_перебір_з_ключем() перебір_з_ключем<число, Т>
  чародія_додатнє()
кінець

макет структура словник<К, З>
  розмір число

  отримати(ключ К) З або пусто
  ключі() перебір<К>
  значення() перебір<З>
  очистити() словник<К, З>

  чародія_отримати(ключ К) З
  чародія_покласти(ключ К, значення З) З
  чародія_перебір() перебір<К>
  чародія_перебір_з_ключем() перебір_з_ключем<К, З>
кінець
)";

    const auto root_parser_result = mavka::parser::parse(root_code);
    if (root_parser_result->error) {
      return error(root_parser_result->error->message);
    }

    const auto parser_result = mavka::parser::parse(code);
    if (parser_result->error) {
      return error(root_parser_result->error->message);
    }

    const auto root_scope = new Scope();
    root_scope->is_async = true;

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
    structure_object->parent = object_type;
    const auto structure_type = new Type(structure_object);
    const auto structure_subject = new Subject();
    structure_subject->add_type(structure_type);

    empty_object->structure = object_type;
    object_object->structure = structure_type;

    root_scope->set_local("пусто", empty_subject);
    root_scope->set_local("обʼєкт", object_subject);
    root_scope->set_local("Структура", structure_subject);

    const auto compiled_root_body =
        root_scope->compile_body(root_parser_result->program_node->body);
    if (compiled_root_body->error) {
      return compiled_root_body;
    }

    const auto program_scope = root_scope->make_child();
    const auto compiled_body =
        program_scope->compile_body(parser_result->program_node->body);
    if (compiled_body->error) {
      return compiled_body;
    }

    return compiled_body;
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