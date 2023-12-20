#pragma once

#ifndef JEJALYK_H
#define JEJALYK_H

#include <string>
#include "compiler/compile.h"
#include "compiler/instructions/compile_body.h"
#include "head.h"
#include "parser.h"
#include "tools.h"

namespace jejalyk {
  inline std::string wrap_run(std::string head,
                              std::string std,
                              std::string code) {
    return R"(
)" + head +
           R"(
)" + std +
           R"(
try{
)" + code +
           R"(
}catch(e) {
  if(e) {
    if(e instanceof Падіння){
      if(e.ді) {
        м_друк(e.ді+":",e.значення);
      }else{
        м_друк(e.значення);
      }
    }else{
      throw e;
    }
  }else{
    throw e;
  }
}
)";
  }

  inline CompilationResult* compile(const std::string& code,
                                    CompilationOptions* options) {
    const auto root_scope = new CompilationScope();
    const auto state = new CompilationState();
    std::vector<std::string> args = tools::split(options->args, " ");
    for (const auto& arg : args) {
      const auto arg_parts = tools::split(arg, "=");

      if (arg_parts[0] == "--інфо-викликів") {
        state->store_debug = arg_parts[1] == "1";
      }
      if (arg_parts[0] == "--розширення") {
        options->allow_js = arg_parts[1] == "1";
      }
    }
    const auto compilation_result = new CompilationResult();

    const auto head =
        "js \"\"\"" + MAVKA_HEAD_JS + "\"\"\"" + "\n" + MAVKA_HEAD_M;

    const auto head_parser_result = mavka::parser::parse(head);
    if (head_parser_result->error) {
      const auto head_compilation_result = new CompilationResult();
      head_compilation_result->error = new CompilationError();
      // head_compilation_result->error->path = "[ГОЛОВА]";
      head_compilation_result->error->line = head_parser_result->error->line;
      head_compilation_result->error->column =
          head_parser_result->error->column;
      head_compilation_result->error->message =
          "[ВАДА В ГОЛОВІ :(] " + head_parser_result->error->message;
      return head_compilation_result;
    }
    const auto head_compilation_result = new CompilationResult();
    const auto head_scope = new CompilationScope();
    head_scope->parent = root_scope;
    const auto head_options = options->clone();
    head_options->allow_js = true;
    const auto head_body_compilation_result =
        jejalyk::compile_body(head_parser_result->program_node->body,
                              head_scope, head_options, state, false);
    if (head_body_compilation_result->error) {
      head_body_compilation_result->error->message =
          "[ВАДА В ГОЛОВІ :(] " + head_body_compilation_result->error->message;
      head_compilation_result->error = head_body_compilation_result->error;
      return head_compilation_result;
    }
    for (const auto& [name, value] : head_scope->subjects) {
      root_scope->subjects[name] = value;
    }

    if (!options->std_code.empty()) {
      const auto std_parser_result = mavka::parser::parse(options->std_code);
      if (std_parser_result->error) {
        const auto std_compilation_result = new CompilationResult();
        std_compilation_result->error = new CompilationError();
        // std_compilation_result->error->path = "[STD]";
        std_compilation_result->error->line = std_parser_result->error->line;
        std_compilation_result->error->column =
            std_parser_result->error->column;
        std_compilation_result->error->message =
            "[ВАДА В STD] " + std_parser_result->error->message;
        return std_compilation_result;
      }
      const auto std_compilation_result = new CompilationResult();
      const auto std_scope = new CompilationScope();
      std_scope->parent = root_scope;
      const auto std_options = options->clone();
      std_options->allow_js = true;
      const auto std_body_compilation_result =
          jejalyk::compile_body(std_parser_result->program_node->body,
                                std_scope, std_options, state, false);
      if (std_body_compilation_result->error) {
        std_body_compilation_result->error->message =
            "[ВАДА В STD] " + std_body_compilation_result->error->message;
        std_compilation_result->error = std_body_compilation_result->error;
        return std_compilation_result;
      }
      compilation_result->result = std_body_compilation_result->result;
      for (const auto& [name, value] : std_scope->subjects) {
        root_scope->subjects[name] = value;
      }
    }

    const auto parser_result = mavka::parser::parse(code);
    if (parser_result->error) {
      compilation_result->error = new CompilationError();
      compilation_result->error->path = options->current_module_path;
      compilation_result->error->line = parser_result->error->line;
      compilation_result->error->column = parser_result->error->column;
      compilation_result->error->message = parser_result->error->message;
    } else {
      const auto scope = new CompilationScope();
      scope->parent = root_scope;

      const auto body_compilation_result = jejalyk::compile_body(
          parser_result->program_node->body, scope, options, state, false);
      if (body_compilation_result->error) {
        compilation_result->error = body_compilation_result->error;
      } else {
        std::string compiled_di;
        for (const auto& di : state->debug) {
          compiled_di += "var " + di.first + "=" + di.second + ";";
        }
        std::vector<std::string> compiled_modules;
        for (const auto& module : state->modules) {
          compiled_modules.push_back(module.second);
        }
        const auto compiled_modules_string =
            tools::implode(compiled_modules, "\n");
        compilation_result->result = wrap_run(
            compiled_di + "\n" + head_body_compilation_result->result,
            compilation_result->result,
            compiled_modules_string + "\n" + body_compilation_result->result);
            }
        }
        return compilation_result;
    }
}
#endif //JEJALYK_H
