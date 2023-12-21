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

структура список
кінець

дія друк(...значення список)
кінець

структура Конв1Д
  в список
кінець

дія Конв1Д.створити(розмір)
  я.в = []
  розмір = розмір - 1
  перебрати 0..розмір як х
    я.в[х] = 0.5
  кінець
кінець

дія Конв1Д.активувати(вхід)
  вихід = []
  д_в = я.в.довжина()
  д_вх = вхід.довжина()

  перебрати 0..(д_вх - д_в) як х1
    т = []
    перебрати 0..(д_в - 1) як ін
      т[ін] = (вхід[(ін + х1)] * я.в[ін])
    кінець
    рез = 0
    перебрати 0..(д_в - 1) як ін
      рез = рез + т[ін]
    кінець
    вихід[х1] = рез
  кінець

  вернути вихід
кінець

вхід = [1,1,1,1,1,1,1,1]

к1 = Конв1Д([])
к1.створити(3)
к1.в = [0.4974,-0.1678,-0.4847]

друк(к1.активувати(вхід))
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