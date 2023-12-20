#ifndef COMPILE_FROM_TO_COMPLEX_NODE_H
#define COMPILE_FROM_TO_COMPLEX_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_from_to_complex_node(
      const mavka::ast::FromToComplexNode* from_to_complex_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_FROM_TO_COMPLEX_NODE_H
