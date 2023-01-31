#pragma once
#include "StatementParser.h"
#include "core/model/Statement.h"

class AssignStatementParser : public StatementParser {
 public:
  AssignStatementParser() = default;
  Statement *ParseEntity(TokenStream &tokens) override;
};