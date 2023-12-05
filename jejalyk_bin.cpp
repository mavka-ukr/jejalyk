#include <string>
#include "jejalyk.hpp"

int main(int argc, char** argv) {
    const auto options = new jejalyk::CompilationOptions();

    const auto result = jejalyk::compile(R"(друк("один", "два", 3))", options);
    if (result->parser_error) {
        std::cout << result->parser_error->message << std::endl;
    } else {
        std::cout << result->result << std::endl;
    }

    return 0;
}
