#include "ConstantParser.h"

shared_ptr<Expression> ConstantParser::ParseEntity(TokenStream &tokens) {
  return ParseEntity(tokens.front());
}

shared_ptr<Expression> ConstantParser::ParseEntity(Line &line) {
  if (line.size() == 1) {
    return make_shared<Constant>(line[0]->GetValue());
  }
  throw SemanticErrorException("Has more expressions other than a Constant");
}
