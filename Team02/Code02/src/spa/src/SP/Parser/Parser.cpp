#include "Parser.h"
#include "ProcedureParser.h"

shared_ptr<Program> Parser::ParseSource(TokenStream &tokens) {
  shared_ptr<Program> program = make_shared<Program>();
  auto proc_parser = make_shared<ProcedureParser>();

  // Parsing procedures
  while (!tokens.empty()) {
    try {
      shared_ptr<Procedure> proc = proc_parser->ParseEntity(tokens);
      program->AddToProcedureList(proc);
    } catch (SyntaxErrorException &e) {
      throw SyntaxErrorException(e.what());
    } catch (SemanticErrorException &e) {
      throw SemanticErrorException(e.what());
    }
  }
  return program;
}

bool Parser::IsStatement(Line &line) {
  return !IsProcedure(line);
}

bool Parser::IsProcedure(Line &line) {
  return !line.empty() && line[0]->GetValue() == sp_constants::k_procedure_;
}

