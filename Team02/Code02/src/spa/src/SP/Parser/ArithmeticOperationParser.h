#pragma once

#include "OperationParser.h"
#include "../../core/model/ArithmeticOperation.h"
#include "../../core/model/Constant.h"
#include "../../core/model/Variable.h"
#include "SP/Tokenizer/Token.h"
#include "../../General/SpaException/SyntaxErrorException.h"

using namespace std;


class ArithmeticOperationParser : public OperationParser {
 public:
  ArithmeticOperationParser() = default;
  shared_ptr<Expression> Parse() override;
 private:
  vector<TokenType> term_operators_ = { PLUS, MINUS };
  vector<TokenType> factor_operators_ = {MULTIPLY, DIV, MOD};
  shared_ptr<Expression> Term();
  shared_ptr<Expression> Factor();
};

