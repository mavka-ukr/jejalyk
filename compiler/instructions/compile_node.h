#ifndef COMPILE_NODE_H
#define COMPILE_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_node(mavka::ast::ASTNode* node,
                                      CompilationScope* scope,
                                      CompilationOptions* options,
                                      CompilationState* state);
}

#endif  // COMPILE_NODE_H
