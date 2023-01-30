#ifndef SPA_SRC_SPA_SRC_SP_NAMETOKEN_H_
#define SPA_SRC_SPA_SRC_SP_NAMETOKEN_H_
#include "Token.h"

class NameToken : public Token {
 public:
  bool Equals(NameToken *other);
};

#endif //SPA_SRC_SPA_SRC_SP_NAMETOKEN_H_
