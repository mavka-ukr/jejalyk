#ifndef COMPILE_CALL_NODE_H
#define COMPILE_CALL_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_call_node(
      const mavka::ast::CallNode* call_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_CALL_NODE_H
