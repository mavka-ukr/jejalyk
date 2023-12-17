#pragma once

#include <string>

namespace jejalyk {
    class CompilationError {
    public:
        std::string path;
        size_t line{};
        size_t column{};
        std::string message;
    };
}
