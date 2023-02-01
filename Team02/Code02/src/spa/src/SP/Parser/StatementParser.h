#pragma once

#include "core/model/Statement.h"
#include "core/model/Procedure.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "EntityParser.h"

class StatementParser : public EntityParser<Statement> {
 public:
  virtual Statement *ParseEntity(TokenStream &tokens) = 0;
};