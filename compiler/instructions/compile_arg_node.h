#ifndef COMPILE_ARG_NODE_H
#define COMPILE_ARG_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_arg_node(const mavka::ast::ArgNode* arg_node,
                                          CompilationScope* scope,
                                          CompilationOptions* options,
                                          CompilationState* state);
}

#endif  // COMPILE_ARG_NODE_H
