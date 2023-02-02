#pragma once

#include<deque>
#include<vector>
#include "StatementParser.h"
#include "AssignStatementParser.h"

class StatementParserFactory {
  typedef std::vector<Token *> Line;
  typedef std::deque<Line> TokenStream;
 public:
  static StatementParser *GetStatementParser(TokenStream &tokens);
 private:
  static inline bool CheckStatementType(Line &line,
                                        std::string_view type_to_check);

};