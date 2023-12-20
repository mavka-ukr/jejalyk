#ifndef COMPILE_FUNCTION_NODE_H
#define COMPILE_FUNCTION_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_function_node(
      const mavka::ast::FunctionNode* function_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_FUNCTION_NODE_H
