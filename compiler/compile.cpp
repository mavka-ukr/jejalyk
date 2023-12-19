#include "compile.h"

#include "CompilationScope.h"
#include "CompilationOptions.h"
#include "CompilationResult.h"
#include "../ast.h"
#include "../parser.h"

namespace jejalyk {
    std::string varname(const std::string& name) {
        return "м_" + name;
    }
}
