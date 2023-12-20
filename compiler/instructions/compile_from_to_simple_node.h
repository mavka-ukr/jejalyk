#ifndef COMPILE_FROM_TO_SIMPLE_NODE_H
#define COMPILE_FROM_TO_SIMPLE_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_from_to_simple_node(
      const mavka::ast::FromToSimpleNode* from_to_simple_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_FROM_TO_SIMPLE_NODE_H
