#ifndef COMPILE_TYPE_VALUE_SINGLE_NODE_H
#define COMPILE_TYPE_VALUE_SINGLE_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_type_value_single_node(mavka::ast::TypeValueSingleNode* node,
                                                              CompilationScope* scope,
                                                              CompilationOptions* options);
}

#endif //COMPILE_TYPE_VALUE_SINGLE_NODE_H
