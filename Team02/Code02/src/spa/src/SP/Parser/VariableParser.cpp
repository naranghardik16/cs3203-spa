#include "VariableParser.h"

shared_ptr<Expression> VariableParser::ParseEntity(TokenStream &tokens) {
  return ParseEntity(tokens.front());
}

shared_ptr<Expression> VariableParser::ParseEntity(Line &line) {
  if (line.size() == 1) {
    return make_shared<Variable>(line[0]->GetValue());
  }
  throw SemanticErrorException("Has more expressions other than one Variable");
}