#ifndef COMPILE_POSITIVE_NODE_H
#define COMPILE_POSITIVE_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {

  NodeCompilationResult* compile_positive_node(
      const mavka::ast::PositiveNode* positive_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_POSITIVE_NODE_H
