#include "StatementParserFactory.h"

StatementParser *StatementParserFactory::GetStatementParser(std::deque<
    StatementParserFactory::Line> &tokens) {
  auto line = tokens.front();
  if (CheckStatementType(line, "=")) {
    return new AssignStatementParser();
  }

  return nullptr;
}
bool StatementParserFactory::CheckStatementType(StatementParserFactory::Line &line,
                                                std::string_view type_to_check) {
  for (auto token : line) {
    if (token->GetValue() == type_to_check) {
      return true;
    }
  }
  return false;
}