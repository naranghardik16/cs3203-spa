#pragma once

#include "ExpressionParser.h"
#include "core/model/Constant.h"

class ConstantParser : public ExpressionParser {
 public:
  ConstantParser() = default;
  shared_ptr<Expression> ParseEntity(TokenStream &tokens) override;
  shared_ptr<Expression> ParseEntity(Line &line) override;
 private:
  const int k_max_tokens_ = 1;
};