#ifndef JS_H
#define JS_H

#include <string>
#include <vector>

#include "../tools.h"

// насправді компілятор настільки гнучкий,
// що можна зробити компіляцію в будь-яку мову (в тому числі машинний код)

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
    JsNode* identifier;
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
    std::vector<JsNode*> params;
    JsBody* body = nullptr;
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

  class JsRawNode : public JsNode {
   public:
    std::string code;
  };

  class JsElementNode : public JsNode {
   public:
    JsNode* value;
    JsNode* element;
  };

  class JsNestedNode : public JsNode {
   public:
    JsNode* value;
  };

  class JsFlatBodyNode : public JsNode {
   public:
    std::vector<JsNode*> nodes;
  };

  inline JsIdentifierNode* null() {
    const auto js_identifier_node = new JsIdentifierNode();
    js_identifier_node->name = "null";
    return js_identifier_node;
  }

  inline JsIdentifierNode* make_null() {
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

  inline JsVarNode* make_var(std::string name) {
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

  inline JsIdentifierNode* make_id(std::string name) {
    const auto js_identifier_node = new JsIdentifierNode();
    js_identifier_node->name = name;
    return js_identifier_node;
  }

  inline JsChainNode* make_chain(JsNode* left, JsNode* right) {
    const auto js_chain_node = new JsChainNode();
    js_chain_node->left = left;
    js_chain_node->right = right;
    return js_chain_node;
  }

  inline JsChainNode* make_chain(std::string left, std::string right) {
    const auto js_chain_node = new JsChainNode();
    js_chain_node->left = make_id(left);
    js_chain_node->right = make_id(right);
    return js_chain_node;
  }

  inline JsCallNode* make_call(JsNode* value, std::vector<JsNode*> arguments) {
    const auto js_call_node = new JsCallNode();
    js_call_node->value = value;
    js_call_node->arguments = arguments;
    return js_call_node;
  }

  inline JsElementNode* make_element(JsNode* value, JsNode* element) {
    const auto js_element_node = new JsElementNode();
    js_element_node->value = value;
    js_element_node->element = element;
    return js_element_node;
  }

  inline JsArithmeticNode* make_arithmetic(JsNode* left,
                                           std::string op,
                                           JsNode* right) {
    const auto js_arithmetic_node = new JsArithmeticNode();
    js_arithmetic_node->left = left;
    js_arithmetic_node->op = op;
    js_arithmetic_node->right = right;
    return js_arithmetic_node;
  }

  inline JsAssignNode* make_assign(JsNode* left, JsNode* value) {
    const auto js_assign_node = new JsAssignNode();
    js_assign_node->identifier = left;
    js_assign_node->value = value;
    return js_assign_node;
  }

  inline JsAssignNode* make_assign(std::string left, std::string value) {
    const auto js_assign_node = new JsAssignNode();
    js_assign_node->identifier = make_id(left);
    js_assign_node->value = make_id(value);
    return js_assign_node;
  }

  inline JsNegativeNode* make_negative(JsNode* value) {
    const auto js_negative_node = new JsNegativeNode();
    js_negative_node->value = value;
    return js_negative_node;
  }

  inline JsPositiveNode* make_positive(JsNode* value) {
    const auto js_positive_node = new JsPositiveNode();
    js_positive_node->value = value;
    return js_positive_node;
  }

  inline JsNotNode* make_not(JsNode* value) {
    const auto js_not_node = new JsNotNode();
    js_not_node->value = value;
    return js_not_node;
  }

  inline JsComparisonNode* make_comparison(JsNode* left,
                                           std::string op,
                                           JsNode* right) {
    const auto js_comparison_node = new JsComparisonNode();
    js_comparison_node->left = left;
    js_comparison_node->op = op;
    js_comparison_node->right = right;
    return js_comparison_node;
  }

  inline JsNumberNode* make_number(std::string value) {
    const auto js_number_node = new JsNumberNode();
    js_number_node->value = value;
    return js_number_node;
  }

  inline JsStringNode* make_string(std::string value) {
    const auto js_string_node = new JsStringNode();
    js_string_node->value = value;
    return js_string_node;
  }

  inline JsAccessNode* make_access(JsNode* value, JsNode* index) {
    const auto js_access_node = new JsAccessNode();
    js_access_node->value = value;
    js_access_node->index = index;
    return js_access_node;
  }

  inline JsAccessNode* make_access(std::string value, std::string index) {
    const auto js_access_node = new JsAccessNode();
    js_access_node->value = make_id(value);
    js_access_node->index = make_id(index);
    return js_access_node;
  }

  inline JsTestNode* make_test(JsNode* left, std::string op, JsNode* right) {
    const auto js_test_node = new JsTestNode();
    js_test_node->left = left;
    js_test_node->op = op;
    js_test_node->right = right;
    return js_test_node;
  }

  inline JsReturnNode* make_return(JsNode* value) {
    const auto js_return_node = new JsReturnNode();
    js_return_node->value = value;
    return js_return_node;
  }

  inline JsArrayNode* make_array(std::vector<JsNode*> elements) {
    const auto js_array_node = new JsArrayNode();
    js_array_node->elements = elements;
    return js_array_node;
  }

  inline JsMapNode* make_map(std::vector<JsMapElementNode*> elements) {
    const auto js_map_node = new JsMapNode();
    js_map_node->elements = elements;
    return js_map_node;
  }

  inline JsMapElementNode* make_map_element(JsNode* key, JsNode* value) {
    const auto js_map_element_node = new JsMapElementNode();
    js_map_element_node->key = key;
    js_map_element_node->value = value;
    return js_map_element_node;
  }

  inline JsMapElementNode* make_map_element(std::string key, JsNode* value) {
    const auto js_map_element_node = new JsMapElementNode();
    js_map_element_node->key = make_string(key);
    js_map_element_node->value = value;
    return js_map_element_node;
  }

  inline JsNestedNode* make_nested(JsNode* value) {
    const auto js_nested_node = new JsNestedNode();
    js_nested_node->value = value;
    return js_nested_node;
  }

  inline JsNode* make_maybe_nested(JsNode* value) {
    if (dynamic_cast<JsNumberNode*>(value) ||
        dynamic_cast<JsStringNode*>(value) ||
        dynamic_cast<JsIdentifierNode*>(value) ||
        dynamic_cast<JsArrayNode*>(value)) {
      return value;
    }
    const auto js_nested_node = new JsNestedNode();
    js_nested_node->value = value;
    return js_nested_node;
  }

  inline JsAwaitNode* make_await(JsNode* value) {
    const auto js_await_node = new JsAwaitNode();
    js_await_node->value = value;
    return js_await_node;
  }

  inline JsRawNode* make_raw(std::string code) {
    const auto js_raw_node = new JsRawNode();
    js_raw_node->code = code;
    return js_raw_node;
  }

  inline JsBody* make_body(std::vector<JsNode*> nodes) {
    const auto js_body = new JsBody();
    js_body->nodes = nodes;
    return js_body;
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
      std::string prefix;
      for (size_t i = 0; i < depth; ++i) {
        prefix += " ";
      }
      return "try {\n" + stringify_body(js_try_node->try_body, depth + 1) +
             "\n" + prefix + "} catch (" + js_try_node->name + ") {\n" +
             stringify_body(js_try_node->catch_body, depth + 1) + "\n" +
             prefix + "}";
    }
    if (const auto js_await_node = dynamic_cast<JsAwaitNode*>(js_node)) {
      return "await " + stringify(js_await_node->value, depth);
    }
    if (const auto js_while_node = dynamic_cast<JsWhileNode*>(js_node)) {
      std::string prefix;
      for (size_t i = 0; i < depth; ++i) {
        prefix += " ";
      }
      return "while (" + stringify(js_while_node->condition, depth) + ") {\n" +
             stringify_body(js_while_node->body, depth + 1) + "\n" + prefix +
             "}";
    }
    if (const auto js_if_node = dynamic_cast<JsIfNode*>(js_node)) {
      std::string prefix;
      for (size_t i = 0; i < depth; ++i) {
        prefix += " ";
      }
      if (js_if_node->else_body && !js_if_node->else_body->nodes.empty()) {
        return "if (" + stringify(js_if_node->condition, depth) + ") {\n" +
               stringify_body(js_if_node->body, depth + 1) + "\n" + prefix +
               "} else {\n" + stringify_body(js_if_node->else_body, depth + 1) +
               "\n" + prefix + "}";
      } else {
        return "if (" + stringify(js_if_node->condition, depth) + ") {\n" +
               stringify_body(js_if_node->body, depth + 1) + "\n" + prefix +
               "}";
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
      std::string prefix;
      for (size_t i = 0; i < depth; ++i) {
        prefix += " ";
      }
      head += "(" + tools::implode(params, ", ") + ") {\n";
      return head + stringify_body(js_function_node->body, depth + 1) + "\n" +
             prefix + "}";
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
      const auto result = head + stringify_body(js_for_node->body, depth + 1) +
                          "\n" + tools::repeat_string(" ", depth) + "}";
      if (js_for_node->cleanup) {
        return result + "\n" + stringify_body(js_for_node->cleanup, depth);
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
    if (const auto js_raw_node = dynamic_cast<JsRawNode*>(js_node)) {
      return js_raw_node->code;
    }
    if (const auto js_element_node = dynamic_cast<JsElementNode*>(js_node)) {
      return stringify(js_element_node->value, depth) + "[" +
             stringify(js_element_node->element, depth) + "]";
    }
    if (const auto js_comparison_node =
            dynamic_cast<JsComparisonNode*>(js_node)) {
      return "(" + stringify(js_comparison_node->left, depth) + " " +
             js_comparison_node->op + " " +
             stringify(js_comparison_node->right, depth) + ")";
    }
    if (const auto js_nested_node = dynamic_cast<JsNestedNode*>(js_node)) {
      return "(" + stringify(js_nested_node->value, depth) + ")";
    }
    if (const auto js_flat_body_node = dynamic_cast<JsFlatBodyNode*>(js_node)) {
      std::vector<std::string> lines;
      for (const auto js_fb_node : js_flat_body_node->nodes) {
        const auto line = stringify(js_fb_node, depth);
        if (!line.empty()) {
          lines.push_back(line);
        }
      }
      std::string prefix;
      for (size_t i = 0; i < depth; ++i) {
        prefix += " ";
      }
      return tools::trim(tools::implode_with_prefix(lines, ";\n", prefix));
    }
    if (js_node == nullptr) {
      return "undefined";
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
