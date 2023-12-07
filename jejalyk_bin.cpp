#include <iostream>
#include <fstream>
#include <string>
#include "jejalyk.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Використання: джеджалик [команда] [...опції] <вхід.м> [вихід.{js|html}]" << std::endl;
        return 1;
    }

    std::map<std::string, std::string> x;

    std::ifstream file(argv[1]);
    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    const auto options = new jejalyk::CompilationOptions();

    const auto result = jejalyk::compile(code, options);

    if (result->error) {
        std::cout << result->error->line << ":" << result->error->column << ": " << result->error->message << std::endl;
    } else if (argc > 2) {
        std::ofstream out(argv[2]);
        out << result->result;
    } else {
        std::cout << result->result << std::endl;
    }

    return 0;
}
