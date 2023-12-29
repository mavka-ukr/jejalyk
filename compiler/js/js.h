#ifndef JS_H
#define JS_H

#include <string>
#include <vector>

namespace jejalyk::js {
  class JsNode {
   public:
    size_t start_line = 0;
    size_t start_column = 0;
    size_t end_line = 0;
    size_t end_column = 0;

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

  class JsComparisonNode : public JsNode {
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

  class JsFunctionNode : public JsNode {
   public:
    bool async;
    std::string name;
    std::vector<JsIdentifierNode*> params;
    JsBody* body;
  };

  class JsVarNode : public JsNode {
   public:
    std::string name;
  };

  class JsVarsNode : public JsNode {
   public:
    std::vector<std::string> names;
  };

  class JsForNode : public JsNode {
   public:
    JsNode* init;
    JsNode* condition;
    JsNode* update;
    JsBody* body;
    JsBody* cleanup;
  };

  class JsMapElementNode : public JsNode {
   public:
    JsNode* key;
    JsNode* value;
  };

  class JsMapNode : public JsNode {
   public:
    std::vector<JsMapElementNode*> elements;
  };

  inline JsIdentifierNode* null() {
    const auto js_identifier_node = new JsIdentifierNode();
    js_identifier_node->name = "null";
    return js_identifier_node;
  }

  inline JsStringNode* string(std::string value) {
    const auto js_string_node = new JsStringNode();
    js_string_node->value = value;
    return js_string_node;
  }

  inline JsVarNode* var(std::string name) {
    const auto js_var_node = new JsVarNode();
    js_var_node->name = name;
    return js_var_node;
  }

  inline JsVarsNode* vars(std::vector<std::string> names) {
    const auto js_vars_node = new JsVarsNode();
    js_vars_node->names = names;
    return js_vars_node;
  }

  inline JsIdentifierNode* id(std::string name) {
    const auto js_identifier_node = new JsIdentifierNode();
    js_identifier_node->name = name;
    return js_identifier_node;
  }

  std::string stringify(JsNode* js_node, size_t depth = 0);
  std::string stringify_body(JsBody* js_body, size_t depth = 0);

