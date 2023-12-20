#ifndef COMPILE_EACH_NODE_H
#define COMPILE_EACH_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_each_node(
      const mavka::ast::EachNode* each_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_EACH_NODE_H
