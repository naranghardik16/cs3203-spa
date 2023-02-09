#pragma once

#include "StatementParser.h"
#include "StatementParserFactory.h"
#include "core/model/IfStatement.h"
#include "core/model/Program.h"

class IfStatementParser : public StatementParser {
 public:
  IfStatementParser() = default;
  IfStatement *ParseEntity(TokenStream &tokens) override;
  [[nodiscard]] ConditionalOperation ExtractCondition(Line &line);
  void CheckStartOfIfStatement(Line &line) const;
  bool IsEndOfThenStatement(Line &line) const;
  bool IsEndOfIfElseStatement(Line &line) const;
};