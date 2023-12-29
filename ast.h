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

  class ASTValueNode : public ASTNode {
   public:
  };

  class ASTExprNode : public ASTNode {
   public:
  };

  class AnonDiiaNode;
  class ArgNode;
  class ArithmeticNode;
  class ArrayNode;
  class AsNode;
  class AssignByElementNode;
  class AssignByIdentifierNode;
  class AssignSimpleNode;
  class BitwiseNode;
  class BitwiseNotNode;
  class BreakNode;
  class CallNode;
  class ChainNode;
  class ComparisonNode;
  class ContinueNode;
  class DictionaryElementNode;
  class DictionaryNode;
  class DiiaNode;
  class EachNode;
  class EvalNode;
  class FromToComplexNode;
  class FromToSimpleNode;
  class FunctionNode;
  class GenericNode;
  class GetElementNode;
  class GiveElementNode;
  class GiveNode;
  class GodNode;
  class IdentifierNode;
  class IfNode;
  class MethodDeclarationNode;
  class MMLNode;
  class MockupDiiaNode;
  class MockupModuleNode;
  class MockupStructureNode;
  class MockupSubjectNode;
  class ModuleNode;
  class NegativeNode;
  class NotNode;
  class NumberNode;
  class ParamNode;
  class PositiveNode;
  class PostDecrementNode;
  class PostIncrementNode;
  class PreDecrementNode;
  class PreIncrementNode;
  class ProgramNode;
  class ReturnNode;
  class StringNode;
  class StructureNode;
  class TakeModuleNode;
  class TakePakNode;
  class TernaryNode;
  class TestNode;
  class ThrowNode;
  class TryNode;
  class TypeValueSingleNode;
  class WaitNode;
  class WhileNode;

  class ParamNode final : public ASTExprNode {
   public:
    bool ee = false;
    std::string name;
    std::vector<TypeValueSingleNode*> types;
    ASTNode* value;
    bool variadic = false;
  };

  class AnonDiiaNode final : public ASTValueNode {
   public:
    bool async;
    std::vector<GenericNode*> generics;
    std::vector<ParamNode*> params;
    std::vector<TypeValueSingleNode*> return_types;
    std::vector<ASTNode*> body;
  };

  class ArgNode final : public ASTExprNode {
   public:
    int index;
    std::string name;
    ASTNode* value;
    bool spread = false;
  };

  class ArithmeticNode final : public ASTValueNode {
   public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
  };

  class ArrayNode final : public ASTValueNode {
   public:
    std::vector<ASTNode*> elements;
    std::vector<TypeValueSingleNode*> types;
  };

  class AsNode final : public ASTValueNode {
   public:
    ASTNode* left;
    ASTNode* right;
  };

  class AssignByIdentifierNode final : public ASTExprNode {
   public:
    ASTNode* left;
    std::string identifier;
    std::string op;
    ASTNode* value;
  };

  class AssignByElementNode final : public ASTExprNode {
   public:
    ASTNode* left;
    ASTNode* element;
    std::string op;
    ASTNode* value;
  };

  class AssignSimpleNode final : public ASTExprNode {
   public:
    std::string name;
    std::vector<TypeValueSingleNode*> types;
    std::string op;
    ASTNode* value;
  };

  class BitwiseNode final : public ASTValueNode {
   public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
  };

  class BitwiseNotNode final : public ASTValueNode {
   public:
    ASTNode* value;
  };

  class BreakNode final : public ASTExprNode {};

  class CallNode final : public ASTValueNode {
   public:
    ASTNode* value;
    std::vector<std::vector<TypeValueSingleNode*>> generics;
    std::vector<ArgNode*> args;
  };

  class ChainNode final : public ASTValueNode {
   public:
    ASTNode* left;
    ASTNode* right;
  };

  class ComparisonNode final : public ASTValueNode {
   public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
  };

  class ContinueNode final : public ASTExprNode {};

  class DictionaryElementNode final : public ASTExprNode {
   public:
    std::string key;
    ASTNode* value;
  };

  class DictionaryNode final : public ASTValueNode {
   public:
    std::vector<TypeValueSingleNode*> key_types;
    std::vector<TypeValueSingleNode*> value_types;
    std::vector<DictionaryElementNode*> elements;
  };

  class DiiaNode final : public ASTExprNode {
   public:
    bool ee = false;
    bool async = false;
    std::string structure;
    std::string name;
    std::vector<GenericNode*> generics;
    std::vector<ParamNode*> params;
    std::vector<TypeValueSingleNode*> return_types;
    std::vector<ASTNode*> body;
  };

  class EachNode final : public ASTExprNode {
   public:
    ASTNode* value;
    std::string keyName;
    std::string name;
    std::vector<ASTNode*> body;
  };

  class EvalNode final : public ASTExprNode {
   public:
    ASTNode* value = nullptr;
  };

  class GenericNode final : public ASTExprNode {
   public:
    std::string name;
  };

  class FunctionNode final : public ASTExprNode {
   public:
    bool async;
    std::vector<ParamNode*> params;
    std::vector<TypeValueSingleNode*> return_types;
    std::vector<ASTNode*> body;
  };

  class FromToSimpleNode final : public ASTExprNode {
   public:
    ASTNode* from;
    ASTNode* to;
    std::string toSymbol;
  };

  class FromToComplexNode final : public ASTExprNode {
   public:
    ASTNode* from;
    ASTNode* to;
    std::string toSymbol;
    ASTNode* step;
    std::string stepSymbol;
  };

  class GetElementNode final : public ASTValueNode {
   public:
    ASTNode* value = nullptr;
    ASTNode* index = nullptr;
  };

  class GiveElementNode final : public ASTExprNode {
   public:
    std::string name;
    std::string as;
  };

  class GiveNode final : public ASTExprNode {
   public:
    std::vector<GiveElementNode*> elements;
  };

  class GodNode final : public ASTExprNode {
   public:
    std::vector<ASTNode*> elements;
  };

  class IdentifierNode final : public ASTValueNode {
   public:
    std::string name;
  };

  class IfNode final : public ASTExprNode {
   public:
    ASTNode* condition;
    std::vector<ASTNode*> body;
    std::vector<ASTNode*> else_body;
  };

  class MethodDeclarationNode final : public ASTExprNode {
   public:
    bool ee = false;
    bool async = false;
    std::string name;
    std::vector<GenericNode*> generics;
    std::vector<ParamNode*> params;
    std::vector<TypeValueSingleNode*> return_types;
  };

  class MMLNode final : public ASTValueNode {
   public:
    std::string text;
  };

  class MockupDiiaNode final : public ASTExprNode {
   public:
    bool ee = false;
    bool async = false;
    std::string structure;
    std::string name;
    std::vector<GenericNode*> generics;
    std::vector<ParamNode*> params;
    std::vector<TypeValueSingleNode*> return_types;
  };

  class MockupModuleNode final : public ASTExprNode {
   public:
    std::string name;
    std::vector<ASTNode*> elements;
  };

  class MockupStructureNode final : public ASTExprNode {
   public:
    std::string name;
    std::vector<GenericNode*> generics;
    ASTNode* parent;
    std::vector<ParamNode*> params;
    std::vector<MethodDeclarationNode*> methods;
  };

  class MockupSubjectNode final : public ASTExprNode {
   public:
    std::string name;
    std::vector<TypeValueSingleNode*> types;
  };

  class ModuleNode final : public ASTExprNode {
   public:
    std::string name;
    std::vector<ASTNode*> body;
  };

  class NegativeNode final : public ASTValueNode {
   public:
    ASTNode* value = nullptr;
  };

  class NotNode final : public ASTValueNode {
   public:
    ASTNode* value = nullptr;
  };

  class NumberNode final : public ASTValueNode {
   public:
    std::string value;
  };

  class PositiveNode final : public ASTValueNode {
   public:
    ASTNode* value = nullptr;
  };

  class PostDecrementNode final : public ASTValueNode {
   public:
    ASTNode* value = nullptr;
  };

  class PostIncrementNode final : public ASTValueNode {
   public:
    ASTNode* value = nullptr;
  };

  class PreDecrementNode final : public ASTValueNode {
   public:
    ASTNode* value = nullptr;
  };

  class PreIncrementNode final : public ASTValueNode {
   public:
    ASTNode* value = nullptr;
  };

  class ProgramNode final : public ASTExprNode {
   public:
    std::vector<ASTNode*> body;
  };

  class ReturnNode final : public ASTExprNode {
   public:
    ASTNode* value = nullptr;
  };

  class StringNode final : public ASTValueNode {
   public:
    std::string value;
  };

  class StructureNode final : public ASTExprNode {
   public:
    std::string name;
    std::vector<GenericNode*> generics;
    ASTNode* parent;
    std::vector<ParamNode*> params;
    std::vector<MethodDeclarationNode*> methods;
  };

  class TakeModuleNode final : public ASTExprNode {
   public:
    bool relative;
    std::string name;
    std::string as;
  };

  class TakePakNode final : public ASTExprNode {
   public:
    std::string name;
    std::string as;
  };

  class TernaryNode final : public ASTValueNode {
   public:
    ASTNode* condition = nullptr;
    ASTNode* body = nullptr;
    ASTNode* else_body = nullptr;
  };

  class TestNode final : public ASTValueNode {
   public:
    ASTNode* left;
    ASTNode* right;
    std::string op;
  };

  class ThrowNode final : public ASTExprNode {
   public:
    ASTNode* value = nullptr;
  };

  class TryNode final : public ASTExprNode {
   public:
    std::vector<ASTNode*> body;
    std::string name;
    std::vector<ASTNode*> catch_body;
  };

  class TypeValueSingleNode final : public ASTExprNode {
   public:
    ASTNode* value;
    std::vector<std::vector<TypeValueSingleNode*>> generics;
  };

  class WaitNode final : public ASTValueNode {
   public:
    ASTNode* value = nullptr;
  };

  class WhileNode final : public ASTExprNode {
   public:
    ASTNode* condition;
    std::vector<ASTNode*> body;
  };
} // namespace mavka::ast
#endif // AST_H
