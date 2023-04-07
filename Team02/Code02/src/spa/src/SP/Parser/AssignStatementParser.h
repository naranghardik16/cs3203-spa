#pragma once
#include "StatementParser.h"
#include "core/model/Program.h"
#include "core/model/AssignStatement.h"
#include "SP/Util/SPConstants.h"

class AssignStatementParser : public StatementParser {
 public:
  AssignStatementParser() = default;
  shared_ptr<Statement> ParseEntity(TokenStream &tokens) override;
  [[nodiscard]] std::string ExtractVariableName(Line &line) const;
  void CheckEndOfStatement(Line &line) const;
 private:
  const int k_min_tokens_ = 4;
  const int k_pos_lhs_ = 0;
};