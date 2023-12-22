#pragma once

#ifndef PARSER_H
#define PARSER_H

#include "MavkaLexer.h"
#include "MavkaParser.h"
#include "MavkaParserBaseVisitor.h"
#include "antlr4-runtime.h"
#include "ast.h"
#include "tools.h"

namespace mavka::parser {
  class ASTResult {
   public:
    ast::ASTNode* node;
  };

  inline ASTResult* any_to_ast_result(std::any any) {
    return std::any_cast<ASTResult*>(any);
  }

  inline ASTResult* create_ast_result(ast::ASTNode* node) {
    const auto ast_result = new ASTResult();
    ast_result->node = node;
    return ast_result;
  }

  inline std::string process_number(std::string number) {
    auto number_copy = std::string(number);
    if (number_copy.find("ш") != std::string::npos) {
      jejalyk::tools::replace_all(number_copy, "ш", "x");
      jejalyk::tools::replace_all(number_copy, "Ш", "X");
      jejalyk::tools::replace_all(number_copy, "а", "а");
      jejalyk::tools::replace_all(number_copy, "А", "A");
      jejalyk::tools::replace_all(number_copy, "б", "b");
      jejalyk::tools::replace_all(number_copy, "Б", "B");
      jejalyk::tools::replace_all(number_copy, "в", "c");
      jejalyk::tools::replace_all(number_copy, "В", "C");
      jejalyk::tools::replace_all(number_copy, "г", "d");
      jejalyk::tools::replace_all(number_copy, "Г", "D");
      jejalyk::tools::replace_all(number_copy, "ґ", "e");
      jejalyk::tools::replace_all(number_copy, "Ґ", "E");
      jejalyk::tools::replace_all(number_copy, "д", "f");
      jejalyk::tools::replace_all(number_copy, "Д", "F");
    } else {
      jejalyk::tools::replace_all(number_copy, "д", "b");
    }
    return number_copy;
  }

  inline std::vector<ast::ASTNode*> processASTBody(
      const std::vector<ast::ASTNode*>& body) {
    std::vector<ast::ASTNode*> result;
    for (auto& item : body) {
      if (jejalyk::tools::instance_of<ast::IdentifierNode>(item)) {
        const auto identifier_node = dynamic_cast<ast::IdentifierNode*>(item);
        if (identifier_node->name == "break") {
          result.push_back(new ast::BreakNode());
          continue;
        }
        if (identifier_node->name == "continue") {
          result.push_back(new ast::ContinueNode());
          continue;
        }
      }

      if (item) {
        result.push_back(item);
      }
    }
    return result;
  }

  class MavkaASTVisitor final : public MavkaParserBaseVisitor {
   public:
    std::any visitFile(MavkaParser::FileContext* ctx) override {
      return visitProgram(ctx->f_program);
    }

    std::any visitProgram(MavkaParser::ProgramContext* context) override {
      std::vector<ast::ASTNode*> body;
      for (const auto program_element : context->program_element()) {
        const auto ast_result =
            any_to_ast_result(visitProgram_element(program_element));
        body.push_back(ast_result->node);
      }
      body = processASTBody(body);
      const auto program_node = new ast::ProgramNode();
      program_node->start_line = context->getStart()->getLine();
      program_node->start_column = context->getStart()->getCharPositionInLine();
      program_node->end_line = context->getStop()->getLine();
      program_node->end_column = context->getStop()->getCharPositionInLine();
      program_node->body = body;
      return create_ast_result(program_node);
    }

    std::any visitProgram_element(
        MavkaParser::Program_elementContext* context) override {
      if (context->module()) {
        return visitModule(context->module());
      }
      if (context->structure()) {
        return visitStructure(context->structure());
      }
      if (context->mockup()) {
        return visitMockup(context->mockup());
      }
      if (context->diia()) {
        return visitDiia(context->diia());
      }
      if (context->if_()) {
        return visitIf(context->if_());
      }
      if (context->each()) {
        return visitEach(context->each());
      }
      if (context->while_()) {
        return visitWhile(context->while_());
      }
      if (context->try_()) {
        return visitTry(context->try_());
      }
      if (context->expr()) {
        return visitExpr(context->expr());
      }
      if (context->take()) {
        return visitTake(context->take());
      }
      if (context->throw_()) {
        return visitThrow(context->throw_());
      }
      if (context->eval()) {
        return visitEval(context->eval());
      }
      if (context->wait_assign()) {
        return visitWait_assign(context->wait_assign());
      }
      if (context->assign()) {
        return visitAssign(context->assign());
      }
      if (context->give()) {
        return visitGive(context->give());
      }
      return create_ast_result(nullptr);
    }

    std::any visitModule(MavkaParser::ModuleContext* context) override {
      const auto module_node = new ast::ModuleNode();
      module_node->start_line = context->getStart()->getLine();
      module_node->start_column = context->getStart()->getCharPositionInLine();
      module_node->end_line = context->getStop()->getLine();
      module_node->end_column = context->getStop()->getCharPositionInLine();
      module_node->name = context->m_name->getText();
      if (context->module_body()) {
        std::any module_body = visitModule_body(context->module_body());
        module_node->body =
            std::any_cast<std::vector<ast::ASTNode*>>(module_body);
      }
      return create_ast_result(module_node);
    }

    std::any visitModule_body(
        MavkaParser::Module_bodyContext* context) override {
      std::vector<ast::ASTNode*> body;
      for (const auto module_element : context->module_body_element()) {
        const auto ast_result =
            any_to_ast_result(visitModule_body_element(module_element));
        body.push_back(ast_result->node);
      }
      body = processASTBody(body);
      return body;
    }

    std::any visitModule_body_element(
        MavkaParser::Module_body_elementContext* context) override {
      if (context->module()) {
        return visitModule(context->module());
      }
      if (context->structure()) {
        return visitStructure(context->structure());
      }
      if (context->mockup()) {
        return visitMockup(context->mockup());
      }
      if (context->diia()) {
        return visitDiia(context->diia());
      }
      if (context->if_()) {
        return visitIf(context->if_());
      }
      if (context->each()) {
        return visitEach(context->each());
      }
      if (context->while_()) {
        return visitWhile(context->while_());
      }
      if (context->try_()) {
        return visitTry(context->try_());
      }
      if (context->expr()) {
        return visitExpr(context->expr());
      }
      if (context->throw_()) {
        return visitThrow(context->throw_());
      }
      if (context->eval()) {
        return visitEval(context->eval());
      }
      if (context->wait_assign()) {
        return visitWait_assign(context->wait_assign());
      }
      if (context->assign()) {
        return visitAssign(context->assign());
      }
      if (context->give()) {
        return visitGive(context->give());
      }
      return create_ast_result(nullptr);
    }

    std::any visitStructure(MavkaParser::StructureContext* context) override {
      const std::string name = context->s_name->getText();
      std::vector<ast::GenericNode*> generics;
      if (context->s_generics) {
        generics = std::any_cast<std::vector<ast::GenericNode*>>(
            visitGenerics(context->s_generics));
      }
      std::vector<ast::ASTNode*> params;
      if (context->structure_elements()) {
        params = std::any_cast<std::vector<ast::ASTNode*>>(
            visitStructure_elements(context->structure_elements()));
      }
      const auto structure_node = new ast::StructureNode();
      structure_node->start_line = context->getStart()->getLine();
      structure_node->start_column =
          context->getStart()->getCharPositionInLine();
      structure_node->end_line = context->getStop()->getLine();
      structure_node->end_column = context->getStop()->getCharPositionInLine();
      structure_node->name = name;
      structure_node->generics = generics;
      if (context->s_parent) {
        const auto parent =
            any_to_ast_result(visitSuper_identifiers_chain(context->s_parent))
                ->node;
        structure_node->parent = parent;
      }
      structure_node->params = std::vector<ast::ASTNode*>();
      for (const auto& param : params) {
        structure_node->params.push_back(param);
      }
      return create_ast_result(structure_node);
    }

    std::any visitStructure_elements(
        MavkaParser::Structure_elementsContext* context) override {
      std::vector<ast::ASTNode*> elements;
      for (const auto structure_element : context->structure_element()) {
        const auto ast_result =
            any_to_ast_result(visitStructure_element(structure_element));
        elements.push_back(ast_result->node);
      }
      return elements;
    }

    std::any visitStructure_element(
        MavkaParser::Structure_elementContext* context) override {
      if (context->structure_param()) {
        return visitStructure_param(context->structure_param());
      }
      return create_ast_result(nullptr);
    }

    std::any visitStructure_param(
        MavkaParser::Structure_paramContext* context) override {
      const std::string name = context->sp_name->getText();
      std::vector<ast::ASTNode*> types;
      if (context->sp_type) {
        types = std::any_cast<std::vector<ast::ASTNode*>>(
            visitType_value(context->sp_type));
      }
      ast::ASTNode* value = nullptr;
      if (context->sp_value) {
        value = any_to_ast_result(visitParam_value(context->sp_value))->node;
      }
      const auto structure_param_node = new ast::ParamNode();
      structure_param_node->start_line = context->getStart()->getLine();
      structure_param_node->start_column =
          context->getStart()->getCharPositionInLine();
      structure_param_node->end_line = context->getStop()->getLine();
      structure_param_node->end_column =
          context->getStop()->getCharPositionInLine();
      structure_param_node->ee = context->sp_static != nullptr;
      structure_param_node->name = name;
      structure_param_node->types = types;
      structure_param_node->value = value;
      return create_ast_result(structure_param_node);
    }

    std::any visitGenerics(MavkaParser::GenericsContext* context) override {
      std::vector<ast::GenericNode*> generics;
      for (const auto identifier_node : context->identifier()) {
        const auto identifier_result =
            any_to_ast_result(visitIdentifier(identifier_node));
        const auto identifier =
            dynamic_cast<ast::IdentifierNode*>(identifier_result->node);
        const auto generic = new ast::GenericNode();
        generic->start_line = identifier->start_line;
        generic->start_column = identifier->start_column;
        generic->end_line = identifier->end_line;
        generic->end_column = identifier->end_column;
        generic->name = identifier->name;
        generics.push_back(generic);
      }
      return generics;
    }

