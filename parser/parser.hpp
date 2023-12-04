#include "antlr4-runtime.h"
#include "MavkaLexer.h"
#include "MavkaParser.h"
#include "ast.hpp"

namespace mavka {
    namespace parser {
        class MavkaParserError : public std::exception {
        public:
            size_t line{};
            size_t column{};
            std::string message;
        };

        class MavkaParserErrorListener final : public antlr4::BaseErrorListener {
        public:
            void syntaxError(antlr4::Recognizer* recognizer,
                             antlr4::Token* offendingSymbol,
                             size_t line,
                             size_t charPositionInLine,
                             const std::string& msg,
                             std::exception_ptr e) override {
                const auto error = new MavkaParserError();
                error->line = line;
                error->column = charPositionInLine;
                error->message = msg;
                throw error;
            }
        };

        class MavkaParserResult {
        public:
            MavkaParserError* error = nullptr;
            mavka::ast::ProgramNode* program_node = nullptr;
        };

        MavkaParserResult* parse(std::string code) {
            try {
                antlr4::ANTLRInputStream input(code);

                const auto lexer_error_listener = new MavkaParserErrorListener();
                MavkaLexer lexer(&input);
                lexer.removeErrorListeners();
                lexer.addErrorListener(lexer_error_listener);

                antlr4::CommonTokenStream tokens(&lexer);

                const auto parser_error_listener = new MavkaParserErrorListener();
                MavkaParser parser(&tokens);
                parser.removeErrorListeners();
                parser.addErrorListener(parser_error_listener);

                MavkaParser::FileContext* tree = parser.file();

                ast::MavkaASTVisitor visitor;

                const auto ast_result = ast::any_to_ast_result(visitor.visitFile(tree));
                const auto program_node = dynamic_cast<ast::ProgramNode *>(ast_result->node);
                const auto parser_result = new MavkaParserResult();
                parser_result->program_node = program_node;
                return parser_result;
            } catch (MavkaParserError& parser_error) {
                const auto parser_result = new MavkaParserResult();
                parser_result->error = &parser_error;
                return parser_result;
            } catch (antlr4::RuntimeException& e) {
                const auto parser_result = new MavkaParserResult();
                const auto parser_error = new MavkaParserError();
                // todo: handle
                parser_error->message = "antlr4::RuntimeException";
                parser_result->error = parser_error;
                return parser_result;
            }
        }
    }
}
