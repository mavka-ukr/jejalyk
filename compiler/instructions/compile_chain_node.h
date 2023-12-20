#ifndef COMPILE_CHAIN_NODE_H
#define COMPILE_CHAIN_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_chain_node(
      const mavka::ast::ChainNode* chain_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_CHAIN_NODE_H
