#include "ConstantParser.h"

Constant *ConstantParser::ParseEntity(TokenStream &tokens) {
  return ParseEntity(tokens.front());
}

Constant *ConstantParser::ParseEntity(Line &line) {
  if (line.size() == 1) {
    return new Constant(line[0]->GetValue());
  }
  throw SemanticErrorException("Has more expressions other than a Constant");
}