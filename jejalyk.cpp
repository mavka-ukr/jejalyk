#include "jejalyk.h"
#include "chrono.h"
#include "head.h"

namespace jejalyk {
  CompilationResult* compile(const std::string& code,
                             typeinterpreter::Options* options) {
    START_CHRONO(overall)

    const auto args = tools::split(options->args, " ");
    for (const auto& arg : args) {
      const auto arg_parts = tools::split(arg, "=");

      if (arg_parts[0] == "--розширення") {
        options->arg_extensions = arg_parts[1];
      }
      if (arg_parts[0] == "--строгість") {
        options->arg_strictness = arg_parts[1];
      }
    }

    const auto root_scope = new typeinterpreter::Scope();
    root_scope->is_async = true;

    const auto empty_object = new typeinterpreter::Object();
    empty_object->name = "пусто";
    const auto empty_type = new typeinterpreter::Type(empty_object);
    const auto empty_subject = new typeinterpreter::Subject();
    empty_subject->add_type(empty_type);

    const auto object_object = new typeinterpreter::Object();
    object_object->name = "обʼєкт";
    const auto object_type = new typeinterpreter::Type(object_object);
    const auto object_subject = new typeinterpreter::Subject();
    object_subject->add_type(object_type);

    const auto structure_object = new typeinterpreter::Object();
    structure_object->name = "Структура";
    structure_object->structure = object_type;
    structure_object->parent = object_type;
    const auto structure_type = new typeinterpreter::Type(structure_object);
    const auto structure_subject = new typeinterpreter::Subject();
    structure_subject->add_type(structure_type);

    const auto diia_object = new typeinterpreter::Object();
    diia_object->name = "Дія";
    diia_object->structure = structure_type;
    const auto diia_type = new typeinterpreter::Type(diia_object);
    const auto diia_subject = new typeinterpreter::Subject();
    diia_subject->add_type(diia_type);

    empty_object->structure = empty_type;
    empty_object->parent = object_type;
    object_object->structure = structure_type;

    root_scope->set_local("пусто", empty_subject);
    root_scope->set_local("обʼєкт", object_subject);
    root_scope->set_local("Структура", structure_subject);
    root_scope->set_local("Дія", diia_subject);

    const auto head_parser_result =
        mavka::parser::parse(MAVKA_HEAD_M, "[ГОЛОВА]");
    if (head_parser_result->error) {
      const auto compilation_result = new CompilationResult();
      compilation_result->error = new CompilationError();
      compilation_result->error->path = head_parser_result->error->path;
      compilation_result->error->line = head_parser_result->error->line;
      compilation_result->error->column = head_parser_result->error->column;
      compilation_result->error->message = head_parser_result->error->message;
      return compilation_result;
    }

    const auto head_options = options->clone();
    head_options->current_module_path = "[ГОЛОВА]";
    head_options->root_module_path = "[ГОЛОВА]";
    head_options->arg_extensions = "1";
    root_scope->options = head_options;

    const auto head_result =
        root_scope->compile_body(head_parser_result->program_node->body);
    if (head_result->error) {
      const auto compilation_result = new CompilationResult();
      compilation_result->error = new CompilationError();
      compilation_result->error->path = head_result->error->path;
      compilation_result->error->line = head_result->error->line;
      compilation_result->error->column = head_result->error->column;
      compilation_result->error->message = head_result->error->message;
      return compilation_result;
    }

    const auto std_scope = root_scope->make_child();
    std_scope->is_async = true;

    auto std_result = new typeinterpreter::Result();
    std_result->js_body = new js::JsBody();

    if (!options->std_code.empty()) {
      const auto std_parser_result =
          mavka::parser::parse(options->std_code, "[STD]");
      if (std_parser_result->error) {
        const auto compilation_result = new CompilationResult();
        compilation_result->error = new CompilationError();
        compilation_result->error->path = std_parser_result->error->path;
        compilation_result->error->line = std_parser_result->error->line;
        compilation_result->error->column = std_parser_result->error->column;
        compilation_result->error->message = std_parser_result->error->message;
        return compilation_result;
      }

      const auto std_options = options->clone();
      std_options->current_module_path = "[STD]";
      std_options->root_module_path = "[STD]";
      std_options->arg_extensions = "1";
      root_scope->options = std_options;

      std_result =
          std_scope->compile_body(std_parser_result->program_node->body);
      if (std_result->error) {
        const auto compilation_result = new CompilationResult();
        compilation_result->error = new CompilationError();
        compilation_result->error->path = std_result->error->path;
        compilation_result->error->line = std_result->error->line;
        compilation_result->error->column = std_result->error->column;
        compilation_result->error->message = std_result->error->message;
        return compilation_result;
      }
    }

    for (const auto& [std_var_name, std_var_value] : std_scope->variables) {
      root_scope->set_local(std_var_name, std_var_value);
    }

    const auto program_scope = root_scope->make_child();
    program_scope->is_async = true;

    root_scope->options = options;

    const auto program_parser_result =
        mavka::parser::parse(code, options->current_module_path);
    if (program_parser_result->error) {
      const auto compilation_result = new CompilationResult();
      compilation_result->error = new CompilationError();
      compilation_result->error->path = program_parser_result->error->path;
      compilation_result->error->line = program_parser_result->error->line;
      compilation_result->error->column = program_parser_result->error->column;
      compilation_result->error->message =
          program_parser_result->error->message;
      return compilation_result;
    }

    START_CHRONO(compile_program)

    const auto program_result =
        program_scope->compile_body(program_parser_result->program_node->body);
    if (program_result->error) {
      const auto compilation_result = new CompilationResult();
      compilation_result->error = new CompilationError();
      compilation_result->error->path = program_result->error->path;
      compilation_result->error->line = program_result->error->line;
      compilation_result->error->column = program_result->error->column;
      compilation_result->error->message = program_result->error->message;
      return compilation_result;
    }

    END_CHRONO(compile_program, "compiling ", options->current_module_path)

    START_CHRONO(transpile_program)

    const auto std_string = jejalyk::js::stringify_body(std_result->js_body);
    const auto program_string =
        jejalyk::js::stringify_body(program_result->js_body);

    std::string modules_string;
    for (const auto& [module_hash_name, module_js_node] : options->modules) {
      modules_string += ("\n" + js::stringify(module_js_node));
    }

    END_CHRONO(transpile_program, "transpiling ", options->current_module_path)

    const auto program_compilation_result = new CompilationResult();
    program_compilation_result->result = MAVKA_HEAD_JS + "\n" + std_string +
                                         "\n" + modules_string + "\n" +
                                         program_string;
    // program_compilation_result->result = program_string;

    END_CHRONO(overall, "overall ", options->current_module_path)

    return program_compilation_result;
  }
} // namespace jejalyk