#include "compiler.h"

namespace supercompiler {
  CompilationResult* compile(mavka::ast::ProgramNode* program_node) {
    const auto result = new CompilationResult();

    const auto scope = new Scope();
    scope->body = &program_node->body;

    const auto empty = new Object();
    empty->structure_name = "пусто";

    const auto object = new Object();
    object->structure_name = "обʼєкт";

    const auto structure = new Object();
    structure->structure_name = "Структура";
    structure->structure = object;

    empty->structure = object;
    object->structure = structure;

    const auto empty_subject = new Subject();
    empty_subject->types.push_back(empty);
    const auto object_subject = new Subject();
    object_subject->types.push_back(object);
    const auto structure_subject = new Subject();
    structure_subject->types.push_back(structure);

    scope->set("пусто", empty_subject);
    scope->set("обʼєкт", object_subject);
    scope->set("Структура", structure_subject);

    for (int i = 0; i < program_node->body.size(); ++i) {
      const auto node = program_node->body[i];
      if (!node) {
        continue;
      }

      if (jejalyk::tools::instance_of<mavka::ast::StructureNode>(node)) {
        const auto structure_node =
            dynamic_cast<mavka::ast::StructureNode*>(node);
        const auto structure_result = scope->define_structure_from_ast(
            false, structure_node->name, structure_node->generics,
            structure_node->parent, {});
        if (structure_result->error) {
          result->error = structure_result->error;
          return result;
        }
      }
      if (jejalyk::tools::instance_of<mavka::ast::MockupStructureNode>(node)) {
        const auto mockup_structure_node =
            dynamic_cast<mavka::ast::MockupStructureNode*>(node);
        const auto structure_result = scope->define_structure_from_ast(
            true, mockup_structure_node->name, mockup_structure_node->generics,
            mockup_structure_node->parent, {});
        if (structure_result->error) {
          result->error = structure_result->error;
          return result;
        }
      }
    }

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

    for (int i = 0; i < scope->bodies_to_compile.size(); ++i) {
      const auto body_to_compile = scope->bodies_to_compile[i];

      const auto compilation_result =
          body_to_compile->scope->compile_body(body_to_compile->body);
      if (compilation_result->error) {
        result->error = compilation_result->error;
        return result;
      }
    }

    return result;
  }
}