#ifndef COMPILE_POST_DECREMENT_NODE_H
#define COMPILE_POST_DECREMENT_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {

  NodeCompilationResult* compile_post_decrement_node(
      const mavka::ast::PostDecrementNode* post_decrement_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_POST_DECREMENT_NODE_H
