#pragma once

#include "ExpressionParser.h"
#include "core/model/Variable.h"

class VariableParser : public ExpressionParser {
 public:
  VariableParser() = default;
  Variable *ParseEntity(TokenStream &tokens) override;
  Variable *ParseEntity(Line &line) override;
};