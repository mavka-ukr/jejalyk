#ifndef COMPILE_
#define COMPILE_

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_arg_node(const mavka::ast::ArgNode* arg_node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);
}

#endif //COMPILE_
