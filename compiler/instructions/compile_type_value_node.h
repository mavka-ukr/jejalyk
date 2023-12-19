#ifndef COMPILE_TYPE_VALUE_NODE_H
#define COMPILE_TYPE_VALUE_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_type_value_node(mavka::ast::TypeValueNode* type_value_node,
                                                       CompilationScope* scope,
                                                       CompilationOptions* options);
}

#endif //COMPILE_TYPE_VALUE_NODE_H
