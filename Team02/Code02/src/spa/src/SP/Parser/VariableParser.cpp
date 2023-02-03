#include "VariableParser.h"

Variable *VariableParser::ParseEntity(TokenStream &tokens) {
  ParseEntity(tokens.front());
}

Variable *VariableParser::ParseEntity(Line &line) {
  if (line.size() == 1) {
    return new Variable(line[0]->GetValue());
  }
  throw SemanticErrorException("Has more expressions other than one Variable");
}