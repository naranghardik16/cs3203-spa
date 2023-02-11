#pragma once

#include "OperationParser.h"
#include "../../core/model/ArithmeticOperation.h"
#include "../../core/model/Constant.h"
#include "../../core/model/Variable.h"
#include "../Token.h"
#include "../../General/SpaException/SyntaxErrorException.h"

using namespace std;


class ArithmeticOperationParser : public OperationParser {
 public:
  ArithmeticOperationParser() = default;
  Expression *Parse() override;
 private:
  vector<TokenType> term_operators_ = { PLUS, MINUS };
  vector<TokenType> factor_operators_ = {MULTIPLY, DIV, MOD};
  Expression *Term();
  Expression *Factor();
};

