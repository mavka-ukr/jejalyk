#include "../typeinterpreter.h"

namespace typeinterpreter {
  Result* compile_structure_node(Scope* scope,
                                 mavka::ast::StructureNode* structure_node) {
    const auto structure_compilation_result = scope->compile_structure(
        structure_node->name, structure_node->generics, "", {},
        structure_node->params, structure_node->methods);
    if (structure_compilation_result->error) {
      return structure_compilation_result;
    }
    scope->set_local(structure_node->name, structure_compilation_result->value);
    return structure_compilation_result;
  }
} // namespace typeinterpreter