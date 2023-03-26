#pragma
#include "StatementParser.h"
#include "core/model/Program.h"
#include "core/model/CallStatement.h"
#include "SP/Util/SPConstants.h"


class CallStatementParser : public StatementParser {
  public:
    CallStatementParser() = default;
    shared_ptr<Statement> ParseEntity(TokenStream &tokens) override;
    [[nodiscard]] std::string ExtractProcedureName(Line &line) const;
    void CheckEndOfStatement(Line &line) const;
 private:
  const int k_max_tokens_ = 3;
};