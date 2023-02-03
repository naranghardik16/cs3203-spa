#include "catch.hpp"

#include "QPS/ValidationHandler/StmtToStmtHandler.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test StmtToStmtHandler handlerSyntax") {
  StmtToStmtHandler handler;

  SECTION("Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Follows", {"a", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test invalid clause syntax - invalid rel") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Followed", {"a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause syntax - arg_1 not stmt ref") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Follows", {"\"a\"", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause syntax - arg_2 not stmt ref") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Parent", {"a", "\"p\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }
}

TEST_CASE("Test StmtToStmtHandler handlerSemantic") {
  StmtToStmtHandler handler;

  SECTION("Test valid clause semantic - ref(stmt, stmt)") {
    Map declaration{{"a", "stmt"},
                    {"p", "stmt"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Follows", {"a", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test invalid clause semantic - invalid rel") {
    Map declaration{{"a", "stmt"},
                    {"p", "stmt"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Uses", {"a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test valid clause semantic - ref(assign, assign)") {
    Map declaration{{"a", "assign"},
                    {"p", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Follows", {"a", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test invalid clause - arg_1 not stmt entity") {
    Map declaration{{"a", "variable"},
                    {"p", "stmt"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Follows", {"a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause - arg_2 not stmt entity") {
    Map declaration{{"a", "read"},
                    {"p", "variable"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Follows", {"a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }
}
