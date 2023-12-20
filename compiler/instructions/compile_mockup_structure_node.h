#ifndef COMPILE_MOCKUP_STRUCTURE_NODE_H
#define COMPILE_MOCKUP_STRUCTURE_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_mockup_structure_node(
      const mavka::ast::MockupStructureNode* mockup_structure,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_MOCKUP_STRUCTURE_NODE_H
