#ifndef COMPILE_NUMBER_NODE_H
#define COMPILE_NUMBER_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {

    NodeCompilationResult* compile_number_node(const mavka::ast::NumberNode* number_node,
                                               CompilationScope* scope,
                                               CompilationOptions* options);
}

#endif //COMPILE_NUMBER_NODE_H
