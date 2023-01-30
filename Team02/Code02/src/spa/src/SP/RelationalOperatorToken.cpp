#include "RelationalOperatorToken.h"
using namespace std;

RelationalOperatorToken::RelationalOperatorToken(string val) : Token(val) {
  if (this->GetValue() == LT) {
    type_ = LT;
  } else if (this->GetValue() == LTE) {
    type_ = LTE;
  } else if (this->GetValue() == GT) {
    type_ = GT;
  } else if (this->GetValue() == GTE) {
    type_ = GTE;
  } else if (this->GetValue() == EQUALS) {
    type_ = EQUALS;
  } else if (this->GetValue() == NE) {
    type_ = NE;
  }
}

string RelationalOperatorToken::GetType() {
  return type_;
}

bool RelationalOperatorToken::Equals(RelationalOperatorToken *other) {
  return this->GetType() == other->GetType() && this->GetValue() == other->GetValue() == 0;
}

