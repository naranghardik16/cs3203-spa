#pragma once
#include "ExpressionParser.h"
#include "core/model/Operation.h"
#include "../ArithmeticOperatorToken.h"
#include "../RelationalOperatorToken.h"
#include "../ConditionalOperatorToken.h"
#include "ArithmeticOperationParser.h"


class OperationParser : public ExpressionParser {
 public:
  OperationParser() = default;
  Operation *ParseEntity(TokenStream &tokens) override;
  Operation *ParseEntity(Line &line) override;
};