    std::any visitMethod_declaration(
        MavkaParser::Method_declarationContext* context) override {
      const auto method_declaration_node = new ast::MethodDeclarationNode();
      method_declaration_node->start_line = context->getStart()->getLine();
      method_declaration_node->start_column =
          context->getStart()->getCharPositionInLine();
      method_declaration_node->end_line = context->getStop()->getLine();
      method_declaration_node->end_column =
          context->getStop()->getCharPositionInLine();
      method_declaration_node->ee = context->md_static != nullptr;
      method_declaration_node->async = context->md_async != nullptr;
      method_declaration_node->name = context->md_name->getText();
      if (context->md_generics) {
        method_declaration_node->generics =
            std::any_cast<std::vector<ast::GenericNode*>>(
                visitGenerics(context->md_generics));
      }
      if (context->md_params) {
        method_declaration_node->params =
            std::any_cast<std::vector<ast::ParamNode*>>(
                visitParams(context->md_params));
      }
      if (context->md_type) {
        method_declaration_node->return_types =
            std::any_cast<std::vector<ast::ASTNode*>>(
                visitType_value(context->md_type));
      }
      return create_ast_result(method_declaration_node);
    }

    std::any visitMockup(MavkaParser::MockupContext* context) override {
      if (context->mockup_module()) {
        return visitMockup_module(context->mockup_module());
      }
      if (context->mockup_structure()) {
        return visitMockup_structure(context->mockup_structure());
      }
      if (context->mockup_diia()) {
        return visitMockup_diia(context->mockup_diia());
      }
      if (context->mockup_subject()) {
        return visitMockup_subject(context->mockup_subject());
      }
      if (context->mockup_object()) {
        return visitMockup_object(context->mockup_object());
      }
      return create_ast_result(nullptr);
    }

    std::any visitMockup_module(
        MavkaParser::Mockup_moduleContext* context) override {
      const auto mockup_module_node = new ast::MockupModuleNode();
      mockup_module_node->start_line = context->getStart()->getLine();
      mockup_module_node->start_column =
          context->getStart()->getCharPositionInLine();
      mockup_module_node->end_line = context->getStop()->getLine();
      mockup_module_node->end_column =
          context->getStop()->getCharPositionInLine();
      mockup_module_node->name = context->mm_name->getText();
      if (context->mm_elements) {
        mockup_module_node->elements =
            std::any_cast<std::vector<ast::ASTNode*>>(
                visitMockup_body(context->mm_elements));
      }
      return create_ast_result(mockup_module_node);
    }

    std::any visitMockup_structure(
        MavkaParser::Mockup_structureContext* context) override {
      const auto mockup_structure_node = new ast::MockupStructureNode();
      mockup_structure_node->start_line = context->getStart()->getLine();
      mockup_structure_node->start_column =
          context->getStart()->getCharPositionInLine();
      mockup_structure_node->end_line = context->getStop()->getLine();
      mockup_structure_node->end_column =
          context->getStop()->getCharPositionInLine();
      mockup_structure_node->name = context->ms_name->getText();
      if (context->ms_generics) {
        mockup_structure_node->generics =
            std::any_cast<std::vector<ast::GenericNode*>>(
                visitGenerics(context->ms_generics));
      }
      if (context->ms_elements) {
        mockup_structure_node->params =
            std::any_cast<std::vector<ast::ASTNode*>>(
                visitMockup_body(context->ms_elements));
      }
      return create_ast_result(mockup_structure_node);
    }

    std::any visitMockup_body(
        MavkaParser::Mockup_bodyContext* context) override {
      std::vector<ast::ASTNode*> elements;
      for (const auto mockup_element : context->mockup_body_element()) {
        const auto ast_result =
            any_to_ast_result(visitMockup_body_element(mockup_element));
        elements.push_back(ast_result->node);
      }
      return elements;
    }

    std::any visitMockup_body_element(
        MavkaParser::Mockup_body_elementContext* context) override {
      if (context->structure_param()) {
        return visitStructure_param(context->structure_param());
      }
      if (context->method_declaration()) {
        return visitMethod_declaration(context->method_declaration());
      }
      return create_ast_result(nullptr);
    }

    std::any visitMockup_diia(
        MavkaParser::Mockup_diiaContext* context) override {
      const auto mockup_diia_node = new ast::MockupDiiaNode();
      mockup_diia_node->start_line = context->getStart()->getLine();
      mockup_diia_node->start_column =
          context->getStart()->getCharPositionInLine();
      mockup_diia_node->end_line = context->getStop()->getLine();
      mockup_diia_node->end_column =
          context->getStop()->getCharPositionInLine();
      mockup_diia_node->ee = context->md_static != nullptr;
      mockup_diia_node->async = context->md_async != nullptr;
      mockup_diia_node->name = context->md_name->getText();
      if (context->md_generics) {
        mockup_diia_node->generics =
            std::any_cast<std::vector<ast::GenericNode*>>(
                visitGenerics(context->md_generics));
      }
      if (context->md_params) {
        mockup_diia_node->params = std::any_cast<std::vector<ast::ParamNode*>>(
            visitParams(context->md_params));
      }
      if (context->md_type) {
        mockup_diia_node->return_types =
            std::any_cast<std::vector<ast::ASTNode*>>(
                visitType_value(context->md_type));
      }
      return create_ast_result(mockup_diia_node);
    }

    std::any visitMockup_subject(
        MavkaParser::Mockup_subjectContext* context) override {
      const auto mockup_subject_node = new ast::MockupSubjectNode();
      mockup_subject_node->start_line = context->getStart()->getLine();
      mockup_subject_node->start_column =
          context->getStart()->getCharPositionInLine();
      mockup_subject_node->end_line = context->getStop()->getLine();
      mockup_subject_node->end_column =
          context->getStop()->getCharPositionInLine();
      mockup_subject_node->name = context->ms_name->getText();
      mockup_subject_node->types = std::any_cast<std::vector<ast::ASTNode*>>(
          visitType_value(context->ms_type));
      return create_ast_result(mockup_subject_node);
    }

    std::any visitMockup_object(
        MavkaParser::Mockup_objectContext* context) override {
      const auto mockup_object_node = new ast::MockupObjectNode();
      mockup_object_node->start_line = context->getStart()->getLine();
      mockup_object_node->start_column =
          context->getStart()->getCharPositionInLine();
      mockup_object_node->end_line = context->getStop()->getLine();
      mockup_object_node->end_column =
          context->getStop()->getCharPositionInLine();
      mockup_object_node->name = context->mo_name->getText();
      if (context->mo_elements) {
        mockup_object_node->elements =
            std::any_cast<std::vector<ast::ASTNode*>>(
                visitMockup_body(context->mo_elements));
      }
      return create_ast_result(mockup_object_node);
    }

    std::any visitDiia(MavkaParser::DiiaContext* context) override {
      const auto diia_node = new ast::DiiaNode();
      diia_node->start_line = context->getStart()->getLine();
      diia_node->start_column = context->getStart()->getCharPositionInLine();
      diia_node->end_line = context->getStop()->getLine();
      diia_node->end_column = context->getStop()->getCharPositionInLine();
      diia_node->ee = context->d_static != nullptr;
      diia_node->async = context->d_async != nullptr;
      diia_node->structure =
          context->d_structure ? context->d_structure->getText() : "";
      diia_node->name = context->d_name->getText();
      if (context->d_generics) {
        diia_node->generics = std::any_cast<std::vector<ast::GenericNode*>>(
            visitGenerics(context->d_generics));
      }
      if (context->d_params) {
        diia_node->params = std::any_cast<std::vector<ast::ParamNode*>>(
            visitParams(context->d_params));
      }
      if (context->d_type) {
        diia_node->return_types = std::any_cast<std::vector<ast::ASTNode*>>(
            visitType_value(context->d_type));
      }
      if (context->d_body) {
        diia_node->body = std::any_cast<std::vector<ast::ASTNode*>>(
            visitBody(context->d_body));
      }
      return create_ast_result(diia_node);
    }

    std::any visitIf(MavkaParser::IfContext* context) override {
      const auto if_node = new ast::IfNode();
      if_node->start_line = context->getStart()->getLine();
      if_node->start_column = context->getStart()->getCharPositionInLine();
      if_node->end_line = context->getStop()->getLine();
      if_node->end_column = context->getStop()->getCharPositionInLine();
      if_node->condition = any_to_ast_result(visitExpr(context->i_value))->node;
      if (context->i_body) {
        if_node->body = std::any_cast<std::vector<ast::ASTNode*>>(
            visitBody(context->i_body));
      }
      if (context->i_else_body) {
        if_node->else_body = std::any_cast<std::vector<ast::ASTNode*>>(
            visitBody(context->i_else_body));
      }
      return create_ast_result(if_node);
    }

    std::any visitEach(MavkaParser::EachContext* context) override {
      const auto each_node = new ast::EachNode();
      each_node->start_line = context->getStart()->getLine();
      each_node->start_column = context->getStart()->getCharPositionInLine();
      each_node->end_line = context->getStop()->getLine();
      each_node->end_column = context->getStop()->getCharPositionInLine();
      if (context->e_iterator) {
        each_node->value =
            any_to_ast_result(visitExpr(context->e_iterator))->node;
      }
      if (context->e_fromto) {
        each_node->value =
            any_to_ast_result(visitFromto(context->e_fromto))->node;
      }
      each_node->keyName =
          context->e_key_name ? context->e_key_name->getText() : "";
      each_node->name = context->e_name->getText();
      if (context->e_body) {
        each_node->body = std::any_cast<std::vector<ast::ASTNode*>>(
            visitBody(context->e_body));
      }
      return create_ast_result(each_node);
    }

