#pragma once

#ifndef COMPILE_H
#define COMPILE_H

#include <map>
#include <string>
#include <vector>

#include "../ast.h"
#include "../parser.h"

namespace jejalyk {
  const std::string MAVKA_CALL = "мВикл";  // мВикл(значення, аргументи)
  const std::string MAVKA_GET = "мОтрм";  // мОтрм(значення, властивість)
  const std::string MAVKA_SET =
      "мВстн";  // мВстн(значення, властивість, значення)
  const std::string MAVKA_SET_ELEMENT =
      "мПклс";  // мПклс(значення, елемент, значення)
  const std::string MAVKA_GET_ELEMENT = "мОтре";  // мОтрм(значення, елемент)
  const std::string MAVKA_DIIA = "мДія";  // мДія(назва, параметри, функція)
  const std::string MAVKA_METHOD = "мМетд";  // мМетд(назва, параметри, функція)
  const std::string MAVKA_SET_METHOD = "мВМтд";  // мВМтд(структура, метод)
  const std::string MAVKA_PARAM = "мПарм";  // мПарм(назва, тип, значення)
  const std::string MAVKA_VPARAM = "мВпрм";  // мВпрм(назва, тип, значення)
  const std::string MAVKA_ADD = "мДодт";         // мДодт(а, б)
  const std::string MAVKA_SUB = "мВідн";         // мВідн(а, б)
  const std::string MAVKA_MUL = "мМнож";         // мМнож(а, б)
  const std::string MAVKA_DIV = "мДілт";         // мДілт(а, б)
  const std::string MAVKA_MOD = "мОстч";         // мОстч(а, б)
  const std::string MAVKA_DIV_DIV = "мОст2";     // мОст2(а, б)
  const std::string MAVKA_POW = "мСтпн";         // мСтпн(а, б)
  const std::string MAVKA_NOT = "мНі";           // мНі(а)
  const std::string MAVKA_BIT_AND = "мДвІ";      // мДвІ(а, б)
  const std::string MAVKA_BIT_OR = "мДАбо";      // мДАбо(а, б)
  const std::string MAVKA_BIT_XOR = "мДваб";     // мДваб(а, б)
  const std::string MAVKA_BIT_NOT = "мДні";      // мДні(а)
  const std::string MAVKA_BIT_LSHIFT = "мЗвлв";  // мЗвлв(а, б)
  const std::string MAVKA_BIT_RSHIFT = "мЗвпр";  // мЗвпр(а, б)
  const std::string MAVKA_AS = "мЯк";            // мЯк(а, б)
  const std::string MAVKA_EQ = "мРівн";          // мРівн(а, б)
  const std::string MAVKA_LT = "мМенш";          // мМенш(а, б)
  const std::string MAVKA_LE = "мМері";          // мМері(а, б)
  const std::string MAVKA_GT = "мБілш";          // мБілш(а, б)
  const std::string MAVKA_GE = "мБірі";          // мБірі(а, б)
  const std::string MAVKA_MODULE = "мМодл";  // мМодл(назва, функція)
  const std::string MAVKA_NEGATIVE = "мНегт";  // мНегт(значення)
  const std::string MAVKA_POSITIVE = "мПозт";  // мПозт(значення)
  const std::string MAVKA_POST_DECREMENT = "мПдек";  // мПдек(значення)
  const std::string MAVKA_POST_INCREMENT = "мПінк";  // мПінк(значення)
  const std::string MAVKA_PRE_DECREMENT = "мПрдк";  // мПрдк(значення)
  const std::string MAVKA_PRE_INCREMENT = "мПрік";  // мПрік(значення)
  const std::string MAVKA_GIVE = "мДати";  // мДати(модуль, назва, значення)
  const std::string MAVKA_STRUCTURE =
      "мСтрк";  // мСтрк(назва, параметри, предок)
  const std::string MAVKA_IS = "мЄ";          // мЄ(а, б)
  const std::string MAVKA_CONTAINS = "мМає";  // мМає(а, б)
  const std::string MAVKA_FROM_TO = "мЦВід";  // мЦВід(від, до, символ, функція)
  const std::string MAVKA_FROM_TO_FN = "мЦВідФ";  // мЦВідФ(оператор, крок)
  const std::string MAVKA_VALUES_ITERATOR = "мІтер";  // мІтер(значення)
  const std::string MAVKA_ENTRIES_ITERATOR = "мІтерП";  // мІтерП(значення)
  const std::string MAVKA_PARENT = "мСпрд";             // мСпрд(я)

