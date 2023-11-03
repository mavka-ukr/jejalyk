#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

#include <string>
#include <cstring>
#include "nlohmann/json.hpp"
#include "antlr4-runtime.h"
#include "MavkaLexer.h"
#include "MavkaParser.h"
#include "MavkaParserBaseVisitor.h"

using json = nlohmann::json;

char *cstr(const std::string &message) {
    char *cstr = new char[message.length() + 1];
    std::strcpy(cstr, message.c_str());
    return cstr;
}

std::string implode(const std::vector<std::string> &strs, const std::string &delim) {
    if (strs.size() == 0) {
        return std::string("");
    }
    std::ostringstream os;
    for (int i = 0; i < strs.size() - 1; ++i) {
        os << strs.at(i) << delim;
    }
    os << strs.back();
    return os.str();
}

class TreeShapeVisitor : public MavkaParserBaseVisitor {
public:
    std::any visitFile(MavkaParser::FileContext *ctx) override {
        return visitProgram(ctx->f_program);
    }

    std::any visitProgram(MavkaParser::ProgramContext *ctx) {
        std::vector<std::string> elements;
        for (auto &program_element: ctx->program_element()) {
            std::string element = std::any_cast<std::string>(visit(program_element));
            if (!element.empty()) {
                elements.push_back(element + ";");
            }
        }
        return implode(elements, "\n");
    }
    // visitProgram_element

    std::any visitModule(MavkaParser::ModuleContext *ctx) override {
        std::string name = ctx->m_name->getText();
        std::string body = std::any_cast<std::string>(visit(ctx->m_body));
        // todo: render module
        return std::string("");
    }

    std::any visitModule_body(MavkaParser::Module_bodyContext *ctx) override {
        std::vector<std::string> elements;
        for (auto &module_body_element: ctx->module_body_element()) {
            std::string element = std::any_cast<std::string>(visit(module_body_element));
            elements.push_back(element + ";");
        }
        return implode(elements, "\n");
    }
    // visitModule_body_element

    // visitStructure
    // visitStructure_elements
    // visitStructure_element

    std::any visitDiia(MavkaParser::DiiaContext *ctx) override {
        std::string name = ctx->d_name->getText();
        std::string body = std::any_cast<std::string>(visit(ctx->d_body));
        std::vector<std::string> params;
        if (ctx->d_params != nullptr) {
            for (auto &param: ctx->d_params->param()) {
                std::cout << "x" << std::endl;
                std::string name = param->p_name->getText();
                std::string default_value = param->p_value ? std::any_cast<std::string>(visit(param->p_value))
                                                           : std::string("");
                bool is_variadic = param->p_spread != nullptr;
                if (default_value.empty()) {
                    if (is_variadic) {
                        params.push_back("..." + name);
                    } else {
                        params.push_back(name);
                    }
                } else {
                    if (is_variadic) {
                        params.push_back("..." + name.append(" = ").append(default_value));
                    } else {
                        params.push_back(name.append(" = ").append(default_value));
                    }
                }
            }
        }
        std::string params_str = implode(params, ", ");
        return std::string("function " + name + "(" + params_str + ") {\n" + body + "\n}");
    }

    std::any visitIf(MavkaParser::IfContext *ctx) override {
        std::string condition = std::any_cast<std::string>(visit(ctx->i_value));
        std::string body = std::any_cast<std::string>(visit(ctx->i_body));
        if (ctx->i_else_body != nullptr) {
            std::string else_body = std::any_cast<std::string>(visit(ctx->i_else_body));
            return std::string("if (" + condition + ") {\n" + body + "\n} else {\n" + else_body + "\n}");
        }
        return std::string("if (" + condition + ") {\n" + body + "\n}");
    }

    std::any visitEach(MavkaParser::EachContext *ctx) override {
        return std::string("");
    }

    // visitFromto
    // visitFromto_number
    // visitFromto_string
    // visitFromto_id
    // visitFromto_nested
    // visitFromto_middle
    // visitFromto_symbol

    std::any visitWhile(MavkaParser::WhileContext *ctx) override {
        return std::string("");
    }

    std::any visitTry(MavkaParser::TryContext *ctx) override {
        return std::string("");
    }

    std::any visitTake_module(MavkaParser::Take_moduleContext *ctx) override {
        return std::string("");
    }

    std::any visitTake_file(MavkaParser::Take_fileContext *ctx) override {
        return std::string("");
    }

    std::any visitTake_remote(MavkaParser::Take_remoteContext *ctx) override {
        return std::string("");
    }

    std::any visitGive(MavkaParser::GiveContext *ctx) override {
        return std::string("");
    }

    std::any visitGive_element(MavkaParser::Give_elementContext *ctx) override {
        return std::string("");
    }

    std::any visitNumber(MavkaParser::NumberContext *ctx) override {
        return std::string(ctx->getText());
    }

    std::any visitString(MavkaParser::StringContext *ctx) override {
        return std::string(ctx->getText());
    }

    std::any visitId(MavkaParser::IdContext *ctx) override {
        return std::string(ctx->getText());
    }

