#ifndef JS_H
#define JS_H

#include <string>
#include <vector>

namespace jejalyk::js {
  class JsNode {
   public:
    size_t start_line;
    size_t start_column;
    size_t end_line;
    size_t end_column;

    virtual ~JsNode() = default;
  };

  class JsEmptyNode : public JsNode {};

  class JsBody {
   public:
    std::vector<JsNode*> nodes;
  };

  class JsNumberNode : public JsNode {
   public:
    std::string value;
  };

  class JsStringNode : public JsNode {
   public:
    std::string value;
  };

  class JsIdentifierNode : public JsNode {
   public:
    std::string name;
  };

  class JsCallNode : public JsNode {
   public:
    JsNode* value;
    std::vector<JsNode*> arguments;
  };

  class JsAccessNode : public JsNode {
   public:
    JsNode* value;
    JsNode* index;
  };

  class JsArithmeticNode : public JsNode {
   public:
    std::string op;
    JsNode* left;
    JsNode* right;
  };

  class JsChainNode : public JsNode {
   public:
    JsNode* left;
    JsNode* right;
  };

  class JsAssignNode : public JsNode {
   public:
    JsIdentifierNode* identifier;
    JsNode* value;
  };

  class JsNegativeNode : public JsNode {
   public:
    JsNode* value;
  };

  class JsNotNode : public JsNode {
   public:
    JsNode* value;
  };

  class JsPositiveNode : public JsNode {
   public:
    JsNode* value;
  };

  class JsPostDecrementNode : public JsNode {
   public:
    JsNode* value;
  };

  class JsPostIncrementNode : public JsNode {
   public:
    JsNode* value;
  };

  class JsReturnNode : public JsNode {
   public:
    JsNode* value;
  };

  class JsTernaryNode : public JsNode {
   public:
    JsNode* condition;
    JsNode* true_value;
    JsNode* false_value;
  };

  class JsArrayNode : public JsNode {
   public:
    std::vector<JsNode*> elements;
  };

  class JsTestNode : public JsNode {
   public:
    JsNode* left;
    JsNode* right;
    std::string op;
  };

  class JsThrowNode : public JsNode {
   public:
    JsNode* value;
  };

  class JsTryNode : public JsNode {
   public:
    JsBody* try_body;
    JsBody* catch_body;
    std::string name;
  };

  class JsAwaitNode : public JsNode {
   public:
    JsNode* value;
  };

  class JsWhileNode : public JsNode {
   public:
    JsNode* condition;
    JsBody* body;
  };

  class JsIfNode : public JsNode {
   public:
    JsNode* condition;
    JsBody* body;
    JsBody* else_body;
  };

  class JsContinueNode : public JsNode {};
  class JsBreakNode : public JsNode {};

  std::string stringify(JsNode* js_node);
  std::string stringify_body(JsBody* js_body);

