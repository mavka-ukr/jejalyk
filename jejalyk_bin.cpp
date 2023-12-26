#include <iostream>

#include "compiler/typeinterpreter/typeinterpreter.h"
#include "parser.h"

int main() {
  const auto code = R"(
макет структура Дія
кінець

макет структура Щось
кінець

макет структура А<АТ>
  т АТ
кінець

А<А<Дія>>(А<Щось>(Щось()))
)";
  const auto parser_result = mavka::parser::parse(code);
  if (parser_result->error) {
    std::cout << parser_result->error->message << std::endl;
    return 1;
  }
  const auto result = typeinterpreter::compile(parser_result->program_node);
  if (result->error) {
    if (result->error->full) {
      std::cout << result->error->line << ":" << result->error->column << ": ";
    }
    std::cout << result->error->message << std::endl;
    return 1;
  }
  std::cout << "compilation successful" << std::endl;
  return 0;
}