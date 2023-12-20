#ifndef COMPILE_DIIA_NODE_H
#define COMPILE_DIIA_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_diia_node(
      const mavka::ast::DiiaNode* diia_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_DIIA_NODE_H
