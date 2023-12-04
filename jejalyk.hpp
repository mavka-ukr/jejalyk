#include <string>
#include "nlohmann/json.hpp"
#include "parser.hpp"

namespace jejalyk {
    class CompilationResult {
    public:
        mavka::parser::MavkaParserError* parser_error = nullptr;
        std::string result;
    };

    class CompilationScope {
    public:
        CompilationScope* parent = nullptr;
    };

    class CompilationOptions {
    public:
        CompilationOptions* parent = nullptr;
    };

    CompilationResult* compile(std::string code, CompilationOptions* options) {
        const auto parse_result = mavka::parser::parse(code);
        const auto compilation_result = new CompilationResult();

        if (parse_result->error) {
            compilation_result->parser_error = parse_result->error;
        } else {
            // todo: compile

            compilation_result->result = "";
        }
        return compilation_result;
    }

    CompilationResult* compile_node(mavka::ast::ASTNode* node, CompilationOptions* options) {
        const auto compilation_result = new CompilationResult();

        if (mavka::ast::instanceof<mavka::ast::ProgramNode>(node)) {
        }

        return compilation_result;
    }
}