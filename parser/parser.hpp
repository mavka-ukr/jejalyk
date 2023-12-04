#include "antlr4-runtime.h"
#include "MavkaLexer.h"
#include "MavkaParser.h"
#include "ast.hpp"

namespace mavka {
    namespace parser {
        class MavkaParserError {
        public:
            size_t line{};
            size_t column{};
            std::string message;
        };

        class MavkaParserErrorListener final : public antlr4::BaseErrorListener {
        public:
            MavkaParserError* error = nullptr;

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
                this->error = error;
            }

            void reportAmbiguity(antlr4::Parser* recognizer, const antlr4::dfa::DFA& dfa, size_t startIndex,
                                 size_t stopIndex, bool exact, const antlrcpp::BitSet& ambigAlts,
                                 antlr4::atn::ATNConfigSet* configs) override {
                std::cout << "lol";
            }

            void reportContextSensitivity(antlr4::Parser* recognizer, const antlr4::dfa::DFA& dfa, size_t startIndex,
                                          size_t stopIndex, size_t prediction,
                                          antlr4::atn::ATNConfigSet* configs) override {
                std::cout << "lol";
            }

            void reportAttemptingFullContext(antlr4::Parser* recognizer, const antlr4::dfa::DFA& dfa, size_t startIndex,
                                             size_t stopIndex, const antlrcpp::BitSet& conflictingAlts,
                                             antlr4::atn::ATNConfigSet* configs) override {
                std::cout << "lol";
            }
        };

        class MavkaParserResult {
        public:
            MavkaParserError* error = nullptr;
            mavka::ast::ProgramNode* program_node = nullptr;
        };

        MavkaParserResult* parse(std::string code) {
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

            if (lexer_error_listener->error) {
                const auto parser_result = new MavkaParserResult();
                parser_result->error = lexer_error_listener->error;
                return parser_result;
            }
            if (parser_error_listener->error) {
                const auto parser_result = new MavkaParserResult();
                parser_result->error = parser_error_listener->error;
                return parser_result;
            }

            mavka::ast::MavkaASTVisitor visitor;

            const auto ast_result = mavka::ast::any_to_ast_result(visitor.visitFile(tree));
            const auto program_node = dynamic_cast<mavka::ast::ProgramNode *>(ast_result->node);
            const auto parse_result = new MavkaParserResult();
            parse_result->program_node = program_node;
            return parse_result;
        }
    }
}
