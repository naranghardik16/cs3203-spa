//
// Created by Kai Qi Yong on 29/1/23.
//

#ifndef SPA_SRC_SPA_SRC_SP_INTEGERTOKEN_H_
#define SPA_SRC_SPA_SRC_SP_INTEGERTOKEN_H_
#include "Token.h"

class IntegerToken : public Token {
 public:
  bool Equals(IntegerToken *other);
};

#endif //SPA_SRC_SPA_SRC_SP_INTEGERTOKEN_H_
