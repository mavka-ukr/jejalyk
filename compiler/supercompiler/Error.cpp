#include "compiler.h"

namespace supercompiler {
  Result* error(const std::string& message) {
    const auto result = new Result();
    result->error = new Error();
    result->error->message = message;
    return result;
  }

  Result* success(Subject* value) {
    const auto result = new Result();
    result->value = value;
    return result;
  }
}  // namespace supercompiler