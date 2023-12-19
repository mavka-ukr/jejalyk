#ifndef COMPILE_NOT_NODE_H
#define COMPILE_NOT_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {


    NodeCompilationResult* compile_not_node(const mavka::ast::NotNode* not_node,
                                            CompilationScope* scope,
                                            CompilationOptions* options);
}

#endif //COMPILE_NOT_NODE_H
