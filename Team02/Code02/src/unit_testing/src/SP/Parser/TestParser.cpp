#include "SP/Parser/Parser.h"

#include "catch.hpp"
#include <string>
#include "SP/NameToken.h"

TEST_CASE("Check if IsProcedure works") {
  Parser::Line proc_line{"procedure", "main", "{"};
  Parser::Line stmt_line{"x", "assign", "y"};
  REQUIRE(Parser::IsProcedure(proc_line) == true);
  REQUIRE(Parser::IsProcedure(stmt_line) == false);
}

TEST_CASE(
    "Check if Parser throws Syntax Error for not starting with a procedure") {
  Parser::TokenStream invalid_proc_tokens{{new NameToken("x"), new NameToken("assign"), new NameToken("y")}};
  auto parser = new Parser();
  try {
    auto program = parser->ParseSource(invalid_proc_tokens);
  } catch (const SyntaxErrorException &e) {
    REQUIRE(1);
  }

}