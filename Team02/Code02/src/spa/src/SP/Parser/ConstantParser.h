#pragma once

#include "ExpressionParser.h"
#include "core/model/Constant.h"

class ConstantParser : public ExpressionParser {
 public:
  ConstantParser() = default;
  Constant *ParseEntity(TokenStream &tokens) override;
  Constant *ParseEntity(Line &line) override;
};