#ifndef SPA_SRC_SPA_SRC_SP_CONDITIONALOPERATORTOKEN_H_
#define SPA_SRC_SPA_SRC_SP_CONDITIONALOPERATORTOKEN_H_
#include "Token.h"
using namespace std;

class ConditionalOperatorToken : public Token {
 private:
  string type_;
 public:
  inline static const string AND = "&&";
  inline static const string OR = "||";
  inline static const string NOT = "!";
  ConditionalOperatorToken(string val);
  string GetType();
  bool Equals(ConditionalOperatorToken *other);
};
#endif //SPA_SRC_SPA_SRC_SP_CONDITIONALOPERATORTOKEN_H_
