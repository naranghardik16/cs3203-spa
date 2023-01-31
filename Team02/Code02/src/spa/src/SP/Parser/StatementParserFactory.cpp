#include "StatementParserFactory.h"
StatementParser *StatementParserFactory::GetStatementParser(std::deque<
    StatementParserFactory::Line> &tokens) {
  auto line = tokens.front();
  if (CheckStatementType(line, "assign")) {
  }

  return new StatementParser();

}
bool StatementParserFactory::CheckStatementType(StatementParserFactory::Line &line,
                                                std::string_view type_to_check) {
  return std::find(line.begin(), line.end(), type_to_check) != line.end();
}