    std::any visitChain(MavkaParser::ChainContext *ctx) override {
        return std::string("");
    }

    std::any visitCall(MavkaParser::CallContext *ctx) override {
        std::string value = std::any_cast<std::string>(visit(ctx->c_value));
        if (ctx->c_args == nullptr) {
            return std::string(value + "()");
        }
        std::string args = std::any_cast<std::string>(visit(ctx->c_args));
        return std::string(value + "(" + args + ")");
    }

    std::any visitPositive(MavkaParser::PositiveContext *ctx) override {
        return std::string("");
    }

    std::any visitNegative(MavkaParser::NegativeContext *ctx) override {
        return std::string("");
    }

    std::any visitPre_decrement(MavkaParser::Pre_decrementContext *ctx) override {
        return std::string("");
    }

    std::any visitPre_increment(MavkaParser::Pre_incrementContext *ctx) override {
        return std::string("");
    }

    std::any visitPost_decrement(MavkaParser::Post_decrementContext *ctx) override {
        return std::string("");
    }

    std::any visitPost_increment(MavkaParser::Post_incrementContext *ctx) override {
        return std::string("");
    }

    std::any visitNot(MavkaParser::NotContext *ctx) override {
        return std::string("");
    }

    std::any visitBitwise_not(MavkaParser::Bitwise_notContext *ctx) override {
        return std::string("");
    }

    std::any visitGet_element(MavkaParser::Get_elementContext *ctx) override {
        return std::string("");
    }

    std::any visitNested(MavkaParser::NestedContext *ctx) override {
        return std::string("");
    }

    std::any visitCall_expr(MavkaParser::Call_exprContext *ctx) override {
        return std::string("");
    }

    std::any visitArithmetic_mul(MavkaParser::Arithmetic_mulContext *ctx) override {
        std::string left = std::any_cast<std::string>(visit(ctx->a_left));
        std::string right = std::any_cast<std::string>(visit(ctx->a_right));
        std::string op = ctx->a_operation->getText();
        if (op == "*") {
            return std::string("mul(" + left + ", " + right + ")");
        }
        if (op == "/") {
            return std::string("div(" + left + ", " + right + ")");
        }
        if (op == "%") {
            return std::string("mod(" + left + ", " + right + ")");
        }
        if (op == "//") {
            return std::string("divdiv(" + left + ", " + right + ")");
        }
        if (op == "**") {
            return std::string("pow(" + left + ", " + right + ")");
        }
        throw std::runtime_error("Unknown arithmetic operator: " + op);
    }

    std::any visitArithmetic_add(MavkaParser::Arithmetic_addContext *ctx) override {
        std::string left = std::any_cast<std::string>(visit(ctx->a_left));
        std::string right = std::any_cast<std::string>(visit(ctx->a_right));
        std::string op = ctx->a_operation->getText();
        if (op == "+") {
            return std::string("add(" + left + ", " + right + ")");
        }
        if (op == "-") {
            return std::string("sub(" + left + ", " + right + ")");
        }
        throw std::runtime_error("Unknown arithmetic operator: " + op);
    }

    std::any visitBitwise(MavkaParser::BitwiseContext *ctx) override {
        return std::string("");
    }

    std::any visitComparison(MavkaParser::ComparisonContext *ctx) override {
        return std::string("");
    }

    std::any visitTest(MavkaParser::TestContext *ctx) override {
        return std::string("");
    }

    std::any visitTernary(MavkaParser::TernaryContext *ctx) override {
        return std::string("");
    }

    std::any visitArray(MavkaParser::ArrayContext *ctx) override {
        return std::string("");
    }

    std::any visitDictionary(MavkaParser::DictionaryContext *ctx) override {
        return std::string("");
    }

    std::any visitArray_elements(MavkaParser::Array_elementsContext *ctx) override {
        return std::string("");
    }

    std::any visitArray_element(MavkaParser::Array_elementContext *ctx) override {
        return std::string("");
    }

    std::any visitDictionary_args(MavkaParser::Dictionary_argsContext *ctx) override {
        return std::string("");
    }

    std::any visitDictionary_arg(MavkaParser::Dictionary_argContext *ctx) override {
        return std::string("");
    }

    std::any visitSimple(MavkaParser::SimpleContext *ctx) override {
        return visit(ctx->value());
    }

    std::any visitWait(MavkaParser::WaitContext *ctx) override {
        return std::string("await ").append(std::any_cast<std::string>(visit(ctx->w_value)));
    }

    std::any visitFunction(MavkaParser::FunctionContext *ctx) override {
        return std::string("");
    }

    std::any visitAnonymous_diia(MavkaParser::Anonymous_diiaContext *ctx) override {
        return std::string("");
    }

    std::any visitThrow(MavkaParser::ThrowContext *ctx) override {
        return std::string("");
    }

    std::any visitAssign(MavkaParser::AssignContext *ctx) override {
        return std::string("");
    }

    std::any visitAssign_value(MavkaParser::Assign_valueContext *ctx) override {
        return std::string("");
    }

    std::any visitAssign_symbol(MavkaParser::Assign_symbolContext *ctx) override {
        return std::string("");
    }

