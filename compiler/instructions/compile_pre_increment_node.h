#ifndef COMPILE_PRE_INCREMENT_NODE_H
#define COMPILE_PRE_INCREMENT_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {

  NodeCompilationResult* compile_pre_increment_node(
      const mavka::ast::PreIncrementNode* pre_increment_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_PRE_INCREMENT_NODE_H
