#include "parser.h"

namespace mavka::parser {
  ast::ASTSome* any_to_ast_some(std::any any) {
    return std::any_cast<ast::ASTSome*>(any);
  }

  void fill_ast_node(ast::ASTNode* node, antlr4::ParserRuleContext* context) {
    node->start_line = context->getStart()->getLine();
    node->start_column = context->getStart()->getCharPositionInLine();
    node->end_line = context->getStop()->getLine();
    node->end_column = context->getStop()->getCharPositionInLine();
  }

  std::string process_number(std::string number) {
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

  void processASTBody(const std::vector<ast::ASTSome*>& body) {
    for (const auto& item : body) {
      if (item->IdentifierNode) {
        if (item->IdentifierNode->name == "break") {
          item->IdentifierNode = nullptr;
          item->BreakNode = new ast::BreakNode();
          continue;
        }
        if (item->IdentifierNode->name == "continue") {
          item->IdentifierNode = nullptr;
          item->ContinueNode = new ast::ContinueNode();
          continue;
        }
      }
    }
  }

  std::any MavkaASTVisitor::visitFile(MavkaParser::FileContext* ctx) {
    return visitProgram(ctx->f_program);
  }

  std::any MavkaASTVisitor::visitProgram(MavkaParser::ProgramContext* context) {
    std::vector<ast::ASTSome*> body;
    for (const auto program_element : context->program_element()) {
      const auto ast_some =
          any_to_ast_some(visitProgram_element(program_element));
      body.push_back(ast_some);
    }
    processASTBody(body);
    const auto program_node = new ast::ProgramNode();
    // program_node->start_line = context->getStart()->getLine();
    // program_node->start_column = context->getStart()->getCharPositionInLine();
    // program_node->end_line = context->getStop()->getLine();
    // program_node->end_column = context->getStop()->getCharPositionInLine();
    program_node->body = body;
    return (ast::make_ast_some(program_node));
  }

  std::any MavkaASTVisitor::visitProgram_element(
      MavkaParser::Program_elementContext* context) {
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
      return _visitContext(context->expr());
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
    if (context->comp_inst_block_program()) {
      return visitComp_inst_block_program(context->comp_inst_block_program());
    }
    if (context->comp_inst_assign()) {
      return visitComp_inst_assign(context->comp_inst_assign());
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitModule(MavkaParser::ModuleContext* context) {
    const auto module_node = new ast::ModuleNode();
    module_node->start_line = context->getStart()->getLine();
    module_node->start_column = context->getStart()->getCharPositionInLine();
    module_node->end_line = context->getStop()->getLine();
    module_node->end_column = context->getStop()->getCharPositionInLine();
    module_node->name = context->m_name->getText();
    if (context->module_body()) {
      std::any module_body = visitModule_body(context->module_body());
      module_node->body =
          std::any_cast<std::vector<ast::ASTSome*>>(module_body);
    }
    return (ast::make_ast_some(module_node));
  }

  std::any MavkaASTVisitor::visitModule_body(
      MavkaParser::Module_bodyContext* context) {
    std::vector<ast::ASTSome*> body;
    for (const auto module_element : context->module_body_element()) {
      const auto ast_result =
          any_to_ast_some(visitModule_body_element(module_element));
      body.push_back(ast_result);
    }
    processASTBody(body);
    return body;
  }

  std::any MavkaASTVisitor::visitModule_body_element(
      MavkaParser::Module_body_elementContext* context) {
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
      return _visitContext(context->expr());
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
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitStructure(
      MavkaParser::StructureContext* context) {
    const std::string name = context->s_name->getText();
    std::vector<ast::GenericNode*> generics;
    if (context->s_generics) {
      generics = std::any_cast<std::vector<ast::GenericNode*>>(
          visitGenerics(context->s_generics));
    }
    const auto structure_node = new ast::StructureNode();
    structure_node->start_line = context->getStart()->getLine();
    structure_node->start_column = context->getStart()->getCharPositionInLine();
    structure_node->end_line = context->getStop()->getLine();
    structure_node->end_column = context->getStop()->getCharPositionInLine();
    structure_node->name = name;
    structure_node->generics = generics;
    if (context->s_parent) {
      const auto parent =
          any_to_ast_some(visitSuper_identifiers_chain(context->s_parent));
      structure_node->parent = parent;
    }
    if (context->s_elements) {
      const auto elements = std::any_cast<std::vector<ast::ASTSome*>>(
          visitStructure_elements(context->s_elements));
      for (const auto element : elements) {
        if (element->ParamNode) {
          structure_node->params.push_back(element->ParamNode);
        }
        if (element->MethodDeclarationNode) {
          structure_node->methods.push_back(element->MethodDeclarationNode);
        }
      }
    }
    return (ast::make_ast_some(structure_node));
  }

  std::any MavkaASTVisitor::visitStructure_elements(
      MavkaParser::Structure_elementsContext* context) {
    std::vector<ast::ASTSome*> elements;
    for (const auto structure_element : context->structure_element()) {
      const auto ast_result =
          any_to_ast_some(visitStructure_element(structure_element));
      elements.push_back(ast_result);
    }
    return elements;
  }

  std::any MavkaASTVisitor::visitStructure_element(
      MavkaParser::Structure_elementContext* context) {
    if (context->structure_param()) {
      return visitStructure_param(context->structure_param());
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitStructure_param(
      MavkaParser::Structure_paramContext* context) {
    const std::string name = context->sp_name->getText();
    std::vector<ast::TypeValueSingleNode*> types;
    if (context->sp_type) {
      types = std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
          visitType_value(context->sp_type));
    }
    ast::ASTSome* value = nullptr;
    if (context->sp_value) {
      value = any_to_ast_some(visitParam_value(context->sp_value));
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
    return (ast::make_ast_some(structure_param_node));
  }

  std::any MavkaASTVisitor::visitGenerics(
      MavkaParser::GenericsContext* context) {
    std::vector<ast::GenericNode*> generics;
    for (const auto identifier_node : context->identifier()) {
      const auto identifier_result =
          any_to_ast_some(visitIdentifier(identifier_node));
      const auto identifier = identifier_result->IdentifierNode;
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

  std::any MavkaASTVisitor::visitMethod_declaration(
      MavkaParser::Method_declarationContext* context) {
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
          std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
              visitType_value(context->md_type));
    }
    return (ast::make_ast_some(method_declaration_node));
  }

  std::any MavkaASTVisitor::visitMockup(MavkaParser::MockupContext* context) {
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
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitMockup_module(
      MavkaParser::Mockup_moduleContext* context) {
    const auto mockup_module_node = new ast::MockupModuleNode();
    mockup_module_node->start_line = context->getStart()->getLine();
    mockup_module_node->start_column =
        context->getStart()->getCharPositionInLine();
    mockup_module_node->end_line = context->getStop()->getLine();
    mockup_module_node->end_column =
        context->getStop()->getCharPositionInLine();
    mockup_module_node->name = context->mm_name->getText();
    if (context->mm_elements) {
      mockup_module_node->elements = std::any_cast<std::vector<ast::ASTSome*>>(
          visitMockup_module_body(context->mm_elements));
    }
    return (ast::make_ast_some(mockup_module_node));
  }

  std::any MavkaASTVisitor::visitMockup_structure(
      MavkaParser::Mockup_structureContext* context) {
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
      const auto elements = std::any_cast<std::vector<ast::ASTSome*>>(
          visitMockup_structure_body(context->ms_elements));
      for (const auto element : elements) {
        if (element->ParamNode) {
          mockup_structure_node->params.push_back(element->ParamNode);
        }
        if (element->MethodDeclarationNode) {
          mockup_structure_node->methods.push_back(
              element->MethodDeclarationNode);
        }
      }
    }
    return (ast::make_ast_some(mockup_structure_node));
  }

  std::any MavkaASTVisitor::visitMockup_module_body(
      MavkaParser::Mockup_module_bodyContext* context) {
    std::vector<ast::ASTSome*> elements;
    for (const auto mockup_module_element_ctx : context->mockup()) {
      const auto ast_result =
          any_to_ast_some(_visitContext(mockup_module_element_ctx));
      elements.push_back(ast_result);
    }
    for (const auto element : elements) {
      const auto give_node = new ast::GiveNode();
      // give_node->start_line = element->start_line;
      // give_node->start_column = element->start_column;
      // give_node->end_line = element->end_line;
      // give_node->end_column = element->end_column;
      const auto give_element_node = new ast::GiveElementNode();
      // give_element_node->start_line = element->start_line;
      // give_element_node->start_column = element->start_column;
      // give_element_node->end_line = element->end_line;
      // give_element_node->end_column = element->end_column;

      if (element->MockupDiiaNode) {
        if (!element->MockupDiiaNode->structure.empty()) {
          continue;
        }
        give_element_node->name = element->MockupDiiaNode->name;
        give_node->elements.push_back(give_element_node);
        elements.push_back(ast::make_ast_some(give_node));
      }
      if (element->MockupModuleNode) {
        give_element_node->name = element->MockupModuleNode->name;
        give_node->elements.push_back(give_element_node);
        elements.push_back(ast::make_ast_some(give_node));
      }
      if (element->MockupSubjectNode) {
        give_element_node->name = element->MockupSubjectNode->name;
        give_node->elements.push_back(give_element_node);
        elements.push_back(ast::make_ast_some(give_node));
      }
      if (element->MockupStructureNode) {
        give_element_node->name = element->MockupStructureNode->name;
        give_node->elements.push_back(give_element_node);
        elements.push_back(ast::make_ast_some(give_node));
      }
    }
    return elements;
  }

  std::any MavkaASTVisitor::visitMockup_structure_body(
      MavkaParser::Mockup_structure_bodyContext* context) {
    std::vector<ast::ASTSome*> elements;
    for (const auto mockup_structure_element :
         context->mockup_structure_body_element()) {
      const auto ast_result = any_to_ast_some(
          visitMockup_structure_body_element(mockup_structure_element));
      elements.push_back(ast_result);
    }
    return elements;
  }

  std::any MavkaASTVisitor::visitMockup_structure_body_element(
      MavkaParser::Mockup_structure_body_elementContext* context) {
    if (context->structure_param()) {
      return visitStructure_param(context->structure_param());
    }
    if (context->method_declaration()) {
      return visitMethod_declaration(context->method_declaration());
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitMockup_diia(
      MavkaParser::Mockup_diiaContext* context) {
    const auto mockup_diia_node = new ast::MockupDiiaNode();
    mockup_diia_node->start_line = context->getStart()->getLine();
    mockup_diia_node->start_column =
        context->getStart()->getCharPositionInLine();
    mockup_diia_node->end_line = context->getStop()->getLine();
    mockup_diia_node->end_column = context->getStop()->getCharPositionInLine();
    mockup_diia_node->ee = context->md_static != nullptr;
    mockup_diia_node->async = context->md_async != nullptr;
    mockup_diia_node->name = context->md_name->getText();
    if (context->md_structure) {
      mockup_diia_node->structure = context->md_structure->getText();
    }
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
          std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
              visitType_value(context->md_type));
    }
    return (ast::make_ast_some(mockup_diia_node));
  }

  std::any MavkaASTVisitor::visitMockup_subject(
      MavkaParser::Mockup_subjectContext* context) {
    const auto mockup_subject_node = new ast::MockupSubjectNode();
    mockup_subject_node->start_line = context->getStart()->getLine();
    mockup_subject_node->start_column =
        context->getStart()->getCharPositionInLine();
    mockup_subject_node->end_line = context->getStop()->getLine();
    mockup_subject_node->end_column =
        context->getStop()->getCharPositionInLine();
    mockup_subject_node->name = context->ms_name->getText();
    mockup_subject_node->types =
        std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
            visitType_value(context->ms_type));
    return (ast::make_ast_some(mockup_subject_node));
  }

  std::any MavkaASTVisitor::visitDiia(MavkaParser::DiiaContext* context) {
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
      diia_node->return_types =
          std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
              visitType_value(context->d_type));
    }
    if (context->d_body) {
      diia_node->body = std::any_cast<std::vector<ast::ASTSome*>>(
          _visitDiiaBody(context->d_body));
    }
    return (ast::make_ast_some(diia_node));
  }

  std::any MavkaASTVisitor::visitIf(MavkaParser::IfContext* context) {
    const auto if_node = new ast::IfNode();
    if_node->start_line = context->getStart()->getLine();
    if_node->start_column = context->getStart()->getCharPositionInLine();
    if_node->end_line = context->getStop()->getLine();
    if_node->end_column = context->getStop()->getCharPositionInLine();
    if_node->condition = any_to_ast_some(_visitContext(context->i_value));
    if (context->i_body) {
      if_node->body =
          std::any_cast<std::vector<ast::ASTSome*>>(visitBody(context->i_body));
    }
    if (context->i_else_if) {
      const auto else_if = any_to_ast_some(visitIf(context->i_else_if));
      if_node->else_body.push_back(else_if);
    } else if (context->i_else_body) {
      if_node->else_body = std::any_cast<std::vector<ast::ASTSome*>>(
          visitBody(context->i_else_body));
    }
    return (ast::make_ast_some(if_node));
  }

  std::any MavkaASTVisitor::visitEach(MavkaParser::EachContext* context) {
    const auto each_node = new ast::EachNode();
    each_node->start_line = context->getStart()->getLine();
    each_node->start_column = context->getStart()->getCharPositionInLine();
    each_node->end_line = context->getStop()->getLine();
    each_node->end_column = context->getStop()->getCharPositionInLine();
    if (context->e_iterator) {
      each_node->value = any_to_ast_some(_visitContext(context->e_iterator));
    }
    if (context->e_fromto) {
      each_node->value = any_to_ast_some(visitFromto(context->e_fromto));
    }
    each_node->keyName =
        context->e_key_name ? context->e_key_name->getText() : "";
    each_node->name = context->e_name->getText();
    if (context->e_body) {
      each_node->body =
          std::any_cast<std::vector<ast::ASTSome*>>(visitBody(context->e_body));
    }
    return (ast::make_ast_some(each_node));
  }

  std::any MavkaASTVisitor::visitFromto(MavkaParser::FromtoContext* context) {
    if (context->fromto_simple()) {
      return visitFromto_simple(context->fromto_simple());
    }
    if (context->fromto_complex()) {
      return visitFromto_complex(context->fromto_complex());
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitFromto_simple(
      MavkaParser::Fromto_simpleContext* context) {
    const auto fromto_simple_node = new ast::FromToSimpleNode();
    fromto_simple_node->start_line = context->getStart()->getLine();
    fromto_simple_node->start_column =
        context->getStart()->getCharPositionInLine();
    fromto_simple_node->end_line = context->getStop()->getLine();
    fromto_simple_node->end_column =
        context->getStop()->getCharPositionInLine();
    fromto_simple_node->from =
        any_to_ast_some(visitFromto_value(context->fs_from));
    fromto_simple_node->to = any_to_ast_some(visitFromto_value(context->fs_to));
    fromto_simple_node->toSymbol =
        context->fs_to_symbol ? context->fs_to_symbol->getText() : "<=";
    return (ast::make_ast_some(fromto_simple_node));
  }

  std::any MavkaASTVisitor::visitFromto_complex(
      MavkaParser::Fromto_complexContext* context) {
    const auto fromto_complex_node = new ast::FromToComplexNode();
    fromto_complex_node->start_line = context->getStart()->getLine();
    fromto_complex_node->start_column =
        context->getStart()->getCharPositionInLine();
    fromto_complex_node->end_line = context->getStop()->getLine();
    fromto_complex_node->end_column =
        context->getStop()->getCharPositionInLine();
    fromto_complex_node->from =
        any_to_ast_some(visitFromto_value(context->fc_from));
    fromto_complex_node->to =
        any_to_ast_some(visitFromto_value(context->fc_to));
    fromto_complex_node->toSymbol =
        context->fc_to_symbol ? context->fc_to_symbol->getText() : "<=";
    fromto_complex_node->step =
        any_to_ast_some(visitFromto_value(context->fc_middle));
    fromto_complex_node->stepSymbol =
        context->fc_middle_symbol ? context->fc_middle_symbol->getText() : "+";
    return (ast::make_ast_some(fromto_complex_node));
  }

  std::any MavkaASTVisitor::visitFromto_value(
      MavkaParser::Fromto_valueContext* context) {
    if (jejalyk::tools::instance_of<MavkaParser::Fromto_numberContext>(
            context)) {
      const auto number_node = new ast::NumberNode();
      number_node->start_line = context->getStart()->getLine();
      number_node->start_column = context->getStart()->getCharPositionInLine();
      number_node->end_line = context->getStop()->getLine();
      number_node->end_column = context->getStop()->getCharPositionInLine();
      number_node->value = process_number(
          dynamic_cast<MavkaParser::Fromto_numberContext*>(context)
              ->NUMBER()
              ->getText());
      return (ast::make_ast_some(number_node));
    }
    if (jejalyk::tools::instance_of<MavkaParser::Fromto_stringContext>(
            context)) {
      const auto string_node = new ast::StringNode();
      string_node->start_line = context->getStart()->getLine();
      string_node->start_column = context->getStart()->getCharPositionInLine();
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
      return (ast::make_ast_some(string_node));
    }
    if (jejalyk::tools::instance_of<MavkaParser::Fromto_idContext>(context)) {
      return visitIdentifier(
          dynamic_cast<MavkaParser::Fromto_idContext*>(context)->identifier());
    }
    if (jejalyk::tools::instance_of<MavkaParser::Fromto_nestedContext>(
            context)) {
      return _visitContext(
          dynamic_cast<MavkaParser::Fromto_nestedContext*>(context)->fn_value);
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitWhile(MavkaParser::WhileContext* context) {
    const auto while_node = new ast::WhileNode();
    while_node->start_line = context->getStart()->getLine();
    while_node->start_column = context->getStart()->getCharPositionInLine();
    while_node->end_line = context->getStop()->getLine();
    while_node->end_column = context->getStop()->getCharPositionInLine();
    while_node->condition = any_to_ast_some(_visitContext(context->w_value));
    if (context->w_body) {
      while_node->body =
          std::any_cast<std::vector<ast::ASTSome*>>(visitBody(context->w_body));
    }
    return (ast::make_ast_some(while_node));
  }

  std::any MavkaASTVisitor::visitTry(MavkaParser::TryContext* context) {
    const auto try_node = new ast::TryNode();
    try_node->start_line = context->getStart()->getLine();
    try_node->start_column = context->getStart()->getCharPositionInLine();
    try_node->end_line = context->getStop()->getLine();
    try_node->end_column = context->getStop()->getCharPositionInLine();
    try_node->body =
        std::any_cast<std::vector<ast::ASTSome*>>(visitBody(context->t_body));
    try_node->name = context->tc_name->getText();
    try_node->catch_body =
        std::any_cast<std::vector<ast::ASTSome*>>(visitBody(context->tc_body));
    return (ast::make_ast_some(try_node));
  }

  std::any MavkaASTVisitor::_visitContext(antlr4::ParserRuleContext* context) {
    if (jejalyk::tools::instance_of<MavkaParser::NumberContext>(context)) {
      return visitNumber(dynamic_cast<MavkaParser::NumberContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::Value_atomContext>(context)) {
      return visitValue_atom(
          dynamic_cast<MavkaParser::Value_atomContext*>(context));
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
    // if
    // (jejalyk::tools::instance_of<MavkaParser::Call_with_genericsContext>(
    //         context)) {
    //   return visitCall_with_generics(
    //       dynamic_cast<MavkaParser::Call_with_genericsContext*>(context));
    // }
    // if (jejalyk::tools::instance_of<
    //         MavkaParser::Atom_call_with_genericsContext>(context)) {
    //   return visitAtom_call_with_generics(
    //       dynamic_cast<MavkaParser::Atom_call_with_genericsContext*>(
    //           context));
    // }
    if (jejalyk::tools::instance_of<MavkaParser::CallContext>(context)) {
      return visitCall(dynamic_cast<MavkaParser::CallContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::Get_elementContext>(context)) {
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
    if (jejalyk::tools::instance_of<MavkaParser::Bitwise_notContext>(context)) {
      return visitBitwise_not(
          dynamic_cast<MavkaParser::Bitwise_notContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::NestedContext>(context)) {
      return visitNested(dynamic_cast<MavkaParser::NestedContext*>(context));
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
      return visitBitwise(dynamic_cast<MavkaParser::BitwiseContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::ComparisonContext>(context)) {
      return visitComparison(
          dynamic_cast<MavkaParser::ComparisonContext*>(context));
    }
    if (jejalyk::tools::instance_of<
            MavkaParser::Comp_inst_block_programContext>(context)) {
      return visitComp_inst_block_program(
          dynamic_cast<MavkaParser::Comp_inst_block_programContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::Comp_inst_assignContext>(
            context)) {
      return visitComp_inst_assign(
          dynamic_cast<MavkaParser::Comp_inst_assignContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::TestContext>(context)) {
      return visitTest(dynamic_cast<MavkaParser::TestContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::TernaryContext>(context)) {
      return visitTernary(dynamic_cast<MavkaParser::TernaryContext*>(context));
    }
    // if (jejalyk::tools::instance_of<MavkaParser::ArrayContext>(context)) {
    //   return visitArray(dynamic_cast<MavkaParser::ArrayContext*>(context));
    // }
    if (jejalyk::tools::instance_of<MavkaParser::Typeless_arrayContext>(
            context)) {
      return visitTypeless_array(
          dynamic_cast<MavkaParser::Typeless_arrayContext*>(context));
    }
    // if (jejalyk::tools::instance_of<MavkaParser::DictionaryContext>(
    //         context)) {
    //   return visitDictionary(
    //       dynamic_cast<MavkaParser::DictionaryContext*>(context));
    // }
    if (jejalyk::tools::instance_of<MavkaParser::Typeless_dictionaryContext>(
            context)) {
      return visitTypeless_dictionary(
          dynamic_cast<MavkaParser::Typeless_dictionaryContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::GodContext>(context)) {
      return visitGod(dynamic_cast<MavkaParser::GodContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::Call_parentContext>(context)) {
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
      identifier_node->end_column = context->getStop()->getCharPositionInLine();
      identifier_node->name = "предок";
      chain_node->left = ast::make_ast_some(identifier_node);
      chain_node->right =
          any_to_ast_some(visitIdentifier(call_parent_context->cp_id));
      call_node->value = ast::make_ast_some(chain_node);
      if (call_parent_context->cp_args) {
        call_node->args = std::any_cast<std::vector<ast::ArgNode*>>(
            visitArgs(call_parent_context->cp_args));
      }
      if (call_parent_context->cp_named_args) {
        call_node->args = std::any_cast<std::vector<ast::ArgNode*>>(
            visitNamed_args(call_parent_context->cp_named_args));
      }
      return (ast::make_ast_some(call_node));
    }
    if (jejalyk::tools::instance_of<MavkaParser::SimpleContext>(context)) {
      const auto simple_context =
          dynamic_cast<MavkaParser::SimpleContext*>(context);
      return _visitContext(simple_context->value());
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
    if (jejalyk::tools::instance_of<MavkaParser::Expr_mmlContext>(context)) {
      const auto expr_mml_context =
          dynamic_cast<MavkaParser::Expr_mmlContext*>(context);
      const auto mml_text = expr_mml_context->MML()->getText();
      const auto mml_node = new ast::MMLNode();
      mml_node->start_line = context->getStart()->getLine();
      mml_node->start_column = context->getStart()->getCharPositionInLine();
      mml_node->end_line = context->getStop()->getLine();
      mml_node->end_column = context->getStop()->getCharPositionInLine();
      mml_node->text = mml_text;
      return (ast::make_ast_some(mml_node));
    }
    if (jejalyk::tools::instance_of<MavkaParser::MockupContext>(context)) {
      const auto mockup_context =
          dynamic_cast<MavkaParser::MockupContext*>(context);
      return visitMockup(mockup_context);
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitValue_atom(
      MavkaParser::Value_atomContext* context) {
    return _visitContext(context->atom());
  }

  std::any MavkaASTVisitor::visitNumber(MavkaParser::NumberContext* context) {
    const auto number_node = new ast::NumberNode();
    number_node->start_line = context->getStart()->getLine();
    number_node->start_column = context->getStart()->getCharPositionInLine();
    number_node->end_line = context->getStop()->getLine();
    number_node->end_column = context->getStop()->getCharPositionInLine();
    number_node->value = process_number(context->getText());
    return (ast::make_ast_some(number_node));
  }

  std::any MavkaASTVisitor::visitString_value(
      MavkaParser::String_valueContext* context) {
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
    return (ast::make_ast_some(string_node));
  }

  std::any MavkaASTVisitor::visitId(MavkaParser::IdContext* context) {
    const auto identifier_node = new ast::IdentifierNode();
    identifier_node->start_line = context->getStart()->getLine();
    identifier_node->start_column =
        context->getStart()->getCharPositionInLine();
    identifier_node->end_line = context->getStop()->getLine();
    identifier_node->end_column = context->getStop()->getCharPositionInLine();
    identifier_node->name = context->getText();
    return (ast::make_ast_some(identifier_node));
  }

  std::any MavkaASTVisitor::visitIdentifier(
      MavkaParser::IdentifierContext* context) {
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
    return (ast::make_ast_some(identifier_node));
  }

  std::any MavkaASTVisitor::visitChain(MavkaParser::ChainContext* context) {
    const auto chain_node = new ast::ChainNode();
    chain_node->start_line = context->getStart()->getLine();
    chain_node->start_column = context->getStart()->getCharPositionInLine();
    chain_node->end_line = context->getStop()->getLine();
    chain_node->end_column = context->getStop()->getCharPositionInLine();
    chain_node->left = any_to_ast_some(_visitContext(context->c_left));
    chain_node->right = any_to_ast_some(visitIdentifier(context->c_right));
    return (ast::make_ast_some(chain_node));
  }

  std::any MavkaASTVisitor::visitCall(MavkaParser::CallContext* context) {
    const auto call_node = new ast::CallNode();
    call_node->start_line = context->getStart()->getLine();
    call_node->start_column = context->getStart()->getCharPositionInLine();
    call_node->end_line = context->getStop()->getLine();
    call_node->end_column = context->getStop()->getCharPositionInLine();
    call_node->value = any_to_ast_some(_visitContext(context->c_value));
    if (context->call_generics()) {
      call_node->generics =
          std::any_cast<std::vector<std::vector<ast::TypeValueSingleNode*>>>(
              visitCall_generics(context->call_generics()));
    }
    if (context->c_args) {
      call_node->args =
          std::any_cast<std::vector<ast::ArgNode*>>(visitArgs(context->c_args));
    }
    if (context->c_named_args) {
      call_node->args = std::any_cast<std::vector<ast::ArgNode*>>(
          visitNamed_args(context->c_named_args));
    }
    return (ast::make_ast_some(call_node));
  }

  std::any MavkaASTVisitor::visitCall_generics(
      MavkaParser::Call_genericsContext* context) {
    std::vector<std::vector<ast::TypeValueSingleNode*>> generics;
    for (const auto type_value_node : context->type_value()) {
      const auto type_value_result = visitType_value(type_value_node);
      generics.push_back(std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
          type_value_result));
    }
    return generics;
  }

  std::any MavkaASTVisitor::visitGet_element(
      MavkaParser::Get_elementContext* context) {
    const auto get_element_node = new ast::GetElementNode();
    get_element_node->start_line = context->getStart()->getLine();
    get_element_node->start_column =
        context->getStart()->getCharPositionInLine();
    get_element_node->end_line = context->getStop()->getLine();
    get_element_node->end_column = context->getStop()->getCharPositionInLine();
    get_element_node->value = any_to_ast_some(_visitContext(context->ge_left));
    get_element_node->index =
        any_to_ast_some(_visitContext(context->ge_element));
    return (ast::make_ast_some(get_element_node));
  }

  std::any MavkaASTVisitor::visitPositive(
      MavkaParser::PositiveContext* context) {
    const auto positive_node = new ast::PositiveNode();
    positive_node->start_line = context->getStart()->getLine();
    positive_node->start_column = context->getStart()->getCharPositionInLine();
    positive_node->end_line = context->getStop()->getLine();
    positive_node->end_column = context->getStop()->getCharPositionInLine();
    positive_node->value = any_to_ast_some(_visitContext(context->p_value));
    return (ast::make_ast_some(positive_node));
  }

  std::any MavkaASTVisitor::visitNegative(
      MavkaParser::NegativeContext* context) {
    const auto negative_node = new ast::NegativeNode();
    negative_node->start_line = context->getStart()->getLine();
    negative_node->start_column = context->getStart()->getCharPositionInLine();
    negative_node->end_line = context->getStop()->getLine();
    negative_node->end_column = context->getStop()->getCharPositionInLine();
    negative_node->value = any_to_ast_some(_visitContext(context->n_value));
    return (ast::make_ast_some(negative_node));
  }

  std::any MavkaASTVisitor::visitPre_decrement(
      MavkaParser::Pre_decrementContext* context) {
    const auto pre_decrement_node = new ast::PreDecrementNode();
    pre_decrement_node->start_line = context->getStart()->getLine();
    pre_decrement_node->start_column =
        context->getStart()->getCharPositionInLine();
    pre_decrement_node->end_line = context->getStop()->getLine();
    pre_decrement_node->end_column =
        context->getStop()->getCharPositionInLine();
    pre_decrement_node->value =
        any_to_ast_some(_visitContext(context->pd_value));
    return (ast::make_ast_some(pre_decrement_node));
  }

  std::any MavkaASTVisitor::visitPre_increment(
      MavkaParser::Pre_incrementContext* context) {
    const auto pre_increment_node = new ast::PreIncrementNode();
    pre_increment_node->start_line = context->getStart()->getLine();
    pre_increment_node->start_column =
        context->getStart()->getCharPositionInLine();
    pre_increment_node->end_line = context->getStop()->getLine();
    pre_increment_node->end_column =
        context->getStop()->getCharPositionInLine();
    pre_increment_node->value =
        any_to_ast_some(_visitContext(context->pi_value));
    return (ast::make_ast_some(pre_increment_node));
  }

  std::any MavkaASTVisitor::visitPost_decrement(
      MavkaParser::Post_decrementContext* context) {
    const auto post_decrement_node = new ast::PostDecrementNode();
    post_decrement_node->start_line = context->getStart()->getLine();
    post_decrement_node->start_column =
        context->getStart()->getCharPositionInLine();
    post_decrement_node->end_line = context->getStop()->getLine();
    post_decrement_node->end_column =
        context->getStop()->getCharPositionInLine();
    post_decrement_node->value =
        any_to_ast_some(_visitContext(context->pd_value));
    return (ast::make_ast_some(post_decrement_node));
  }

  std::any MavkaASTVisitor::visitPost_increment(
      MavkaParser::Post_incrementContext* context) {
    const auto post_increment_node = new ast::PostIncrementNode();
    post_increment_node->start_line = context->getStart()->getLine();
    post_increment_node->start_column =
        context->getStart()->getCharPositionInLine();
    post_increment_node->end_line = context->getStop()->getLine();
    post_increment_node->end_column =
        context->getStop()->getCharPositionInLine();
    post_increment_node->value =
        any_to_ast_some(_visitContext(context->pi_value));
    return (ast::make_ast_some(post_increment_node));
  }

  std::any MavkaASTVisitor::visitNot(MavkaParser::NotContext* context) {
    const auto not_node = new ast::NotNode();
    not_node->start_line = context->getStart()->getLine();
    not_node->start_column = context->getStart()->getCharPositionInLine();
    not_node->end_line = context->getStop()->getLine();
    not_node->end_column = context->getStop()->getCharPositionInLine();
    not_node->value = any_to_ast_some(_visitContext(context->n_value));
    return (ast::make_ast_some(not_node));
  }

  std::any MavkaASTVisitor::visitBitwise_not(
      MavkaParser::Bitwise_notContext* context) {
    const auto bitwise_not_node = new ast::BitwiseNotNode();
    bitwise_not_node->start_line = context->getStart()->getLine();
    bitwise_not_node->start_column =
        context->getStart()->getCharPositionInLine();
    bitwise_not_node->end_line = context->getStop()->getLine();
    bitwise_not_node->end_column = context->getStop()->getCharPositionInLine();
    bitwise_not_node->value = any_to_ast_some(_visitContext(context->bn_value));
    return (ast::make_ast_some(bitwise_not_node));
  }

  std::any MavkaASTVisitor::visitNested(MavkaParser::NestedContext* context) {
    return _visitContext(context->n_value);
  }

  std::any MavkaASTVisitor::visitAs(MavkaParser::AsContext* context) {
    const auto as_node = new ast::AsNode();
    as_node->start_line = context->getStart()->getLine();
    as_node->start_column = context->getStart()->getCharPositionInLine();
    as_node->end_line = context->getStop()->getLine();
    as_node->end_column = context->getStop()->getCharPositionInLine();
    as_node->left = any_to_ast_some(_visitContext(context->a_left));
    as_node->right = any_to_ast_some(_visitContext(context->a_right));
    return (ast::make_ast_some(as_node));
  }

  std::any MavkaASTVisitor::visitArithmetic_mul(
      MavkaParser::Arithmetic_mulContext* context) {
    const auto arithmetic_node = new ast::ArithmeticNode();
    arithmetic_node->start_line = context->getStart()->getLine();
    arithmetic_node->start_column =
        context->getStart()->getCharPositionInLine();
    arithmetic_node->end_line = context->getStop()->getLine();
    arithmetic_node->end_column = context->getStop()->getCharPositionInLine();
    arithmetic_node->left = any_to_ast_some(_visitContext(context->a_left));
    arithmetic_node->right = any_to_ast_some(_visitContext(context->a_right));
    arithmetic_node->op = context->a_operation->getText();
    return (ast::make_ast_some(arithmetic_node));
  }

  std::any MavkaASTVisitor::visitArithmetic_op_mul(
      MavkaParser::Arithmetic_op_mulContext* context) {
    return context->getText();
  }

  std::any MavkaASTVisitor::visitArithmetic_add(
      MavkaParser::Arithmetic_addContext* context) {
    const auto arithmetic_node = new ast::ArithmeticNode();
    arithmetic_node->start_line = context->getStart()->getLine();
    arithmetic_node->start_column =
        context->getStart()->getCharPositionInLine();
    arithmetic_node->end_line = context->getStop()->getLine();
    arithmetic_node->end_column = context->getStop()->getCharPositionInLine();
    arithmetic_node->left = any_to_ast_some(_visitContext(context->a_left));
    arithmetic_node->right = any_to_ast_some(_visitContext(context->a_right));
    arithmetic_node->op = context->a_operation->getText();
    return (ast::make_ast_some(arithmetic_node));
  }

  std::any MavkaASTVisitor::visitArithmetic_op_add(
      MavkaParser::Arithmetic_op_addContext* context) {
    return context->getText();
  }

  std::any MavkaASTVisitor::visitBitwise(MavkaParser::BitwiseContext* context) {
    const auto bitwise_node = new ast::BitwiseNode();
    bitwise_node->start_line = context->getStart()->getLine();
    bitwise_node->start_column = context->getStart()->getCharPositionInLine();
    bitwise_node->end_line = context->getStop()->getLine();
    bitwise_node->end_column = context->getStop()->getCharPositionInLine();
    bitwise_node->left = any_to_ast_some(_visitContext(context->b_left));
    bitwise_node->right = any_to_ast_some(_visitContext(context->b_right));
    bitwise_node->op = context->b_operation->getText();
    return (ast::make_ast_some(bitwise_node));
  }

  std::any MavkaASTVisitor::visitBitwise_op(
      MavkaParser::Bitwise_opContext* context) {
    return context->getText();
  }

  std::any MavkaASTVisitor::visitComparison(
      MavkaParser::ComparisonContext* context) {
    const auto comparison_node = new ast::ComparisonNode();
    comparison_node->start_line = context->getStart()->getLine();
    comparison_node->start_column =
        context->getStart()->getCharPositionInLine();
    comparison_node->end_line = context->getStop()->getLine();
    comparison_node->end_column = context->getStop()->getCharPositionInLine();
    comparison_node->left = any_to_ast_some(_visitContext(context->c_left));
    comparison_node->right = any_to_ast_some(_visitContext(context->c_right));
    comparison_node->op = context->c_operation->getText();
    return (ast::make_ast_some(comparison_node));
  }

  std::any MavkaASTVisitor::visitComp_inst_block_program(
      MavkaParser::Comp_inst_block_programContext* context) {
    const auto comp_inst_block_program_node =
        new ast::CompInstBlockProgramNode();
    comp_inst_block_program_node->start_line = context->getStart()->getLine();
    comp_inst_block_program_node->start_column =
        context->getStart()->getCharPositionInLine();
    comp_inst_block_program_node->end_line = context->getStop()->getLine();
    comp_inst_block_program_node->end_column =
        context->getStop()->getCharPositionInLine();
    comp_inst_block_program_node->name = context->cibp_name->getText();
    comp_inst_block_program_node->value = context->cibp_value->getText().substr(
        1, context->cibp_value->getText().length() - 2);
    if (context->cibp_program) {
      const auto program_node =
          any_to_ast_some(visitProgram(context->cibp_program))->ProgramNode;
      comp_inst_block_program_node->body = program_node->body;
    }
    return (ast::make_ast_some(comp_inst_block_program_node));
  }

  std::any MavkaASTVisitor::visitComp_inst_assign(
      MavkaParser::Comp_inst_assignContext* context) {
    const auto comp_inst_assign_node = new ast::CompInstAssignNode();
    comp_inst_assign_node->start_line = context->getStart()->getLine();
    comp_inst_assign_node->start_column =
        context->getStart()->getCharPositionInLine();
    comp_inst_assign_node->end_line = context->getStop()->getLine();
    comp_inst_assign_node->end_column =
        context->getStop()->getCharPositionInLine();
    comp_inst_assign_node->name = context->cia_name->getText();
    comp_inst_assign_node->value = context->cia_value->getText().substr(
        1, context->cia_value->getText().length() - 2);
    return (ast::make_ast_some(comp_inst_assign_node));
  }

  std::any MavkaASTVisitor::visitTest(MavkaParser::TestContext* context) {
    const auto test_node = new ast::TestNode();
    test_node->start_line = context->getStart()->getLine();
    test_node->start_column = context->getStart()->getCharPositionInLine();
    test_node->end_line = context->getStop()->getLine();
    test_node->end_column = context->getStop()->getCharPositionInLine();
    test_node->left = any_to_ast_some(_visitContext(context->t_left));
    test_node->right = any_to_ast_some(_visitContext(context->t_right));
    test_node->op = context->t_operation->getText();
    return (ast::make_ast_some(test_node));
  }

  std::any MavkaASTVisitor::visitTernary(MavkaParser::TernaryContext* context) {
    const auto ternary_node = new ast::TernaryNode();
    ternary_node->start_line = context->getStart()->getLine();
    ternary_node->start_column = context->getStart()->getCharPositionInLine();
    ternary_node->end_line = context->getStop()->getLine();
    ternary_node->end_column = context->getStop()->getCharPositionInLine();
    ternary_node->condition = any_to_ast_some(_visitContext(context->t_value));
    std::vector<ast::ASTSome*> body;
    if (context->t_positive) {
      ternary_node->body = any_to_ast_some(_visitContext(context->t_positive));
    }
    if (context->t_negative) {
      ternary_node->else_body =
          any_to_ast_some(_visitContext(context->t_negative));
    }
    return (ast::make_ast_some(ternary_node));
  }

  std::any MavkaASTVisitor::visitTypeless_array(
      MavkaParser::Typeless_arrayContext* context) {
    const auto array_node = new ast::ArrayNode();
    array_node->start_line = context->getStart()->getLine();
    array_node->start_column = context->getStart()->getCharPositionInLine();
    array_node->end_line = context->getStop()->getLine();
    array_node->end_column = context->getStop()->getCharPositionInLine();
    if (context->a_elements) {
      array_node->elements = std::any_cast<std::vector<ast::ASTSome*>>(
          visitArray_elements(context->a_elements));
    }
    return (ast::make_ast_some(array_node));
  }

  std::any MavkaASTVisitor::visitArray_elements(
      MavkaParser::Array_elementsContext* context) {
    std::vector<ast::ASTSome*> elements;
    for (const auto array_element : context->array_element()) {
      const auto ast_result =
          any_to_ast_some(visitArray_element(array_element));
      elements.push_back(ast_result);
    }
    return elements;
  }

  std::any MavkaASTVisitor::visitArray_element(
      MavkaParser::Array_elementContext* context) {
    return _visitContext(context->ae_value);
  }

  std::any MavkaASTVisitor::visitTypeless_dictionary(
      MavkaParser::Typeless_dictionaryContext* context) {
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
    return (ast::make_ast_some(dictionary_node));
  }

  std::any MavkaASTVisitor::visitDictionary_args(
      MavkaParser::Dictionary_argsContext* context) {
    std::vector<ast::DictionaryElementNode*> elements;
    for (const auto dictionary_arg : context->dictionary_arg()) {
      const auto value =
          any_to_ast_some(_visitContext(dictionary_arg->da_value));
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
        const auto string_node = new ast::StringNode();
        string_node->start_line =
            dictionary_arg->da_name_id->getStart()->getLine();
        string_node->start_column =
            dictionary_arg->da_name_id->getStart()->getCharPositionInLine();
        string_node->end_line =
            dictionary_arg->da_name_id->getStop()->getLine();
        string_node->end_column =
            dictionary_arg->da_name_id->getStop()->getCharPositionInLine();
        string_node->value = dictionary_arg->da_name_id->getText();
        dictionary_element_node->key = ast::make_ast_some(string_node);
        dictionary_element_node->value = value;
        elements.push_back(dictionary_element_node);
      } else if (dictionary_arg->da_name_string) {
        const auto name_string = dictionary_arg->da_name_string->getText();
        if (name_string.starts_with(R"(""")")) {
          const auto dictionary_element_node = new ast::DictionaryElementNode();
          dictionary_element_node->start_line =
              dictionary_arg->getStart()->getLine();
          dictionary_element_node->start_column =
              dictionary_arg->getStart()->getCharPositionInLine();
          dictionary_element_node->end_line =
              dictionary_arg->getStop()->getLine();
          dictionary_element_node->end_column =
              dictionary_arg->getStop()->getCharPositionInLine();
          const auto string_node = new ast::StringNode();
          string_node->start_line = dictionary_arg->getStart()->getLine();
          string_node->start_column =
              dictionary_arg->getStart()->getCharPositionInLine();
          string_node->end_line = dictionary_arg->getStop()->getLine();
          string_node->end_column =
              dictionary_arg->getStop()->getCharPositionInLine();
          string_node->value = name_string.substr(3, name_string.length() - 6);
          dictionary_element_node->key = ast::make_ast_some(string_node);
          dictionary_element_node->value = value;
          elements.push_back(dictionary_element_node);
        } else {
          const auto dictionary_element_node = new ast::DictionaryElementNode();
          dictionary_element_node->start_line =
              dictionary_arg->getStart()->getLine();
          dictionary_element_node->start_column =
              dictionary_arg->getStart()->getCharPositionInLine();
          dictionary_element_node->end_line =
              dictionary_arg->getStop()->getLine();
          dictionary_element_node->end_column =
              dictionary_arg->getStop()->getCharPositionInLine();
          const auto string_node = new ast::StringNode();
          string_node->start_line = dictionary_arg->getStart()->getLine();
          string_node->start_column =
              dictionary_arg->getStart()->getCharPositionInLine();
          string_node->end_line = dictionary_arg->getStop()->getLine();
          string_node->end_column =
              dictionary_arg->getStop()->getCharPositionInLine();
          string_node->value = name_string.substr(1, name_string.length() - 2);
          dictionary_element_node->key = ast::make_ast_some(string_node);
          dictionary_element_node->value = value;
          elements.push_back(dictionary_element_node);
        }
      }
    }
    return elements;
  }

  std::any MavkaASTVisitor::visitGod(MavkaParser::GodContext* context) {
    const auto god_node = new ast::GodNode();
    god_node->start_line = context->getStart()->getLine();
    god_node->start_column = context->getStart()->getCharPositionInLine();
    god_node->end_line = context->getStop()->getLine();
    god_node->end_column = context->getStop()->getCharPositionInLine();
    std::vector<ast::ASTSome*> elements;
    for (const auto value : context->atom()) {
      const auto value_node = any_to_ast_some(_visitContext(value));
      elements.push_back(value_node);
    }
    god_node->elements = elements;
    return (ast::make_ast_some(god_node));
  }

  std::any MavkaASTVisitor::visitWait(MavkaParser::WaitContext* context) {
    const auto wait_node = new ast::WaitNode();
    wait_node->start_line = context->getStart()->getLine();
    wait_node->start_column = context->getStart()->getCharPositionInLine();
    wait_node->end_line = context->getStop()->getLine();
    wait_node->end_column = context->getStop()->getCharPositionInLine();
    wait_node->value = any_to_ast_some(_visitContext(context->w_value));
    return (ast::make_ast_some(wait_node));
  }

  std::any MavkaASTVisitor::visitFunction(
      MavkaParser::FunctionContext* context) {
    const auto function_node = new ast::FunctionNode();
    function_node->start_line = context->getStart()->getLine();
    function_node->start_column = context->getStart()->getCharPositionInLine();
    function_node->end_line = context->getStop()->getLine();
    function_node->end_column = context->getStop()->getCharPositionInLine();
    function_node->async = context->f_async != nullptr;
    if (context->f_params) {
      function_node->params = std::any_cast<std::vector<ast::ParamNode*>>(
          visitParams(context->f_params));
    }
    if (context->f_type) {
      function_node->return_types =
          std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
              visitType_value(context->f_type));
    }
    if (context->f_body) {
      const auto function_node_body =
          any_to_ast_some(_visitContext(context->f_body));
      const auto return_node = new ast::ReturnNode();
      // return_node->start_line = function_node_body->start_line;
      // return_node->start_column = function_node_body->start_column;
      // return_node->end_line = function_node_body->end_line;
      // return_node->end_column = function_node_body->end_column;
      return_node->value = function_node_body;
      function_node->body.push_back(ast::make_ast_some(return_node));
    }
    return (ast::make_ast_some(function_node));
  }

  std::any MavkaASTVisitor::visitAnonymous_diia(
      MavkaParser::Anonymous_diiaContext* context) {
    const auto anon_diia_node = new ast::AnonDiiaNode();
    anon_diia_node->start_line = context->getStart()->getLine();
    anon_diia_node->start_column = context->getStart()->getCharPositionInLine();
    anon_diia_node->end_line = context->getStop()->getLine();
    anon_diia_node->end_column = context->getStop()->getCharPositionInLine();
    anon_diia_node->async = context->d_async != nullptr;
    if (context->d_generics) {
      anon_diia_node->generics = std::any_cast<std::vector<ast::GenericNode*>>(
          visitGenerics(context->d_generics));
    }
    if (context->d_params) {
      anon_diia_node->params = std::any_cast<std::vector<ast::ParamNode*>>(
          visitParams(context->d_params));
    }
    if (context->d_type) {
      anon_diia_node->return_types =
          std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
              visitType_value(context->d_type));
    }
    if (context->d_body) {
      anon_diia_node->body = std::any_cast<std::vector<ast::ASTSome*>>(
          _visitDiiaBody(context->d_body));
    }
    return (ast::make_ast_some(anon_diia_node));
  }

  std::any MavkaASTVisitor::visitThrow(MavkaParser::ThrowContext* context) {
    const auto throw_node = new ast::ThrowNode();
    throw_node->start_line = context->getStart()->getLine();
    throw_node->start_column = context->getStart()->getCharPositionInLine();
    throw_node->end_line = context->getStop()->getLine();
    throw_node->end_column = context->getStop()->getCharPositionInLine();
    throw_node->value = any_to_ast_some(_visitContext(context->t_value));
    return (ast::make_ast_some(throw_node));
  }

  std::any MavkaASTVisitor::visitEval(MavkaParser::EvalContext* context) {
    const auto eval_node = new ast::EvalNode();
    eval_node->start_line = context->getStart()->getLine();
    eval_node->start_column = context->getStart()->getCharPositionInLine();
    eval_node->end_line = context->getStop()->getLine();
    eval_node->end_column = context->getStop()->getCharPositionInLine();
    if (context->e_value->getText().starts_with(R"(""")")) {
      eval_node->value = context->e_value->getText().substr(
          3, context->e_value->getText().length() - 6);
    } else {
      eval_node->value = context->e_value->getText().substr(
          1, context->e_value->getText().length() - 2);
    }
    return (ast::make_ast_some(eval_node));
  }

  std::any MavkaASTVisitor::visitWait_assign(
      MavkaParser::Wait_assignContext* context) {
    const auto assign_node = any_to_ast_some(visitAssign(context->wa_assign));
    if (assign_node->AssignSimpleNode) {
      const auto assign_simple_node = assign_node->AssignSimpleNode;
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
      new_assign_simple_node->value = ast::make_ast_some(wait_node);
      return (ast::make_ast_some(new_assign_simple_node));
    }
    if (assign_node->AssignByIdentifierNode) {
      const auto assign_by_identifier_node =
          assign_node->AssignByIdentifierNode;
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
      new_assign_by_identifier_node->value = ast::make_ast_some(wait_node);
      return (ast::make_ast_some(new_assign_by_identifier_node));
    }
    if (assign_node->AssignByElementNode) {
      const auto assign_by_element_node = assign_node->AssignByElementNode;
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
      new_assign_by_element_node->value = ast::make_ast_some(wait_node);
      return (ast::make_ast_some(new_assign_by_element_node));
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitAssign(MavkaParser::AssignContext* context) {
    if (context->assign_simple()) {
      return visitAssign_simple(context->assign_simple());
    }
    if (context->assign_by_identifier()) {
      return visitAssign_by_identifier(context->assign_by_identifier());
    }
    if (context->assign_by_element()) {
      return visitAssign_by_element(context->assign_by_element());
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitAssign_simple(
      MavkaParser::Assign_simpleContext* context) {
    const auto assign_simple_node = new ast::AssignSimpleNode();
    assign_simple_node->start_line = context->getStart()->getLine();
    assign_simple_node->start_column =
        context->getStart()->getCharPositionInLine();
    assign_simple_node->end_line = context->getStop()->getLine();
    assign_simple_node->end_column =
        context->getStop()->getCharPositionInLine();
    assign_simple_node->name = context->as_identifier->ID()->getText();
    if (context->as_type) {
      assign_simple_node->types =
          std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
              visitType_value(context->as_type));
    }
    assign_simple_node->op = context->assign_symbol()->getText();
    assign_simple_node->value =
        any_to_ast_some(_visitContext(context->as_value));
    return (ast::make_ast_some(assign_simple_node));
  }

  std::any MavkaASTVisitor::visitAssign_by_identifier(
      MavkaParser::Assign_by_identifierContext* context) {
    const auto assign_by_identifier_node = new ast::AssignByIdentifierNode();
    assign_by_identifier_node->start_line = context->getStart()->getLine();
    assign_by_identifier_node->start_column =
        context->getStart()->getCharPositionInLine();
    assign_by_identifier_node->end_line = context->getStop()->getLine();
    assign_by_identifier_node->end_column =
        context->getStop()->getCharPositionInLine();
    assign_by_identifier_node->left =
        any_to_ast_some(visitSuper_identifiers_chain(context->abi_left));
    assign_by_identifier_node->identifier = context->abi_identifier->getText();
    assign_by_identifier_node->op = context->assign_symbol()->getText();
    assign_by_identifier_node->value =
        any_to_ast_some(_visitContext(context->abi_value));
    return (ast::make_ast_some(assign_by_identifier_node));
  }

  std::any MavkaASTVisitor::visitAssign_by_element(
      MavkaParser::Assign_by_elementContext* context) {
    const auto assign_by_element_node = new ast::AssignByElementNode();
    assign_by_element_node->start_line = context->getStart()->getLine();
    assign_by_element_node->start_column =
        context->getStart()->getCharPositionInLine();
    assign_by_element_node->end_line = context->getStop()->getLine();
    assign_by_element_node->end_column =
        context->getStop()->getCharPositionInLine();
    assign_by_element_node->left =
        any_to_ast_some(visitSuper_identifiers_chain(context->abe_left));
    assign_by_element_node->element =
        any_to_ast_some(_visitContext(context->abe_index));
    assign_by_element_node->op = context->assign_symbol()->getText();
    assign_by_element_node->value =
        any_to_ast_some(_visitContext(context->abe_value));
    return (ast::make_ast_some(assign_by_element_node));
  }

  std::any MavkaASTVisitor::visitAssign_array_destruction(
      MavkaParser::Assign_array_destructionContext* context) {
    // todo
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitAssign_object_destruction(
      MavkaParser::Assign_object_destructionContext* context) {
    // todo
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitAssign_symbol(
      MavkaParser::Assign_symbolContext* context) {
    // todo
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitTake(MavkaParser::TakeContext* context) {
    if (jejalyk::tools::instance_of<MavkaParser::Take_moduleContext>(context)) {
      return visitTake_module(
          dynamic_cast<MavkaParser::Take_moduleContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::Take_fileContext>(context)) {
      return visitTake_file(
          dynamic_cast<MavkaParser::Take_fileContext*>(context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::Take_remoteContext>(context)) {
      return visitTake_remote(
          dynamic_cast<MavkaParser::Take_remoteContext*>(context));
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitTake_module(
      MavkaParser::Take_moduleContext* context) {
    const auto take_module_node = new ast::TakeModuleNode();
    take_module_node->start_line = context->getStart()->getLine();
    take_module_node->start_column =
        context->getStart()->getCharPositionInLine();
    take_module_node->end_line = context->getStop()->getLine();
    take_module_node->end_column = context->getStop()->getCharPositionInLine();
    take_module_node->relative = context->tm_relative != nullptr;
    take_module_node->name = context->tm_elements_chain->getText();
    take_module_node->as = context->tm_as ? context->tm_as->getText() : "";
    return (ast::make_ast_some(take_module_node));
  }

  std::any MavkaASTVisitor::visitTake_file(
      MavkaParser::Take_fileContext* context) {
    // todo
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitTake_remote(
      MavkaParser::Take_remoteContext* context) {
    const auto take_pak_node = new ast::TakePakNode();
    take_pak_node->start_line = context->getStart()->getLine();
    take_pak_node->start_column = context->getStart()->getCharPositionInLine();
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
    return (ast::make_ast_some(take_pak_node));
  }

  std::any MavkaASTVisitor::visitGive(MavkaParser::GiveContext* context) {
    const auto give_node = new ast::GiveNode();
    give_node->start_line = context->getStart()->getLine();
    give_node->start_column = context->getStart()->getCharPositionInLine();
    give_node->end_line = context->getStop()->getLine();
    give_node->end_column = context->getStop()->getCharPositionInLine();
    for (const auto give_element : context->give_element()) {
      const auto ast_result = any_to_ast_some(visitGive_element(give_element));
      const auto give_element_node = ast_result->GiveElementNode;
      give_node->elements.push_back(give_element_node);
    }
    return (ast::make_ast_some(give_node));
  }

  std::any MavkaASTVisitor::visitGive_element(
      MavkaParser::Give_elementContext* context) {
    const auto give_element_node = new ast::GiveElementNode();
    give_element_node->start_line = context->getStart()->getLine();
    give_element_node->start_column =
        context->getStart()->getCharPositionInLine();
    give_element_node->end_line = context->getStop()->getLine();
    give_element_node->end_column = context->getStop()->getCharPositionInLine();
    give_element_node->name = context->ge_name->getText();
    if (context->ge_as) {
      give_element_node->as = context->ge_as->getText();
    }
    return (ast::make_ast_some(give_element_node));
  }

  std::any MavkaASTVisitor::visitParams(MavkaParser::ParamsContext* context) {
    std::vector<ast::ParamNode*> params;
    for (int i = 0; i < context->param().size(); ++i) {
      const auto param = context->param()[i];
      const auto ast_result = any_to_ast_some(visitParam(param));
      params.push_back(ast_result->ParamNode);
    }
    if (context->p_variadic) {
      const auto param_node = new ast::ParamNode();
      param_node->start_line = context->getStart()->getLine();
      param_node->start_column = context->getStart()->getCharPositionInLine();
      param_node->end_line = context->getStop()->getLine();
      param_node->end_column = context->getStop()->getCharPositionInLine();
      param_node->name = context->p_variadic_name->getText();
      if (context->p_variadic_type) {
        param_node->types =
            std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
                visitType_value(context->p_variadic_type));
      }
      param_node->variadic = true;
      params.push_back(param_node);
    }
    return params;
  }

  std::any MavkaASTVisitor::visitParam(MavkaParser::ParamContext* context) {
    const auto param_node = new ast::ParamNode();
    param_node->name = context->p_name->getText();
    if (context->p_type) {
      param_node->types = std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
          visitType_value(context->p_type));
    }
    if (context->p_value) {
      param_node->value = any_to_ast_some(visitParam_value(context->p_value));
    }
    return (ast::make_ast_some(param_node));
  }

  std::any MavkaASTVisitor::visitParam_value(
      MavkaParser::Param_valueContext* context) {
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
    if (jejalyk::tools::instance_of<MavkaParser::Param_value_identifierContext>(
            context)) {
      return visitParam_value_identifier(
          dynamic_cast<MavkaParser::Param_value_identifierContext*>(context));
    }
    if (jejalyk::tools::instance_of<
            MavkaParser::Param_value_empty_dictionaryContext>(context)) {
      return visitParam_value_empty_dictionary(
          dynamic_cast<MavkaParser::Param_value_empty_dictionaryContext*>(
              context));
    }
    if (jejalyk::tools::instance_of<MavkaParser::Param_value_empty_listContext>(
            context)) {
      return visitParam_value_empty_list(
          dynamic_cast<MavkaParser::Param_value_empty_listContext*>(context));
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitParam_value_string(
      MavkaParser::Param_value_stringContext* context) {
    if (context->STRING()) {
      const auto string_node = new ast::StringNode();
      string_node->start_line = context->getStart()->getLine();
      string_node->start_column = context->getStart()->getCharPositionInLine();
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
      return (ast::make_ast_some(string_node));
    } else if (context->STRING_MULTILINE()) {
      const auto string_node = new ast::StringNode();
      string_node->start_line = context->getStart()->getLine();
      string_node->start_column = context->getStart()->getCharPositionInLine();
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
      return (ast::make_ast_some(string_node));
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitParam_value_number(
      MavkaParser::Param_value_numberContext* context) {
    const auto number_node = new ast::NumberNode();
    number_node->start_line = context->getStart()->getLine();
    number_node->start_column = context->getStart()->getCharPositionInLine();
    number_node->end_line = context->getStop()->getLine();
    number_node->end_column = context->getStop()->getCharPositionInLine();
    number_node->value = process_number(context->NUMBER()->getText());
    return (ast::make_ast_some(number_node));
  }

  std::any MavkaASTVisitor::visitParam_value_identifier(
      MavkaParser::Param_value_identifierContext* context) {
    const auto identifier_node = new ast::IdentifierNode();
    identifier_node->start_line = context->getStart()->getLine();
    identifier_node->start_column =
        context->getStart()->getCharPositionInLine();
    identifier_node->end_line = context->getStop()->getLine();
    identifier_node->end_column = context->getStop()->getCharPositionInLine();
    identifier_node->name = context->identifier()->getText();
    return (ast::make_ast_some(identifier_node));
  }

  std::any MavkaASTVisitor::visitParam_value_empty_dictionary(
      MavkaParser::Param_value_empty_dictionaryContext* context) {
    const auto dictionary_node = new ast::DictionaryNode();
    dictionary_node->start_line = context->getStart()->getLine();
    dictionary_node->start_column =
        context->getStart()->getCharPositionInLine();
    dictionary_node->end_line = context->getStop()->getLine();
    dictionary_node->end_column = context->getStop()->getCharPositionInLine();
    return (ast::make_ast_some(dictionary_node));
  }

  std::any MavkaASTVisitor::visitParam_value_empty_list(
      MavkaParser::Param_value_empty_listContext* context) {
    const auto array_node = new ast::ArrayNode();
    array_node->start_line = context->getStart()->getLine();
    array_node->start_column = context->getStart()->getCharPositionInLine();
    array_node->end_line = context->getStop()->getLine();
    array_node->end_column = context->getStop()->getCharPositionInLine();
    return (ast::make_ast_some(array_node));
  }

  std::any MavkaASTVisitor::visitIdentifiers_chain(
      MavkaParser::Identifiers_chainContext* context) {
    if (context->ic_identifier) {
      return visitIdentifier(context->ic_identifier);
    }
    const auto chain_node = new ast::ChainNode();
    chain_node->start_line = context->getStart()->getLine();
    chain_node->start_column = context->getStart()->getCharPositionInLine();
    chain_node->end_line = context->getStop()->getLine();
    chain_node->end_column = context->getStop()->getCharPositionInLine();
    chain_node->left =
        any_to_ast_some(visitIdentifiers_chain(context->ic_left));
    chain_node->right = any_to_ast_some(visitIdentifier(context->ic_right));
    return (ast::make_ast_some(chain_node));
  }

  std::any MavkaASTVisitor::visitSuper_identifiers_chain(
      MavkaParser::Super_identifiers_chainContext* context) {
    if (context->sic_identifier) {
      return visitIdentifier(context->sic_identifier);
    }
    const auto left =
        any_to_ast_some(visitSuper_identifiers_chain(context->sic_left));
    if (context->sic_right) {
      const auto right = any_to_ast_some(visitIdentifier(context->sic_right));
      const auto chain_node = new ast::ChainNode();
      chain_node->start_line = context->getStart()->getLine();
      chain_node->start_column = context->getStart()->getCharPositionInLine();
      chain_node->end_line = context->getStop()->getLine();
      chain_node->end_column = context->getStop()->getCharPositionInLine();
      chain_node->left = left;
      chain_node->right = right;
      return (ast::make_ast_some(chain_node));
    }
    const auto index = any_to_ast_some(_visitContext(context->sic_index));
    const auto get_element_node = new ast::GetElementNode();
    get_element_node->start_line = context->getStart()->getLine();
    get_element_node->start_column =
        context->getStart()->getCharPositionInLine();
    get_element_node->end_line = context->getStop()->getLine();
    get_element_node->end_column = context->getStop()->getCharPositionInLine();
    get_element_node->value = left;
    get_element_node->index = index;
    return (ast::make_ast_some(get_element_node));
  }

  std::any MavkaASTVisitor::visitType_value(
      MavkaParser::Type_valueContext* context) {
    std::vector<ast::TypeValueSingleNode*> types;
    for (int i = 0; i < context->type_value_item().size(); ++i) {
      const auto type = context->type_value_item()[i];
      const auto ast_result = any_to_ast_some(visitType_value_item(type));
      types.push_back(ast_result->TypeValueSingleNode);
    }
    return types;
  }

  std::any MavkaASTVisitor::visitType_value_item(
      MavkaParser::Type_value_itemContext* context) {
    if (context->type_value_item_array()) {
      return visitType_value_item_array(context->type_value_item_array());
    }
    if (context->type_value_item_simple()) {
      return visitType_value_item_simple(context->type_value_item_simple());
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitType_value_item_array(
      MavkaParser::Type_value_item_arrayContext* context) {
    const auto type_value_array = new ast::TypeValueSingleNode();
    type_value_array->start_line = context->getStart()->getLine();
    type_value_array->start_column =
        context->getStart()->getCharPositionInLine();
    type_value_array->end_line = context->getStop()->getLine();
    type_value_array->end_column = context->getStop()->getCharPositionInLine();
    const auto array_identifier_node = new ast::IdentifierNode();
    array_identifier_node->start_line = context->getStart()->getLine();
    array_identifier_node->start_column =
        context->getStart()->getCharPositionInLine();
    array_identifier_node->end_line = context->getStop()->getLine();
    array_identifier_node->end_column =
        context->getStop()->getCharPositionInLine();
    array_identifier_node->name = "список";
    type_value_array->value = ast::make_ast_some(array_identifier_node);
    const auto type_value_single_result =
        any_to_ast_some(visitType_value_item(context->type_value_item()));
    const auto type_value_single =
        type_value_single_result->TypeValueSingleNode;
    type_value_array->generics.push_back({type_value_single});
    return (ast::make_ast_some(type_value_array));
  }

  std::any MavkaASTVisitor::visitType_value_item_simple(
      MavkaParser::Type_value_item_simpleContext* context) {
    const auto ast_result =
        any_to_ast_some(visitIdentifiers_chain(context->tvi_value));
    const auto type_value_single = new ast::TypeValueSingleNode();
    type_value_single->start_line = context->getStart()->getLine();
    type_value_single->start_column =
        context->getStart()->getCharPositionInLine();
    type_value_single->end_line = context->getStop()->getLine();
    type_value_single->end_column = context->getStop()->getCharPositionInLine();
    type_value_single->value = ast_result;
    if (context->tvi_generics) {
      for (const auto generic_type : context->tvi_generics->type_value()) {
        type_value_single->generics.push_back(
            std::any_cast<std::vector<ast::TypeValueSingleNode*>>(
                visitType_value(generic_type)));
      }
    }
    return (ast::make_ast_some(type_value_single));
  }

  std::any MavkaASTVisitor::visitArgs(MavkaParser::ArgsContext* context) {
    std::vector<ast::ArgNode*> args;
    for (int i = 0; i < context->arg().size(); ++i) {
      const auto arg = context->arg()[i];
      const auto ast_result = any_to_ast_some(visitArg(arg, i));
      args.push_back(ast_result->ArgNode);
    }
    return args;
  }

  std::any MavkaASTVisitor::visitArg(MavkaParser::ArgContext* context,
                                     int index) {
    const auto arg_node = new ast::ArgNode();
    arg_node->start_line = context->getStart()->getLine();
    arg_node->start_column = context->getStart()->getCharPositionInLine();
    arg_node->end_line = context->getStop()->getLine();
    arg_node->end_column = context->getStop()->getCharPositionInLine();
    arg_node->index = index;
    arg_node->value = any_to_ast_some(_visitContext(context->a_value));
    arg_node->spread = context->a_spread != nullptr;
    return (ast::make_ast_some(arg_node));
  }

  std::any MavkaASTVisitor::visitNamed_args(
      MavkaParser::Named_argsContext* context) {
    std::vector<ast::ArgNode*> args;
    for (int i = 0; i < context->named_arg().size(); ++i) {
      const auto arg = context->named_arg()[i];
      const auto ast_result = any_to_ast_some(visitNamed_arg(arg, i));
      args.push_back(ast_result->ArgNode);
    }
    return args;
  }

  std::any MavkaASTVisitor::visitNamed_arg(
      MavkaParser::Named_argContext* context,
      int index) {
    const auto arg_node = new ast::ArgNode();
    arg_node->start_line = context->getStart()->getLine();
    arg_node->start_column = context->getStart()->getCharPositionInLine();
    arg_node->end_line = context->getStop()->getLine();
    arg_node->end_column = context->getStop()->getCharPositionInLine();
    arg_node->index = index;
    arg_node->name = context->na_name->getText();
    arg_node->value = any_to_ast_some(_visitContext(context->na_value));
    return (ast::make_ast_some(arg_node));
  }

  std::any MavkaASTVisitor::visitBody(MavkaParser::BodyContext* context) {
    std::vector<ast::ASTSome*> body;
    for (const auto body_element : context->body_element_or_return()) {
      const auto ast_result =
          any_to_ast_some(visitBody_element_or_return(body_element));
      if (ast_result->IdentifierNode) {
        if (ast_result->IdentifierNode->name == "перервати") {
          const auto break_node = new ast::BreakNode();
          break_node->start_line = ast_result->IdentifierNode->start_line;
          break_node->start_column = ast_result->IdentifierNode->start_column;
          break_node->end_line = ast_result->IdentifierNode->end_line;
          break_node->end_column = ast_result->IdentifierNode->end_column;
          body.push_back(ast::make_ast_some(break_node));
        } else if (ast_result->IdentifierNode->name == "продовжити") {
          const auto continue_node = new ast::ContinueNode();
          continue_node->start_line = ast_result->IdentifierNode->start_line;
          continue_node->start_column =
              ast_result->IdentifierNode->start_column;
          continue_node->end_line = ast_result->IdentifierNode->end_line;
          continue_node->end_column = ast_result->IdentifierNode->end_column;
          body.push_back(ast::make_ast_some(continue_node));
        } else {
          body.push_back(ast_result);
        }
      } else {
        body.push_back(ast_result);
      }
    }
    return body;
  }

  std::any MavkaASTVisitor::_visitDiiaBody(MavkaParser::BodyContext* context) {
    auto body = std::any_cast<std::vector<ast::ASTSome*>>(visitBody(context));
    if (!body.empty()) {
      const auto last_node = body.back();
      if (jejalyk::tools::instance_of<ast::ASTValueNode>(
              mavka::ast::get_ast_node(last_node))) {
        const auto return_node = new ast::ReturnNode();
        // return_node->start_line = last_node->start_line;
        // return_node->start_column = last_node->start_column;
        // return_node->end_line = last_node->end_line;
        // return_node->end_column = last_node->end_column;
        return_node->value = last_node;
        body.pop_back();
        body.push_back(ast::make_ast_some(return_node));
      }
    }
    return body;
  }

  std::any MavkaASTVisitor::visitBody_element_or_return(
      MavkaParser::Body_element_or_returnContext* context) {
    if (context->body_element()) {
      return visitBody_element(context->body_element());
    }
    if (context->return_body_line()) {
      return visitReturn_body_line(context->return_body_line());
    }
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitBody_element(
      MavkaParser::Body_elementContext* context) {
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
      return _visitContext(context->expr());
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
    return new ast::ASTSome();
  }

  std::any MavkaASTVisitor::visitReturn_body_line(
      MavkaParser::Return_body_lineContext* context) {
    const auto return_node = new ast::ReturnNode();
    return_node->start_line = context->getStart()->getLine();
    return_node->start_column = context->getStart()->getCharPositionInLine();
    return_node->end_line = context->getStop()->getLine();
    return_node->end_column = context->getStop()->getCharPositionInLine();
    return_node->value = any_to_ast_some(_visitContext(context->rbl_value));
    return (ast::make_ast_some(return_node));
  }

  void MavkaParserErrorListener::syntaxError(antlr4::Recognizer* recognizer,
                                             antlr4::Token* offendingSymbol,
                                             size_t line,
                                             size_t charPositionInLine,
                                             const std::string& msg,
                                             std::exception_ptr e) {
    std::cout << msg << std::endl;
    const auto error = new MavkaParserError();
    error->line = line;
    error->column = charPositionInLine;
    error->message = "syntaxError";
    throw *error;
  }

  MavkaParserResult* parse(std::string code, std::string path) {
    try {
      antlr4::ANTLRInputStream input(code);

      const auto lexer_error_listener = new MavkaParserErrorListener();
      MavkaLexer lexer(&input);
      lexer.removeErrorListeners();
      lexer.addErrorListener(lexer_error_listener);

      antlr4::CommonTokenStream tokens(&lexer);

      const auto parser_error_listener = new MavkaParserErrorListener();
      MavkaParser parser(&tokens);
      // parser.setErrorHandler(std::shared_ptr<MavkaParserErrorHandler>(error_handler));
      parser.removeParseListeners();
      parser.removeErrorListeners();
      parser.addErrorListener(parser_error_listener);

      MavkaParser::FileContext* tree = parser.file();

      MavkaASTVisitor visitor;

      const auto ast_result = any_to_ast_some(visitor.visitFile(tree));

      const auto program_node = ast_result->ProgramNode;
      const auto parser_result = new MavkaParserResult();
      parser_result->program_node = program_node;
      return parser_result;
    } catch (const antlr4::RecognitionException& e) {
      const auto parser_result = new MavkaParserResult();
      const auto parser_error = new MavkaParserError();
      // wasm cannot properly handle antlr4 exceptions
      // do not handle it for now
      // todo: fix it
      // try {
      // parser_error->line = e.getOffendingToken()->getLine();
      // parser_error->column = e.getOffendingToken()->getCharPositionInLine();
      // } catch (...) {
      // ignore
      // }
      parser_error->path = path;
      parser_error->message = "Помилка парсингу.";
      parser_result->error = parser_error;
      return parser_result;
    }
    // catch (...) {
    //   const auto parser_result = new MavkaParserResult();
    //   const auto parser_error = new MavkaParserError();
    //   parser_error->message = "Невідома помилка парсингу.";
    //   parser_result->error = parser_error;
    //   return parser_result;
    // }
  }
}
