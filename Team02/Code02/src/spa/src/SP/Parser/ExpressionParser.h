#pragma once

#include "core/model/Expression.h"
#include "core/model/Statement.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"
#include "EntityParser.h"

class ExpressionParser : public EntityParser<Expression> {
 public:
  virtual shared_ptr<Expression> ParseEntity(Line &line) = 0;
};