#include "catch.hpp"
#include "QPS/ExpressionSpecParser.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test ExpressionSpecParser") {
  SECTION("Invalid expressions - throw syntax error") {
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("__"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("___"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_    \"    _"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"   \""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"_    \""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"    \"\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"\"\"\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"(\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"{\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\")\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"()\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"+\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"-\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"1+\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"+1 * 3\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"1+   +1\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"1c+ 1\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"()+ 1\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"(+ 1\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"(1+ 1) -\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"(1+ 1) - (1) + 2 - (4\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"(\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\")\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"()\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"+\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"-\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"1+\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"+1\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"1+   +1\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"1c+ 1\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"()+ 1\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"(+ 1\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"(1+ 1) -\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("_\"01+1\"_"), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"4 * (6 + 3\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"(5 - 2) * 7)\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"1 + 2 + 3 + \""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"2 */ 3\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"(2 + 3)) * 4\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"2 3\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"2 @ 3\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"2 ^ 3\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\")2 + 3(\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"               \""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"2(3 + 4)\""), SyntaxErrorException);
    REQUIRE_THROWS_AS(ExpressionSpecParser::ParseExpressionSpec("\"(3 + 4);\""), SyntaxErrorException);
  }

  SECTION("Valid Expression - does not throw exception") {
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("_   \"1+ 2\"  _"));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"1+ a\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"(1+ a)\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"(1)/ a\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"(1)- (a)\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"(1%v) *(a)\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"((((1)%((v))))) *(a)\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"2 * (3 + 4) / (5 - 6) + 7 % 2 - 8 * (9 - 10) + 11\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"(((((((((((1 / 2) / 3) / 4) / 5) / 6) / 7) / 8) / 9) / 10) / 11) / 12)\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"(((x * (x + y)) * (x + (x + y))) + ((y * (x + y)) * (y + (x + y)))) / ((x + y) * (x + y))\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"(a + (b + (c + (d + (e + (f + (g + (h + (i + (j + (k + (l + (m + (n + (o + p)))))))))))))))\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"2 * (3 * (4 * (5 * (6 * (7 * (8 * (9 * (10 * (11 * (12 * (13 * (14 * (15)))))))))))))\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"((((((1 + 2) * 3) / 4) - 5) * 6) + 7) - (((8 - 9) * 10) / ((11 * 12) + 13))\""));
    REQUIRE_NOTHROW(ExpressionSpecParser::ParseExpressionSpec("\"(((2 + 3) * 4) / ((5 - 6) * (7 + 8))) - (((9 - 10) * 11) + ((12 * 13) / (14 + 15)))\""));
  }
}
