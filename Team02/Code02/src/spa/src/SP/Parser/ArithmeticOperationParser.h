#pragma once
#include "../../core/model/ArithmeticOperation.h"
#include "../../core/model/Constant.h"
#include "../../core/model/Variable.h"
#include "../Token.h"
#include "../../General/SpaException/SyntaxErrorException.h"

using namespace std;


class ArithmeticOperationParser {
 public:
  ArithmeticOperationParser(vector<Token*> &line);
  ArithmeticOperation *Parse();
 private:
  vector<Token*> line_;
  vector<TokenType> term_operators_ = { PLUS, MINUS };
  vector<TokenType> factor_operators_ = {MULTIPLY, DIV, MOD};
  int pos_ = 0;
  Token *curr_token_;
  string curr_token_value_;
  void GetNext();
  Expression *Term();
  Expression *Factor();
};

