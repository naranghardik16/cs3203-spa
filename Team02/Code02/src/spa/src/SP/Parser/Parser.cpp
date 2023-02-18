#pragma once

#include "Parser.h"
#include "ProcedureParser.h"

// TODO remove the below const
const std::string kProc = "procedure";

shared_ptr<Program> Parser::ParseSource(TokenStream &tokens) {
  // take in tokens
  shared_ptr<Program> program = make_shared<Program>();
  auto proc_parser = make_shared<ProcedureParser>();
  while (!tokens.empty()) {
    try {
      shared_ptr<Procedure> proc = proc_parser->ParseEntity(tokens);
      program->AddToProcedureList(proc);
    } catch (SyntaxErrorException &e) {
      throw SyntaxErrorException(e.what());
    } catch (const SemanticErrorException &e) {
    }
  }
  return program;
}

bool Parser::IsStatement(Line &line) {
  return !IsProcedure(line);
}

bool Parser::IsProcedure(Line &line) {
  return !line.empty() && line[0]->GetValue() == kProc;
}

