#include <string>
#include "nlohmann/json.hpp"
#include "parser.cpp"

class MavkaCompilationResult {
public:
    MavkaParserError* parser_error = nullptr;
    std::string result;
};

MavkaCompilationResult* compile(std::string code) {
    const auto parse_result = parse_mavka(code);
    const auto compilation_result = new MavkaCompilationResult();
    if (parse_result->error) {
        compilation_result->parser_error = parse_result->error;
    } else {
        compilation_result->result = parse_result->node->toJson().dump(2);
    }
    return compilation_result;
}

int main(int argc, char** argv) {
    const auto compilation_result = compile("модуль А\nкінець");
    if (compilation_result->parser_error) {
        std::cout << "Parser error: " << compilation_result->parser_error->message << std::endl;
    } else {
        std::cout << compilation_result->result << std::endl;
    }
    return 0;
}
