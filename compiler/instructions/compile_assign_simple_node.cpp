#include "compile_assign_simple_node.h"

#include "../compile.h"
#include "compile_node.h"
#include "compile_types.h"

namespace jejalyk {
  NodeCompilationResult* compile_assign_simple_node(
      const mavka::ast::AssignSimpleNode* assign_simple_node,
      CompilationScope* scope,
      CompilationOptions* options,
      CompilationState* state) {
    if (assign_simple_node->op == "=") {
      const auto node_compilation_result = new NodeCompilationResult();
      const auto assign_name = assign_simple_node->name;

      if (scope->has_local(assign_name)) {
        if (!assign_simple_node->types.empty()) {
          node_compilation_result->error = compilation_error_from_ast_node(
              assign_simple_node, options->current_module_path,
              "[X] Неможливо перевизначити субʼєкт \"" + assign_name + "\".");
          return node_compilation_result;
        }
      } else {
        const auto types_compilation_result =
            compile_types(assign_simple_node->types, scope, options, state);
        if (types_compilation_result->error) {
          node_compilation_result->error = types_compilation_result->error;
          return node_compilation_result;
        }
        if (const auto define_error =
                scope->define(assign_name, types_compilation_result->subject)) {
          node_compilation_result->error = define_error;
          return node_compilation_result;
        }
      }

      const auto compiled_assign_value =
          compile_node(assign_simple_node->value, scope, options, state);
      if (compiled_assign_value->error) {
        node_compilation_result->error = compiled_assign_value->error;
        return node_compilation_result;
      }
      if (const auto assign_error =
              scope->assign(assign_name, compiled_assign_value->subject)) {
        node_compilation_result->error = assign_error;
        return node_compilation_result;
      }
      node_compilation_result->result =
          varname(assign_name) + "=" + compiled_assign_value->result;
      return node_compilation_result;
    } else {
      auto operation = assign_simple_node->op;
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
      const auto new_assign_simple_node = new mavka::ast::AssignSimpleNode();
      new_assign_simple_node->name = assign_simple_node->name;
      new_assign_simple_node->op = "=";
      const auto arithmetic_node = new mavka::ast::ArithmeticNode();
      const auto identifier_node = new mavka::ast::IdentifierNode();
      identifier_node->name = assign_simple_node->name;
      arithmetic_node->left = identifier_node;
      arithmetic_node->right = assign_simple_node->value;
      arithmetic_node->op = operation;
      new_assign_simple_node->value = arithmetic_node;
      return compile_assign_simple_node(new_assign_simple_node, scope, options,
                                        state);
    }
}
}  // namespace jejalyk
