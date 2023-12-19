#ifndef COMPILE_BODY_H
#define COMPILE_BODY_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {

    NodeCompilationResult* compile_body(const std::vector<mavka::ast::ASTNode *>& body,
                                        CompilationScope* scope,
                                        CompilationOptions* options,
                                        const bool wrap = true,
                                        const std::string& before = "",
                                        const bool handle_return = false);

}

#endif //COMPILE_BODY_H
