#include "VariableParser.h"

shared_ptr<Expression> VariableParser::ParseEntity(TokenStream &tokens) {
  return ParseEntity(tokens.front());
}

shared_ptr<Expression> VariableParser::ParseEntity(Line &line) {
  if (line.size() == k_max_tokens_) {
    return make_shared<Variable>(line[0]->GetValue());
  }
  throw SemanticErrorException("Has more expressions other than one Variable");
}
