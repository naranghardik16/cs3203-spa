#include "catch.hpp"

#include <memory>
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Clause/PatternClauseSyntax.h"
#include "QPS/ValidationHandler/PatternHandler.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test PatternHandler HandleSyntax") {
  PatternHandler handler;

  SECTION("Test valid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax{{"a", {"v", "_\"x\"_"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - arg_1 is underscore") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax{{"a", {"_", "_\"x\"_"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - 3 args") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax{{"a", {"a", "_", "_"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - arg_2(_   \"1+ 2\"  _)") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax{{"a", {"_", "_   \"1+ 2\"  _"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - arg_2(_   \"1+ a\"  _)") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax{{"a", {"_", "_   \"1+ a\"  _"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - arg_2(_   \"(1+ a)\"  _)") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax{{"a", {"_", "_   \"(1+ a)\"  _"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - arg_2(_   \"(1)/ a\"  _)") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax{{"a", {"_", "_   \"(1)/ a\"  _"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - arg_2(_   \"(1)- (a)\"  _)") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "_   \"(1)- (a)\"  _"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - arg_2(_   \"(1%v) *(a)\"  _)") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "_   \"(1%v) *(a)\"  _"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - arg_2(_   \"((((1)%((v))))) *(a)\"  _)") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "_   \"((((1)%((v))))) *(a)\"  _"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - arg_2(\"2 * (3 + 4) / (5 - 6) + 7 % 2 - 8 * (9 - 10) + 11\")") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "\"2 * (3 + 4) / (5 - 6) + "
                                            "7 % 2 - 8 * (9 - 10) + 11\""}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - "
          "arg_2(\"(((((((((((1 / 2) / 3) / 4) / 5) / 6) / 7) / 8) / 9) / 10) / 11) / 12)\")") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "\"(((((((((((1 / 2) / 3) / 4) / 5) / 6) "
                                            "/ 7) / 8) / 9) / 10) / 11) / 12)\""}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - "
          "arg_2(\"(((x * (x + y)) * (x + (x + y))) + ((y * (x + y)) * (y + (x + y)))) / ((x + y) * (x + y))\")") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "\"(((x * (x + y)) * (x + (x + y))) + "
                                            "((y * (x + y)) * (y + (x + y)))) / ((x + y) * (x + y))\""}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - "
          "arg_2(\"(a + (b + (c + (d + (e + (f + (g + (h + (i + (j + (k + (l + (m + (n + (o + p)))))))))))))))\")") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "\"(a + (b + (c + (d + (e + (f + (g + (h + "
                                            "(i + (j + (k + (l + (m + (n + (o + p)))))))))))))))\""}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - "
          "arg_2(\"2 * (3 * (4 * (5 * (6 * (7 * (8 * (9 * (10 * (11 * (12 * (13 * (14 * (15)))))))))))))\")") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "\"2 * (3 * (4 * (5 * (6 * (7 * (8 * (9 * "
                                            "(10 * (11 * (12 * (13 * (14 * (15)))))))))))))\""}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - "
          "arg_2(\"((((((1 + 2) * 3) / 4) - 5) * 6) + 7) - (((8 - 9) * 10) / ((11 * 12) + 13))\")") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "\"((((((1 + 2) * 3) / 4) - 5) * 6) + 7) "
                                            "- (((8 - 9) * 10) / ((11 * 12) + 13))\""}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax - "
          "arg_2(\"(((2 + 3) * 4) / ((5 - 6) * (7 + 8))) - (((9 - 10) * 11) + ((12 * 13) / (14 + 15)))\")") {
    std::shared_ptr<ClauseSyntax> clause(
        new PatternClauseSyntax{{"a", {"_", "\"(((2 + 3) * 4) / ((5 - 6) * (7 + 8))) - "
                                            "(((9 - 10) * 11) + ((12 * 13) / (14 + 15)))\""}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test invalid clause, syn_assign not synonym") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"1", {"_", "_\"x\"_"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_1 not entRef") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"1", "_\"x\"_"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(__)") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "__"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(___)") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "___"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(_\"_)") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "_ \"  _"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(_\"\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "_ \"  \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"_ \")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "  \" _  \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"\"\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "  \"  \"  \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"(\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"  (  \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\")\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"  )  \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"{\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "  \"{\"  "}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"()\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "  \"(  )  \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"+\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"  +\"  "}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"-\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", " \" - \" "}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"/\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"  / \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"1+\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\" 1 +  \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"+1\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"  +  1 \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"1++1\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\" 1 +  + 1\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"1c+1\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"1c  +  1\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"(1+1\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"(1  +  1\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(_\"2(3 + 4)\"_)") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "_\"2(3 + 4)\"_"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"(5 - 2) * 7)\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"(5 - 2) * 7)\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"2 */ 3\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"2 */ 3\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"2  3\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"2  3\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"2 @ 3\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"2 @  3\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\")2  3(\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\")2  3(\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"    \")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"     \""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2(\"(3 + 4);\")") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"(3 + 4);\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2 is not wildcard") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "\"(3 + 4)\"", "_"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_3 is not wildcard") {
    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "_", "\"(3 + 4)\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }
}

TEST_CASE("Test PatternHandler HandleSemantic") {
  PatternHandler handler;

  SECTION("Test valid clause semantic - assign") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "_\"x\"_"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic - if") {
    Map declaration{{"a", "if"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"\"x\"", "_", "_"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic - while") {
    Map declaration{{"a", "while"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"\"x\"", "_"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test invalid clause semantic - if with only 2 args") {
    Map declaration{{"a", "if"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"\"x\"", "_"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic - 3 args not if syn") {
    Map declaration{{"a", "while"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"\"x\"", "_", "_"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic - if with args_2 not wildcard") {
    Map declaration{{"a", "if"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"\"x\"", "\"x\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic - while with args_2 not wildcard") {
    Map declaration{{"a", "while"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"\"x\"", "\"x\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid syn_assign not 'assign' synonym") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"v", {"_", "_\"x\"_"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, syn_assign not declared") {
    Map declaration{{"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"v", {"_", "_\"x\"_"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, arg_1 not 'variable' entity") {
    Map declaration{{"a", "assign"},
                    {"v", "stmt"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "_\"x\"_"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_1 synonym not declared") {
    Map declaration{{"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new PatternClauseSyntax {{"a", {"v", "_\"x\"_"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }
}