  inline std::string stringify(JsNode* js_node) {
    if (const auto js_empty_node = dynamic_cast<JsEmptyNode*>(js_node)) {
      return "";
    }
    if (const auto js_number_node = dynamic_cast<JsNumberNode*>(js_node)) {
      return js_number_node->value;
    }
    if (const auto js_string_node = dynamic_cast<JsStringNode*>(js_node)) {
      return "\"" + js_string_node->value + "\"";
    }
    if (const auto js_identifier_node =
            dynamic_cast<JsIdentifierNode*>(js_node)) {
      return js_identifier_node->name;
    }
    if (const auto js_assign_node = dynamic_cast<JsAssignNode*>(js_node)) {
      return stringify(js_assign_node->identifier) + " = " +
             stringify(js_assign_node->value);
    }
    if (const auto js_arithmetic_node =
            dynamic_cast<JsArithmeticNode*>(js_node)) {
      return "(" + stringify(js_arithmetic_node->left) + " " +
             js_arithmetic_node->op + " " +
             stringify(js_arithmetic_node->right) + ")";
    }
    if (const auto js_array_node = dynamic_cast<JsArrayNode*>(js_node)) {
      std::vector<std::string> elements;
      for (const auto element : js_array_node->elements) {
        elements.push_back(stringify(element));
      }
      return "[" + tools::implode(elements, ", ") + "]";
    }
    if (const auto js_call_node = dynamic_cast<JsCallNode*>(js_node)) {
      std::vector<std::string> args;
      for (const auto arg_js_node : js_call_node->arguments) {
        args.push_back(stringify(arg_js_node));
      }
      return stringify(js_call_node->value) + "(" + tools::implode(args, ", ") +
             ")";
    }
    if (const auto js_access_node = dynamic_cast<JsAccessNode*>(js_node)) {
      return stringify(js_access_node->value) + "[" +
             stringify(js_access_node->index) + "]";
    }
    if (const auto js_chain_node = dynamic_cast<JsChainNode*>(js_node)) {
      return "" + stringify(js_chain_node->left) + "." +
             stringify(js_chain_node->right) + "";
    }
    if (const auto js_negative_node = dynamic_cast<JsNegativeNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_negative_node->value)) {
        return "-" + stringify(js_negative_node->value);
      } else {
        return "-(" + stringify(js_negative_node->value) + ")";
      }
    }
    if (const auto js_positive_node = dynamic_cast<JsPositiveNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_positive_node->value)) {
        return "+" + stringify(js_positive_node->value);
      } else {
        return "+(" + stringify(js_positive_node->value) + ")";
      }
    }
    if (const auto js_not_node = dynamic_cast<JsNotNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_not_node->value)) {
        return "!" + stringify(js_not_node->value);
      } else {
        return "!(" + stringify(js_not_node->value) + ")";
      }
    }
    if (const auto js_post_decrement =
            dynamic_cast<JsPostDecrementNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_post_decrement->value)) {
        return stringify(js_post_decrement->value) + "--";
      } else {
        return "(" + stringify(js_post_decrement->value) + ")--";
      }
    }
    if (const auto js_post_increment =
            dynamic_cast<JsPostIncrementNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_post_increment->value)) {
        return stringify(js_post_increment->value) + "++";
      } else {
        return "(" + stringify(js_post_increment->value) + ")++";
      }
    }
    if (const auto js_return_node = dynamic_cast<JsReturnNode*>(js_node)) {
      return "return " + stringify(js_return_node->value);
    }
    if (const auto js_ternary_node = dynamic_cast<JsTernaryNode*>(js_node)) {
      return "((" + stringify(js_ternary_node->condition) + ") ? (" +
             stringify(js_ternary_node->true_value) + ") : (" +
             stringify(js_ternary_node->false_value) + "))";
    }
    if (const auto js_test_node = dynamic_cast<JsTestNode*>(js_node)) {
      return "(" + stringify(js_test_node->left) + " " + js_test_node->op +
             " " + stringify(js_test_node->right) + ")";
    }
    if (const auto js_throw_node = dynamic_cast<JsThrowNode*>(js_node)) {
      return "throw " + stringify(js_throw_node->value);
    }
    if (const auto js_try_node = dynamic_cast<JsTryNode*>(js_node)) {
      return "try {\n" + stringify_body(js_try_node->try_body) + "\n} catch (" +
             js_try_node->name + ") {\n" +
             stringify_body(js_try_node->catch_body) + "\n}";
    }
    if (const auto js_await_node = dynamic_cast<JsAwaitNode*>(js_node)) {
      return "await " + stringify(js_await_node->value);
    }
    if (const auto js_while_node = dynamic_cast<JsWhileNode*>(js_node)) {
      return "while (" + stringify(js_while_node->condition) + ") {\n" +
             stringify_body(js_while_node->body) + "\n}";
    }
    if (const auto js_if_node = dynamic_cast<JsIfNode*>(js_node)) {
      if (js_if_node->else_body && !js_if_node->else_body->nodes.empty()) {
        return "if (" + stringify(js_if_node->condition) + ") {\n" +
               stringify_body(js_if_node->body) + "\n} else {\n" +
               stringify_body(js_if_node->else_body) + "\n}";
      } else {
        return "if (" + stringify(js_if_node->condition) + ") {\n" +
               stringify_body(js_if_node->body) + "\n}";
      }
    }
    if (const auto js_continue_node = dynamic_cast<JsContinueNode*>(js_node)) {
      return "continue";
    }
    if (const auto js_break_node = dynamic_cast<JsBreakNode*>(js_node)) {
      return "break";
    }
    return "[CANNOT STRINGIFY]";
  }

  inline std::string stringify_body(JsBody* js_body) {
    std::vector<std::string> lines;
    for (const auto js_node : js_body->nodes) {
      if (const auto js_empty_node = dynamic_cast<JsEmptyNode*>(js_node)) {
      } else {
        lines.push_back(stringify(js_node));
      }
    }
    return tools::implode(lines, ";\n");
  }
} // namespace jejalyk::js

#endif // JS_H
