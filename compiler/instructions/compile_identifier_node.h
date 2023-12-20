#ifndef COMPILE_IDENTIFIER_NODE_H
#define COMPILE_IDENTIFIER_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_identifier_node(
      const mavka::ast::IdentifierNode* identifier_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_IDENTIFIER_NODE_H
