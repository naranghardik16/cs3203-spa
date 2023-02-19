#pragma once

#include "ExpressionParser.h"
#include "core/model/Variable.h"

class VariableParser : public ExpressionParser {
 public:
  VariableParser() = default;
  shared_ptr<Expression> ParseEntity(TokenStream &tokens) override;
  shared_ptr<Expression> ParseEntity(Line &line) override;
};