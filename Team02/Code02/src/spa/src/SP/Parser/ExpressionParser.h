#pragma once

#include "core/model/Expression.h"
#include "core/model/Statement.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "EntityParser.h"

class ExpressionParser : public EntityParser<Expression> {
 public:
  virtual Expression *ParseEntity(Line &line) = 0;
};