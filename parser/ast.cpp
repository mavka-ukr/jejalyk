#include <vector>
#include "MavkaParserBaseVisitor.h"
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

template<typename Base, typename T>
inline bool ast_instanceof(const T* ptr) {
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

// base
class ASTNode {
public:
    std::string TYPE = "ASTNode";

    virtual ~ASTNode() = default;

    virtual json toJson() {
        return json::object({
            "type", TYPE
        });
    }
};

// program
class ProgramNode final : public ASTNode {
public:
    std::string TYPE = "ProgramNode";

    std::vector<ASTNode *> body;

    json toJson() override {
        json result;
        result["type"] = TYPE;
        result["body"] = json::array();
        for (const auto item: body) {
            if (item) {
                result["body"].push_back(item->toJson());
            }
        }
        return result;
    }
};

// module
class ModuleNode final : public ASTNode {
public:
    std::string TYPE = "ModuleNode";

    std::string name;
    std::vector<ASTNode *> body;

    json toJson() override {
        json result;
        result["type"] = TYPE;
        result["name"] = name;
        result["body"] = json::array();
        for (const auto item: body) {
            if (item) {
                result["body"].push_back(item->toJson());
            }
        }
        return result;
    }
};

// structure
class StructureParamNode final : public ASTNode {
public:
    std::string TYPE = "StructureParamNode";

    std::string name;
    ASTNode* type;
    ASTNode* value;
};

class StructureNode final : public ASTNode {
public:
    std::string TYPE = "StructureNode";

    std::string name;
    std::vector<StructureParamNode *> params;
};

// diia
class ParamNode final : public ASTNode {
public:
    std::string TYPE = "ParamNode";

    std::string name;
    ASTNode* type;
    ASTNode* value;
};

class DiiaNode final : public ASTNode {
public:
    std::string TYPE = "DiiaNode";

    bool async;
    std::string structure;
    std::string name;
    std::vector<ParamNode *> params;
    ASTNode* type;
    std::vector<ASTNode *> body;
};

// if
class IfNode final : public ASTNode {
public:
    std::string TYPE = "IfNode";

    ASTNode* condition;
    std::vector<ASTNode *> body;
    std::vector<ASTNode *> else_body;
};

// each
class EachNode final : public ASTNode {
public:
    std::string TYPE = "EachNode";

    ASTNode* value;
    std::string keyName;
    std::string name;
    std::vector<ASTNode *> body;
};

// while
class WhileNode final : public ASTNode {
public:
    std::string TYPE = "WhileNode";

    ASTNode* condition;
    std::vector<ASTNode *> body;
};

// try
class TryNode final : public ASTNode {
public:
    std::string TYPE = "TryNode";

    std::vector<ASTNode *> body;
    std::string name;
    std::vector<ASTNode *> catch_body;
};

// wait
class WaitNode final : public ASTNode {
public:
    std::string TYPE = "WaitNode";

    ASTNode* value;
};

// function
class FunctionNode final : public ASTNode {
public:
    std::string TYPE = "FunctionNode";

    bool async;
    std::vector<ParamNode *> params;
    ASTNode* type;
    std::vector<ASTNode *> body;
};

// anon diia
class AnonDiiaNode final : public ASTNode {
public:
    std::string TYPE = "AnonDiiaNode";

    bool async;
    std::vector<ParamNode *> params;
    ASTNode* type;
    std::vector<ASTNode *> body;
};

// number
class NumberNode final : public ASTNode {
public:
    std::string TYPE = "NumberNode";

    std::string value;
};

// string
class StringNode final : public ASTNode {
public:
    std::string TYPE = "StringNode";

    std::string value;
};

// identifier
class IdentifierNode final : public ASTNode {
public:
    std::string TYPE = "IdentifierNode";

    std::string name;
};

// chain
class ChainNode final : public ASTNode {
public:
    std::string TYPE = "ChainNode";

    ASTNode* left;
    ASTNode* right;
};

// call
class ArgNode final : public ASTNode {
public:
    std::string TYPE = "ArgNode";

    int index;
    std::string name;
    ASTNode* value;
};

class CallNode final : public ASTNode {
public:
    std::string TYPE = "CallNode";

    ASTNode* value;
    std::vector<ArgNode *> args;
};

// get element
class GetElementNode final : public ASTNode {
public:
    std::string TYPE = "GetElementNode";

    ASTNode* value;
    ASTNode* index;
};

// positive
class PositiveNode final : public ASTNode {
public:
    std::string TYPE = "PositiveNode";

    ASTNode* value;
};

// negative
class NegativeNode final : public ASTNode {
public:
    std::string TYPE = "NegativeNode";

    ASTNode* value;
};

// pre decrement
class PreDecrementNode final : public ASTNode {
public:
    std::string TYPE = "PreDecrementNode";

    ASTNode* value;
};

// pre increment
class PreInrementNode final : public ASTNode {
public:
    std::string TYPE = "PreInrementNode";

    ASTNode* value;
};

// post decrement
class PostDecrementNode final : public ASTNode {
public:
    std::string TYPE = "PostDecrementNode";

    ASTNode* value;
};

// post increment
class PostIncrementNode final : public ASTNode {
public:
    std::string TYPE = "PostIncrementNode";

    ASTNode* value;
};

// not
class NotNode final : public ASTNode {
public:
    std::string TYPE = "NotNode";

    ASTNode* value;
};

// bitwise not
class BitwiseNotNode final : public ASTNode {
public:
    std::string TYPE = "BitwiseNotNode";

    ASTNode* value;
};

// as
class AsNode final : public ASTNode {
public:
    std::string TYPE = "AsNode";

    ASTNode* left;
    ASTNode* right;
};

// arithmetic
class ArithmeticNode final : public ASTNode {
public:
    std::string TYPE = "ArithmeticNode";

    ASTNode* left;
    ASTNode* right;
    std::string op;
};

// bitwise
class BitwiseNode final : public ASTNode {
public:
    std::string TYPE = "BitwiseNode";

    ASTNode* left;
    ASTNode* right;
    std::string op;
};

// bitwise
class ComparisonNode final : public ASTNode {
public:
    std::string TYPE = "ComparisonNode";

    ASTNode* left;
    ASTNode* right;
    std::string op;
};

// test
class TestNode final : public ASTNode {
public:
    std::string TYPE = "TestNode";

    ASTNode* left;
    ASTNode* right;
    std::string op;
};

// ternary
class TernaryNode final : public ASTNode {
public:
    std::string TYPE = "TernaryNode";

    ASTNode* condition;
    std::vector<ASTNode *> body;
    std::vector<ASTNode *> else_body;
};

// array
class ArrayNode final : public ASTNode {
public:
    std::string TYPE = "ArrayNode";

    std::vector<ASTNode *> elements;
};

// dictionary
class DictionaryNode final : public ASTNode {
public:
    std::string TYPE = "DictionaryNode";

    std::map<std::string, ASTNode *> elements;
};

// god
class GodNode final : public ASTNode {
public:
    std::string TYPE = "GodNode";

    std::vector<ASTNode *> elements;
};

// throw
class ThrowNode final : public ASTNode {
public:
    std::string TYPE = "ThrowNode";

    ASTNode* value;
};

// eval
class EvalNode final : public ASTNode {
public:
    std::string TYPE = "EvalNode";

    ASTNode* value;
};

// assign simple
class AssignSimpleNode final : public ASTNode {
public:
    std::string TYPE = "AssignSimpleNode";

    std::string name;
    ASTNode* type;
    std::string op;
    ASTNode* value;
};

// assign complex
class AssignComplexNode final : public ASTNode {
public:
    std::string TYPE = "AssignComplexNode";

    ASTNode* left;
    ASTNode* right;
    ASTNode* value;
};

// take pak
class TakePakNode final : public ASTNode {
public:
    std::string TYPE = "TakePakNode";

    std::string name;
    std::string as;
};

// take module
class TakeModuleNode final : public ASTNode {
public:
    std::string TYPE = "TakeModuleNode";

    std::string name;
    std::string as;
};

// break module
class BreakNode final : public ASTNode {
public:
    std::string TYPE = "BreakNode";
};

// continue module
class ContinueNode final : public ASTNode {
public:
    std::string TYPE = "ContinueNode";
};

class ASTResult {
public:
    ASTNode* node;
};

ASTResult* any_to_ast_result(std::any any) {
    return std::any_cast<ASTResult *>(any);
}

ASTResult* create_ast_result(ASTNode* node) {
    const auto ast_result = new ASTResult();
    ast_result->node = node;
    return ast_result;
}

std::vector<ASTNode *> processASTBody(const std::vector<ASTNode *>& body) {
    std::vector<ASTNode *> result;
    for (auto& item: body) {
        if (ast_instanceof<IdentifierNode>(item)) {
            const auto identifier_node = dynamic_cast<IdentifierNode *>(item);
            if (identifier_node->name == "break") {
                result.push_back(new BreakNode());
                continue;
            }
            if (identifier_node->name == "continue") {
                result.push_back(new ContinueNode());
                continue;
            }
        }

        result.push_back(item);
    }
    return result;
}

class MavkaASTVisitor final : public MavkaParserBaseVisitor {
public:
    std::any visitFile(MavkaParser::FileContext* ctx) override {
        return visitProgram(ctx->f_program);
    }

    std::any visitProgram(MavkaParser::ProgramContext* context) override {
        std::vector<ASTNode *> body;
        for (const auto program_element: context->program_element()) {
            const auto ast_result = any_to_ast_result(visitProgram_element(program_element));
            body.push_back(ast_result->node);
        }
        body = processASTBody(body);
        const auto program_node = new ProgramNode();
        program_node->body = body;
        return create_ast_result(program_node);
    }

    std::any visitProgram_element(MavkaParser::Program_elementContext* context) override {
        if (context->module()) {
            return visitModule(context->module());
        }
        return create_ast_result(new ASTNode());
    }

    std::any visitModule(MavkaParser::ModuleContext* context) override {
        const auto module_node = new ModuleNode();
        module_node->name = context->m_name->getText();
        if (context->module_body()) {
            std::any module_body = visitModule_body(context->module_body());
            module_node->body = std::any_cast<std::vector<ASTNode *>>(module_body);
        }
        return create_ast_result(module_node);
    }

    std::any visitModule_body(MavkaParser::Module_bodyContext* context) override {
        std::vector<ASTNode *> body;
        for (const auto module_element: context->module_body_element()) {
            const auto ast_result = any_to_ast_result(visitModule_body_element(module_element));
            body.push_back(ast_result->node);
        }
        body = processASTBody(body);
        return body;
    }

    std::any visitModule_body_element(MavkaParser::Module_body_elementContext* context) override {
        return create_ast_result(new ASTNode());
    }
};
