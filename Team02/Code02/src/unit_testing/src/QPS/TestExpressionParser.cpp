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
    try {
      spec = "_\"x\"";
      output = ExpressionParser::ParseExpressionSpec(spec);
    } catch (const SyntaxErrorException &e) {
      REQUIRE(1);

    }

    try {
      spec = "_x\"_";
      output = ExpressionParser::ParseExpressionSpec(spec);
    } catch (const SyntaxErrorException &e) {

      REQUIRE(1);
    }


    try {
      spec = "_\"1x\"_";
      output = ExpressionParser::ParseExpressionSpec(spec);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }
}