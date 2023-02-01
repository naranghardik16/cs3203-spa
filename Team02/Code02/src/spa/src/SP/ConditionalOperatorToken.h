#ifndef SPA_SRC_SPA_SRC_SP_CONDITIONALOPERATORTOKEN_H_
#define SPA_SRC_SPA_SRC_SP_CONDITIONALOPERATORTOKEN_H_
#include "Token.h"
#include "ConditionalOperatorType.h"
using namespace std;

class ConditionalOperatorToken : public Token {
 private:
  ConditionalOperatorType type_;
 public:
//  inline static const string AND = "&&";
//  inline static const string OR = "||";
//  inline static const string NOT = "!";
  ConditionalOperatorToken(string val, ConditionalOperatorType type);
  ConditionalOperatorType GetType();
  bool Equals(Token &other);
};
#endif //SPA_SRC_SPA_SRC_SP_CONDITIONALOPERATORTOKEN_H_
