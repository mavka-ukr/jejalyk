#ifndef COMPILE_EVAL_NODE_H
#define COMPILE_EVAL_NODE_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  NodeCompilationResult* compile_eval_node(mavka::ast::EvalNode* eval_node,
                                           CompilationScope* scope,
                                           CompilationOptions* options,
                                           CompilationState* state);
}

#endif  // COMPILE_EVAL_NODE_H
