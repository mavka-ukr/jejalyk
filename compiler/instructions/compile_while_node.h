#ifndef COMPILE_WHILE_NODE_H
#define COMPILE_WHILE_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_while_node(
      const mavka::ast::WhileNode* while_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_WHILE_NODE_H
