#pragma once

#include "StatementParser.h"
#include "StatementParserFactory.h"
#include "core/model/IfStatement.h"
#include "core/model/Program.h"
#include "SP/Util/SPConstants.h"


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
 private:
  const int k_min_tokens_ = 2;
  const string k_else_ = "else";
  const string k_then_ = "then";
};