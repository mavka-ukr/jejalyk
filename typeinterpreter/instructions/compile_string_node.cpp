#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_string_node(Scope* scope,
                              mavka::ast::StringNode* string_node) {
    std::vector<mavka::ast::ASTSome*> parts;
    std::string current_part;
    bool interpolation = false;

    for (int i = 0; i < string_node->value.length(); ++i) {
      if (!interpolation &&
          tools::is_digit(tools::safe_substr(string_node->value, i, 1)) &&
          tools::safe_substr(string_node->value, i - 1, 1) == "\\" &&
          tools::safe_substr(string_node->value, i - 2, 1) != "\\") {
        return scope->error(string_node, "Не вдалось розібрати текст.");
      }

      if (!interpolation &&
          tools::safe_substr(string_node->value, i, 1) == "%" &&
          tools::safe_substr(string_node->value, i + 1, 1) == "(" &&
          tools::safe_substr(string_node->value, i - 1, 1) != "\\") {
        interpolation = true;
        const auto part_string = new mavka::ast::StringNode();
        part_string->value = current_part;
        parts.push_back(mavka::ast::make_ast_some(part_string));
        current_part = "";
        i += 1;
        continue;
      }

      if (interpolation &&
          tools::safe_substr(string_node->value, i, 1) == ")" &&
          tools::safe_substr(string_node->value, i - 1, 1) != "\\") {
        interpolation = false;
        const auto parser_result = mavka::parser::parse(
            current_part, scope->get_options()->current_module_path);
        if (parser_result->error) {
          return scope->error(string_node, "Не вдалось розібрати текст.");
        }
        parts.push_back(parser_result->program_node->body[0]);
        current_part = "";
        continue;
      }

      current_part += string_node->value[i];
    }
    const auto last_part = new mavka::ast::StringNode();
    last_part->value = current_part;
    parts.push_back(mavka::ast::make_ast_some(last_part));

    std::vector<js::JsNode*> js_nodes;

    for (const auto& part : parts) {
      if (part->StringNode) {
        auto string_value = part->StringNode->value;
        tools::replace_all(string_value, "\n", "\\n");
        tools::replace_all(string_value, "\r", "\\r");
        tools::replace_all(string_value, "\t", "\\t");
        tools::replace_all(string_value, "\"", "\\\"");
        js_nodes.push_back(js::make_string(string_value));
      } else {
        const auto part_result = scope->compile_node(part);
        if (part_result->error) {
          part_result->error->line = string_node->start_line;
          part_result->error->column = string_node->start_column;
          return part_result;
        }
        if (part_result->value->is_string(scope)) {
          js_nodes.push_back(part_result->js_node);
        } else {
          const auto js_call =
              js::make_call(js::make_id("мТекст"), {part_result->js_node});
          js_nodes.push_back(js_call);
        }
      }
    }

    std::vector<std::string> js_nodes_strings;
    for (const auto js_node : js_nodes) {
      js_nodes_strings.push_back(js::stringify(js_node));
    }
    const auto js_raw = new js::JsRawNode();
    js_raw->code = tools::implode(js_nodes_strings, "+");

    const auto string_structure = scope->get_root_text();
    const auto string_result = string_structure->create_instance(scope, {});

    return success(string_result->value, js_raw);
  }
} // namespace jejalyk::typeinterpreter