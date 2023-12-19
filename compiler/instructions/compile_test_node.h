#ifndef COMPILE_TEST_NODE_H
#define COMPILE_TEST_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_test_node(const mavka::ast::TestNode* test_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options);
}

#endif //COMPILE_TEST_NODE_H
