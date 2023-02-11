#pragma once

#include "OperationParser.h"
#include "ArithmeticOperationParser.h"
#include "../../core/model/RelationalOperation.h"
#include "../Token.h"
#include "../../General/SpaException/SyntaxErrorException.h"

using namespace std;

class RelationalOperationParser : public OperationParser {
 public:
  RelationalOperationParser() = default;
  Expression *Parse() override;
 private:
  Expression *Factor();
};