  std::string varname(const std::string& name);

  class CompilationSubject;
  class CompilationObject;
  class CompilationError;
  class CompilationOptions;
  class NodeCompilationResult;
  class CompilationResult;

  class CompilationState {
   public:
    virtual ~CompilationState() = default;

    std::map<std::string, std::string> modules;
    std::map<std::string, std::string> debug;
    bool store_debug = false;

    virtual bool has_module(const std::string& name);

    virtual std::string get_module(const std::string& name);

    virtual void set_module(const std::string& name, std::string code);

    virtual std::string put_debug(const std::string& path,
                                  const size_t& line,
                                  const size_t& column);
  };

  class CompilationScope {
   public:
    virtual ~CompilationScope() = default;

    CompilationScope* parent = nullptr;
    std::map<std::string, CompilationSubject*> subjects;

    virtual CompilationError* define(const std::string& name,
                                     CompilationSubject* subject);

    virtual CompilationError* assign(const std::string& name,
                                     CompilationSubject* subject);

    virtual CompilationSubject* get_local(const std::string& name) const;

    virtual bool has_local(const std::string& name) const;

    virtual CompilationSubject* get(const std::string& name) const;

    virtual bool has(const std::string& name) const;

    virtual CompilationScope* root();
  };

  class CompilationMicroScope final : public CompilationScope {
   public:
    virtual CompilationError* assign(const std::string& name,
                                     CompilationSubject* subject) override;

    virtual CompilationSubject* get_local(
        const std::string& name) const override;

    virtual bool has_local(const std::string& name) const override;

    virtual CompilationSubject* get(const std::string& name) const override;

    virtual bool has(const std::string& name) const override;

    virtual CompilationScope* root() override;
  };

  class CompilationObjectDiiaParam {
   public:
    int index;
    std::string name;
    CompilationSubject* subject;
    CompilationSubject* value;
    bool spread;
  };

  class CompilationObjectStructureParam {
   public:
    int index;
    std::string name;
    CompilationSubject* subject;
    CompilationSubject* value;
  };

  inline std::vector<CompilationObjectDiiaParam*>
  compilation_object_structure_params_to_diia_params(
      std::vector<CompilationObjectStructureParam*> params) {
    std::vector<CompilationObjectDiiaParam*> diia_params;
    for (const auto& param : params) {
      const auto diia_param = new CompilationObjectDiiaParam();
      diia_param->index = param->index;
      diia_param->name = param->name;
      diia_param->subject = param->subject;
      diia_param->value = param->value;
      diia_param->spread = false;
      diia_params.push_back(diia_param);
    }
    return diia_params;
  }

  class CompilationObject {
   public:
    virtual ~CompilationObject() = default;

    static const int OBJECT = 0;
    static const int DIIA = 1;
    static const int STRUCTURE = 2;

    int type;  // 0 - object, 1 - diia, 2 - structure
    CompilationObject* structure;
    std::map<std::string, CompilationSubject*> properties;

    std::vector<CompilationObjectDiiaParam*> diia_params;
    CompilationSubject* diia_return_type;

    std::vector<CompilationObjectStructureParam*> structure_params;
    CompilationObject* structure_parent;

    NodeCompilationResult* get(std::string name,
                               CompilationScope* scope,
                               CompilationOptions* options);

    NodeCompilationResult* set(std::string name,
                               CompilationSubject* value,
                               CompilationScope* scope,
                               CompilationOptions* options);

    NodeCompilationResult* call(std::vector<CompilationSubject*> args,
                                CompilationScope* scope,
                                CompilationOptions* options);

    NodeCompilationResult* call_named(
        std::map<std::string, CompilationSubject*> args,
        CompilationScope* scope,
        CompilationOptions* options);

    bool is(CompilationObject* object);
    bool is_subject(CompilationSubject* subject);

    CompilationObject* create_instance();

    inline bool is_structure() { return type == CompilationObject::STRUCTURE; }
    inline bool is_diia() { return type == CompilationObject::DIIA; }
    inline bool is_object() { return type == CompilationObject::OBJECT; }
  };

