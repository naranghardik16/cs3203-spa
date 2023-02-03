#pragma once
#include "StatementParser.h"
#include "core/model/AssignStatement.h"

class AssignStatementParser : public StatementParser {
 public:
  AssignStatementParser() = default;
  AssignStatement *ParseEntity(TokenStream &tokens) override;
  [[nodiscard]] std::string_view ExtractVariableName(Line &line) const;
  void CheckEndOfStatement(Line &line) const;
};