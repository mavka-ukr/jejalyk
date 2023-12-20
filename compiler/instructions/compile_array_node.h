#ifndef COMPILE_ARRAY_NODE_H
#define COMPILE_ARRAY_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_array_node(
      const mavka::ast::ArrayNode* array_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_ARRAY_NODE_H
