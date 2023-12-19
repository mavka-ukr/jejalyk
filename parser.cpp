#include "parser.h"

namespace mavka::parser {
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
            // parser.setErrorHandler(std::shared_ptr<MavkaParserErrorHandler>(error_handler));
            parser.removeParseListeners();
            parser.removeErrorListeners();
            parser.addErrorListener(parser_error_listener);

            MavkaParser::FileContext* tree = parser.file();

            MavkaASTVisitor visitor;

            const auto ast_result = any_to_ast_result(visitor.visitFile(tree));
            const auto program_node = dynamic_cast<ast::ProgramNode *>(ast_result->node);
            const auto parser_result = new MavkaParserResult();
            parser_result->program_node = program_node;
            return parser_result;
        } catch (const antlr4::RecognitionException& e) {
            const auto parser_result = new MavkaParserResult();
            const auto parser_error = new MavkaParserError();
            // wasm cannot properly handle antlr4 exceptions
            // do not handle it for now
            // todo: fix it
            // try {
            // parser_error->line = e.getOffendingToken()->getLine();
            // parser_error->column = e.getOffendingToken()->getCharPositionInLine();
            // } catch (...) {
            // ignore
            // }
            parser_error->message = "Помилка парсингу.";
            parser_result->error = parser_error;
            return parser_result;
        } catch (...) {
            const auto parser_result = new MavkaParserResult();
            const auto parser_error = new MavkaParserError();
            parser_error->message = "Помилка парсингу";
            parser_result->error = parser_error;
            return parser_result;
        }
    }
}
