#pragma once

#include "StatementParser.h"
#include "StatementParserFactory.h"
#include "core/model/Program.h"
#include "core/model/WhileStatement.h"

class WhileStatementParser : public StatementParser {
 public:
  WhileStatementParser() = default;
  WhileStatement *ParseEntity(TokenStream &tokens) override;
  [[nodiscard]] ConditionalOperation ExtractCondition(Line &line);
  void CheckStartOfLoopStatement(Line &line) const;
  bool IsEndOfWhileStatement(Line &line) const;
};