    std::any visitFromto(MavkaParser::FromtoContext* context) override {
      if (context->fromto_simple()) {
        return visitFromto_simple(context->fromto_simple());
      }
      if (context->fromto_complex()) {
        return visitFromto_complex(context->fromto_complex());
      }
      return create_ast_result(nullptr);
    }

    std::any visitFromto_simple(
        MavkaParser::Fromto_simpleContext* context) override {
      const auto fromto_simple_node = new ast::FromToSimpleNode();
      fromto_simple_node->start_line = context->getStart()->getLine();
      fromto_simple_node->start_column =
          context->getStart()->getCharPositionInLine();
      fromto_simple_node->end_line = context->getStop()->getLine();
      fromto_simple_node->end_column =
          context->getStop()->getCharPositionInLine();
      fromto_simple_node->from =
          any_to_ast_result(visitFromto_value(context->fs_from))->node;
      fromto_simple_node->to =
          any_to_ast_result(visitFromto_value(context->fs_to))->node;
      fromto_simple_node->toSymbol =
          context->fs_to_symbol ? context->fs_to_symbol->getText() : "<=";
      return create_ast_result(fromto_simple_node);
    }

    std::any visitFromto_complex(
        MavkaParser::Fromto_complexContext* context) override {
      const auto fromto_complex_node = new ast::FromToComplexNode();
      fromto_complex_node->start_line = context->getStart()->getLine();
      fromto_complex_node->start_column =
          context->getStart()->getCharPositionInLine();
      fromto_complex_node->end_line = context->getStop()->getLine();
      fromto_complex_node->end_column =
          context->getStop()->getCharPositionInLine();
      fromto_complex_node->from =
          any_to_ast_result(visitFromto_value(context->fc_from))->node;
      fromto_complex_node->to =
          any_to_ast_result(visitFromto_value(context->fc_to))->node;
      fromto_complex_node->toSymbol =
          context->fc_to_symbol ? context->fc_to_symbol->getText() : "<=";
      fromto_complex_node->step =
          any_to_ast_result(visitFromto_value(context->fc_middle))->node;
      fromto_complex_node->stepSymbol =
          context->fc_middle_symbol ? context->fc_middle_symbol->getText()
                                    : "+";
      return create_ast_result(fromto_complex_node);
    }

    std::any visitFromto_value(MavkaParser::Fromto_valueContext* context) {
      if (jejalyk::tools::instance_of<MavkaParser::Fromto_numberContext>(
              context)) {
        const auto number_node = new ast::NumberNode();
        number_node->start_line = context->getStart()->getLine();
        number_node->start_column =
            context->getStart()->getCharPositionInLine();
        number_node->end_line = context->getStop()->getLine();
        number_node->end_column = context->getStop()->getCharPositionInLine();
        number_node->value = process_number(
            dynamic_cast<MavkaParser::Fromto_numberContext*>(context)
                ->NUMBER()
                ->getText());
        return create_ast_result(number_node);
      }
      if (jejalyk::tools::instance_of<MavkaParser::Fromto_stringContext>(
              context)) {
        const auto string_node = new ast::StringNode();
        string_node->start_line = context->getStart()->getLine();
        string_node->start_column =
            context->getStart()->getCharPositionInLine();
        string_node->end_line = context->getStop()->getLine();
        string_node->end_column = context->getStop()->getCharPositionInLine();
        string_node->value =
            dynamic_cast<MavkaParser::Fromto_stringContext*>(context)
                ->STRING()
                ->getText();
        if (string_node->value.starts_with(R"(""")")) {
          string_node->value =
              string_node->value.substr(3, string_node->value.length() - 6);
        } else {
          string_node->value =
              string_node->value.substr(1, string_node->value.length() - 2);
        }
        return create_ast_result(string_node);
      }
      if (jejalyk::tools::instance_of<MavkaParser::Fromto_idContext>(context)) {
        return visitIdentifier(
            dynamic_cast<MavkaParser::Fromto_idContext*>(context)
                ->identifier());
      }
      if (jejalyk::tools::instance_of<MavkaParser::Fromto_nestedContext>(
              context)) {
        return visitValue(
            dynamic_cast<MavkaParser::Fromto_nestedContext*>(context)
                ->fn_value);
      }
      return create_ast_result(nullptr);
    }

    std::any visitWhile(MavkaParser::WhileContext* context) override {
      const auto while_node = new ast::WhileNode();
      while_node->start_line = context->getStart()->getLine();
      while_node->start_column = context->getStart()->getCharPositionInLine();
      while_node->end_line = context->getStop()->getLine();
      while_node->end_column = context->getStop()->getCharPositionInLine();
      while_node->condition =
          any_to_ast_result(visitExpr(context->w_value))->node;
      if (context->w_body) {
        while_node->body = std::any_cast<std::vector<ast::ASTNode*>>(
            visitBody(context->w_body));
      }
      return create_ast_result(while_node);
    }

    std::any visitTry(MavkaParser::TryContext* context) override {
      const auto try_node = new ast::TryNode();
      try_node->start_line = context->getStart()->getLine();
      try_node->start_column = context->getStart()->getCharPositionInLine();
      try_node->end_line = context->getStop()->getLine();
      try_node->end_column = context->getStop()->getCharPositionInLine();
      try_node->body =
          std::any_cast<std::vector<ast::ASTNode*>>(visitBody(context->t_body));
      try_node->name = context->tc_name->getText();
      try_node->catch_body = std::any_cast<std::vector<ast::ASTNode*>>(
          visitBody(context->tc_body));
      return create_ast_result(try_node);
    }

    std::any visitExpr(MavkaParser::ExprContext* context) {
      if (jejalyk::tools::instance_of<MavkaParser::Call_parentContext>(
              context)) {
        const auto call_parent_context =
            dynamic_cast<MavkaParser::Call_parentContext*>(context);
        const auto call_node = new ast::CallNode();
        call_node->start_line = context->getStart()->getLine();
        call_node->start_column = context->getStart()->getCharPositionInLine();
        call_node->end_line = context->getStop()->getLine();
        call_node->end_column = context->getStop()->getCharPositionInLine();
        const auto chain_node = new ast::ChainNode();
        chain_node->start_line = context->getStart()->getLine();
        chain_node->start_column = context->getStart()->getCharPositionInLine();
        chain_node->end_line = context->getStop()->getLine();
        chain_node->end_column = context->getStop()->getCharPositionInLine();
        const auto identifier_node = new ast::IdentifierNode();
        identifier_node->start_line = context->getStart()->getLine();
        identifier_node->start_column =
            context->getStart()->getCharPositionInLine();
        identifier_node->end_line = context->getStop()->getLine();
        identifier_node->end_column =
            context->getStop()->getCharPositionInLine();
        identifier_node->name = "предок";
        chain_node->left = identifier_node;
        chain_node->right =
            any_to_ast_result(visitIdentifier(call_parent_context->cp_id))
                ->node;
        call_node->value = chain_node;
        if (call_parent_context->cp_args) {
          call_node->args = std::any_cast<std::vector<ast::ArgNode*>>(
              visitArgs(call_parent_context->cp_args));
        }
        if (call_parent_context->cp_named_args) {
          call_node->args = std::any_cast<std::vector<ast::ArgNode*>>(
              visitNamed_args(call_parent_context->cp_named_args));
        }
        return create_ast_result(call_node);
      }
      if (jejalyk::tools::instance_of<MavkaParser::SimpleContext>(context)) {
        const auto simple_context =
            dynamic_cast<MavkaParser::SimpleContext*>(context);
        return visitValue(simple_context->value());
      }
      if (jejalyk::tools::instance_of<MavkaParser::WaitContext>(context)) {
        const auto wait_context =
            dynamic_cast<MavkaParser::WaitContext*>(context);
        return visitWait(wait_context);
      }
      if (jejalyk::tools::instance_of<MavkaParser::FunctionContext>(context)) {
        const auto function_context =
            dynamic_cast<MavkaParser::FunctionContext*>(context);
        return visitFunction(function_context);
      }
      if (jejalyk::tools::instance_of<MavkaParser::Anonymous_diiaContext>(
              context)) {
        const auto anonymous_diia_context =
            dynamic_cast<MavkaParser::Anonymous_diiaContext*>(context);
        return visitAnonymous_diia(anonymous_diia_context);
      }
      return create_ast_result(nullptr);
    }

