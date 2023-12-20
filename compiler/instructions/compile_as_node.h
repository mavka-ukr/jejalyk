#ifndef COMPILE_AS_NODE_H
#define COMPILE_AS_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_as_node(const mavka::ast::AsNode* as_node,
                                         CompilationScope* scope,
                                         CompilationOptions* options,
                                         CompilationState* state);
}

#endif  // COMPILE_AS_NODE_H
