#include "compiler.h"

namespace supercompiler {
  Param* Param::clone() {
    const auto param = new Param();
    param->index = this->index;
    param->name = this->name;
    param->types = this->types;
    param->value = this->value;
    param->variadic = this->variadic;
    return param;
  }
}  // namespace supercompiler