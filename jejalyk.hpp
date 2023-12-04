#include <string>
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
        std::string root_module_path;
        std::string current_module_path;

        std::string (*get_module_name)(bool, std::string, CompilationOptions*) = nullptr;

        std::string (*get_module_path)(bool, std::string, CompilationOptions*) = nullptr;

        std::string (*get_module_code)(bool, std::string, CompilationOptions*) = nullptr;

        std::string (*get_butintin_module_code)(std::string, CompilationOptions*) = nullptr;

        std::string (*get_remote_module_name)(std::string, CompilationOptions*) = nullptr;

        std::string (*get_remote_module_pak_path)(std::string, CompilationOptions*) = nullptr;

        std::string (*get_remote_module_path)(std::string, CompilationOptions*) = nullptr;

        std::string (*get_remote_module_code)(std::string, CompilationOptions*) = nullptr;
    };

    CompilationResult* compile(std::string code, CompilationOptions* options) {
        const auto parser_result = mavka::parser::parse(code);
        const auto compilation_result = new CompilationResult();

        if (parser_result->error) {
            compilation_result->parser_error = parser_result->error;
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
