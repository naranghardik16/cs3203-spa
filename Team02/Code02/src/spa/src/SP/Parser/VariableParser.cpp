#include "VariableParser.h"

Variable *VariableParser::ParseEntity(TokenStream &tokens) {
  ParseEntity(tokens.front());
}

Variable *VariableParser::ParseEntity(Line &line) {
  if (line.size() == 2 && line[1] == ";") {
    return new Variable(line[0]);
  }
  throw SyntaxErrorException();
  return nullptr;
}