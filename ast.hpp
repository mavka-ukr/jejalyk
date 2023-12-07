#pragma once

#include <vector>

namespace mavka::ast {
    class ASTNode {
    public:
        std::string TYPE = "ASTNode";
        int start_line = 0;
        int start_column = 0;
        int end_line = 0;
        int end_column = 0;

        virtual ~ASTNode() = default;
    };

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

    class ArgNode final : public ASTNode {
    public:
        std::string TYPE = "ArgNode";

        int index;
        std::string name;
        ASTNode* value;
    };

    class ArithmeticNode final : public ASTNode {
    public:
        std::string TYPE = "ArithmeticNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    class ArrayNode final : public ASTNode {
    public:
        std::string TYPE = "ArrayNode";

        std::vector<ASTNode *> elements;
    };

    class AsNode final : public ASTNode {
    public:
        std::string TYPE = "AsNode";

        ASTNode* left;
        ASTNode* right;
    };

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

    class AssignSimpleNode final : public ASTNode {
    public:
        std::string TYPE = "AssignSimpleNode";

        std::string name;
        ASTNode* type;
        std::string op;
        ASTNode* value;
    };

    class BitwiseNode final : public ASTNode {
    public:
        std::string TYPE = "BitwiseNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    class BitwiseNotNode final : public ASTNode {
    public:
        std::string TYPE = "BitwiseNotNode";

        ASTNode* value;
    };

    class BreakNode final : public ASTNode {
    public:
        std::string TYPE = "BreakNode";
    };

    class CallNode final : public ASTNode {
    public:
        std::string TYPE = "CallNode";

        ASTNode* value;
        std::vector<ArgNode *> args;
    };

    class ChainNode final : public ASTNode {
    public:
        std::string TYPE = "ChainNode";

        ASTNode* left;
        ASTNode* right;
    };

    class ComparisonNode final : public ASTNode {
    public:
        std::string TYPE = "ComparisonNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    class ContinueNode final : public ASTNode {
    public:
        std::string TYPE = "ContinueNode";
    };

    class DictionaryNode final : public ASTNode {
    public:
        std::string TYPE = "DictionaryNode";

        std::unordered_map<std::string, ASTNode *> elements;
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

    class EachNode final : public ASTNode {
    public:
        std::string TYPE = "EachNode";

        ASTNode* value;
        std::string keyName;
        std::string name;
        std::vector<ASTNode *> body;
    };

    class EvalNode final : public ASTNode {
    public:
        std::string TYPE = "EvalNode";

        ASTNode* value;
    };

    class FunctionNode final : public ASTNode {
    public:
        std::string TYPE = "FunctionNode";

        bool async;
        std::vector<ParamNode *> params;
        ASTNode* type;
        std::vector<ASTNode *> body;
    };

    class FromToSimpleNode final : public ASTNode {
    public:
        ASTNode* from;
        ASTNode* to;
        std::string toSymbol;
    };

    class FromToComplexNode final : public ASTNode {
    public:
        ASTNode* from;
        ASTNode* to;
        std::string toSymbol;
        ASTNode* step;
        std::string stepSymbol;
    };

    class GetElementNode final : public ASTNode {
    public:
        std::string TYPE = "GetElementNode";

        ASTNode* value;
        ASTNode* index;
    };

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

    class GodNode final : public ASTNode {
    public:
        std::string TYPE = "GodNode";

        std::vector<ASTNode *> elements;
    };

    class IdentifierNode final : public ASTNode {
    public:
        std::string TYPE = "IdentifierNode";

        std::string name;
    };

    class IfNode final : public ASTNode {
    public:
        std::string TYPE = "IfNode";

        ASTNode* condition;
        std::vector<ASTNode *> body;
        std::vector<ASTNode *> else_body;
    };

    class MockupDiiaNode final : public ASTNode {
    public:
        bool async;
        std::string name;
        std::vector<ParamNode *> params;
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

    class ModuleNode final : public ASTNode {
    public:
        std::string TYPE = "ModuleNode";

        std::string name;
        std::vector<ASTNode *> body;
    };

    class NegativeNode final : public ASTNode {
    public:
        std::string TYPE = "NegativeNode";

        ASTNode* value;
    };

    class NotNode final : public ASTNode {
    public:
        std::string TYPE = "NotNode";

        ASTNode* value;
    };

    class NumberNode final : public ASTNode {
    public:
        std::string TYPE = "NumberNode";

        std::string value;
    };

    class PositiveNode final : public ASTNode {
    public:
        std::string TYPE = "PositiveNode";

        ASTNode* value;
    };

    class PostDecrementNode final : public ASTNode {
    public:
        std::string TYPE = "PostDecrementNode";

        ASTNode* value;
    };

    class PostIncrementNode final : public ASTNode {
    public:
        std::string TYPE = "PostIncrementNode";

        ASTNode* value;
    };

    class PreDecrementNode final : public ASTNode {
    public:
        std::string TYPE = "PreDecrementNode";

        ASTNode* value;
    };

    class PreInrementNode final : public ASTNode {
    public:
        std::string TYPE = "PreInrementNode";

        ASTNode* value;
    };

    class ProgramNode final : public ASTNode {
    public:
        std::string TYPE = "ProgramNode";

        std::vector<ASTNode *> body;
    };

    class ReturnNode final : public ASTNode {
    public:
        std::string TYPE = "ReturnNode";

        ASTNode* value;
    };

    class StringNode final : public ASTNode {
    public:
        std::string TYPE = "StringNode";

        std::string value;
    };

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

    class TakeModuleNode final : public ASTNode {
    public:
        std::string TYPE = "TakeModuleNode";

        std::string name;
        std::string as;
    };

    class TakePakNode final : public ASTNode {
    public:
        std::string TYPE = "TakePakNode";

        std::string name;
        std::string as;
    };

    class TernaryNode final : public ASTNode {
    public:
        std::string TYPE = "TernaryNode";

        ASTNode* condition;
        std::vector<ASTNode *> body;
        std::vector<ASTNode *> else_body;
    };

    class TestNode final : public ASTNode {
    public:
        std::string TYPE = "TestNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    class ThrowNode final : public ASTNode {
    public:
        std::string TYPE = "ThrowNode";

        ASTNode* value;
    };

    class TryNode final : public ASTNode {
    public:
        std::string TYPE = "TryNode";

        std::vector<ASTNode *> body;
        std::string name;
        std::vector<ASTNode *> catch_body;
    };

    class TypeValueNode final : public ASTNode {
    public:
        std::string TYPE = "TypeValueNode";

        ASTNode* left;
        ASTNode* right;
        std::string op;
    };

    class TypeValueSingleNode final : public ASTNode {
    public:
        std::string TYPE = "TypeValueSingleNode";

        bool is_array;
        ASTNode* value;
    };

    class WaitNode final : public ASTNode {
    public:
        std::string TYPE = "WaitNode";

        ASTNode* value;
    };

    class WhileNode final : public ASTNode {
    public:
        std::string TYPE = "WhileNode";

        ASTNode* condition;
        std::vector<ASTNode *> body;
    };
}
