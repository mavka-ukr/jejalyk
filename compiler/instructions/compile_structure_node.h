#ifndef COMPILE_STRUCTURE_NODE_H
#define COMPILE_STRUCTURE_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_structure_node(
      const mavka::ast::StructureNode* structure_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_STRUCTURE_NODE_H
