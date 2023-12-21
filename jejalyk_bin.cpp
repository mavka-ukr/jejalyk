#include <iostream>

#include "compiler/supercompiler.h"
#include "parser.h"

int main() {
  const auto code = R"(
структура Дія
кінець

структура число
кінець

структура текст
кінець

структура А
  значення число = 2
кінець

дія привіт(а число)
кінець

ф = 2
ф = "2"
х = привіт(ф)
)";
  const auto parser_result = mavka::parser::parse(code);
  if (parser_result->error) {
    std::cout << parser_result->error->message << std::endl;
    return 1;
  }
  const auto result = supercompiler::compile(parser_result->program_node);
  if (result->error) {
    std::cout << result->error->message << std::endl;
    return 1;
  }
  std::cout << "compilation successful" << std::endl;
  return 0;
}