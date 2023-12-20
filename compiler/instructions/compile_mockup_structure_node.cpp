#include "compile_mockup_structure_node.h"

#include "../../tools.h"
#include "compile_structure_params.h"

namespace jejalyk {
  NodeCompilationResult* compile_mockup_structure_node(
      const mavka::ast::MockupStructureNode* mockup_structure,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    const auto node_compilation_result = new NodeCompilationResult();

    const auto name = mockup_structure->name;
    std::vector<CompilationObjectStructureParam*> compilation_structure_params;

    const auto structure_compilation_type = new CompilationObject();
    structure_compilation_type->type = CompilationObject::STRUCTURE;
    structure_compilation_type->structure_params = compilation_structure_params;
    const auto compilation_subject = new CompilationSubject();
    compilation_subject->types.push_back(structure_compilation_type);
    const auto constructor_diia = new CompilationObject();
    constructor_diia->type = CompilationObject::DIIA;
    constructor_diia->diia_params =
        compilation_object_structure_params_to_diia_params(
            compilation_structure_params);
    constructor_diia->diia_return_type = compilation_subject;
    const auto constructor_diia_compilation_subject = new CompilationSubject();
    constructor_diia_compilation_subject->types.push_back(constructor_diia);
    structure_compilation_type->properties["чародія_викликати"] =
        constructor_diia_compilation_subject;

    if (const auto define_error = scope->define(name, compilation_subject)) {
      node_compilation_result->error = define_error;
      return node_compilation_result;
    }

    return node_compilation_result;
  }

}  // namespace jejalyk
