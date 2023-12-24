#include "typeinterpreter.h"

namespace typeinterpreter {
  Result* error(const std::string& message) {
    const auto result = new Result();
    result->error = new Error();
    result->error->message = message;
    return result;
  }

  Result* error_from_ast(const mavka::ast::ASTNode* node,
                         const std::string& message) {
    const auto result = new Result();
    result->error = new Error();
    result->error->full = true;
    result->error->line = node->start_line;
    result->error->column = node->start_column;
    result->error->message = message;
    return result;
  }

  Result* success(Subject* value) {
    const auto result = new Result();
    result->value = value;
    return result;
  }

  Result* compile(mavka::ast::ProgramNode* program_node) {
    return new Result();
  }
} // namespace typeinterpreter