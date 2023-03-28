
#pragma once

#include "SP/Parser/ExpressionParserFactory.h"
#include "SP/Tokenizer/Tokenizer.h"
#include "core/model/Expression.h"

class ExpressionGeneratorStub {
 public:
  typedef std::shared_ptr<Expression> ExpressionPtr;
  typedef std::vector<std::shared_ptr<Token>> TokenList;
  typedef std::string String;

  ExpressionGeneratorStub();
  ~ExpressionGeneratorStub();
  ExpressionPtr GetExpressionFromInput(TokenList input, String type);
};
