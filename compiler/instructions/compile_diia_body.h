#ifndef COMPILE_DIIA_BODY_H
#define COMPILE_DIIA_BODY_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {

    NodeCompilationResult* compile_diia_body(const std::vector<mavka::ast::ASTNode *>& body,
                                             const std::vector<mavka::ast::ParamNode *>& params,
                                             CompilationScope* scope,
                                             CompilationOptions* options,
                                             const bool wrap = true,
                                             const bool parent = false);

}

#endif //COMPILE_DIIA_BODY_H
