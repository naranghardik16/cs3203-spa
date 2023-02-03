#include "ArithmeticOperatorToken.h"
using namespace std;

ArithmeticOperatorToken::ArithmeticOperatorToken(string val, TokenType type) : Token(val, type) {}

bool ArithmeticOperatorToken::Equals(Token &other) {
  // make sure that the passed type is the same
  ArithmeticOperatorToken *aot = dynamic_cast<ArithmeticOperatorToken*>(&other);
  if (aot) {
    return this->GetType() == aot->GetType() && this->GetValue() == aot->GetValue();
  }
  return false;
}
