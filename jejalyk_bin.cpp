#include <iostream>

#include "compiler/supercompiler/compiler.h"
#include "parser.h"

int main() {
  const auto code = R"(
макет структура Дія
кінець

макет структура логічне
  чародія_створити(значення обʼєкт або пусто) логічне
кінець

макет субʼєкт так логічне
макет субʼєкт ні логічне

макет структура число
  чародія_створити(значення обʼєкт або пусто) число
  чародія_додати(значення число) число
  чародія_відняти(значення число) число
  чародія_помножити(значення число) число
  чародія_поділити(значення число) число
кінець

макет структура текст
  чародія_створити(значення обʼєкт або пусто) текст
  чародія_додати(значення текст) текст
кінець

макет структура список
  довжина число

  чародія_змінити_спеціальну_властивість(позиція, значення)
  чародія_отримати_спеціальну_властивість(позиція)
кінець

макет структура словник
кінець

макет дія друк(...значення список)

;; ---

а = текст(2)
)";
  const auto parser_result = mavka::parser::parse(code);
  if (parser_result->error) {
    std::cout << parser_result->error->message << std::endl;
    return 1;
  }
  const auto result = supercompiler::compile(parser_result->program_node);
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