#include "RelationalOperatorToken.h"

RelationalOperatorToken::RelationalOperatorToken(string val, TokenType type) : Token(val, type) {}

bool RelationalOperatorToken::Equals(shared_ptr<Token> other) {
  // make sure that the passed type is the same
  shared_ptr<RelationalOperatorToken> rot = dynamic_pointer_cast<RelationalOperatorToken>(other);
  if (rot) {
    return this->GetType() == rot->GetType() && this->GetValue() == rot->GetValue();
  }
  return false;
}

