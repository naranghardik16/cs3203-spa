#pragma once
#include "StatementParser.h"
#include "core/model/Program.h"
#include "core/model/ReadStatement.h"

class ReadStatementParser : public StatementParser {
 public:
  ReadStatementParser() = default;
  shared_ptr<Statement> ParseEntity(TokenStream &tokens) override;
  [[nodiscard]] std::string ExtractVariableName(Line &line) const;
  void CheckEndOfStatement(Line &line) const;
};