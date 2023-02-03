#include "catch.hpp"

#include "QPS/ValidationHandler/StmtProcToVarHandler.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test StmtProcToVarHandler HandleSyntax") {
  StmtProcToVarHandler handler;

  SECTION("Test valid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Uses", {"a", "v"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax, both is underscore") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Uses", {"_", "_"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test invalid clause syntax, arg_1 is not stmtRef/entRef") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Modifies", {"1a", "v"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause syntax, arg_2 is not entRef") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Modifies", {"a", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }
}

TEST_CASE("Test StmtProcToVarHandler HandleSemantic") {
  StmtProcToVarHandler handler;

  SECTION("Test clause semantic") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Modifies", {"a", "v"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test invalid clause semantic, arg_1 is underscore") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Uses", {"_", "_"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_1 is not invalid design entity") {
    Map declaration{{"a", "constant"},
                    {"v", "variable"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Modifies", {"a", "v"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_2 is not invalid design entity") {
    Map declaration{{"a", "constant"},
                    {"v", "stmt"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Modifies", {"a", "v"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }
}
