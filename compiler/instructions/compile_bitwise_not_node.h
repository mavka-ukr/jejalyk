#ifndef COMPILE_BITWISE_NOT_NODE_H
#define COMPILE_BITWISE_NOT_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_bitwise_not_node(
      const mavka::ast::BitwiseNotNode* bitwise_not_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_BITWISE_NOT_NODE_H
