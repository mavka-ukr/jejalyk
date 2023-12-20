#ifndef COMPILE_IF_NODE_H
#define COMPILE_IF_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_if_node(const mavka::ast::IfNode* if_node,
                                         CompilationScope* scope,
                                         CompilationOptions* options,
                                         CompilationState* state);
}

#endif  // COMPILE_IF_NODE_H
