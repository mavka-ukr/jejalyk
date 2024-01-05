#include "../typeinterpreter.h"

namespace jejalyk::typeinterpreter {
  Result* compile_take_module_node(
      Scope* scope,
      mavka::ast::TakeModuleNode* take_module_node) {
    const auto options = scope->get_options();
    const auto module_name_result = options->get_module_name(
        take_module_node->relative, take_module_node->name, options);
    if (!module_name_result->error.empty()) {
      return scope->error(take_module_node, module_name_result->error);
    }

    const auto module_name = module_name_result->result;
    const auto module_path_result = options->get_module_path(
        take_module_node->relative, take_module_node->name, options);
    if (!module_path_result->error.empty()) {
      return scope->error(take_module_node, module_path_result->error);
    }

    const auto module_path = module_path_result->result;
    constexpr std::hash<std::string> hash_fn;
    const auto module_variable_name =
        take_module_node->as.empty() ? module_name : take_module_node->as;
    const auto temp_module_name =
        "module_" + std::to_string(hash_fn(module_path));
    const auto init_module_js_flat_body = new js::JsFlatBodyNode();
    // await init_temp_module_name()
    init_module_js_flat_body->nodes.push_back(js::make_await(
        js::make_call(js::make_id("init_" + temp_module_name), {})));
    // м_назва = temp_module_name
    init_module_js_flat_body->nodes.push_back(
        js::make_assign(js::make_id("м_" + module_variable_name),
                        js::make_id(temp_module_name)));
    if (options->has_module(module_path)) {
      const auto module = options->get_module(module_path);
      if (take_module_node->as.empty()) {
        scope->set_local(module_name, module->subject);
      } else {
        scope->set_local(take_module_node->as, module->subject);
      }
      return success(nullptr, init_module_js_flat_body);
    }
    const auto temp_module = new Module();
    temp_module->subject = Subject::create(scope);
    temp_module->js_node = new js::JsEmptyNode();
    options->set_module(module_path, temp_module);

    const auto scope_compilation_options = options->clone();
    scope_compilation_options->current_module_path = module_path;
    if (module_path_result->builtin) {
      scope_compilation_options->arg_extensions = "1";
    }

    const auto module_code_result = options->get_module_code(
        take_module_node->relative, take_module_node->name,
        scope_compilation_options);
    if (!module_code_result->error.empty()) {
      return scope->error(take_module_node, module_code_result->error);
    }

    const auto module_code = module_code_result->result;

    const auto module_parser_result =
        mavka::parser::parse(module_code, module_path);
    if (module_parser_result->error) {
      const auto error = new Error();
      error->path = module_parser_result->error->path;
      error->message = module_parser_result->error->message;
      error->line = module_parser_result->error->line;
      error->column = module_parser_result->error->column;
      const auto result = new Result();
      result->error = error;
      return result;
    }

    const auto module_scope = scope->get_root()->make_child();
    module_scope->options = scope_compilation_options;

    const auto module_result = module_scope->compile_module(
        module_name, module_parser_result->program_node->body, module_path,
        {js::make_assign(js::make_id(temp_module_name),
                         js::make_id("мmodule"))});
    if (module_result->error) {
      return module_result;
    }

    if (take_module_node->as.empty()) {
      scope->set_local(module_name, module_result->value);
    } else {
      scope->set_local(take_module_node->as, module_result->value);
    }

    const auto js_flat_body = new js::JsFlatBodyNode();
    // var temp_module_name
    js_flat_body->nodes.push_back(js::make_var(temp_module_name));
    // async function() { ... }
    const auto js_temp_module_function = new js::JsFunctionNode();
    js_temp_module_function->async = true;
    // if (temp_module_name) return;
    const auto js_if = new js::JsIfNode();
    js_if->condition = js::make_raw(temp_module_name);
    js_if->body = js::make_body({js::make_raw("return;")});
    js_temp_module_function->body = js::make_body({js_if});

    js_temp_module_function->body->nodes.push_back(module_result->js_node);

    // var init_temp_module_name = async function() { ... }
    js_flat_body->nodes.push_back(js::make_var("init_" + temp_module_name));
    js_flat_body->nodes.push_back(js::make_assign(
        js::make_id("init_" + temp_module_name), js_temp_module_function));

    const auto module = new Module();
    module->subject = module_result->value;
    module->js_node = js_flat_body;

    options->set_module(module_path, module);

    return success(nullptr, init_module_js_flat_body);
  }
} // namespace jejalyk::typeinterpreter