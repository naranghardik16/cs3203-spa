#include "StatementParserFactory.h"
#include "PrintStatementParser.h"
#include "ReadStatementParser.h"

StatementParser *StatementParserFactory::GetStatementParser(std::deque<
    StatementParserFactory::Line> &tokens) {
  auto line = tokens.front();
  if (CheckStatementType(line, "=")) {
    return new AssignStatementParser();
  } else if (CheckStatementType(line, "print")) {
    return new PrintStatementParser();
  } else if (CheckStatementType(line, "read")) {
    return new ReadStatementParser();
  }
  throw SemanticErrorException("Unknown Statement type");
}
bool StatementParserFactory::CheckStatementType(StatementParserFactory::Line &line,
                                                std::string_view type_to_check) {
  auto entity_itr =
      std::find_if(std::begin(line), std::end(line), [&](Token *const p) {
        return p->GetValue() == type_to_check;
      });
  return entity_itr != std::end(line);
}