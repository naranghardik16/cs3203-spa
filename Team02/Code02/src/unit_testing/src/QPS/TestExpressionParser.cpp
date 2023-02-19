#include "catch.hpp"
#include "QPS/ExpressionParser.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test if the expression parser works as expected") {
  std::string spec;
  std::string output;

  SECTION("Valid cases") {
    spec = "_\"x\"_";
    output = ExpressionParser::ParseExpressionSpec(spec);
    REQUIRE(output == "_x_");

    spec = "_";
    output = ExpressionParser::ParseExpressionSpec(spec);
    REQUIRE(output == spec);

    spec = "_\"1\"_";
    REQUIRE(ExpressionParser::ParseExpressionSpec(spec) == "_1_");

  }

  SECTION("Invalid syntax") {
    spec = "";
    REQUIRE_THROWS_AS(ExpressionParser::ParseExpressionSpec(spec), SyntaxErrorException);

    spec = "_\"x\"";
    REQUIRE_THROWS_AS(ExpressionParser::ParseExpressionSpec(spec), SyntaxErrorException);

    spec = "_x\"_";
    REQUIRE_THROWS_AS(ExpressionParser::ParseExpressionSpec(spec), SyntaxErrorException);

    spec = "_\"1x\"_";
    REQUIRE_THROWS_AS(ExpressionParser::ParseExpressionSpec(spec), SyntaxErrorException);
  }
}