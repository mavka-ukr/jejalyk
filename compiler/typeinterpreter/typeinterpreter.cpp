#include "typeinterpreter.h"

namespace typeinterpreter {
  Result* error(const std::string& message) {
    const auto result = new Result();
    result->error = new Error();
    result->error->message = message;
    return result;
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
    empty_subject->types.push_back(empty_type);

    const auto object_object = new Object();
    object_object->name = "обʼєкт";
    const auto object_type = new Type(object_object);
    const auto object_subject = new Subject();
    object_subject->types.push_back(object_type);

    const auto structure_object = new Object();
    structure_object->name = "Структура";
    structure_object->structure = object_type;
    const auto structure_type = new Type(structure_object);
    const auto structure_subject = new Subject();
    structure_subject->types.push_back(structure_type);

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

      const auto compiled_node_result = scope->compile_node(node);
      if (compiled_node_result->error) {
        return compiled_node_result;
      }
    }

    return new Result();
  }
} // namespace typeinterpreter