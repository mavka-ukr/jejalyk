#include "compile_structure_node.h"

#include <any>

#include "../compile.h"
#include "compile_node.h"
#include "compile_structure_params.h"

namespace jejalyk {
  NodeCompilationResult* compile_structure_node(
      const mavka::ast::StructureNode* structure_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    const auto node_compilation_result = new NodeCompilationResult();

    const std::string name = structure_node->name;

    if (scope->has_local(name)) {
      node_compilation_result->error = compilation_error_from_message(
          "Неможливо перевизначити структуру \"" + name + "\".");
      return node_compilation_result;
    }

    const auto compiled_params =
        compile_structure_params(structure_node->params, scope, options, state);
    if (compiled_params->error) {
      node_compilation_result->error = compiled_params->error;
      return node_compilation_result;
    }

    std::string parent = "undefined";
    if (structure_node->parent) {
      const auto compiled_parent =
          compile_node(structure_node->parent, scope, options, state);
      if (compiled_parent->error) {
        node_compilation_result->error = compiled_parent->error;
        return node_compilation_result;
      }
      parent = compiled_parent->result;
    }
    node_compilation_result->result = varname(name) + "=" + MAVKA_STRUCTURE +
                                      "(" + "\"" + structure_node->name + "\"" +
                                      "," + compiled_params->result + "," +
                                      parent + ")";

    const auto structure_compilation_type = new CompilationObject();
    structure_compilation_type->type = CompilationObject::STRUCTURE;
    structure_compilation_type->structure_params =
        compiled_params->structure_params;
    const auto compilation_subject = new CompilationSubject();
    compilation_subject->types.push_back(structure_compilation_type);
    const auto constructor_diia = new CompilationObject();
    constructor_diia->type = CompilationObject::DIIA;
    constructor_diia->diia_params =
        compilation_object_structure_params_to_diia_params(
            compiled_params->structure_params);
    constructor_diia->diia_return_type = compilation_subject;
    const auto constructor_diia_compilation_subject = new CompilationSubject();
    constructor_diia_compilation_subject->types.push_back(constructor_diia);
    structure_compilation_type->properties["чародія_викликати"] =
        constructor_diia_compilation_subject;

    if (const auto define_error =
            scope->define(structure_node->name, compilation_subject)) {
      node_compilation_result->error = define_error;
      return node_compilation_result;
    }

    return node_compilation_result;
  }
}  // namespace jejalyk
