#include "ConstantParser.h"

shared_ptr<Expression> ConstantParser::ParseEntity(TokenStream &tokens) {
  return ParseEntity(tokens.front());
}

shared_ptr<Expression> ConstantParser::ParseEntity(Line &line) {
  if (line.size() == k_max_tokens_) {
    return make_shared<Constant>(line[k_pos_const_]->GetValue());
  }
  throw SemanticErrorException("Has more expressions other than a Constant");
}
