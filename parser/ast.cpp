#include <vector>
#include "MavkaParserBaseVisitor.h"

// base
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// program
class ProgramNode : public ASTNode {
public:
    std::vector<ASTNode *> body;
};

// module
class ModuleNode : public ASTNode {
public:
    std::string name;
    std::vector<ASTNode *> body;
};

// structure
class StructureParamNode : public ASTNode {
public:
    std::string name;
    ASTNode* type;
    ASTNode* value;
};

class StructureNode : public ASTNode {
public:
    std::string name;
    std::vector<StructureParamNode *> params;
};

// diia
class ParamNode : public ASTNode {
public:
    std::string name;
    ASTNode* type;
    ASTNode* value;
};

class DiiaNode : public ASTNode {
public:
    bool async;
    std::string structure;
    std::string name;
    std::vector<ParamNode *> params;
    ASTNode* type;
    std::vector<ASTNode *> body;
};

// if
class IfNode : public ASTNode {
public:
    ASTNode* condition;
    std::vector<ASTNode *> body;
    std::vector<ASTNode *> else_body;
};

// each
class EachNode : public ASTNode {
public:
    ASTNode* value;
    std::string keyName;
    std::string name;
    std::vector<ASTNode *> body;
};

// while
class WhileNode : public ASTNode {
public:
    ASTNode* condition;
    std::vector<ASTNode *> body;
};

// try
class TryNode : public ASTNode {
    std::vector<ASTNode *> body;
    std::string name;
    std::vector<ASTNode *> catch_body;
};

// wait
class WaitNode : public ASTNode {
public:
    ASTNode* value;
};

// function
class FunctionNode : public ASTNode {
public:
    bool async;
    std::vector<ParamNode *> params;
    ASTNode* type;
    std::vector<ASTNode *> body;
};

// anon diia
class AnonDiiaNode : public ASTNode {
public:
    bool async;
    std::vector<ParamNode *> params;
    ASTNode* type;
    std::vector<ASTNode *> body;
};

// number
class NumberNode : public ASTNode {
public:
    std::string value;
};

// string
class StringNode : public ASTNode {
public:
    std::string value;
};

// identifier
class IdentifierNode : public ASTNode {
public:
    std::string name;
};

// chain
class ChainNode : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
};

// call
class ArgNode : public ASTNode {
public:
    int index;
    std::string name;
    ASTNode* value;
};

class CallNode : public ASTNode {
public:
    ASTNode* value;
    std::vector<ArgNode *> args;
};

// get element
class GetElementNode : public ASTNode {
public:
    ASTNode* value;
    ASTNode* index;
};

// positive
class PositiveNode : public ASTNode {
public:
    ASTNode* value;
};

// negative
class NegativeNode : public ASTNode {
public:
    ASTNode* value;
};

// pre decrement
class PreDecrementNode : public ASTNode {
public:
    ASTNode* value;
};

// pre increment
class PreInrementNode : public ASTNode {
public:
    ASTNode* value;
};

// post decrement
class PostDecrementNode : public ASTNode {
public:
    ASTNode* value;
};

// post increment
class PostIncrementNode : public ASTNode {
public:
    ASTNode* value;
};

// not
class NotNode : public ASTNode {
public:
    ASTNode* value;
};

// bitwise not
class BitwiseNotNode : public ASTNode {
public:
    ASTNode* value;
};

// as
class AsNode : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
};

// arithmetic
class ArithmeticNode : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
};

// bitwise
class BitwiseNode : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
};

// bitwise
class ComparisonNode : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
};

// test
class TestNode : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
};

// ternary
class TernaryNode : public ASTNode {
public:
    ASTNode* condition;
    std::vector<ASTNode *> body;
    std::vector<ASTNode *> else_body;
};

// array
class ArrayNode : public ASTNode {
public:
    std::vector<ASTNode *> elements;
};

// dictionary
class DictionaryNode : public ASTNode {
public:
    std::map<std::string, ASTNode *> elements;
};

// god
class GodNode : public ASTNode {
public:
    std::vector<ASTNode *> elements;
};

// throw
class ThrowNode : public ASTNode {
public:
    ASTNode* value;
};

// eval
class EvalNode : public ASTNode {
public:
    ASTNode* value;
};

// assign simple
class AssignSimpleNode : public ASTNode {
public:
    std::string name;
    ASTNode* type;
    std::string op;
    ASTNode* value;
};

// assign complex
class AssignComplexNode : public ASTNode {
public:
    ASTNode* left;
    ASTNode* right;
    ASTNode* value;
};

// take pak
class TakePakNode : public ASTNode {
public:
    std::string name;
    std::string as;
};

// take module
class TakeModuleNode : public ASTNode {
public:
    std::string name;
    std::string as;
};

class MavkaASTVisitor : public MavkaParserBaseVisitor {
public:
    std::any visitFile(MavkaParser::FileContext* ctx) override {
        return ProgramNode();
    }
};
