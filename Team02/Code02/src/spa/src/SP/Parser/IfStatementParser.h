#pragma once

#include "StatementParser.h"
#include "StatementParserFactory.h"
#include "core/model/IfStatement.h"
#include "core/model/Program.h"

class IfStatementParser : public StatementParser {
 public:
  IfStatementParser() = default;
  shared_ptr<Statement> ParseEntity(TokenStream &tokens) override;
  [[nodiscard]] shared_ptr<ConditionalOperation> ExtractCondition(Line &line);
  void CheckStartOfIfStatement(Line &line) const;
  void CheckStartOfElseStatement(Line &line) const;
  bool HasElseStatements(Line &line) const;
  bool IsEndOfThenStatement(Line &line) const;
  bool IsEndOfIfElseStatement(Line &line) const;
};