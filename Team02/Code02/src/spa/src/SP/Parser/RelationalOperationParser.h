#pragma once

#include "OperationParser.h"
#include "ArithmeticOperationParser.h"
#include "../../core/model/RelationalOperation.h"
#include "SP/Tokenizer/Token.h"
#include "../../General/SpaException/SyntaxErrorException.h"

using namespace std;

class RelationalOperationParser : public OperationParser {
 public:
  RelationalOperationParser() = default;
  shared_ptr<Expression> Parse() override;
 private:
  shared_ptr<Expression> Factor();
};