  inline std::string stringify(JsNode* js_node, size_t depth) {
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
      return stringify(js_assign_node->identifier, depth) + " = " +
             stringify(js_assign_node->value, depth);
    }
    if (const auto js_arithmetic_node =
            dynamic_cast<JsArithmeticNode*>(js_node)) {
      return "(" + stringify(js_arithmetic_node->left, depth) + " " +
             js_arithmetic_node->op + " " +
             stringify(js_arithmetic_node->right, depth) + ")";
    }
    if (const auto js_array_node = dynamic_cast<JsArrayNode*>(js_node)) {
      std::vector<std::string> elements;
      for (const auto element : js_array_node->elements) {
        elements.push_back(stringify(element, depth));
      }
      return "[" + tools::implode(elements, ", ") + "]";
    }
    if (const auto js_call_node = dynamic_cast<JsCallNode*>(js_node)) {
      std::vector<std::string> args;
      for (const auto arg_js_node : js_call_node->arguments) {
        args.push_back(stringify(arg_js_node, depth));
      }
      return stringify(js_call_node->value, depth) + "(" +
             tools::implode(args, ", ") + ")";
    }
    if (const auto js_access_node = dynamic_cast<JsAccessNode*>(js_node)) {
      return stringify(js_access_node->value, depth) + "[" +
             stringify(js_access_node->index, depth) + "]";
    }
    if (const auto js_chain_node = dynamic_cast<JsChainNode*>(js_node)) {
      return "" + stringify(js_chain_node->left, depth) + "." +
             stringify(js_chain_node->right, depth) + "";
    }
    if (const auto js_negative_node = dynamic_cast<JsNegativeNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_negative_node->value)) {
        return "-" + stringify(js_negative_node->value, depth);
      } else {
        return "-(" + stringify(js_negative_node->value, depth) + ")";
      }
    }
    if (const auto js_positive_node = dynamic_cast<JsPositiveNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_positive_node->value)) {
        return "+" + stringify(js_positive_node->value, depth);
      } else {
        return "+(" + stringify(js_positive_node->value, depth) + ")";
      }
    }
    if (const auto js_not_node = dynamic_cast<JsNotNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_not_node->value)) {
        return "!" + stringify(js_not_node->value, depth);
      } else {
        return "!(" + stringify(js_not_node->value, depth) + ")";
      }
    }
    if (const auto js_post_decrement =
            dynamic_cast<JsPostDecrementNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_post_decrement->value)) {
        return stringify(js_post_decrement->value, depth) + "--";
      } else {
        return "(" + stringify(js_post_decrement->value, depth) + ")--";
      }
    }
    if (const auto js_post_increment =
            dynamic_cast<JsPostIncrementNode*>(js_node)) {
      if (dynamic_cast<JsNumberNode*>(js_post_increment->value)) {
        return stringify(js_post_increment->value, depth) + "++";
      } else {
        return "(" + stringify(js_post_increment->value, depth) + ")++";
      }
    }
    if (const auto js_return_node = dynamic_cast<JsReturnNode*>(js_node)) {
      return "return " + stringify(js_return_node->value, depth);
    }
    if (const auto js_ternary_node = dynamic_cast<JsTernaryNode*>(js_node)) {
      return "((" + stringify(js_ternary_node->condition, depth) + ") ? (" +
             stringify(js_ternary_node->true_value, depth) + ") : (" +
             stringify(js_ternary_node->false_value, depth) + "))";
    }
    if (const auto js_test_node = dynamic_cast<JsTestNode*>(js_node)) {
      return "(" + stringify(js_test_node->left, depth) + " " +
             js_test_node->op + " " + stringify(js_test_node->right, depth) +
             ")";
    }
    if (const auto js_throw_node = dynamic_cast<JsThrowNode*>(js_node)) {
      return "throw " + stringify(js_throw_node->value, depth);
    }
    if (const auto js_try_node = dynamic_cast<JsTryNode*>(js_node)) {
      return "try {\n" + stringify_body(js_try_node->try_body, depth + 1) +
             "\n} catch (" + js_try_node->name + ") {\n" +
             stringify_body(js_try_node->catch_body, depth + 1) + "\n}";
    }
    if (const auto js_await_node = dynamic_cast<JsAwaitNode*>(js_node)) {
      return "await " + stringify(js_await_node->value, depth);
    }
    if (const auto js_while_node = dynamic_cast<JsWhileNode*>(js_node)) {
      return "while (" + stringify(js_while_node->condition, depth) + ") {\n" +
             stringify_body(js_while_node->body, depth + 1) + "\n}";
    }
    if (const auto js_if_node = dynamic_cast<JsIfNode*>(js_node)) {
      if (js_if_node->else_body && !js_if_node->else_body->nodes.empty()) {
        return "if (" + stringify(js_if_node->condition, depth) + ") {\n" +
               stringify_body(js_if_node->body, depth + 1) + "\n} else {\n" +
               stringify_body(js_if_node->else_body, depth + 1) + "\n}";
      } else {
        return "if (" + stringify(js_if_node->condition, depth) + ") {\n" +
               stringify_body(js_if_node->body, depth + 1) + "\n}";
      }
    }
    if (const auto js_continue_node = dynamic_cast<JsContinueNode*>(js_node)) {
      return "continue";
    }
    if (const auto js_break_node = dynamic_cast<JsBreakNode*>(js_node)) {
      return "break";
    }
    if (const auto js_function_node = dynamic_cast<JsFunctionNode*>(js_node)) {
      std::vector<std::string> params;
      for (const auto param : js_function_node->params) {
        params.push_back(stringify(param, depth));
      }
      std::string head;
      if (js_function_node->async) {
        head += "async ";
      }
      head += "function";
      if (!js_function_node->name.empty()) {
        head += " " + js_function_node->name;
      }
      head += "(" + tools::implode(params, ", ") + ") {\n";
      return head + stringify_body(js_function_node->body, depth + 1) + "\n}";
    }
    if (const auto js_var_node = dynamic_cast<JsVarNode*>(js_node)) {
      return "var " + js_var_node->name;
    }
    if (const auto js_vars_node = dynamic_cast<JsVarsNode*>(js_node)) {
      if (js_vars_node->names.empty()) {
        return "";
      }
      return "var " + tools::implode(js_vars_node->names, ", ");
    }
    if (const auto js_for_node = dynamic_cast<JsForNode*>(js_node)) {
      std::string head = "for (";
      if (js_for_node->init) {
        head += stringify(js_for_node->init, depth);
      }
      head += "; ";
      if (js_for_node->condition) {
        head += stringify(js_for_node->condition, depth);
      }
      head += "; ";
      if (js_for_node->update) {
        head += stringify(js_for_node->update, depth);
      }
      head += ") {\n";
      const auto result =
          head + stringify_body(js_for_node->body, depth + 1) + "\n}";
      if (js_for_node->cleanup) {
        return result + "\n" + stringify_body(js_for_node->cleanup, depth) +
               "\n";
      }
      return result;
    }
    if (const auto js_map_element_node =
            dynamic_cast<JsMapElementNode*>(js_node)) {
      return "[" + stringify(js_map_element_node->key, depth) + ", " +
             stringify(js_map_element_node->value, depth) + "]";
    }
    if (const auto js_map_node = dynamic_cast<JsMapNode*>(js_node)) {
      std::vector<std::string> elements;
      for (const auto element : js_map_node->elements) {
        elements.push_back(stringify(element, depth));
      }
      return "new Map([" + tools::implode(elements, ", ") + "])";
    }
    return "[CANNOT STRINGIFY]";
  }

  inline std::string stringify_body(JsBody* js_body, size_t depth) {
    std::vector<std::string> lines;
    for (const auto js_node : js_body->nodes) {
      if (const auto js_empty_node = dynamic_cast<JsEmptyNode*>(js_node)) {
      } else {
        const auto line = stringify(js_node, depth);
        if (!line.empty()) {
          lines.push_back(line);
        }
      }
    }
    std::string prefix;
    for (size_t i = 0; i < depth; ++i) {
      prefix += " ";
    }
    return tools::implode_with_prefix(lines, ";\n", prefix);
  }
} // namespace jejalyk::js

#endif // JS_H
