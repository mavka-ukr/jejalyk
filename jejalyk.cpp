// #include <emscripten/bind.h>

#include <string>
#include "nlohmann/json.hpp"
#include "antlr4-runtime.h"
#include "MavkaLexer.h"
#include "MavkaParser.h"
#include "ast.cpp"

std::string compile(std::string code) {
    antlr4::ANTLRInputStream input(code);
    MavkaLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    MavkaParser parser(&tokens);
    MavkaParser::FileContext* tree = parser.file();
    MavkaASTVisitor visitor;

    json result;

    auto ast_result = any_to_ast_result(visitor.visitFile(tree));
    auto program_node = dynamic_cast<ProgramNode *>(ast_result->node);

    result["result"] = program_node->toJson();

    return result.dump(2);
}

int main() {
    std::cout << compile("модуль А\nкінець") << std::endl;
}

// std::string fetch_call() {
//     emscripten::val fetch = emscripten::val::global("fetch");
//     emscripten::val response = fetch(std::string("https://мавка.укр/тачки")).await();
//     emscripten::val text = response.call<emscripten::val>("text").await();
//     auto answer = text.as<std::string>();
//     return answer;
// }

// EMSCRIPTEN_BINDINGS (jejalyk) {
//     emscripten::function("compile", &compile);
// }
