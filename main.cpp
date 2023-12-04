#include <iostream>
#include "jejalyk.hpp"

int main(int argc, char** argv) {
    const auto options = new jejalyk::CompilationOptions();
    const auto compilation_result = jejalyk::compile("модуль А\nкінець", options);
    if (compilation_result->parser_error) {
        std::cout << "Parser error: " << compilation_result->parser_error->message << std::endl;
    } else {
        std::cout << compilation_result->result << std::endl;
    }
    return 0;
}
