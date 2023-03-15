#include "ArithmeticOperatorToken.h"

ArithmeticOperatorToken::ArithmeticOperatorToken(string val, TokenType type) : Token(val, type) {}

bool ArithmeticOperatorToken::Equals(shared_ptr<Token> other) {
  // make sure that the passed type is the same
  shared_ptr<ArithmeticOperatorToken> aot = dynamic_pointer_cast<ArithmeticOperatorToken>(other);
  if (aot) {
    return this->GetType() == aot->GetType() && this->GetValue() == aot->GetValue();
  }
  return false;
}
