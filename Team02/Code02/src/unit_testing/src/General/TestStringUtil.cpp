#include "General/StringUtil.h"
#include "catch.hpp"

TEST_CASE("Check if Trim works as expected") {
  std::string query = "             variable v;         ";
  std::string correct_clause = "variable v;";
  std::string clause = string_util::Trim(query);
  REQUIRE(correct_clause == clause);
}

TEST_CASE("Check if SplitByDelimiter works as expected") {
  std::string query = "variable v, v1;procedure p, p1;\nSelect v";
  std::vector<std::string> correct_clauses {"variable v, v1", "procedure p, p1", "Select v"};
  std::pair<std::vector<std::string>, std::string> clause_pair;
  clause_pair = string_util::SplitStringByDelimiter(query, ";");
  if (clause_pair.second.length() > 0) {
    clause_pair.first.push_back(clause_pair.second);
  }
  REQUIRE(correct_clauses == clause_pair.first);

  query = "     variable v, v1         ;  procedure p, p1 ;   \nSelect v      ";
  clause_pair = string_util::SplitStringByDelimiter(query, ";");
  if (clause_pair.second.length() > 0) {
    clause_pair.first.push_back(clause_pair.second);
  }
  REQUIRE(correct_clauses == clause_pair.first);

  query = "variable v, v1;procedure p, p1;Select v";
  clause_pair = string_util::SplitStringByDelimiter(query, ";");
  if (clause_pair.second.length() > 0) {
    clause_pair.first.push_back(clause_pair.second);
  }
  REQUIRE(correct_clauses == clause_pair.first);

  query = "variable v, v1 procedure p, p1 Select v";
  clause_pair = string_util::SplitStringByDelimiter(query, ";");
  if (clause_pair.second.length() > 0) {
    clause_pair.first.push_back(clause_pair.second);
  }
  correct_clauses = std::vector<std::string>{"variable v, v1 procedure p, p1 Select v"};
  REQUIRE(correct_clauses == clause_pair.first);
}

TEST_CASE("Check if FirstWord works as expected") {
  std::string query = "s such that Follows* (6, s)";
  std::string clause = string_util::GetFirstWord(query);
  std::string correct_clause = "s";
  REQUIRE(correct_clause == clause);

  query = "w such that Parent* (w, a) pattern a (\"count\", _)";
  clause = string_util::GetFirstWord(query);
  correct_clause = "w";
  REQUIRE(correct_clause == clause);

  query = "";
  clause = string_util::GetFirstWord(query);
  correct_clause = "";
  REQUIRE(correct_clause == clause);
}
