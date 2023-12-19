#ifndef COMPILE_ASSIGN_BY_IDENTIFIER_NODE_H
#define COMPILE_ASSIGN_BY_IDENTIFIER_NODE_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_assign_by_identifier_node(const mavka::ast::AssignByIdentifierNode* assign_by_identifier_node,
           CompilationScope* scope,
           CompilationOptions* options);
}

#endif //COMPILE_ASSIGN_BY_IDENTIFIER_NODE_H
