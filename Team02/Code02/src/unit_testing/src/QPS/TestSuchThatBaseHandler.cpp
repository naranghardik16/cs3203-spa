#include "catch.hpp"

#include "QPS/ValidationHandler/SuchThatBaseHandler.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test SuchThatBaseHandler HandleSyntax") {
  SuchThatBaseHandler handler;

  SECTION("Test valid clause syntax - throw exception from default handler") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Uses", {"a", "v"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }


  SECTION("Test valid clause syntax with underscores - throw exception from default handler") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Uses", {"_", "_"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause syntax, invalid relRef") {
    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Usesss", {"_", "_"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }
}

TEST_CASE("Test SuchThatBaseHandler HandleSemantic - throw exception from default handler") {
  SuchThatBaseHandler handler;

  SECTION("Test valid clause semantic") {
    Map declaration{{"a", "assign"},
                    {"v" , "variable"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Uses", {"a", "v"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, synonym not declared") {
    Map declaration{{"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Uses", {"a", "v"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, empty declaration map") {
    Map declaration{};

    std::shared_ptr<ClauseSyntax> clause(new SuchThatClauseSyntax{{"Uses", {"a", "v"}}});


    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }
}
