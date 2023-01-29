#ifndef SPA_SRC_SPA_SRC_SP_PUNCTUATIONTOKEN_H_
#define SPA_SRC_SPA_SRC_SP_PUNCTUATIONTOKEN_H_
#include "Token.h"
using namespace std;

class PunctuationToken : public Token {
 private:
  string type_;
 public:
  inline static const string LEFT_PARENTHESIS = "{";
  inline static const string RIGHT_PARENTHESIS = "}";
  inline static const string LEFT_BRACE = "(";
  inline static const string RIGHT_BRACE = ")";
  inline static const string SEMICOLON = ";";
  inline static const string UNDERSCORE = "_";
  inline static const string DOUBLE_QUOTE = "\"";
  inline static const string EQUAL = "=";
  PunctuationToken(string val);
  string GetType();
  bool Equals(PunctuationToken *other);
};

#endif //SPA_SRC_SPA_SRC_SP_PUNCTUATIONTOKEN_H_
