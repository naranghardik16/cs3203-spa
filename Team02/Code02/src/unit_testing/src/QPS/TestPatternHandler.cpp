#include "catch.hpp"

#include "QPS/ValidationHandler/PatternHandler.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

const std::string kEntityKey = "Entity";
const std::string kAssignEntity = "assign";
const std::string kVariableEntity = "variable";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

TEST_CASE("Test PatternHandler") {
  PatternHandler handler;

  SECTION("Test valid clause") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "a"},
               {kFirstParameterKey, "v"},
               {kSecondParameterKey, "_\"v\"_"}};

    REQUIRE_NOTHROW(handler.Handle(declaration, clause));
  }

  SECTION("Test valid clause, underscore") {
    Map declaration{{"a", "assign"}};

    Map clause{{kEntityKey, "a"},
               {kFirstParameterKey, "_"},
               {kSecondParameterKey, "_"}};

    REQUIRE_NOTHROW(handler.Handle(declaration, clause));
  }


  SECTION("Test empty clause") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{};

    REQUIRE_NOTHROW(handler.Handle(declaration, clause));
  }

  SECTION("Test invalid clause, invalid syn_assign not 'assign' synonym") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "v"},
               {kFirstParameterKey, "_"},
               {kSecondParameterKey, "_"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SemanticErrorException);
  }

  SECTION("Test invalid clause, syn_assign not declared") {
    Map declaration{{"a", "assign"}};

    Map clause{{kEntityKey, "v"},
               {kFirstParameterKey, "_"},
               {kSecondParameterKey, "_"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SemanticErrorException);
  }

  SECTION("Test invalid clause, syn_assign not synonym") {
    Map declaration{{"a", "assign"}};

    Map clause{{kEntityKey, "1"},
               {kFirstParameterKey, "_"},
               {kSecondParameterKey, "_"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_1 not entRef") {
    Map declaration{{"a", "assign"}};

    Map clause{{kEntityKey, "a"},
               {kFirstParameterKey, "1"},
               {kSecondParameterKey, "_"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_1 not 'variable' entity") {
    Map declaration{{"a", "assign"},
                    {"v", "stmt"}};

    Map clause{{kEntityKey, "a"},
               {kFirstParameterKey, "v"},
               {kSecondParameterKey, "_"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_1 synonym not declared") {
    Map declaration{{"a", "assign"}};

    Map clause{{kEntityKey, "a"},
               {kFirstParameterKey, "v"},
               {kSecondParameterKey, "_"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_2 invalid expr") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "a"},
               {kFirstParameterKey, "v"},
               {kSecondParameterKey, "_xx"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SyntaxErrorException);
  }
}
