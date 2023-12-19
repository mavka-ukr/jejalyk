#include "compile_take_pak_node.h"

#include "compile_body.h"
#include "../compile.h"
#include "../../parser.h"

namespace jejalyk {
NodeCompilationResult* compile_take_pak_node(const mavka::ast::TakePakNode* take_pak_node,
                                                 CompilationScope* scope,
                                                 CompilationOptions* options) {
        const auto node_compilation_result = new NodeCompilationResult();
        const auto module_name_result = options->get_remote_module_name(take_pak_node->name, options);
        if (!module_name_result->error.empty()) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = take_pak_node->start_line;
            node_compilation_result->error->column = take_pak_node->start_column;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_name = module_name_result->result;
        const auto module_path_result = options->get_remote_module_path(take_pak_node->name, options);
        if (!module_path_result->error.empty()) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = take_pak_node->start_line;
            node_compilation_result->error->column = take_pak_node->start_column;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_variable_name = take_pak_node->as.empty() ? module_name : take_pak_node->as;
        const auto module_path = module_path_result->result;
        const std::hash<std::string> hash_fn;
        const auto temp_module_name = "module_" + module_name + "_" + std::to_string(hash_fn(module_path));
        const auto init_module_code = "await init_" + temp_module_name + "();\n" + varname(module_variable_name) + "=" +
                                      temp_module_name;
        if (scope->has_module(module_path)) {
            node_compilation_result->result = init_module_code;
            return node_compilation_result;
        }
        scope->set_module(module_path, "");
        const auto scope_compilation_options = options->clone();
        if (module_name_result->builtin) {
            scope_compilation_options->allow_js = true;
        }
        scope_compilation_options->root_module_path = module_path;
        scope_compilation_options->current_module_path = module_path;
        const auto module_code_result = options->get_remote_module_code(
            take_pak_node->name,
            scope_compilation_options
        );
        if (!module_code_result->error.empty()) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = take_pak_node->start_line;
            node_compilation_result->error->column = take_pak_node->start_column;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_code = module_code_result->result;
        if (take_pak_node->as.empty()) {
            scope->assign(module_name);
        } else {
            scope->assign(take_pak_node->as);
        }
        const auto module_parser_result = mavka::parser::parse(module_code);
        if (module_parser_result->error) {
            node_compilation_result->error = new CompilationError();
            node_compilation_result->error->path = options->current_module_path;
            node_compilation_result->error->line = module_parser_result->error->line;
            node_compilation_result->error->column = module_parser_result->error->column;
            node_compilation_result->error->message = module_parser_result->error->message;
            node_compilation_result->error->message = module_name_result->error;
            return node_compilation_result;
        }
        const auto module_scope = new CompilationScope();
        module_scope->parent = scope->root();
        const auto module_compilation_result = compile_body(module_parser_result->program_node->body,
                                                            module_scope,
                                                            scope_compilation_options,
                                                            false);
        if (module_compilation_result->error) {
            node_compilation_result->error = module_compilation_result->error;
            return node_compilation_result;
        }
        const auto compiled_module_code = "var " + temp_module_name + ";\n"
                                          + "var init_" + temp_module_name + "=async function(){\n"
                                          + "if(" + temp_module_name + "){ return; }\n"
                                          + "var module = await " + MAVKA_MODULE + "(" + "\"" + module_name + "\"" +
                                          ",async function(module){\n"
                                          + "var " + varname("___шлях_до_модуля___") + "=\"" + module_path + "\";\n"
                                          + module_compilation_result->result
                                          + "\n});\n"
                                          + temp_module_name + "=module;\n"
                                          + "\n}";
        scope->set_module(module_path, compiled_module_code);
        node_compilation_result->result = init_module_code;
        return node_compilation_result;
    }
}
