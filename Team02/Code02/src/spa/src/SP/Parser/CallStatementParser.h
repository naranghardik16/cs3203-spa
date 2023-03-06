#pragma
#include "StatementParser.h"
#include "core/model/Program.h"
#include "core/model/CallStatement.h"

class CallStatementParser : public StatementParser {
  public:
    CallStatementParser() = default;
    shared_ptr<Statement> ParseEntity(TokenStream &tokens) override;
    [[nodiscard]] std::string ExtractProcedureName(Line &line) const;
    void CheckEndOfStatement(Line &line) const;
};