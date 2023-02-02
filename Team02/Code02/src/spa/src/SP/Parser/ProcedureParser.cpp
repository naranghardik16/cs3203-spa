#include <string>

#include "ProcedureParser.h"
#include "General/SpaException/SyntaxErrorException.h"

Procedure *ProcedureParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  try {
    std::string proc_name = ExtractProcName( line);
    auto proc = new Procedure(proc_name);
    return proc;
  } catch (SyntaxErrorException &e) {
    throw SyntaxErrorException();
  }
}

std::string ProcedureParser::ExtractProcName(Line &line) {
  if (line[0]->GetValue() != "procedure" || line.size() < 2) {
    throw SyntaxErrorException();
  }
  return line[1]->GetValue();
}