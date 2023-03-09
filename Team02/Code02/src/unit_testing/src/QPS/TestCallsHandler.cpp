#include "catch.hpp"

#include "QPS/ValidationHandler/CallsHandler.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test CallsHandler handlerSyntax") {
  CallsHandler handler;

  SECTION("1 - Test valid clause ") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls", {"a", "p1"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("2 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls*", {"a1", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("3 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls", {"\"a\"", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("4 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls*", {"a", "\"p\""}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("5 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls", {"_", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("6 - Test valid clause") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls*", {"a", "_"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("1 - Test invalid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls", {"1", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("2 - Test invalid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls*", {"a", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("3 - Test invalid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls", {"a", "1p"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("4 - Test invalid clause syntax") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls*", {"1a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }
}

TEST_CASE("Test CallsHandler handlerSemantic") {
  CallsHandler handler;

  SECTION("1- Test valid clause semantic") {
    Map declaration{{"a", "procedure"},
                    {"p", "procedure"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls", {"a", "p"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("2- Test valid clause semantic") {
    Map declaration{{"a", "procedure"},
                    {"p", "procedure"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls*", {"a", "\"p\""}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("1- Test invalid clause semantic") {
    Map declaration{{"a", "stmt"},
                    {"p", "procedure"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls*", {"a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("2- Test invalid clause semantic") {
    Map declaration{{"a", "procedure"},
                    {"p", "call"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Calls", {"a", "p"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

}
