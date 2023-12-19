#pragma once

#ifndef COMPILATION_RESULT_H
#define COMPILATION_RESULT_H

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
#endif //COMPILATION_RESULT_H