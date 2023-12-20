#ifndef COMPILE_GET_ELEMENT_NODE_H
#define COMPILE_GET_ELEMENT_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_get_element_node(
      const mavka::ast::GetElementNode* get_element_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);
}

#endif  // COMPILE_GET_ELEMENT_NODE_H
