#include "ConstantParser.h"

Constant *ConstantParser::ParseEntity(TokenStream &tokens) {
  ParseEntity(tokens.front());
}

Constant *ConstantParser::ParseEntity(Line &line) {
  if (line.size() == 1) {
    return new Constant(line[0]->GetValue());
  }
  throw SyntaxErrorException("Has more expressions other than a Constant");
}