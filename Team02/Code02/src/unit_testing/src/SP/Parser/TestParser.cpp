#include "SP/Parser/Parser.h"

#include "catch.hpp"
#include <string>

TEST_CASE("Check if IsProcedure works") {
  Parser::Line proc_line{"procedure", "main", "{"};
  Parser::Line stmt_line{"x", "assign", "y"};
  REQUIRE(Parser::IsProcedure(proc_line) == true);
  REQUIRE(Parser::IsProcedure(stmt_line) == false);
}