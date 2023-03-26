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
  inline static constexpr std::string_view k_if_stmt_ = "if";
  inline static constexpr std::string_view k_while_stmt_ = "while";
  inline static constexpr std::string_view k_print_stmt_ = "print";
  inline static constexpr std::string_view k_read_stmt_ = "read";
  inline static constexpr std::string_view k_call_stmt_ = "call";
  inline static constexpr std::string_view k_parenthesis_ = "(";
  inline static constexpr std::string_view k_assign_ = "=";
  inline static constexpr int k_min_stmt_size_ = 2;
};


