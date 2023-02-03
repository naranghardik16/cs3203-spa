#include "catch.hpp"

#include "QPS/QPSTypeDefs.h"
#include "QPS/Clause/PatternClauseSyntax.h"
#include "QPS/ValidationHandler/PatternHandler.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test PatternHandler HandleSyntax") {
  PatternHandler handler;

  SECTION("Test valid clause syntax") {
    PatternClauseSyntax clause{{"a", {"v", "_\"x\"_"}}};

    REQUIRE_NOTHROW(handler.HandleSyntax(&clause));
  }

  SECTION("Test valid clause syntax - arg_1 is underscore") {
    PatternClauseSyntax clause{{"a", {"_", "_\"x\"_"}}};

    REQUIRE_NOTHROW(handler.HandleSyntax(&clause));
  }

  SECTION("Test invalid clause, syn_assign not synonym") {
    PatternClauseSyntax clause{{"1", {"_", "_\"x\"_"}}};

    REQUIRE_THROWS_AS(handler.HandleSyntax(&clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_1 not entRef") {
    PatternClauseSyntax clause{{"a", {"1", "_\"x\"_"}}};

    REQUIRE_THROWS_AS(handler.HandleSyntax(&clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2 invalid expr") {
    PatternClauseSyntax clause{{"a", {"_", "x"}}};

    REQUIRE_THROWS_AS(handler.HandleSyntax(&clause), SyntaxErrorException);
  }
}

TEST_CASE("Test PatternHandler HandleSemantic") {
  PatternHandler handler;

  SECTION("Test valid clause semantic") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    PatternClauseSyntax clause{{"a", {"v", "_\"x\"_"}}};

    REQUIRE_NOTHROW(handler.HandleSemantic(&clause, declaration));
  }

  SECTION("Test valid clause semantic but invalid syntax") {
    Map declaration{{"1", "assign"},
                    {"v", "variable"}};

    PatternClauseSyntax clause{{"1", {"v", "_\"x\"_"}}};

    REQUIRE_NOTHROW(handler.HandleSemantic(&clause, declaration));
  }

  SECTION("Test invalid clause semantic, invalid syn_assign not 'assign' synonym") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    PatternClauseSyntax clause{{"v", {"_", "_\"x\"_"}}};

    REQUIRE_THROWS_AS(handler.HandleSemantic(&clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, syn_assign not declared") {
    Map declaration{{"a", "assign"}};

    PatternClauseSyntax clause{{"v", {"_", "_\"x\"_"}}};

    REQUIRE_THROWS_AS(handler.HandleSemantic(&clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, arg_1 not 'variable' entity") {
    Map declaration{{"a", "assign"},
                    {"v", "stmt"}};

    PatternClauseSyntax clause{{"a", {"v", "_\"x\"_"}}};

    REQUIRE_THROWS_AS(handler.HandleSemantic(&clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_1 synonym not declared") {
    Map declaration{{"a", "assign"}};

    PatternClauseSyntax clause{{"a", {"v", "_\"x\"_"}}};

    REQUIRE_THROWS_AS(handler.HandleSemantic(&clause, declaration), SemanticErrorException);
  }
}
