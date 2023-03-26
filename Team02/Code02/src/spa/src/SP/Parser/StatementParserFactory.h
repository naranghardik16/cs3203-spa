#pragma once

#include<deque>
#include<vector>
#include "StatementParser.h"
#include "AssignStatementParser.h"
#include "IfStatementParser.h"
#include "PrintStatementParser.h"
#include "ReadStatementParser.h"
#include "WhileStatementParser.h"
#include "CallStatementParser.h"
#include "SP/Util/SPConstants.h"

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
  static bool CheckAssignmentType(Line &line);
  static bool CheckKeywordType(Line &line,
                               std::string_view type_to_check,
                               bool has_parenthesis);
  inline static constexpr int k_min_stmt_size_ = 2;
};


