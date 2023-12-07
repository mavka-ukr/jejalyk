#pragma once

#include <vector>
#include "MavkaParserBaseVisitor.h"

namespace mavka::ast {
    // base
    class ASTNode {
    public:
        std::string TYPE = "ASTNode";
        int start_line = 0;
        int start_column = 0;
        int end_line = 0;
        int end_column = 0;

        virtual ~ASTNode() = default;
    };

    // anon diia
    class ParamNode final : public ASTNode {
    public:
        std::string TYPE = "ParamNode";

        std::string name;
        ASTNode* type;
        ASTNode* value;
    };

    class AnonDiiaNode final : public ASTNode {
    public:
        std::string TYPE = "AnonDiiaNode";

        bool async;
        std::vector<ParamNode *> params;
        ASTNode* type;
        std::vector<ASTNode *> body;
    };

    // arg
    class ArgNode final : public ASTNode {
    public:
        std::string TYPE = "ArgNode";

        int index;
        std::string name;
        ASTNode* value;
    };

    // arithmetic
    class ArithmeticNode final : public ASTNode {
    public:
        std::string TYPE = "ArithmeticNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    // array
    class ArrayNode final : public ASTNode {
    public:
        std::string TYPE = "ArrayNode";

        std::vector<ASTNode *> elements;
    };

    // as
    class AsNode final : public ASTNode {
    public:
        std::string TYPE = "AsNode";

        ASTNode* left;
        ASTNode* right;
    };

    // assign complex
    class AssignComplexRightNode final : public ASTNode {
    public:
        std::string TYPE = "AssignComplexRightNode";

        std::string name;
        ASTNode* index;
    };

    class AssignComplexNode final : public ASTNode {
    public:
        std::string TYPE = "AssignComplexNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
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

    // bitwise
    class BitwiseNode final : public ASTNode {
    public:
        std::string TYPE = "BitwiseNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    // bitwise not
    class BitwiseNotNode final : public ASTNode {
    public:
        std::string TYPE = "BitwiseNotNode";

        ASTNode* value;
    };

    // break
    class BreakNode final : public ASTNode {
    public:
        std::string TYPE = "BreakNode";
    };

    // call
    class CallNode final : public ASTNode {
    public:
        std::string TYPE = "CallNode";

        ASTNode* value;
        std::vector<ArgNode *> args;
    };

    // chain
    class ChainNode final : public ASTNode {
    public:
        std::string TYPE = "ChainNode";

        ASTNode* left;
        ASTNode* right;
    };

    // comparison
    class ComparisonNode final : public ASTNode {
    public:
        std::string TYPE = "ComparisonNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    // continue
    class ContinueNode final : public ASTNode {
    public:
        std::string TYPE = "ContinueNode";
    };

    // dictionary
    class DictionaryNode final : public ASTNode {
    public:
        std::string TYPE = "DictionaryNode";

        std::map<std::string, ASTNode *> elements;
    };

    // diia
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

    // each
    class EachNode final : public ASTNode {
    public:
        std::string TYPE = "EachNode";

        ASTNode* value;
        std::string keyName;
        std::string name;
        std::vector<ASTNode *> body;
    };

    // eval
    class EvalNode final : public ASTNode {
    public:
        std::string TYPE = "EvalNode";

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

    // get element
    class GetElementNode final : public ASTNode {
    public:
        std::string TYPE = "GetElementNode";

        ASTNode* value;
        ASTNode* index;
    };

    // give
    class GiveElementNode final : public ASTNode {
    public:
        std::string TYPE = "GiveElementNode";

        std::string name;
        std::string as;
    };

    class GiveNode final : public ASTNode {
    public:
        std::string TYPE = "GiveNode";

        std::vector<GiveElementNode *> elements;
    };

    // god
    class GodNode final : public ASTNode {
    public:
        std::string TYPE = "GodNode";

        std::vector<ASTNode *> elements;
    };

    // identifier
    class IdentifierNode final : public ASTNode {
    public:
        std::string TYPE = "IdentifierNode";

        std::string name;
    };

    // if
    class IfNode final : public ASTNode {
    public:
        std::string TYPE = "IfNode";

        ASTNode* condition;
        std::vector<ASTNode *> body;
        std::vector<ASTNode *> else_body;
    };

    // mockup
    class MockupDiiaNode final : public ASTNode {
    public:
        bool async;
        std::string name;
        std::vector<ASTNode *> params;
        ASTNode* result;
    };

    class MockupModuleNode final : public ASTNode {
    public:
        std::string name;
        std::vector<ASTNode *> elements;
    };

    class MockupObjectNode final : public ASTNode {
    public:
        std::string name;
        std::vector<ASTNode *> elements;
    };

    class MockupStructureNode final : public ASTNode {
    public:
        std::string name;
        std::vector<ASTNode *> params;
    };

    class MockupSubjectNode final : public ASTNode {
    public:
        std::string name;
        ASTNode* type;
    };

    // module
    class ModuleNode final : public ASTNode {
    public:
        std::string TYPE = "ModuleNode";

        std::string name;
        std::vector<ASTNode *> body;
    };

    // negative
    class NegativeNode final : public ASTNode {
    public:
        std::string TYPE = "NegativeNode";

        ASTNode* value;
    };

    // not
    class NotNode final : public ASTNode {
    public:
        std::string TYPE = "NotNode";

        ASTNode* value;
    };

    // number
    class NumberNode final : public ASTNode {
    public:
        std::string TYPE = "NumberNode";

        std::string value;
    };

    // positive
    class PositiveNode final : public ASTNode {
    public:
        std::string TYPE = "PositiveNode";

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

    // program
    class ProgramNode final : public ASTNode {
    public:
        std::string TYPE = "ProgramNode";

        std::vector<ASTNode *> body;
    };

    // return
    class ReturnNode final : public ASTNode {
    public:
        std::string TYPE = "ReturnNode";

        ASTNode* value;
    };

    // string
    class StringNode final : public ASTNode {
    public:
        std::string TYPE = "StringNode";

        std::string value;
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

    // take module
    class TakeModuleNode final : public ASTNode {
    public:
        std::string TYPE = "TakeModuleNode";

        std::string name;
        std::string as;
    };

    // take pak
    class TakePakNode final : public ASTNode {
    public:
        std::string TYPE = "TakePakNode";

        std::string name;
        std::string as;
    };

    // ternary
    class TernaryNode final : public ASTNode {
    public:
        std::string TYPE = "TernaryNode";

        ASTNode* condition;
        std::vector<ASTNode *> body;
        std::vector<ASTNode *> else_body;
    };

    // test
    class TestNode final : public ASTNode {
    public:
        std::string TYPE = "TestNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    // throw
    class ThrowNode final : public ASTNode {
    public:
        std::string TYPE = "ThrowNode";

        ASTNode* value;
    };

    // try
    class TryNode final : public ASTNode {
    public:
        std::string TYPE = "TryNode";

        std::vector<ASTNode *> body;
        std::string name;
        std::vector<ASTNode *> catch_body;
    };

    // type value
    class TypeValueNode final : public ASTNode {
    public:
        std::string TYPE = "TypeValueNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    // type value sinlge
    class TypeValueSingleNode final : public ASTNode {
    public:
        std::string TYPE = "TypeValueSingleNode";

        bool is_array;
        ASTNode* value;
    };

    // wait
    class WaitNode final : public ASTNode {
    public:
        std::string TYPE = "WaitNode";

        ASTNode* value;
    };

    // while
    class WhileNode final : public ASTNode {
    public:
        std::string TYPE = "WhileNode";

        ASTNode* condition;
        std::vector<ASTNode *> body;
    };
}
