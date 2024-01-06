#include <fstream>
#include <iostream>
#include <string>
#include "jejalyk.h"

int main() {
  const auto options = new jejalyk::typeinterpreter::Options();
  options->std_code = R"(
js """
var друк = мДія("друк", function(values) {
  console.log(...values.map((v) => мГарно(v)));
});
"""

макет дія друк(...значення список<обʼєкт>) пусто
)";

  std::ifstream code_file("тест.м");
  std::stringstream buffer;
  buffer << code_file.rdbuf();
  std::string code = buffer.str();

  const auto compilation_result = jejalyk::compile(code, options);
  if (compilation_result->error) {
    std::cout << compilation_result->error->message << std::endl;
  } else {
    std::cout << "ok" << std::endl;
  }
}