#include <iostream>

#include "compiler/typeinterpreter/typeinterpreter.h"

int main() {
  const auto code = R"(
а = []

дія привіт(а число, б текст) обʼєкт
  а = 3
кінець

тривала дія запустити(а число, б текст) обʼєкт
  а = 3
  вернути чекати запустити(1, "2")
кінець

структура А
кінець

привіт(1, "2")
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