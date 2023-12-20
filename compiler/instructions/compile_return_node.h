#ifndef COMPILE_RETURN_NODE_H
#define COMPILE_RETURN_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_return_node(
      const mavka::ast::ReturnNode* return_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_RETURN_NODE_H
