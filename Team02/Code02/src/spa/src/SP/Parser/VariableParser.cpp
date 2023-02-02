#include "VariableParser.h"

Variable *VariableParser::ParseEntity(TokenStream &tokens) {
  ParseEntity(tokens.front());
}

Variable *VariableParser::ParseEntity(Line &line) {
  if (line.size() == 2 && line[1]->GetValue() == ";") {
    return new Variable(line[0]->GetValue());
  }
  throw SyntaxErrorException("Has more expressions other than one Variable");
}