#include "compile_assign_by_element_node.h"

#include "../compile.h"
#include "compile_node.h"

namespace jejalyk {
NodeCompilationResult* compile_assign_by_element_node(
    const mavka::ast::AssignByElementNode* assign_by_element_node,
    CompilationScope* scope,
    CompilationOptions* options,
    CompilationState* state) {
  const auto diName = state->put_debug(options->current_module_path,
                                       assign_by_element_node->start_line,
                                       assign_by_element_node->start_column);
  if (assign_by_element_node->op == "=") {
    const auto node_compilation_result = new NodeCompilationResult();
    const auto assign_left =
        compile_node(assign_by_element_node->left, scope, options, state);
    if (assign_left->error) {
      node_compilation_result->error = assign_left->error;
      return node_compilation_result;
    }
    const auto assign_element =
        compile_node(assign_by_element_node->element, scope, options, state);
    if (assign_element->error) {
      node_compilation_result->error = assign_element->error;
      return node_compilation_result;
    }
    const auto assign_value =
        compile_node(assign_by_element_node->value, scope, options, state);
    if (assign_value->error) {
      node_compilation_result->error = assign_value->error;
      return node_compilation_result;
    }
    node_compilation_result->result = MAVKA_SET_ELEMENT + "(" +
                                      assign_left->result + "," +
                                      assign_element->result + "," +
                                      assign_value->result + "," + diName + ")";
    return node_compilation_result;
  } else {
    auto operation = assign_by_element_node->op;
    if (operation == "+=") {
      operation = "+";
    }
    if (operation == "-=") {
      operation = "-";
    }
    if (operation == "*=") {
      operation = "*";
    }
    if (operation == "/=") {
      operation = "/";
    }
    if (operation == "%=") {
      operation = "%";
    }
    if (operation == "//=") {
      operation = "//";
    }
    if (operation == "**=") {
      operation = "**";
    }
    const auto new_assign_by_element_node =
        new mavka::ast::AssignByElementNode();
    new_assign_by_element_node->left = assign_by_element_node->left;
    new_assign_by_element_node->element = assign_by_element_node->element;
    new_assign_by_element_node->op = "=";
    const auto arithmetic_node = new mavka::ast::ArithmeticNode();
    const auto get_element_node = new mavka::ast::GetElementNode();
    get_element_node->value = assign_by_element_node->left;
    get_element_node->index = assign_by_element_node->element;
    arithmetic_node->left = get_element_node;
    arithmetic_node->right = assign_by_element_node->value;
    arithmetic_node->op = operation;
    new_assign_by_element_node->value = arithmetic_node;
    return compile_assign_by_element_node(new_assign_by_element_node, scope,
                                          options, state);
  }
}
}  // namespace jejalyk
