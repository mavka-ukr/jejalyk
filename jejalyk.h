#ifndef JEJALYK_H
#define JEJALYK_H

#include <string>

#include "typeinterpreter/typeinterpreter.h"

namespace jejalyk {
  class CompilationError final {
   public:
    std::string path;
    size_t line;
    size_t column;
    std::string message;
  };

  class CompilationResult final {
   public:
    CompilationError* error;
    std::string result;
  };

  CompilationResult* compile(const std::string& code,
                             typeinterpreter::Options* options);
} // namespace jejalyk

#endif // JEJALYK_H
