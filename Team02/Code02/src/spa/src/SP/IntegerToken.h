#ifndef SPA_SRC_SPA_SRC_SP_INTEGERTOKEN_H_
#define SPA_SRC_SPA_SRC_SP_INTEGERTOKEN_H_
#include "Token.h"

class IntegerToken : public Token {
 public:
  IntegerToken(string val);
  bool Equals(Token &other);
};

#endif //SPA_SRC_SPA_SRC_SP_INTEGERTOKEN_H_
