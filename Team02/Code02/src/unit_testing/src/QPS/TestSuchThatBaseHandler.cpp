#include "catch.hpp"

#include "QPS/ValidationHandler/SuchThatBaseHandler.h"
#include "QPS/PqlException/SemanticErrorException.h"
#include "QPS/PqlException/SyntaxErrorException.h"

typedef std::unordered_map<std::string, std::string> Map;

const std::string kEntityKey = "Entity";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

//Check if design entities and corresponding synonyms can be extracted from declarations
TEST_CASE("Check if SuchThatBaseHandler works as expected") {
  SuchThatBaseHandler handler_1;

  SECTION("Test valid clause") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Uses"},
        {kFirstParameterKey, "a"},
        {kSecondParameterKey, "v"}};

    REQUIRE_NOTHROW(handler_1.Handle(declaration, clause));
  }

  SECTION("Test valid clause, underscore") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "_"},
               {kSecondParameterKey, "_"}};

    REQUIRE_NOTHROW(handler_1.Handle(declaration, clause));
  }

  SECTION("Test pass invalid clause for Follow relation with entRef as argument as base handler does not validate it") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Follows"},
               {kFirstParameterKey, "_"},
               {kSecondParameterKey, "\"x\""}};

    REQUIRE_NOTHROW(handler_1.Handle(declaration, clause));
  }

  SECTION("Test empty clause") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{};

    REQUIRE_NOTHROW(handler_1.Handle(declaration, clause));
  }

  SECTION("Test invalid clause, invalid relRef") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Usesss"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "v"}};

    REQUIRE_THROWS_AS(handler_1.Handle(declaration, clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, synonym not declared") {
    Map declaration{{"a", "assign"}};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "v"}};

    REQUIRE_THROWS_AS(handler_1.Handle(declaration, clause), SemanticErrorException);
  }

  SECTION("Test invalid clause, synonym not declared - empty declaration map") {
    Map declaration{};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "v"}};

    REQUIRE_THROWS_AS(handler_1.Handle(declaration, clause), SemanticErrorException);
  }
}