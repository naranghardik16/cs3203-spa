#pragma once

#include<deque>
#include<vector>
#include "StatementParser.h"
#include "AssignStatementParser.h"
#include "IfStatementParser.h"
#include "PrintStatementParser.h"
#include "ReadStatementParser.h"
#include "WhileStatementParser.h"

/**
 * Factory class for getting the appropriate Statement Parser
 * depending on the tokens.
 */
class StatementParserFactory {
  typedef std::vector<shared_ptr<Token>> Line;
  typedef std::deque<Line> TokenStream;
 public:
  static shared_ptr<StatementParser> GetStatementParser(TokenStream &tokens);
 private:
  static inline bool CheckStatementType(Line &line,
                                        std::string_view type_to_check);

};