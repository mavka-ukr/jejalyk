#ifndef COMPILE_ARITHMETIC_NODE_H
#define COMPILE_ARITHMETIC_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_arithmetic_node(
      const mavka::ast::ArithmeticNode* arithmetic_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_ARITHMETIC_NODE_H
