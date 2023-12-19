#ifndef COMPILE_STRUCTURE_PARAMS_H
#define COMPILE_STRUCTURE_PARAMS_H

#include "../../ast.h"
#include "../CompilationResult.h"
#include "../CompilationScope.h"
#include "../CompilationOptions.h"

namespace jejalyk {
    NodeCompilationResult* compile_structure_params(std::vector<mavka::ast::StructureParamNode *> params,
                                                    CompilationScope* scope,
                                                    CompilationOptions* options);

}

#endif //COMPILE_STRUCTURE_PARAMS_H
