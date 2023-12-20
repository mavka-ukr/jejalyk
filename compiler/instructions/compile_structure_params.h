#ifndef COMPILE_STRUCTURE_PARAMS_H
#define COMPILE_STRUCTURE_PARAMS_H

#include "../../ast.h"
#include "../compile.h"

namespace jejalyk {
  StructureParamsCompilationResult* compile_structure_params(
      const std::vector<mavka::ast::StructureParamNode*>& params,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state);

}

#endif  // COMPILE_STRUCTURE_PARAMS_H
