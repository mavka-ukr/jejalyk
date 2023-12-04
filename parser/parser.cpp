#include "antlr4-runtime.h"
#include "MavkaLexer.h"
#include "MavkaParser.h"
#include "ast.cpp"

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
};

class MavkaParserResult {
public:
    MavkaParserError* error = nullptr;
    ASTNode* node = nullptr;
};

MavkaParserResult* parse_mavka(std::string code) {
    antlr4::ANTLRInputStream input(code);
    MavkaLexer lexer(&input);
    lexer.removeErrorListeners();
    const auto lexer_error_listener = new MavkaParserErrorListener();
    lexer.addErrorListener(lexer_error_listener);
    antlr4::CommonTokenStream tokens(&lexer);
    MavkaParser parser(&tokens);
    parser.removeErrorListeners();
    const auto parser_error_listener = new MavkaParserErrorListener();
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
    MavkaASTVisitor visitor;

    const auto ast_result = any_to_ast_result(visitor.visitFile(tree));
    const auto program_node = dynamic_cast<ProgramNode *>(ast_result->node);
    const auto parse_result = new MavkaParserResult();
    parse_result->node = program_node;
    return parse_result;
}