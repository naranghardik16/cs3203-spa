#ifndef SPA_SRC_SPA_SRC_SP_ARITHMETICOPERATORTOKEN_H_
#define SPA_SRC_SPA_SRC_SP_ARITHMETICOPERATORTOKEN_H_
#include "Token.h"
using namespace std;

class ArithmeticOperatorToken : public Token {
 private:
  string type_;
 public:
  inline static const string PLUS = "+";
  inline static const string MINUS = "-";
  inline static const string DIV = "/";
  inline static const string MULTIPLY = "*";
  inline static const string MOD = "%";
  ArithmeticOperatorToken(string val);
  string GetType();
  bool Equals(ArithmeticOperatorToken *other);
};

#endif //SPA_SRC_SPA_SRC_SP_ARITHMETICOPERATORTOKEN_H_
