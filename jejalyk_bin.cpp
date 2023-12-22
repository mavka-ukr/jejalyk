#include <iostream>

#include "compiler/supercompiler/compiler.h"
#include "parser.h"

int main() {
  const auto code = R"(
структура Дія
кінець

структура число
кінець

дія число.чародія_створити(значення) число
кінець

дія число.чародія_додати(значення) число
кінець

дія число.чародія_відняти(значення) число
кінець

дія число.чародія_помножити(значення) число
кінець

дія число.чародія_поділити(значення) число
кінець

структура текст
кінець

дія текст.чародія_створити(значення) текст
кінець

дія текст.чародія_додати(значення) текст
кінець

структура список
  довжина число
кінець

дія список.чародія_змінити_спеціальну_властивість(позиція, значення)
кінець

дія список.чародія_отримати_спеціальну_властивість(позиція)
кінець

структура словник
кінець

дія друк(...значення список)
кінець

;; ---
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