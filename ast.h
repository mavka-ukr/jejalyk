#pragma once

#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

namespace mavka::ast {
  class ASTNode {
   public:
    size_t start_line = 0;
    size_t start_column = 0;
    size_t end_line = 0;
    size_t end_column = 0;

    virtual ~ASTNode() = default;
  };

  class ParamNode final : public ASTNode {
   public:
    std::string name;
    std::vector<ASTNode*> types;
    ASTNode* value;
    bool variadic = false;
  };

  class AnonDiiaNode final : public ASTNode {
   public:
    bool async;
    std::vector<ParamNode*> params;
    std::vector<ASTNode*> return_types;
    std::vector<ASTNode*> body;
  };

  class ArgNode final : public ASTNode {
   public:
    int index;
    std::string name;
    ASTNode* value;
    bool spread = false;
  };

  class ArithmeticNode final : public ASTNode {
   public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
  };

  class ArrayNode final : public ASTNode {
   public:
    std::vector<ASTNode*> elements;
  };

  class AsNode final : public ASTNode {
   public:
    ASTNode* left;
    ASTNode* right;
  };

  class AssignByIdentifierNode final : public ASTNode {
   public:
    ASTNode* left;
    std::string identifier;
    std::string op;
    ASTNode* value;
  };

  class AssignByElementNode final : public ASTNode {
   public:
    ASTNode* left;
    ASTNode* element;
    std::string op;
    ASTNode* value;
  };

  class AssignSimpleNode final : public ASTNode {
   public:
    std::string name;
    std::vector<ASTNode*> types;
    std::string op;
    ASTNode* value;
  };

  class BitwiseNode final : public ASTNode {
   public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
  };

  class BitwiseNotNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class BreakNode final : public ASTNode {};

  class CallNode final : public ASTNode {
   public:
    ASTNode* value;
    std::vector<ArgNode*> args;
  };

  class ChainNode final : public ASTNode {
   public:
    ASTNode* left;
    ASTNode* right;
  };

  class ComparisonNode final : public ASTNode {
   public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
  };

  class ContinueNode final : public ASTNode {};

  class DictionaryElementNode final : public ASTNode {
   public:
    std::string key;
    ASTNode* value;
  };

  class DictionaryNode final : public ASTNode {
   public:
    std::vector<DictionaryElementNode*> elements;
  };

  class DiiaNode final : public ASTNode {
   public:
    bool async;
    std::string structure;
    std::string name;
    std::vector<ParamNode*> params;
    std::vector<ASTNode*> return_types;
    std::vector<ASTNode*> body;
  };

  class EachNode final : public ASTNode {
   public:
    ASTNode* value;
    std::string keyName;
    std::string name;
    std::vector<ASTNode*> body;
  };

  class EvalNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class FunctionNode final : public ASTNode {
   public:
    bool async;
    std::vector<ParamNode*> params;
    std::vector<ASTNode*> return_types;
    std::vector<ASTNode*> body;
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
    ASTNode* value;
    ASTNode* index;
  };

  class GiveElementNode final : public ASTNode {
   public:
    std::string name;
    std::string as;
  };

  class GiveNode final : public ASTNode {
   public:
    std::vector<GiveElementNode*> elements;
  };

  class GodNode final : public ASTNode {
   public:
    std::vector<ASTNode*> elements;
  };

  class IdentifierNode final : public ASTNode {
   public:
    std::string name;
  };

  class IfNode final : public ASTNode {
   public:
    ASTNode* condition;
    std::vector<ASTNode*> body;
    std::vector<ASTNode*> else_body;
  };

  class MockupDiiaNode final : public ASTNode {
   public:
    bool async;
    std::string name;
    std::vector<ParamNode*> params;
    std::vector<ASTNode*> return_types;
  };

  class MockupModuleNode final : public ASTNode {
   public:
    std::string name;
    std::vector<ASTNode*> elements;
  };

  class MockupObjectNode final : public ASTNode {
   public:
    std::string name;
    std::vector<ASTNode*> elements;
  };

  class MockupStructureNode final : public ASTNode {
   public:
    std::string name;
    ASTNode* parent;
    std::vector<ASTNode*> params;
  };

  class MockupSubjectNode final : public ASTNode {
   public:
    std::string name;
    std::vector<ASTNode*> types;
  };

  class ModuleNode final : public ASTNode {
   public:
    std::string name;
    std::vector<ASTNode*> body;
  };

  class NegativeNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class NotNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class NumberNode final : public ASTNode {
   public:
    std::string value;
  };

  class PositiveNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class PostDecrementNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class PostIncrementNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class PreDecrementNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class PreIncrementNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class ProgramNode final : public ASTNode {
   public:
    std::vector<ASTNode*> body;
  };

  class ReturnNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class StringNode final : public ASTNode {
   public:
    std::string value;
  };

  class StructureNode final : public ASTNode {
   public:
    std::string name;
    ASTNode* parent;
    std::vector<ParamNode*> params;
  };

  class TakeModuleNode final : public ASTNode {
   public:
    bool relative;
    std::string name;
    std::string as;
  };

  class TakePakNode final : public ASTNode {
   public:
    std::string name;
    std::string as;
  };

  class TernaryNode final : public ASTNode {
   public:
    ASTNode* condition;
    std::vector<ASTNode*> body;
    std::vector<ASTNode*> else_body;
  };

  class TestNode final : public ASTNode {
   public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
  };

  class ThrowNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class TryNode final : public ASTNode {
   public:
    std::vector<ASTNode*> body;
    std::string name;
    std::vector<ASTNode*> catch_body;
  };

  class TypeValueNode final : public ASTNode {
   public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
  };

  class TypeValueSingleNode final : public ASTNode {
   public:
    bool is_array;
    ASTNode* value;
  };

  class WaitNode final : public ASTNode {
   public:
    ASTNode* value;
  };

  class WhileNode final : public ASTNode {
   public:
    ASTNode* condition;
    std::vector<ASTNode*> body;
  };
}  // namespace mavka::ast
#endif  // AST_H
