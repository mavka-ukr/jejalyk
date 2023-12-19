#ifndef COMPILE_PARAMS_H
#define COMPILE_PARAMS_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_params(std::vector<mavka::ast::ParamNode *> params,
                                          CompilationScope* scope,
                                          CompilationOptions* options);

}

#endif //COMPILE_PARAMS_H
