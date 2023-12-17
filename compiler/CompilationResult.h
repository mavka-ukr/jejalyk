#pragma once

#include <string>

#include "CompilationError.h"

namespace jejalyk {
    class NodeCompilationResult {
    public:
        CompilationError* error = nullptr;
        std::string result;
    };

    class CompilationResult : public NodeCompilationResult {
    };
}
