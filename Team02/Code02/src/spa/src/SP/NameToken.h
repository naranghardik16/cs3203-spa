#ifndef SPA_SRC_SPA_SRC_SP_NAMETOKEN_H_
#define SPA_SRC_SPA_SRC_SP_NAMETOKEN_H_
#include "Token.h"

class NameToken : public Token {
 public:
  NameToken(string val);
  bool Equals(Token &other);
};

#endif //SPA_SRC_SPA_SRC_SP_NAMETOKEN_H_
