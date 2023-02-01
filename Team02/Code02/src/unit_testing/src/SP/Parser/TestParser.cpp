#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"

#include "catch.hpp"
#include <string>

TEST_CASE("Check if IsProcedure works") {
  Parser::Line proc_line{"procedure", "main", "{"};
  Parser::Line stmt_line{"x", "assign", "y"};
  REQUIRE(Parser::IsProcedure(proc_line) == true);
  REQUIRE(Parser::IsProcedure(stmt_line) == false);
}

TEST_CASE("Check if AssignStatementParser works") {
  Parser::Line stmt_line{"x", "assign", "y"};
  Parser::TokenStream stmt_tokens{stmt_line};
  auto parser = new AssignStatementParser();
  try {
    auto stmt = parser->ParseEntity(stmt_tokens);
  } catch (const SpaException &e) {
    REQUIRE(0);
  }
}

TEST_CASE("Check if Parser works with only assign statement") {
  Parser::Line proc_line{"procedure", "main", "{"};
  Parser::Line stmt_line{"x", "assign", "y"};
  Parser::Line end_line{"}"};
  Parser::TokenStream source{proc_line, stmt_line, end_line};
  auto parser = new Parser();
  try {
    auto program = parser->ParseSource(source);
  } catch (const SpaException &e) {
    REQUIRE(0);
  }
}

TEST_CASE(
    "Check if Parser throws Syntax Error for not starting with a procedure") {
  Parser::TokenStream invalid_proc_tokens{{"x", "assign", "y"}};
  auto parser = new Parser();
  try {
    auto program = parser->ParseSource(invalid_proc_tokens);
    REQUIRE(0);
  } catch (const SyntaxErrorException &e) {
    REQUIRE(1);
  }

}