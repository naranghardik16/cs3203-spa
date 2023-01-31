#pragma once

#include "core/model/Statement.h"
#include "core/model/Procedure.h"
#include "EntityParser.h"
#include "StatementParserFactory.h"

class StatementParser : public EntityParser<Statement> {
 public:
  Statement *ParseEntity(TokenStream &tokens) override;
};