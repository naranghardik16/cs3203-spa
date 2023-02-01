#ifndef SPA_SRC_SPA_SRC_SP_RELATIONALOPERATORTOKEN_H_
#define SPA_SRC_SPA_SRC_SP_RELATIONALOPERATORTOKEN_H_
#include "Token.h"
#include "RelationalOperatorType.h"
using namespace std;

class RelationalOperatorToken : public Token {
 private:
  RelationalOperatorType type_;
 public:
//  inline static const string LT = "<";
//  inline static const string LTE = "<=";
//  inline static const string GT = ">";
//  inline static const string GTE = ">=";
//  inline static const string EQUALS = "==";
//  inline static const string NE = "!=";
  RelationalOperatorToken(string val, RelationalOperatorType type);
  RelationalOperatorType GetType();
  bool Equals(Token &other);
};
#endif //SPA_SRC_SPA_SRC_SP_RELATIONALOPERATORTOKEN_H_