    std::any visitValue(MavkaParser::ValueContext* context) {
      if (jejalyk::tools::instance_of<MavkaParser::NumberContext>(context)) {
        return visitNumber(dynamic_cast<MavkaParser::NumberContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::String_valueContext>(
              context)) {
        return visitString_value(
            dynamic_cast<MavkaParser::String_valueContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::IdContext>(context)) {
        return visitId(dynamic_cast<MavkaParser::IdContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::ChainContext>(context)) {
        return visitChain(dynamic_cast<MavkaParser::ChainContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::CallContext>(context)) {
        return visitCall(dynamic_cast<MavkaParser::CallContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Get_elementContext>(
              context)) {
        return visitGet_element(
            dynamic_cast<MavkaParser::Get_elementContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::PositiveContext>(context)) {
        return visitPositive(
            dynamic_cast<MavkaParser::PositiveContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::NegativeContext>(context)) {
        return visitNegative(
            dynamic_cast<MavkaParser::NegativeContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Pre_decrementContext>(
              context)) {
        return visitPre_decrement(
            dynamic_cast<MavkaParser::Pre_decrementContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Pre_incrementContext>(
              context)) {
        return visitPre_increment(
            dynamic_cast<MavkaParser::Pre_incrementContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Post_decrementContext>(
              context)) {
        return visitPost_decrement(
            dynamic_cast<MavkaParser::Post_decrementContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Post_incrementContext>(
              context)) {
        return visitPost_increment(
            dynamic_cast<MavkaParser::Post_incrementContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::NotContext>(context)) {
        return visitNot(dynamic_cast<MavkaParser::NotContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Bitwise_notContext>(
              context)) {
        return visitBitwise_not(
            dynamic_cast<MavkaParser::Bitwise_notContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::NestedContext>(context)) {
        return visitNested(dynamic_cast<MavkaParser::NestedContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Call_exprContext>(context)) {
        return visitCall_expr(
            dynamic_cast<MavkaParser::Call_exprContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::AsContext>(context)) {
        return visitAs(dynamic_cast<MavkaParser::AsContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Arithmetic_mulContext>(
              context)) {
        return visitArithmetic_mul(
            dynamic_cast<MavkaParser::Arithmetic_mulContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Arithmetic_addContext>(
              context)) {
        return visitArithmetic_add(
            dynamic_cast<MavkaParser::Arithmetic_addContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::BitwiseContext>(context)) {
        return visitBitwise(
            dynamic_cast<MavkaParser::BitwiseContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::ComparisonContext>(
              context)) {
        return visitComparison(
            dynamic_cast<MavkaParser::ComparisonContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::TestContext>(context)) {
        return visitTest(dynamic_cast<MavkaParser::TestContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::TernaryContext>(context)) {
        return visitTernary(
            dynamic_cast<MavkaParser::TernaryContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::ArrayContext>(context)) {
        return visitArray(dynamic_cast<MavkaParser::ArrayContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::DictionaryContext>(
              context)) {
        return visitDictionary(
            dynamic_cast<MavkaParser::DictionaryContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::GodContext>(context)) {
        return visitGod(dynamic_cast<MavkaParser::GodContext*>(context));
      }
      return create_ast_result(nullptr);
    }

    std::any visitNumber(MavkaParser::NumberContext* context) override {
      const auto number_node = new ast::NumberNode();
      number_node->start_line = context->getStart()->getLine();
      number_node->start_column = context->getStart()->getCharPositionInLine();
      number_node->end_line = context->getStop()->getLine();
      number_node->end_column = context->getStop()->getCharPositionInLine();
      number_node->value = process_number(context->getText());
      return create_ast_result(number_node);
    }

    std::any visitString_value(
        MavkaParser::String_valueContext* context) override {
      const auto string_node = new ast::StringNode();
      string_node->start_line = context->getStart()->getLine();
      string_node->start_column = context->getStart()->getCharPositionInLine();
      string_node->end_line = context->getStop()->getLine();
      string_node->end_column = context->getStop()->getCharPositionInLine();
      string_node->value = context->getText();
      if (string_node->value.starts_with(R"(""")")) {
        string_node->value =
            string_node->value.substr(3, string_node->value.length() - 6);
      } else {
        string_node->value =
            string_node->value.substr(1, string_node->value.length() - 2);
      }
      return create_ast_result(string_node);
    }

    std::any visitId(MavkaParser::IdContext* context) override {
      const auto identifier_node = new ast::IdentifierNode();
      identifier_node->start_line = context->getStart()->getLine();
      identifier_node->start_column =
          context->getStart()->getCharPositionInLine();
      identifier_node->end_line = context->getStop()->getLine();
      identifier_node->end_column = context->getStop()->getCharPositionInLine();
      identifier_node->name = context->getText();
      return create_ast_result(identifier_node);
    }

    std::any visitIdentifier(MavkaParser::IdentifierContext* context) override {
      const auto identifier_node = new ast::IdentifierNode();
      identifier_node->start_line = context->getStart()->getLine();
      identifier_node->start_column =
          context->getStart()->getCharPositionInLine();
      identifier_node->end_line = context->getStop()->getLine();
      identifier_node->end_column = context->getStop()->getCharPositionInLine();
      if (context->getText()[0] == '\'') {
        identifier_node->name = context->getText().substr(1);
      } else {
        identifier_node->name = context->getText();
      }
      return create_ast_result(identifier_node);
    }

    std::any visitChain(MavkaParser::ChainContext* context) override {
      const auto chain_node = new ast::ChainNode();
      chain_node->start_line = context->getStart()->getLine();
      chain_node->start_column = context->getStart()->getCharPositionInLine();
      chain_node->end_line = context->getStop()->getLine();
      chain_node->end_column = context->getStop()->getCharPositionInLine();
      chain_node->left = any_to_ast_result(visitValue(context->c_left))->node;
      chain_node->right =
          any_to_ast_result(visitIdentifier(context->c_right))->node;
      return create_ast_result(chain_node);
    }

    std::any visitCall(MavkaParser::CallContext* context) override {
      const auto call_node = new ast::CallNode();
      call_node->start_line = context->getStart()->getLine();
      call_node->start_column = context->getStart()->getCharPositionInLine();
      call_node->end_line = context->getStop()->getLine();
      call_node->end_column = context->getStop()->getCharPositionInLine();
      call_node->value = any_to_ast_result(visitValue(context->c_value))->node;
      if (context->c_args) {
        call_node->args = std::any_cast<std::vector<ast::ArgNode*>>(
            visitArgs(context->c_args));
      }
      if (context->c_named_args) {
        call_node->args = std::any_cast<std::vector<ast::ArgNode*>>(
            visitNamed_args(context->c_named_args));
      }
      return create_ast_result(call_node);
    }

    std::any visitGet_element(
        MavkaParser::Get_elementContext* context) override {
      const auto get_element_node = new ast::GetElementNode();
      get_element_node->start_line = context->getStart()->getLine();
      get_element_node->start_column =
          context->getStart()->getCharPositionInLine();
      get_element_node->end_line = context->getStop()->getLine();
      get_element_node->end_column =
          context->getStop()->getCharPositionInLine();
      get_element_node->value =
          any_to_ast_result(visitValue(context->ge_left))->node;
      get_element_node->index =
          any_to_ast_result(visitExpr(context->ge_element))->node;
      return create_ast_result(get_element_node);
    }

    std::any visitPositive(MavkaParser::PositiveContext* context) override {
      const auto positive_node = new ast::PositiveNode();
      positive_node->start_line = context->getStart()->getLine();
      positive_node->start_column =
          context->getStart()->getCharPositionInLine();
      positive_node->end_line = context->getStop()->getLine();
      positive_node->end_column = context->getStop()->getCharPositionInLine();
      positive_node->value =
          any_to_ast_result(visitValue(context->p_value))->node;
      return create_ast_result(positive_node);
    }

    std::any visitNegative(MavkaParser::NegativeContext* context) override {
      const auto negative_node = new ast::NegativeNode();
      negative_node->start_line = context->getStart()->getLine();
      negative_node->start_column =
          context->getStart()->getCharPositionInLine();
      negative_node->end_line = context->getStop()->getLine();
      negative_node->end_column = context->getStop()->getCharPositionInLine();
      negative_node->value =
          any_to_ast_result(visitValue(context->n_value))->node;
      return create_ast_result(negative_node);
    }

    std::any visitPre_decrement(
        MavkaParser::Pre_decrementContext* context) override {
      const auto pre_decrement_node = new ast::PreDecrementNode();
      pre_decrement_node->start_line = context->getStart()->getLine();
      pre_decrement_node->start_column =
          context->getStart()->getCharPositionInLine();
      pre_decrement_node->end_line = context->getStop()->getLine();
      pre_decrement_node->end_column =
          context->getStop()->getCharPositionInLine();
      pre_decrement_node->value =
          any_to_ast_result(visitValue(context->pd_value))->node;
      return create_ast_result(pre_decrement_node);
    }

    std::any visitPre_increment(
        MavkaParser::Pre_incrementContext* context) override {
      const auto pre_increment_node = new ast::PreIncrementNode();
      pre_increment_node->start_line = context->getStart()->getLine();
      pre_increment_node->start_column =
          context->getStart()->getCharPositionInLine();
      pre_increment_node->end_line = context->getStop()->getLine();
      pre_increment_node->end_column =
          context->getStop()->getCharPositionInLine();
      pre_increment_node->value =
          any_to_ast_result(visitValue(context->pi_value))->node;
      return create_ast_result(pre_increment_node);
    }

    std::any visitPost_decrement(
        MavkaParser::Post_decrementContext* context) override {
      const auto post_decrement_node = new ast::PostDecrementNode();
      post_decrement_node->start_line = context->getStart()->getLine();
      post_decrement_node->start_column =
          context->getStart()->getCharPositionInLine();
      post_decrement_node->end_line = context->getStop()->getLine();
      post_decrement_node->end_column =
          context->getStop()->getCharPositionInLine();
      post_decrement_node->value =
          any_to_ast_result(visitValue(context->pd_value))->node;
      return create_ast_result(post_decrement_node);
    }

    std::any visitPost_increment(
        MavkaParser::Post_incrementContext* context) override {
      const auto post_increment_node = new ast::PostIncrementNode();
      post_increment_node->start_line = context->getStart()->getLine();
      post_increment_node->start_column =
          context->getStart()->getCharPositionInLine();
      post_increment_node->end_line = context->getStop()->getLine();
      post_increment_node->end_column =
          context->getStop()->getCharPositionInLine();
      post_increment_node->value =
          any_to_ast_result(visitValue(context->pi_value))->node;
      return create_ast_result(post_increment_node);
    }

    std::any visitNot(MavkaParser::NotContext* context) override {
      const auto not_node = new ast::NotNode();
      not_node->start_line = context->getStart()->getLine();
      not_node->start_column = context->getStart()->getCharPositionInLine();
      not_node->end_line = context->getStop()->getLine();
      not_node->end_column = context->getStop()->getCharPositionInLine();
      not_node->value = any_to_ast_result(visitValue(context->n_value))->node;
      return create_ast_result(not_node);
    }

    std::any visitBitwise_not(
        MavkaParser::Bitwise_notContext* context) override {
      const auto bitwise_not_node = new ast::BitwiseNotNode();
      bitwise_not_node->start_line = context->getStart()->getLine();
      bitwise_not_node->start_column =
          context->getStart()->getCharPositionInLine();
      bitwise_not_node->end_line = context->getStop()->getLine();
      bitwise_not_node->end_column =
          context->getStop()->getCharPositionInLine();
      bitwise_not_node->value =
          any_to_ast_result(visitValue(context->bn_value))->node;
      return create_ast_result(bitwise_not_node);
    }

    std::any visitNested(MavkaParser::NestedContext* context) override {
      return visitExpr(context->n_value);
    }

    std::any visitCall_expr(MavkaParser::Call_exprContext* context) override {
      const auto call_expr_node = new ast::CallNode();
      call_expr_node->start_line = context->getStart()->getLine();
      call_expr_node->start_column =
          context->getStart()->getCharPositionInLine();
      call_expr_node->end_line = context->getStop()->getLine();
      call_expr_node->end_column = context->getStop()->getCharPositionInLine();
      call_expr_node->value =
          any_to_ast_result(visitExpr(context->ce_value))->node;
      if (context->ce_args) {
        call_expr_node->args = std::any_cast<std::vector<ast::ArgNode*>>(
            visitArgs(context->ce_args));
      }
      if (context->ce_named_args) {
        call_expr_node->args = std::any_cast<std::vector<ast::ArgNode*>>(
            visitNamed_args(context->ce_named_args));
      }
      return create_ast_result(call_expr_node);
    }

    std::any visitAs(MavkaParser::AsContext* context) override {
      const auto as_node = new ast::AsNode();
      as_node->start_line = context->getStart()->getLine();
      as_node->start_column = context->getStart()->getCharPositionInLine();
      as_node->end_line = context->getStop()->getLine();
      as_node->end_column = context->getStop()->getCharPositionInLine();
      as_node->left = any_to_ast_result(visitValue(context->a_left))->node;
      as_node->right = any_to_ast_result(visitValue(context->a_right))->node;
      return create_ast_result(as_node);
    }

    std::any visitArithmetic_mul(
        MavkaParser::Arithmetic_mulContext* context) override {
      const auto arithmetic_node = new ast::ArithmeticNode();
      arithmetic_node->start_line = context->getStart()->getLine();
      arithmetic_node->start_column =
          context->getStart()->getCharPositionInLine();
      arithmetic_node->end_line = context->getStop()->getLine();
      arithmetic_node->end_column = context->getStop()->getCharPositionInLine();
      arithmetic_node->left =
          any_to_ast_result(visitValue(context->a_left))->node;
      arithmetic_node->right =
          any_to_ast_result(visitValue(context->a_right))->node;
      arithmetic_node->op = context->a_operation->getText();
      return create_ast_result(arithmetic_node);
    }

    std::any visitArithmetic_op_mul(
        MavkaParser::Arithmetic_op_mulContext* context) override {
      return context->getText();
    }

    std::any visitArithmetic_add(
        MavkaParser::Arithmetic_addContext* context) override {
      const auto arithmetic_node = new ast::ArithmeticNode();
      arithmetic_node->start_line = context->getStart()->getLine();
      arithmetic_node->start_column =
          context->getStart()->getCharPositionInLine();
      arithmetic_node->end_line = context->getStop()->getLine();
      arithmetic_node->end_column = context->getStop()->getCharPositionInLine();
      arithmetic_node->left =
          any_to_ast_result(visitValue(context->a_left))->node;
      arithmetic_node->right =
          any_to_ast_result(visitValue(context->a_right))->node;
      arithmetic_node->op = context->a_operation->getText();
      return create_ast_result(arithmetic_node);
    }

    std::any visitArithmetic_op_add(
        MavkaParser::Arithmetic_op_addContext* context) override {
      return context->getText();
    }

    std::any visitBitwise(MavkaParser::BitwiseContext* context) override {
      const auto bitwise_node = new ast::BitwiseNode();
      bitwise_node->start_line = context->getStart()->getLine();
      bitwise_node->start_column = context->getStart()->getCharPositionInLine();
      bitwise_node->end_line = context->getStop()->getLine();
      bitwise_node->end_column = context->getStop()->getCharPositionInLine();
      bitwise_node->left = any_to_ast_result(visitValue(context->b_left))->node;
      bitwise_node->right =
          any_to_ast_result(visitValue(context->b_right))->node;
      bitwise_node->op = context->b_operation->getText();
      return create_ast_result(bitwise_node);
    }

    std::any visitBitwise_op(MavkaParser::Bitwise_opContext* context) override {
      return context->getText();
    }

    std::any visitComparison(MavkaParser::ComparisonContext* context) override {
      const auto comparison_node = new ast::ComparisonNode();
      comparison_node->start_line = context->getStart()->getLine();
      comparison_node->start_column =
          context->getStart()->getCharPositionInLine();
      comparison_node->end_line = context->getStop()->getLine();
      comparison_node->end_column = context->getStop()->getCharPositionInLine();
      comparison_node->left =
          any_to_ast_result(visitValue(context->c_left))->node;
      comparison_node->right =
          any_to_ast_result(visitValue(context->c_right))->node;
      comparison_node->op = context->c_operation->getText();
      return create_ast_result(comparison_node);
    }

    std::any visitTest(MavkaParser::TestContext* context) override {
      const auto test_node = new ast::TestNode();
      test_node->start_line = context->getStart()->getLine();
      test_node->start_column = context->getStart()->getCharPositionInLine();
      test_node->end_line = context->getStop()->getLine();
      test_node->end_column = context->getStop()->getCharPositionInLine();
      test_node->left = any_to_ast_result(visitValue(context->t_left))->node;
      test_node->right = any_to_ast_result(visitValue(context->t_right))->node;
      test_node->op = context->t_operation->getText();
      return create_ast_result(test_node);
    }

    std::any visitTernary(MavkaParser::TernaryContext* context) override {
      const auto ternary_node = new ast::TernaryNode();
      ternary_node->start_line = context->getStart()->getLine();
      ternary_node->start_column = context->getStart()->getCharPositionInLine();
      ternary_node->end_line = context->getStop()->getLine();
      ternary_node->end_column = context->getStop()->getCharPositionInLine();
      ternary_node->condition =
          any_to_ast_result(visitValue(context->t_value))->node;
      std::vector<ast::ASTNode*> body;
      if (context->t_positive) {
        body.push_back(any_to_ast_result(visitExpr(context->t_positive))->node);
      }
      ternary_node->body = body;
      std::vector<ast::ASTNode*> else_body;
      if (context->t_negative) {
        else_body.push_back(
            any_to_ast_result(visitExpr(context->t_negative))->node);
      }
      ternary_node->else_body = else_body;
      return create_ast_result(ternary_node);
    }

    std::any visitArray(MavkaParser::ArrayContext* context) override {
      const auto array_node = new ast::ArrayNode();
      array_node->start_line = context->getStart()->getLine();
      array_node->start_column = context->getStart()->getCharPositionInLine();
      array_node->end_line = context->getStop()->getLine();
      array_node->end_column = context->getStop()->getCharPositionInLine();
      if (context->a_elements) {
        array_node->elements = std::any_cast<std::vector<ast::ASTNode*>>(
            visitArray_elements(context->a_elements));
      }
      return create_ast_result(array_node);
    }

    std::any visitArray_elements(
        MavkaParser::Array_elementsContext* context) override {
      std::vector<ast::ASTNode*> elements;
      for (const auto array_element : context->array_element()) {
        const auto ast_result =
            any_to_ast_result(visitArray_element(array_element));
        elements.push_back(ast_result->node);
      }
      return elements;
    }

    std::any visitArray_element(
        MavkaParser::Array_elementContext* context) override {
      return visitExpr(context->ae_value);
    }

    std::any visitDictionary(MavkaParser::DictionaryContext* context) override {
      const auto dictionary_node = new ast::DictionaryNode();
      dictionary_node->start_line = context->getStart()->getLine();
      dictionary_node->start_column =
          context->getStart()->getCharPositionInLine();
      dictionary_node->end_line = context->getStop()->getLine();
      dictionary_node->end_column = context->getStop()->getCharPositionInLine();
      if (context->d_args) {
        dictionary_node->elements =
            std::any_cast<std::vector<ast::DictionaryElementNode*>>(
                visitDictionary_args(context->d_args));
      }
      return create_ast_result(dictionary_node);
    }

    std::any visitDictionary_args(
        MavkaParser::Dictionary_argsContext* context) override {
      std::vector<ast::DictionaryElementNode*> elements;
      for (const auto dictionary_arg : context->dictionary_arg()) {
        const auto value =
            any_to_ast_result(visitExpr(dictionary_arg->da_value))->node;
        if (dictionary_arg->da_name_id) {
          const auto dictionary_element_node = new ast::DictionaryElementNode();
          dictionary_element_node->start_line =
              dictionary_arg->getStart()->getLine();
          dictionary_element_node->start_column =
              dictionary_arg->getStart()->getCharPositionInLine();
          dictionary_element_node->end_line =
              dictionary_arg->getStop()->getLine();
          dictionary_element_node->end_column =
              dictionary_arg->getStop()->getCharPositionInLine();
          dictionary_element_node->key = dictionary_arg->da_name_id->getText();
          dictionary_element_node->value = value;
          elements.push_back(dictionary_element_node);
        } else if (dictionary_arg->da_name_string) {
          const auto name_string = dictionary_arg->da_name_string->getText();
          if (name_string.starts_with(R"(""")")) {
            const auto dictionary_element_node =
                new ast::DictionaryElementNode();
            dictionary_element_node->start_line =
                dictionary_arg->getStart()->getLine();
            dictionary_element_node->start_column =
                dictionary_arg->getStart()->getCharPositionInLine();
            dictionary_element_node->end_line =
                dictionary_arg->getStop()->getLine();
            dictionary_element_node->end_column =
                dictionary_arg->getStop()->getCharPositionInLine();
            dictionary_element_node->key =
                name_string.substr(3, name_string.length() - 6);
            dictionary_element_node->value = value;
            elements.push_back(dictionary_element_node);
          } else {
            const auto dictionary_element_node =
                new ast::DictionaryElementNode();
            dictionary_element_node->start_line =
                dictionary_arg->getStart()->getLine();
            dictionary_element_node->start_column =
                dictionary_arg->getStart()->getCharPositionInLine();
            dictionary_element_node->end_line =
                dictionary_arg->getStop()->getLine();
            dictionary_element_node->end_column =
                dictionary_arg->getStop()->getCharPositionInLine();
            dictionary_element_node->key =
                name_string.substr(1, name_string.length() - 2);
            dictionary_element_node->value = value;
            elements.push_back(dictionary_element_node);
          }
        }
      }
      return elements;
    }

    std::any visitGod(MavkaParser::GodContext* context) override {
      const auto god_node = new ast::GodNode();
      god_node->start_line = context->getStart()->getLine();
      god_node->start_column = context->getStart()->getCharPositionInLine();
      god_node->end_line = context->getStop()->getLine();
      god_node->end_column = context->getStop()->getCharPositionInLine();
      std::vector<ast::ASTNode*> elements;
      for (const auto value : context->value()) {
        const auto value_node = any_to_ast_result(visitValue(value))->node;
        elements.push_back(value_node);
      }
      god_node->elements = elements;
      return create_ast_result(god_node);
    }

    std::any visitWait(MavkaParser::WaitContext* context) override {
      const auto wait_node = new ast::WaitNode();
      wait_node->start_line = context->getStart()->getLine();
      wait_node->start_column = context->getStart()->getCharPositionInLine();
      wait_node->end_line = context->getStop()->getLine();
      wait_node->end_column = context->getStop()->getCharPositionInLine();
      wait_node->value = any_to_ast_result(visitValue(context->w_value))->node;
      return create_ast_result(wait_node);
    }

    std::any visitFunction(MavkaParser::FunctionContext* context) override {
      const auto function_node = new ast::FunctionNode();
      function_node->start_line = context->getStart()->getLine();
      function_node->start_column =
          context->getStart()->getCharPositionInLine();
      function_node->end_line = context->getStop()->getLine();
      function_node->end_column = context->getStop()->getCharPositionInLine();
      function_node->async = context->f_async != nullptr;
      if (context->f_params) {
        function_node->params = std::any_cast<std::vector<ast::ParamNode*>>(
            visitParams(context->f_params));
      }
      if (context->f_type) {
        function_node->return_types = std::any_cast<std::vector<ast::ASTNode*>>(
            visitType_value(context->f_type));
      }
      if (context->f_body) {
        const auto function_node_body =
            any_to_ast_result(visitExpr(context->f_body))->node;
        function_node->body.push_back(function_node_body);
      }
      return create_ast_result(function_node);
    }

    std::any visitAnonymous_diia(
        MavkaParser::Anonymous_diiaContext* context) override {
      const auto anon_diia_node = new ast::AnonDiiaNode();
      anon_diia_node->start_line = context->getStart()->getLine();
      anon_diia_node->start_column =
          context->getStart()->getCharPositionInLine();
      anon_diia_node->end_line = context->getStop()->getLine();
      anon_diia_node->end_column = context->getStop()->getCharPositionInLine();
      anon_diia_node->async = context->d_async != nullptr;
      if (context->d_params) {
        anon_diia_node->params = std::any_cast<std::vector<ast::ParamNode*>>(
            visitParams(context->d_params));
      }
      if (context->d_type) {
        anon_diia_node->return_types =
            std::any_cast<std::vector<ast::ASTNode*>>(
                visitType_value(context->d_type));
      }
      if (context->d_body) {
        anon_diia_node->body = std::any_cast<std::vector<ast::ASTNode*>>(
            visitBody(context->d_body));
      }
      return create_ast_result(anon_diia_node);
    }

    std::any visitThrow(MavkaParser::ThrowContext* context) override {
      const auto throw_node = new ast::ThrowNode();
      throw_node->start_line = context->getStart()->getLine();
      throw_node->start_column = context->getStart()->getCharPositionInLine();
      throw_node->end_line = context->getStop()->getLine();
      throw_node->end_column = context->getStop()->getCharPositionInLine();
      throw_node->value = any_to_ast_result(visitExpr(context->t_value))->node;
      return create_ast_result(throw_node);
    }

    std::any visitEval(MavkaParser::EvalContext* context) override {
      const auto eval_node = new ast::EvalNode();
      eval_node->start_line = context->getStart()->getLine();
      eval_node->start_column = context->getStart()->getCharPositionInLine();
      eval_node->end_line = context->getStop()->getLine();
      eval_node->end_column = context->getStop()->getCharPositionInLine();
      eval_node->value = any_to_ast_result(visitValue(context->e_value))->node;
      return create_ast_result(eval_node);
    }

    std::any visitWait_assign(
        MavkaParser::Wait_assignContext* context) override {
      const auto assign_node =
          any_to_ast_result(visitAssign(context->wa_assign))->node;
      if (jejalyk::tools::instance_of<ast::AssignSimpleNode>(assign_node)) {
        const auto assign_simple_node =
            dynamic_cast<ast::AssignSimpleNode*>(assign_node);
        const auto new_assign_simple_node = new ast::AssignSimpleNode();
        new_assign_simple_node->start_line = assign_simple_node->start_line;
        new_assign_simple_node->start_column = assign_simple_node->start_column;
        new_assign_simple_node->end_line = assign_simple_node->end_line;
        new_assign_simple_node->end_column = assign_simple_node->end_column;
        const auto wait_node = new ast::WaitNode();
        wait_node->start_line = assign_simple_node->start_line;
        wait_node->start_column = assign_simple_node->start_column;
        wait_node->end_line = assign_simple_node->end_line;
        wait_node->end_column = assign_simple_node->end_column;
        wait_node->value = assign_simple_node->value;
        new_assign_simple_node->op = assign_simple_node->op;
        new_assign_simple_node->name = assign_simple_node->name;
        new_assign_simple_node->value = wait_node;
        return create_ast_result(new_assign_simple_node);
      }
      if (jejalyk::tools::instance_of<ast::AssignByIdentifierNode>(
              assign_node)) {
        const auto assign_by_identifier_node =
            dynamic_cast<ast::AssignByIdentifierNode*>(assign_node);
        const auto new_assign_by_identifier_node =
            new ast::AssignByIdentifierNode();
        new_assign_by_identifier_node->start_line =
            assign_by_identifier_node->start_line;
        new_assign_by_identifier_node->start_column =
            assign_by_identifier_node->start_column;
        new_assign_by_identifier_node->end_line =
            assign_by_identifier_node->end_line;
        new_assign_by_identifier_node->end_column =
            assign_by_identifier_node->end_column;
        const auto wait_node = new ast::WaitNode();
        wait_node->start_line = assign_by_identifier_node->start_line;
        wait_node->start_column = assign_by_identifier_node->start_column;
        wait_node->end_line = assign_by_identifier_node->end_line;
        wait_node->end_column = assign_by_identifier_node->end_column;
        wait_node->value = assign_by_identifier_node->value;
        new_assign_by_identifier_node->op = assign_by_identifier_node->op;
        new_assign_by_identifier_node->left = assign_by_identifier_node->left;
        new_assign_by_identifier_node->identifier =
            assign_by_identifier_node->identifier;
        new_assign_by_identifier_node->value = wait_node;
        return create_ast_result(new_assign_by_identifier_node);
      }
      if (jejalyk::tools::instance_of<ast::AssignByElementNode>(assign_node)) {
        const auto assign_by_element_node =
            dynamic_cast<ast::AssignByElementNode*>(assign_node);
        const auto new_assign_by_element_node = new ast::AssignByElementNode();
        new_assign_by_element_node->start_line =
            assign_by_element_node->start_line;
        new_assign_by_element_node->start_column =
            assign_by_element_node->start_column;
        new_assign_by_element_node->end_line = assign_by_element_node->end_line;
        new_assign_by_element_node->end_column =
            assign_by_element_node->end_column;
        const auto wait_node = new ast::WaitNode();
        wait_node->start_line = assign_by_element_node->start_line;
        wait_node->start_column = assign_by_element_node->start_column;
        wait_node->end_line = assign_by_element_node->end_line;
        wait_node->end_column = assign_by_element_node->end_column;
        wait_node->value = assign_by_element_node->value;
        new_assign_by_element_node->op = assign_by_element_node->op;
        new_assign_by_element_node->left = assign_by_element_node->left;
        new_assign_by_element_node->element = assign_by_element_node->element;
        new_assign_by_element_node->value = wait_node;
        return create_ast_result(new_assign_by_element_node);
      }
      return create_ast_result(nullptr);
    }

    std::any visitAssign(MavkaParser::AssignContext* context) override {
      if (context->assign_simple()) {
        return visitAssign_simple(context->assign_simple());
      }
      if (context->assign_by_identifier()) {
        return visitAssign_by_identifier(context->assign_by_identifier());
      }
      if (context->assign_by_element()) {
        return visitAssign_by_element(context->assign_by_element());
      }
      return create_ast_result(nullptr);
    }

    std::any visitAssign_simple(
        MavkaParser::Assign_simpleContext* context) override {
      const auto assign_simple_node = new ast::AssignSimpleNode();
      assign_simple_node->start_line = context->getStart()->getLine();
      assign_simple_node->start_column =
          context->getStart()->getCharPositionInLine();
      assign_simple_node->end_line = context->getStop()->getLine();
      assign_simple_node->end_column =
          context->getStop()->getCharPositionInLine();
      assign_simple_node->name = context->as_identifier->ID()->getText();
      if (context->as_type) {
        assign_simple_node->types = std::any_cast<std::vector<ast::ASTNode*>>(
            visitType_value(context->as_type));
      }
      assign_simple_node->op = context->assign_symbol()->getText();
      assign_simple_node->value =
          any_to_ast_result(visitExpr(context->as_value))->node;
      return create_ast_result(assign_simple_node);
    }

    std::any visitAssign_by_identifier(
        MavkaParser::Assign_by_identifierContext* context) override {
      const auto assign_by_identifier_node = new ast::AssignByIdentifierNode();
      assign_by_identifier_node->start_line = context->getStart()->getLine();
      assign_by_identifier_node->start_column =
          context->getStart()->getCharPositionInLine();
      assign_by_identifier_node->end_line = context->getStop()->getLine();
      assign_by_identifier_node->end_column =
          context->getStop()->getCharPositionInLine();
      assign_by_identifier_node->left =
          any_to_ast_result(visitSuper_identifiers_chain(context->abi_left))
              ->node;
      assign_by_identifier_node->identifier =
          context->abi_identifier->getText();
      assign_by_identifier_node->op = context->assign_symbol()->getText();
      assign_by_identifier_node->value =
          any_to_ast_result(visitExpr(context->abi_value))->node;
      return create_ast_result(assign_by_identifier_node);
    }

    std::any visitAssign_by_element(
        MavkaParser::Assign_by_elementContext* context) override {
      const auto assign_by_element_node = new ast::AssignByElementNode();
      assign_by_element_node->start_line = context->getStart()->getLine();
      assign_by_element_node->start_column =
          context->getStart()->getCharPositionInLine();
      assign_by_element_node->end_line = context->getStop()->getLine();
      assign_by_element_node->end_column =
          context->getStop()->getCharPositionInLine();
      assign_by_element_node->left =
          any_to_ast_result(visitSuper_identifiers_chain(context->abe_left))
              ->node;
      assign_by_element_node->element =
          any_to_ast_result(visitExpr(context->abe_index))->node;
      assign_by_element_node->op = context->assign_symbol()->getText();
      assign_by_element_node->value =
          any_to_ast_result(visitExpr(context->abe_value))->node;
      return create_ast_result(assign_by_element_node);
    }

    std::any visitAssign_array_destruction(
        MavkaParser::Assign_array_destructionContext* context) override {
      // todo
      return create_ast_result(new ast::ASTNode());
    }

    std::any visitAssign_object_destruction(
        MavkaParser::Assign_object_destructionContext* context) override {
      // todo
      return create_ast_result(new ast::ASTNode());
    }

    std::any visitAssign_symbol(
        MavkaParser::Assign_symbolContext* context) override {
      // todo
      return create_ast_result(new ast::ASTNode());
    }

    std::any visitTake(MavkaParser::TakeContext* context) {
      if (jejalyk::tools::instance_of<MavkaParser::Take_moduleContext>(
              context)) {
        return visitTake_module(
            dynamic_cast<MavkaParser::Take_moduleContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Take_fileContext>(context)) {
        return visitTake_file(
            dynamic_cast<MavkaParser::Take_fileContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Take_remoteContext>(
              context)) {
        return visitTake_remote(
            dynamic_cast<MavkaParser::Take_remoteContext*>(context));
      }
      return create_ast_result(nullptr);
    }

    std::any visitTake_module(
        MavkaParser::Take_moduleContext* context) override {
      const auto take_module_node = new ast::TakeModuleNode();
      take_module_node->start_line = context->getStart()->getLine();
      take_module_node->start_column =
          context->getStart()->getCharPositionInLine();
      take_module_node->end_line = context->getStop()->getLine();
      take_module_node->end_column =
          context->getStop()->getCharPositionInLine();
      take_module_node->relative = context->tm_relative != nullptr;
      take_module_node->name = context->tm_elements_chain->getText();
      take_module_node->as = context->tm_as ? context->tm_as->getText() : "";
      return create_ast_result(take_module_node);
    }

    std::any visitTake_file(MavkaParser::Take_fileContext* context) override {
      // todo
      return create_ast_result(new ast::ASTNode());
    }

    std::any visitTake_remote(
        MavkaParser::Take_remoteContext* context) override {
      const auto take_pak_node = new ast::TakePakNode();
      take_pak_node->start_line = context->getStart()->getLine();
      take_pak_node->start_column =
          context->getStart()->getCharPositionInLine();
      take_pak_node->end_line = context->getStop()->getLine();
      take_pak_node->end_column = context->getStop()->getCharPositionInLine();
      take_pak_node->name = context->tr_url->getText();
      if (take_pak_node->name.starts_with(R"(""")")) {
        take_pak_node->name =
            take_pak_node->name.substr(3, take_pak_node->name.length() - 6);
      } else {
        take_pak_node->name =
            take_pak_node->name.substr(1, take_pak_node->name.length() - 2);
      }
      take_pak_node->as = context->tr_as ? context->tr_as->getText() : "";
      return create_ast_result(take_pak_node);
    }

    std::any visitGive(MavkaParser::GiveContext* context) override {
      const auto give_node = new ast::GiveNode();
      give_node->start_line = context->getStart()->getLine();
      give_node->start_column = context->getStart()->getCharPositionInLine();
      give_node->end_line = context->getStop()->getLine();
      give_node->end_column = context->getStop()->getCharPositionInLine();
      for (const auto give_element : context->give_element()) {
        const auto ast_result =
            any_to_ast_result(visitGive_element(give_element));
        const auto give_element_node =
            dynamic_cast<ast::GiveElementNode*>(ast_result->node);
        give_node->elements.push_back(give_element_node);
      }
      return create_ast_result(give_node);
    }

    std::any visitGive_element(
        MavkaParser::Give_elementContext* context) override {
      const auto give_element_node = new ast::GiveElementNode();
      give_element_node->start_line = context->getStart()->getLine();
      give_element_node->start_column =
          context->getStart()->getCharPositionInLine();
      give_element_node->end_line = context->getStop()->getLine();
      give_element_node->end_column =
          context->getStop()->getCharPositionInLine();
      give_element_node->name = context->ge_name->getText();
      if (context->ge_as) {
        give_element_node->as = context->ge_as->getText();
      }
      return create_ast_result(give_element_node);
    }

    std::any visitParams(MavkaParser::ParamsContext* context) override {
      std::vector<ast::ParamNode*> params;
      for (int i = 0; i < context->param().size(); ++i) {
        const auto param = context->param()[i];
        const auto ast_result = any_to_ast_result(visitParam(param));
        params.push_back(dynamic_cast<ast::ParamNode*>(ast_result->node));
      }
      if (context->p_variadic) {
        const auto param_node = new ast::ParamNode();
        param_node->start_line = context->getStart()->getLine();
        param_node->start_column = context->getStart()->getCharPositionInLine();
        param_node->end_line = context->getStop()->getLine();
        param_node->end_column = context->getStop()->getCharPositionInLine();
        param_node->name = context->p_variadic_name->getText();
        if (context->p_variadic_type) {
          param_node->types = std::any_cast<std::vector<ast::ASTNode*>>(
              visitType_value(context->p_variadic_type));
        }
        param_node->variadic = true;
        params.push_back(param_node);
      }
      return params;
    }

    std::any visitParam(MavkaParser::ParamContext* context) override {
      const auto param_node = new ast::ParamNode();
      param_node->name = context->p_name->getText();
      if (context->p_type) {
        param_node->types = std::any_cast<std::vector<ast::ASTNode*>>(
            visitType_value(context->p_type));
      }
      if (context->p_value) {
        param_node->value =
            any_to_ast_result(visitParam_value(context->p_value))->node;
      }
      return create_ast_result(param_node);
    }

    std::any visitParam_value(MavkaParser::Param_valueContext* context) {
      if (jejalyk::tools::instance_of<MavkaParser::Param_value_stringContext>(
              context)) {
        return visitParam_value_string(
            dynamic_cast<MavkaParser::Param_value_stringContext*>(context));
      }
      if (jejalyk::tools::instance_of<MavkaParser::Param_value_numberContext>(
              context)) {
        return visitParam_value_number(
            dynamic_cast<MavkaParser::Param_value_numberContext*>(context));
      }
      if (jejalyk::tools::instance_of<
              MavkaParser::Param_value_identifierContext>(context)) {
        return visitParam_value_identifier(
            dynamic_cast<MavkaParser::Param_value_identifierContext*>(context));
      }
      if (jejalyk::tools::instance_of<
              MavkaParser::Param_value_empty_dictionaryContext>(context)) {
        return visitParam_value_empty_dictionary(
            dynamic_cast<MavkaParser::Param_value_empty_dictionaryContext*>(
                context));
      }
      if (jejalyk::tools::instance_of<
              MavkaParser::Param_value_empty_listContext>(context)) {
        return visitParam_value_empty_list(
            dynamic_cast<MavkaParser::Param_value_empty_listContext*>(context));
      }
      return create_ast_result(nullptr);
    }

    std::any visitParam_value_string(
        MavkaParser::Param_value_stringContext* context) override {
      if (context->STRING()) {
        const auto string_node = new ast::StringNode();
        string_node->start_line = context->getStart()->getLine();
        string_node->start_column =
            context->getStart()->getCharPositionInLine();
        string_node->end_line = context->getStop()->getLine();
        string_node->end_column = context->getStop()->getCharPositionInLine();
        string_node->value = context->STRING()->getText();
        if (string_node->value.starts_with(R"(""")")) {
          string_node->value =
              string_node->value.substr(3, string_node->value.length() - 6);
        } else {
          string_node->value =
              string_node->value.substr(1, string_node->value.length() - 2);
        }
        return create_ast_result(string_node);
      } else if (context->STRING_MULTILINE()) {
        const auto string_node = new ast::StringNode();
        string_node->start_line = context->getStart()->getLine();
        string_node->start_column =
            context->getStart()->getCharPositionInLine();
        string_node->end_line = context->getStop()->getLine();
        string_node->end_column = context->getStop()->getCharPositionInLine();
        string_node->value = context->STRING_MULTILINE()->getText();
        if (string_node->value.starts_with(R"(""")")) {
          string_node->value =
              string_node->value.substr(3, string_node->value.length() - 6);
        } else {
          string_node->value =
              string_node->value.substr(1, string_node->value.length() - 2);
        }
        return create_ast_result(string_node);
      }
      return create_ast_result(nullptr);
    }

    std::any visitParam_value_number(
        MavkaParser::Param_value_numberContext* context) override {
      const auto number_node = new ast::NumberNode();
      number_node->start_line = context->getStart()->getLine();
      number_node->start_column = context->getStart()->getCharPositionInLine();
      number_node->end_line = context->getStop()->getLine();
      number_node->end_column = context->getStop()->getCharPositionInLine();
      number_node->value = process_number(context->NUMBER()->getText());
      return create_ast_result(number_node);
    }

    std::any visitParam_value_identifier(
        MavkaParser::Param_value_identifierContext* context) override {
      const auto identifier_node = new ast::IdentifierNode();
      identifier_node->start_line = context->getStart()->getLine();
      identifier_node->start_column =
          context->getStart()->getCharPositionInLine();
      identifier_node->end_line = context->getStop()->getLine();
      identifier_node->end_column = context->getStop()->getCharPositionInLine();
      identifier_node->name = context->identifier()->getText();
      return create_ast_result(identifier_node);
    }

    std::any visitParam_value_empty_dictionary(
        MavkaParser::Param_value_empty_dictionaryContext* context) override {
      const auto dictionary_node = new ast::DictionaryNode();
      dictionary_node->start_line = context->getStart()->getLine();
      dictionary_node->start_column =
          context->getStart()->getCharPositionInLine();
      dictionary_node->end_line = context->getStop()->getLine();
      dictionary_node->end_column = context->getStop()->getCharPositionInLine();
      return create_ast_result(dictionary_node);
    }

    std::any visitParam_value_empty_list(
        MavkaParser::Param_value_empty_listContext* context) override {
      const auto array_node = new ast::ArrayNode();
      array_node->start_line = context->getStart()->getLine();
      array_node->start_column = context->getStart()->getCharPositionInLine();
      array_node->end_line = context->getStop()->getLine();
      array_node->end_column = context->getStop()->getCharPositionInLine();
      return create_ast_result(array_node);
    }

    std::any visitIdentifiers_chain(
        MavkaParser::Identifiers_chainContext* context) override {
      if (context->ic_identifier) {
        return visitIdentifier(context->ic_identifier);
      }
      const auto chain_node = new ast::ChainNode();
      chain_node->start_line = context->getStart()->getLine();
      chain_node->start_column = context->getStart()->getCharPositionInLine();
      chain_node->end_line = context->getStop()->getLine();
      chain_node->end_column = context->getStop()->getCharPositionInLine();
      chain_node->left =
          any_to_ast_result(visitIdentifiers_chain(context->ic_left))->node;
      chain_node->right =
          any_to_ast_result(visitIdentifier(context->ic_right))->node;
      return create_ast_result(chain_node);
    }

    std::any visitSuper_identifiers_chain(
        MavkaParser::Super_identifiers_chainContext* context) override {
      if (context->sic_identifier) {
        return visitIdentifier(context->sic_identifier);
      }
      const auto left =
          any_to_ast_result(visitSuper_identifiers_chain(context->sic_left))
              ->node;
      if (context->sic_right) {
        const auto right =
            any_to_ast_result(visitIdentifier(context->sic_right))->node;
        const auto chain_node = new ast::ChainNode();
        chain_node->start_line = context->getStart()->getLine();
        chain_node->start_column = context->getStart()->getCharPositionInLine();
        chain_node->end_line = context->getStop()->getLine();
        chain_node->end_column = context->getStop()->getCharPositionInLine();
        chain_node->left = left;
        chain_node->right = right;
        return create_ast_result(chain_node);
      }
      const auto index = any_to_ast_result(visitExpr(context->sic_index))->node;
      const auto get_element_node = new ast::GetElementNode();
      get_element_node->start_line = context->getStart()->getLine();
      get_element_node->start_column =
          context->getStart()->getCharPositionInLine();
      get_element_node->end_line = context->getStop()->getLine();
      get_element_node->end_column =
          context->getStop()->getCharPositionInLine();
      get_element_node->value = left;
      get_element_node->index = index;
      return create_ast_result(get_element_node);
    }

    std::any visitType_value(MavkaParser::Type_valueContext* context) override {
      std::vector<ast::ASTNode*> types;
      for (int i = 0; i < context->type_value_item().size(); ++i) {
        const auto type = context->type_value_item()[i];
        const auto ast_result =
            any_to_ast_result(visitIdentifiers_chain(type->tvi_value));
        types.push_back(ast_result->node);
      }
      return types;
    }

    std::any visitArgs(MavkaParser::ArgsContext* context) override {
      std::vector<ast::ArgNode*> args;
      for (int i = 0; i < context->arg().size(); ++i) {
        const auto arg = context->arg()[i];
        const auto ast_result = any_to_ast_result(visitArg(arg, i));
        args.push_back(dynamic_cast<ast::ArgNode*>(ast_result->node));
      }
      return args;
    }

    std::any visitArg(MavkaParser::ArgContext* context, int index) {
      const auto arg_node = new ast::ArgNode();
      arg_node->start_line = context->getStart()->getLine();
      arg_node->start_column = context->getStart()->getCharPositionInLine();
      arg_node->end_line = context->getStop()->getLine();
      arg_node->end_column = context->getStop()->getCharPositionInLine();
      arg_node->index = index;
      arg_node->value = any_to_ast_result(visitExpr(context->a_value))->node;
      arg_node->spread = context->a_spread != nullptr;
      return create_ast_result(arg_node);
    }

    std::any visitNamed_args(MavkaParser::Named_argsContext* context) override {
      std::vector<ast::ArgNode*> args;
      for (int i = 0; i < context->named_arg().size(); ++i) {
        const auto arg = context->named_arg()[i];
        const auto ast_result = any_to_ast_result(visitNamed_arg(arg, i));
        args.push_back(dynamic_cast<ast::ArgNode*>(ast_result->node));
      }
      return args;
    }

    std::any visitNamed_arg(MavkaParser::Named_argContext* context, int index) {
      const auto arg_node = new ast::ArgNode();
      arg_node->start_line = context->getStart()->getLine();
      arg_node->start_column = context->getStart()->getCharPositionInLine();
      arg_node->end_line = context->getStop()->getLine();
      arg_node->end_column = context->getStop()->getCharPositionInLine();
      arg_node->index = index;
      arg_node->name = context->na_name->getText();
      arg_node->value = any_to_ast_result(visitExpr(context->na_value))->node;
      return create_ast_result(arg_node);
    }

    std::any visitBody(MavkaParser::BodyContext* context) override {
      std::vector<ast::ASTNode*> body;
      for (const auto body_element : context->body_element_or_return()) {
        const auto ast_result =
            any_to_ast_result(visitBody_element_or_return(body_element));
        body.push_back(ast_result->node);
      }
      return body;
    }

    std::any visitBody_element_or_return(
        MavkaParser::Body_element_or_returnContext* context) override {
      if (context->body_element()) {
        return visitBody_element(context->body_element());
      }
      if (context->return_body_line()) {
        return visitReturn_body_line(context->return_body_line());
      }
      return create_ast_result(nullptr);
    }

    std::any visitBody_element(
        MavkaParser::Body_elementContext* context) override {
      if (context->if_()) {
        return visitIf(context->if_());
      }
      if (context->each()) {
        return visitEach(context->each());
      }
      if (context->while_()) {
        return visitWhile(context->while_());
      }
      if (context->try_()) {
        return visitTry(context->try_());
      }
      if (context->expr()) {
        return visitExpr(context->expr());
      }
      if (context->throw_()) {
        return visitThrow(context->throw_());
      }
      if (context->wait_assign()) {
        return visitWait_assign(context->wait_assign());
      }
      if (context->assign()) {
        return visitAssign(context->assign());
      }
      return create_ast_result(nullptr);
    }

    std::any visitReturn_body_line(
        MavkaParser::Return_body_lineContext* context) override {
      const auto return_node = new ast::ReturnNode();
      return_node->start_line = context->getStart()->getLine();
      return_node->start_column = context->getStart()->getCharPositionInLine();
      return_node->end_line = context->getStop()->getLine();
      return_node->end_column = context->getStop()->getCharPositionInLine();
      return_node->value =
          any_to_ast_result(visitExpr(context->rbl_value))->node;
      return create_ast_result(return_node);
    }
  };

  class MavkaParserError : public std::exception {
   public:
    size_t line{};
    size_t column{};
    std::string message;
  };

  class MavkaParserErrorListener final : public antlr4::BaseErrorListener {
   public:
    void syntaxError(antlr4::Recognizer* recognizer,
                     antlr4::Token* offendingSymbol,
                     size_t line,
                     size_t charPositionInLine,
                     const std::string& msg,
                     std::exception_ptr e) override {
      std::cout << msg << std::endl;
      const auto error = new MavkaParserError();
      error->line = line;
      error->column = charPositionInLine;
      error->message = "syntaxError";
      throw *error;
    }
  };

  class MavkaParserResult {
   public:
    MavkaParserError* error = nullptr;
    ast::ProgramNode* program_node = nullptr;
  };

  MavkaParserResult* parse(std::string code);
}
#endif //PARSER_H