  class CompilationSubject {
   public:
    virtual ~CompilationSubject() = default;

    std::vector<CompilationObject*> types;

    bool can_set(CompilationSubject* subject);

    NodeCompilationResult* get(std::string name,
                               CompilationScope* scope,
                               CompilationOptions* options);

    NodeCompilationResult* set(std::string name,
                               CompilationSubject* value,
                               CompilationScope* scope,
                               CompilationOptions* options);

    NodeCompilationResult* call(std::vector<CompilationSubject*> args,
                                CompilationScope* scope,
                                CompilationOptions* options);

    NodeCompilationResult* call_named(
        std::map<std::string, CompilationSubject*> args,
        CompilationScope* scope,
        CompilationOptions* options);

    virtual bool is_subject(CompilationSubject* subject);
  };

  class NodeCompilationResult {
   public:
    CompilationError* error = nullptr;
    std::string result;
    CompilationSubject* subject;
  };

  class CompilationResult : public NodeCompilationResult {};

  class StructureParamsCompilationResult : public NodeCompilationResult {
   public:
    std::vector<CompilationObjectStructureParam*> structure_params;
  };

  class GetModuleResult {
   public:
    std::string error;
    std::string result;
    bool builtin = false;
  };

  class CompilationOptions {
   public:
    CompilationOptions* parent = nullptr;
    std::string root_module_path;
    std::string current_module_path;
    std::string std_code;
    std::string args;
    int body_depth = 0;
    bool allow_js = false;

    GetModuleResult* (*get_module_name)(bool,
                                        std::string,
                                        CompilationOptions*) = nullptr;

    GetModuleResult* (*get_module_path)(bool,
                                        std::string,
                                        CompilationOptions*) = nullptr;

    GetModuleResult* (*get_module_code)(bool,
                                        std::string,
                                        CompilationOptions*) = nullptr;

    GetModuleResult* (*get_remote_module_name)(std::string,
                                               CompilationOptions*) = nullptr;

    GetModuleResult* (*get_remote_module_path)(std::string,
                                               CompilationOptions*) = nullptr;

    GetModuleResult* (*get_remote_module_code)(std::string,
                                               CompilationOptions*) = nullptr;

    CompilationOptions* clone();
  };

  class CompilationError {
   public:
    std::string path;
    size_t line{};
    size_t column{};
    std::string message;
  };

  inline CompilationError* compilation_error_from_ast_node(
      const mavka::ast::ASTNode* node,
      const std::string& path,
      const std::string& message) {
    const auto compilation_error = new CompilationError();
    compilation_error->path = path;
    compilation_error->line = node->start_line;
    compilation_error->column = node->start_column;
    compilation_error->message = message;
    return compilation_error;
  }

  inline CompilationError* compilation_error_from_message(
      const std::string& message) {
    const auto compilation_error = new CompilationError();
    compilation_error->message = message;
    return compilation_error;
  }

  inline CompilationSubject* create_number_instance_subject(
      CompilationScope* scope) {
    const auto number_structure = scope->root()->get("число");
    const auto subject = new CompilationSubject();
    const auto instance = number_structure->types[0]->create_instance();
    subject->types.push_back(instance);
    return subject;
  }

  inline CompilationSubject* create_text_instance_subject(
      CompilationScope* scope) {
    const auto text_structure = scope->root()->get("текст");
    const auto subject = new CompilationSubject();
    const auto instance = text_structure->types[0]->create_instance();
    subject->types.push_back(instance);
    return subject;
  }

  inline CompilationSubject* create_list_instance_subject(CompilationScope* scope) {
    const auto list_structure = scope->root()->get("список");
    const auto subject = new CompilationSubject();
    const auto instance = list_structure->types[0]->create_instance();
    subject->types.push_back(instance);
    return subject;
  }

  inline CompilationSubject* create_dictionary_instance_subject(CompilationScope* scope) {
    const auto dictionary_structure = scope->root()->get("список");
    const auto subject = new CompilationSubject();
    const auto instance = dictionary_structure->types[0]->create_instance();
    subject->types.push_back(instance);
    return subject;
  }
}

#endif //COMPILE_H
