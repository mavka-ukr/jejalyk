#include <iostream>

#include "compiler/newcompiler.h"
#include "parser.h"

int main() {
  const auto code = R"(
структура Дія
кінець

структура текст
кінець

структура число
кінець

структура А
  а текст
  б обʼєкт
кінець

дія привіт(а число) число
кінець

лол число = привіт(2)
)";
  const auto parser_result = mavka::parser::parse(code);
  if (parser_result->error) {
    std::cout << parser_result->error->message << std::endl;
    return 1;
  }
  const auto result = newcompiler::compile(parser_result->program_node);
  if (result->error) {
    std::cout << result->error->message << std::endl;
    return 1;
  }
  std::cout << "compilation successful" << std::endl;
  return 0;
}