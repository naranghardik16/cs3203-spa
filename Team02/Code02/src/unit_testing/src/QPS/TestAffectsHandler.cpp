#include "catch.hpp"

#include "QPS/ValidationHandler/AffectsHandler.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test AffectsHandler handlerSyntax") {
  AffectsHandler handler;

  SECTION("1 - Test valid clause ") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects", {"a", "p1"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("2 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects*", {"a1", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("3 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects", {"1", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("4 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects*", {"a", "1"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("5 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects", {"_", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("6 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects*", {"a", "_"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("1 - Test invalid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects", {"1", "\"p\""}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("2 - Test invalid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects*", {"\"a\"", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("3 - Test invalid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects", {"a", "1p"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("4 - Test invalid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects*", {"1a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }
}

TEST_CASE("Test AffectsHandler handlerSemantic") {
  AffectsHandler handler;

  SECTION("1- Test valid clause semantic") {
    Map declaration{{"a", "assign"},
                    {"p", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects", {"a", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("2- Test valid clause semantic") {
    Map declaration{{"a", "assign"},
                    {"p", "procedure"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects*", {"a", "\"p\""}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("1- Test invalid clause semantic") {
    Map declaration{{"a", "stmt"},
                    {"p", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects*", {"a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("2- Test invalid clause semantic") {
    Map declaration{{"a", "assign"},
                    {"p", "call"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Affects", {"a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

}
