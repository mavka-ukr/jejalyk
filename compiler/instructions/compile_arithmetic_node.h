#ifndef COMPILE_ARITHMETIC_NODE_H
#define COMPILE_ARITHMETIC_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_arithmetic_node(const mavka::ast::ArithmeticNode* arithmetic_node,
                                                   CompilationScope* scope,
                                                   CompilationOptions* options);
}

#endif //COMPILE_ARITHMETIC_NODE_H
