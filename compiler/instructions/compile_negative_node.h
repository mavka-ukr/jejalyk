#ifndef COMPILE_NEGATIVE_NODE_H
#define COMPILE_NEGATIVE_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {

  NodeCompilationResult* compile_negative_node(
      const mavka::ast::NegativeNode* negative_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_NEGATIVE_NODE_H
