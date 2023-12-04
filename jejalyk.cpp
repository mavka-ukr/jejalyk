#include <string>
#include "nlohmann/json.hpp"
#include "parser.cpp"

std::string compile(std::string code) {
    const auto parse_result = parse_mavka(code);
    if (parse_result->error) {
        throw std::runtime_error(parse_result->error->message);
    }
    return parse_result->node->toJson().dump(2);
}

int main() {
    std::cout << compile("модуль А") << std::endl;
}
