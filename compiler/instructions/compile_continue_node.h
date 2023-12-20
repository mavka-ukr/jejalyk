#ifndef COMPILE_CONTINUE_NODE_H
#define COMPILE_CONTINUE_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_continue_node(
      mavka::ast::ContinueNode* continue_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_CONTINUE_NODE_H
