#ifndef COMPILE_TRY_NODE_H
#define COMPILE_TRY_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_try_node(const mavka::ast::TryNode* try_node,
                                          CompilationScope* scope,
                                          CompilationOptions* options,
                                          CompilationState* state);
}

#endif  // COMPILE_TRY_NODE_H