    std::any visitWait_assign(MavkaParser::Wait_assignContext *ctx) override {
        return std::string("");
    }

    std::any visitIdentifier(MavkaParser::IdentifierContext *ctx) override {
        return std::string(ctx->getText());
    }

    std::any visitExtended_identifier(MavkaParser::Extended_identifierContext *ctx) override {
        return std::string("");
    }

    std::any visitIdentifiers_chain(MavkaParser::Identifiers_chainContext *ctx) override {
        return std::string("");
    }

    std::any visitType_value(MavkaParser::Type_valueContext *ctx) override {
        return std::string("");
    }

    std::any visitType_value_array(MavkaParser::Type_value_arrayContext *ctx) override {
        return std::string("");
    }

    std::any visitArgs(MavkaParser::ArgsContext *ctx) override {
        std::vector<std::string> args;
        for (auto &arg: ctx->arg()) {
            args.push_back(std::any_cast<std::string>(visit(arg)));
        }
        return implode(args, ", ");
    }

    std::any visitArg(MavkaParser::ArgContext *ctx) override {
        return visit(ctx->a_value);
    }

    std::any visitNamed_args(MavkaParser::Named_argsContext *ctx) override {
        return std::string("");
    }

    std::any visitNamed_arg(MavkaParser::Named_argContext *ctx) override {
        return std::string("");
    }

    std::any visitParams(MavkaParser::ParamsContext *ctx) override {
        return std::string("");
    }

    std::any visitParam(MavkaParser::ParamContext *ctx) override {
        throw std::runtime_error("visitParam not implemented");
    }

    std::any visitParam_value_number(MavkaParser::Param_value_numberContext *ctx) override {
        return std::string(ctx->getText());
    }

    std::any visitParam_value_string(MavkaParser::Param_value_stringContext *ctx) override {
        return std::string(ctx->getText());
    }

    std::any visitParam_value_identifier(MavkaParser::Param_value_identifierContext *ctx) override {
        return visitIdentifier(ctx->identifier());
    }

    std::any visitBody(MavkaParser::BodyContext *ctx) override {
        std::vector<std::string> elements;
        for (auto &body_element: ctx->body_element_or_return()) {
            std::string element = std::any_cast<std::string>(visit(body_element));
            if (!element.empty()) {
                elements.push_back(element.append(";"));
            }
        }
        return implode(elements, "\n");
    }

    std::any visitBody_element_or_return(MavkaParser::Body_element_or_returnContext *ctx) override {
        if (ctx->body_element()) {
            return visit(ctx->body_element());
        }
        return visit(ctx->return_body_line());
    }

    std::any visitBody_element(MavkaParser::Body_elementContext *ctx) override {
        if (ctx->structure()) {
            return visit(ctx->structure());
        }
        if (ctx->diia()) {
            return visit(ctx->diia());
        }
        if (ctx->if_()) {
            return visit(ctx->if_());
        }
        if (ctx->each()) {
            return visit(ctx->each());
        }
        if (ctx->while_()) {
            return visit(ctx->while_());
        }
        if (ctx->try_()) {
            return visit(ctx->try_());
        }
        if (ctx->expr()) {
            return visit(ctx->expr());
        }
        if (ctx->throw_()) {
            return visit(ctx->throw_());
        }
        if (ctx->wait_assign()) {
            return visit(ctx->wait_assign());
        }
        if (ctx->assign()) {
            return visit(ctx->assign());
        }
        return std::string("");
    }

    std::any visitReturn_body_line(MavkaParser::Return_body_lineContext *ctx) override {
        std::string rbl = std::any_cast<std::string>(visit(ctx->rbl));
        return std::string("return ").append(rbl);
    }

    std::any visitArithmetic_op_mul(MavkaParser::Arithmetic_op_mulContext *ctx) override {
        return std::string("");
    }

    std::any visitArithmetic_op_add(MavkaParser::Arithmetic_op_addContext *ctx) override {
        return std::string("");
    }

    std::any visitBitwise_op(MavkaParser::Bitwise_opContext *ctx) override {
        return std::string("");
    }

    std::any visitTest_op(MavkaParser::Test_opContext *ctx) override {
        return std::string("");
    }

    std::any visitComparison_op(MavkaParser::Comparison_opContext *ctx) override {
        return std::string("");
    }

    std::any visitNl(MavkaParser::NlContext *ctx) override {
        return std::string("");
    }

    std::any visitNls(MavkaParser::NlsContext *ctx) override {
        return std::string("");
    }
};

extern "C"
{
EMSCRIPTEN_KEEPALIVE
char *compile(char *code) {
    json result;
    result["ok"] = true;
    result["result"] = "";
    result["error"] = nullptr;

    antlr4::ANTLRInputStream input(code);
    MavkaLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    MavkaParser parser(&tokens);

    MavkaParser::FileContext *tree = parser.file();
    TreeShapeVisitor visitor;
    auto mp = std::any_cast<std::string>(visitor.visitFile(tree));

    result["result"] = mp;

    return cstr(result.dump());
}
}