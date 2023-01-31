#include <string>

#include "ProcedureParser.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "StatementParser.h"

inline const std::string kProcedure = "procedure";
inline const std::string kEndProc = "}";

Procedure *ProcedureParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  auto *stmt_parser = new StatementParser();
  tokens.pop_front();
  try {
    std::string proc_name = ExtractProcName(line);
    auto proc = new Procedure(proc_name);
    line = tokens.front();
    tokens.pop_front();
    while (!IsProcedureEnd(line)) {
      auto stmt = stmt_parser->ParseEntity(tokens);
      proc->AddToStatementList(stmt);
    }
    return proc;
  } catch (SyntaxErrorException &e) {
    throw SyntaxErrorException();
  }
}

std::string ProcedureParser::ExtractProcName(Line &line) {
  if (line[0] != kProcedure || line.size() < 2) {
    throw SyntaxErrorException();
  }
  return line[1];
}

inline bool ProcedureParser::IsProcedureEnd(Line &line) {
  return std::find(line.begin(), line.end(), kEndProc) == line.end();
}