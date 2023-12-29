#include <iostream>

#include "compiler/typeinterpreter/typeinterpreter.h"

int main() {
  const auto code = R"(
дія друк(значення текст) пусто
кінець

поки так
  друк("так")
кінець

ауф = (а текст, б, в) пусто: друк(а)
)";
  const auto result = typeinterpreter::compile(code);
  if (result->error) {
    if (result->error->full) {
      std::cout << result->error->line << ":" << result->error->column << ": ";
    }
    std::cout << result->error->message << std::endl;
    return 1;
  }
  std::cout << "compilation successful" << std::endl;
  std::cout << jejalyk::js::stringify_body(result->js_body) << std::endl;
  return 0;
}