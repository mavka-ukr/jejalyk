#ifndef COMPILE_EVAL_NODE_H
#define COMPILE_EVAL_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_eval_node(mavka::ast::EvalNode* eval_node,
                                             CompilationScope* scope,
                                             CompilationOptions* options);
}

#endif //COMPILE_EVAL_NODE_H
