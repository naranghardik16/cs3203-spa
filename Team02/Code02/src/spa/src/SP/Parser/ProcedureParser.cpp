#include <string>

#include "ProcedureParser.h"

inline const std::string kProcedure = "procedure";
inline const std::string kEndProc = "}";

Procedure *ProcedureParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  std::string proc_name = ExtractProcName(line);
  auto proc = new Procedure(proc_name);
  line = tokens.front();
  while (!IsProcedureEnd(line)) {
    auto stmt_parser = StatementParserFactory::GetStatementParser(tokens);
    auto stmt = stmt_parser->ParseEntity(tokens);
    proc->AddToStatementList(stmt);
    line = tokens.front();
  }
  if (IsProcedureEnd(line)) {
    tokens.pop_front();
  }

  return proc;
}

std::string ProcedureParser::ExtractProcName(Line &line) {
  if (line[0]->GetValue() != "procedure" || line.size() < 2) {
    throw SyntaxErrorException("A procedure Line should start with procedure");
  }
  return line[1]->GetValue();
}

bool ProcedureParser::IsProcedureEnd(Line &line) {
  return std::find_if(std::begin(line), std::end(line),
                      [&](Token *const p) {
                        return p->GetValue() == "}";
                      }) != std::end(line);
}