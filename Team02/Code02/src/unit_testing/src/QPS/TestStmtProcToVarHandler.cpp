#include "catch.hpp"

#include "QPS/ValidationHandler/StmtProcToVarHandler.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test StmtProcToVarHandler HandleSyntax") {
  StmtProcToVarHandler handler;

  SECTION("Test valid clause syntax") {
    SuchThatClauseSyntax clause{{"Uses", {"a", "v"}}};

    REQUIRE_NOTHROW(handler.HandleSyntax(&clause));
  }

  SECTION("Test valid clause syntax, both is underscore") {
    SuchThatClauseSyntax clause{{"Uses", {"_", "_"}}};

    REQUIRE_NOTHROW(handler.HandleSyntax(&clause));
  }

  SECTION("Test invalid clause syntax, arg_1 is not stmtRef/entRef") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    SuchThatClauseSyntax clause{{"Modifies", {"1a", "v"}}};

    REQUIRE_THROWS_AS(handler.HandleSyntax(&clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause syntax, arg_2 is not entRef") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    SuchThatClauseSyntax clause{{"Modifies", {"a", "1"}}};

    REQUIRE_THROWS_AS(handler.HandleSyntax(&clause), SyntaxErrorException);
  }
}

TEST_CASE("Test StmtProcToVarHandler HandleSemantic") {
  StmtProcToVarHandler handler;

  SECTION("Test invalid clause semantic, arg_1 is underscore") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    SuchThatClauseSyntax clause{{"Modifies", {"a", "v"}}};

    REQUIRE_NOTHROW(handler.HandleSemantic(&clause, declaration));
  }

  SECTION("Test invalid clause semantic, arg_1 is underscore") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    SuchThatClauseSyntax clause{{"Uses", {"_", "_"}}};

    REQUIRE_THROWS_AS(handler.HandleSemantic(&clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_1 is not invalid design entity") {
    Map declaration{{"a", "constant"},
                    {"v", "variable"}};

    SuchThatClauseSyntax clause{{"Modifies", {"a", "v"}}};

    REQUIRE_THROWS_AS(handler.HandleSemantic(&clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_2 is not invalid design entity") {
    Map declaration{{"a", "constant"},
                    {"v", "stmt"}};

    SuchThatClauseSyntax clause{{"Modifies", {"a", "v"}}};

    REQUIRE_THROWS_AS(handler.HandleSemantic(&clause, declaration), SemanticErrorException);
  }
}
