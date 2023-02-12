#include "RelationalOperatorToken.h"
using namespace std;

RelationalOperatorToken::RelationalOperatorToken(string val, TokenType type) : Token(val, type) {}

bool RelationalOperatorToken::Equals(Token &other) {
  // make sure that the passed type is the same
  RelationalOperatorToken *rot = dynamic_cast<RelationalOperatorToken*>(&other);
  if (rot) {
    return this->GetType() == rot->GetType() && this->GetValue() == rot->GetValue();
  }
  return false;
}

