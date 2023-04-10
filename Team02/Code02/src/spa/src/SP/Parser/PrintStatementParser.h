#pragma once
#include "StatementParser.h"
#include "core/model/Program.h"
#include "core/model/PrintStatement.h"
#include "SP/Util/SPConstants.h"

class PrintStatementParser : public StatementParser {
 public:
  PrintStatementParser() = default;
  shared_ptr<Statement> ParseEntity(TokenStream &tokens) override;
  [[nodiscard]] std::string ExtractVariableName(Line &line) const;
  void CheckEndOfStatement(Line &line) const;
 private:
  const int k_min_tokens_ = 2;
  const int k_max_tokens_ = 3;
  const int k_pos_var_ = 1;
};