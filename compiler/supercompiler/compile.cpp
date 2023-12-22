#include "compiler.h"

namespace supercompiler {
  CompilationResult* compile(mavka::ast::ProgramNode* program_node) {
    const auto result = new CompilationResult();

    const auto scope = new Scope();
    scope->body = &program_node->body;

    const auto object = new Object();
    const auto structure = new Object();
    structure->structure = object;

    const auto object_subject = new Subject();
    object_subject->types.push_back(object);
    const auto structure_subject = new Subject();
    structure_subject->types.push_back(structure);

    scope->variables.insert_or_assign("обʼєкт", object_subject);
    scope->variables.insert_or_assign("Структура", structure_subject);

    for (int i = 0; i < program_node->body.size(); ++i) {
      const auto node = program_node->body[i];
      if (!node) {
        continue;
      }

      const auto compiled_node = scope->compile_node(node);
      if (compiled_node->error) {
        result->error = compiled_node->error;
        return result;
      }
    }

    return result;
  }
}